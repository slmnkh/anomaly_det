///*
// * save_anomalous_transaction_histories.cpp
// *
// *  Created on: Oct 6, 2014
// *      Author: root
// */

#include "generate_user_transaction_records.h"

using namespace std;

void save_anomalous_transaction_histories(){

  ifstream anomalous_users_stream; // read all anomalous nodes into a list "anomalous_users_list"
  list<unsigned long> anomalous_users_list;
  anomalous_users_stream.open("anomalous_users.txt");
  string line;
  while(anomalous_users_stream.good()){
    getline(anomalous_users_stream, line);
    anomalous_users_list.push_back(atol(line.c_str()));
//		anomalous_users_list.push_back(stoi(line));
  }
  anomalous_users_stream.close();
  ifstream all_user_transactions; // go through this file and save the lines that belong to anomalous users
  all_user_transactions.open("all_users_transactions.txt");

  map<unsigned long, string> anomalous_lines;

  unsigned long outer_counter = 0;

  while(getline(all_user_transactions, line)){
      
      int loc_marker = line.find_first_of(":");
      string word = line.substr(0,loc_marker-1);
      unsigned long user_id = atol(word.c_str());
      list<unsigned long>::iterator i;
      i = find(anomalous_users_list.begin(), anomalous_users_list.end(), user_id);
      if (i != anomalous_users_list.end()){ // if iterator is not at the end this means the value was found in list
    	  anomalous_lines[user_id] = line;
      }
      outer_counter++;
      if(outer_counter % 1000 == 0){
    	  cout << "Checked lines : " << outer_counter << endl;
    	  cout << word;
      }
    }  
   
    ofstream out_file;
    out_file.open("anomalous_users_transactions.txt");
    //    map<unsigned long, string>::iterator map_it;
    for(map<unsigned long, string>::iterator map_it = anomalous_lines.begin(); map_it != anomalous_lines.end(); map_it++){
      out_file << map_it->second << endl;
    }
    out_file.close();
}
