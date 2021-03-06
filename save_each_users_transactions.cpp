/*
 * save_each_users_transactions.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: root
 */

#include "generate_user_transaction_records.h"

using namespace std;

void save_each_users_transactions(){

	ifstream all_transactions_stream;
	all_transactions_stream.open("ordered_user_edges.txt");
	string line;
	unsigned long outer_counter = 0;
	map<unsigned long, list<float> > user_transactions;
	while(getline(all_transactions_stream, line)){
	  //		if(outer_counter > 1000)
	  //		break;
		outer_counter++;
		string word;
		stringstream liness(line);
		unsigned long counter = 0;
		float values[5];
		while(getline(liness, word, ',')){
			values[counter] = atof(word.c_str());
			counter++;
//			cout << word << ", ";
		}
		
		if(outer_counter % 1000 == 0){
		  cout << "transactions read : " << outer_counter << endl;
		}
		user_transactions[(unsigned long)values[1]].push_back(values[4]);
		user_transactions[(unsigned long)values[2]].push_back(-values[4]);
	}
	outer_counter = 0;
	ofstream output_file;
	output_file.open("all_users_transactions.txt");
	for (map <unsigned long, list<float> >::iterator it = user_transactions.begin(); it != user_transactions.end(); it++){
	  //ofstream single_file;
	  //ostringstream ss;
	  //ss << "user_" << it->first << "transactions";
	  //string file_name = ss.str();
	  //single_file.open(file_name.c_str());
	  output_file << it->first << " : ";
	  for(list<float>::iterator listit = it->second.begin(); listit != it->second.end(); listit++){
	    if(listit == it->second.end()){
	      output_file << *listit;
	      // single_file << *listit;
	    }
	    else{
	      output_file << *listit << ", ";
	      //  single_file << *listit << ", ";
	    }
	  }
	  output_file << endl;
	  //	  single_file.close();
	  // if(outer_counter == 100)
	  //break;
	  if(outer_counter % 1000 == 0){
	    cout << "Done with writing user " << it->first << " to file." << endl;
	  }
	  outer_counter++;
	}
	output_file.close();

	ofstream stats_stream;
	unsigned long total_trans = 0;
	list<unsigned long> user_data_stats;

	stats_stream.open("stats.txt");
	outer_counter = 0;
	for(map <unsigned long, list<float> >::iterator it = user_transactions.begin(); it != user_transactions.end(); it++){
	  stats_stream << it->first << " : " << it->second.size() << endl;
	  total_trans = total_trans + it->second.size();
	  if(outer_counter % 1000 == 0){
	    cout << "added transactions for this number of users : " << outer_counter << endl;
	  }
	  outer_counter++;
	}
	stats_stream.close();
	
	cout << "Total number of transactions : " << total_trans << endl;


}
