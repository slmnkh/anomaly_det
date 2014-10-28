/*
 * convert_an_tr_file_to_svr_format.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: root
 */

#include "generate_user_transaction_records.h"
using namespace std;

void convert_an_tr_file_to_svr_format(){

	ifstream in_file;
	ofstream out_file_training;
	ofstream out_file_testing;
	in_file.open("anomalous_users_transactions.txt");
	out_file_training.open("anomalous_users_svr_training.txt");
	out_file_testing.open("anomalous_users_svr_testing.txt");

	unsigned long outer_counter = 0;
	string line;

	while(getline(in_file, line)){


		string sub_line;
		int pos = line.find_first_of(":");
		sub_line = line.substr(pos+2);
		int string_length;
		string_length = count(sub_line.begin(), sub_line.end(), ' ');
		if (string_length < 5)
			continue;
		outer_counter++;
//		replace(sub_line.begin(), sub_line.end(), ',' , ' ');
		sub_line.erase(remove(sub_line.begin(), sub_line.end(), ','), sub_line.end());
		if (outer_counter < 1000){
			out_file_training << sub_line << endl; // << endl;
		}else{
			out_file_testing << sub_line << endl;// << endl;
		}

	}

	in_file.close();
	out_file_training.close();
	out_file_testing.close();



}
