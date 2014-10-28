//***********************************************************************************************
//// Code written by Salman Khokhar, October 04, 2014 for a project proposal for UCF/ORNL
//
////Steps in code:
//
//// - Read the file : components.txt (Each line contains user id and component id to which user belongs, this file is written by main_boost.cpp)
//// - Loop over each line in components.txt, add the user id to a list containing all users in the corresponding component id.
//
//// For debugging purposes, get the following maps ::
//// conn_com_nodes : keys = connected component indices, vals = all users in compopnent
//// histMap 		  : keys = sizes of connected components, vals = indices of connected components with this size
//// histVals       : keys = sizes of connected components, vals = count of number of connected components with this size
//
//// - For sanity check, output each pair in map histVals into component_size_dist.txt, there should be a good distribution of groups of small sizes (larger than 1)
//
//// - Loop over all components in map conn_com_nodes, if they are smaller than 10, add the user indices in them to a list
//// - output the list to a text file
//
////***********************************************************************************************
//
#include "generate_user_transaction_records.h"

using namespace boost;
using namespace std;

float sum_up_positive(string line){

	string sub_line, word;
	int pos = line.find_first_of(":");
	sub_line = line.substr(pos+2);
	float pos_trans_sum = 0.0;
	stringstream liness(sub_line);
	while(getline(liness, word, ',')){
		float temp = atof(word.c_str());
		if (atof(word.c_str()) > 0)
			pos_trans_sum += temp;
	}

	return pos_trans_sum;
}

float get_user_out_transactions(list<string> user_transaction_series, unsigned long user){
  list<string>::iterator us_it;
  int found = 0;
  for(us_it = user_transaction_series.begin(); us_it != user_transaction_series.end(); us_it++){
    string word;
    string line = *us_it;
    stringstream liness(line);
    getline(liness, word, ':');
//    cout << line;
    if(user == atol(word.c_str())){
    	found = 1;
    	break;
    }
  }
  if(found == 1){
	  float out_transactions = sum_up_positive(*us_it);
	  return out_transactions;
  }
  return 0;
}

float get_SCC_transaction_total(list<string> user_transaction_series, list<unsigned long> curr_SCC){ // for a given list of nodes in one SCC, sum up all their transactions.

  list<unsigned long>::iterator node_in_SCC; // iterator over list of nodes in SCC
  float total_transactions = 0.0;
  for(node_in_SCC = curr_SCC.begin(); node_in_SCC != curr_SCC.end(); node_in_SCC++){
    // search for user in the list of all transaction series
    total_transactions += get_user_out_transactions(user_transaction_series, *node_in_SCC);
  }
  return total_transactions;
}


void identify_anomalous_users()
{
//	int maxcomponent_index = 0; // this variable is only used for debugging purposes. may discard
	const unsigned long N = 6336769;
	map < unsigned long, list<unsigned long> > conn_com_nodes; // mapping between SCC numbers and nodes that the SCC contains. the list only stores node ids which are real numbers, so datatype float is not needed.
	ifstream myReadFile;

////	loop over the lines of the file components.txt and add each nodes index in its component index in array of lists (conn_com_nodes)
//	myReadFile.open(args[1]);
	myReadFile.open("components.txt");
	unsigned long counter;
	cout << "Starting file reading" << endl;
	string line;
	if (myReadFile.is_open()) {
	  while (getline(myReadFile, line)) { // each line is two numbers. node id and SCC id
	    stringstream ssline ( line );
	    string word;
	    unsigned long values[2]; // 2 numbers per line
	    int counter = 0;
	    while (getline(ssline, word, ','))
	      {
		values[counter] = (unsigned)atol(word.c_str());
		counter++;
	      }
	    //			maxcomponent_index = max(maxcomponent_index, values[1]);
	    conn_com_nodes[values[1]].push_back(values[0]); // this stores all users in the SCC number "values[1]" at the index "values[1]" of the map
	  }
	}
	myReadFile.close();
	map<unsigned long, list<unsigned long> > histMap; // for each map key (size of SCC), the val list conatins the SCC ids that are of that size
	map<unsigned long, unsigned long> histVals; // for for each map key (size of SCC), the val is the number of SCCs that are of that size
	for (map <unsigned long, list<unsigned long> >::iterator it = conn_com_nodes.begin(); it != conn_com_nodes.end(); it++){
	  //	  cout << "Size of " << it->first << "-th list : " << it->second.size() << endl;
	  histMap[it->second.size()].push_back(it->first); //  for key value = current_SCC.size, add the SCC id to val
	}
	for (map <unsigned long, list<unsigned long> >::iterator it = histMap.begin(); it != histMap.end(); it++){
	  histVals[it->first] = it->second.size(); // for key value = current_SCC.size, set the number of SCCs in the associated list as val
	}

	// ****** write out histogram to file
	ofstream component_dist_file;
	component_dist_file.open("component_size_dist.txt");
	for (map<unsigned long, unsigned long>::iterator it = histVals.begin(); it != histVals.end(); it++){
		component_dist_file << it->first << ", " << it->second << endl;
	}
	component_dist_file.close();
	// **********************************

	ifstream all_users_file;
	all_users_file.open("all_users_transactions.txt");
	list<string> all_users_data;
	string user_line;
	while(getline(all_users_file, user_line)){
	  all_users_data.push_back(user_line);
	}

	// ****** check each SCC, if it passes, check, add its nodes to text file containing anomalous node ids
	ofstream anomalous_users;
	ofstream anomalous_SCCs;
	list<unsigned long> anomalous_user_list;
	anomalous_users.open("anomalous_users.txt");
	anomalous_SCCs.open("anomalous_SCCs.txt");
	int scc_counter = 0;
	for (map<unsigned long, list<unsigned long> >::iterator it = conn_com_nodes.begin(); it != conn_com_nodes.end(); it++){
	  //	  float transaction_amount = get_SCC_transaction_total(all_users_data, it->second);
	  if (it->second.size() <= 10 && it->second.size() > 1){
	    // if (transaction_amount > 0.2){
			  for(list<unsigned long>::iterator user_it = it->second.begin(); user_it != it->second.end(); user_it++){
				  anomalous_user_list.push_back(*user_it);
				  anomalous_SCCs << *user_it << " ";
			  }
			  anomalous_SCCs << endl;
			  // }
	  }
	  scc_counter++;
	  cout << "Done with SCC : " << scc_counter << " out of : " << conn_com_nodes.size() << "\n";
	}
	anomalous_SCCs.close();
	anomalous_user_list.sort();
	anomalous_user_list.unique();
	for(list<unsigned long>::iterator user_it = anomalous_user_list.begin(); user_it != anomalous_user_list.end(); user_it++){
	  anomalous_users << *user_it << endl;
	}
	anomalous_users.close();

	//	save_anomalous_transaction_histories(); // making a separate .cpp for this. to be called from main.


}







//
//	  void plotHistogram(){
//
//	IplImage* imgHistogram = cvCreateImage(cvSize(256, 50), 8, 1);
//	cvRectangle(imgHistogram, cvPoint(0,0),cvPoint(256,50),CV_RGB(255,255,255),-1);
//	int max_value = *(max_element(hist.begin(), hist.end()));
//	for (int i = 0; i < 256; ++i) {
//	int val = hist[i];
//	int nor = cvRound(val * 50 / max_value);
//	cvLine(imgHistogram, cvPoint(i, 50), cvPoint(i, 50-nor), CV_RGB(0,0,0));
//	}
//	cvShowImage("hist", imgHistogram);
//	cvReleaseImage(&imgHistogram);
//
//}
