/*
 * sort_user_edges.cpp
 *
 *  Created on: Oct 7, 2014
 *      Author: root
 */


#include "generate_user_transaction_records.h"

using namespace std;

void sort_user_edges() {

	vector<pair<unsigned long, string> > timestamps;
	ifstream in_file;
	string line;
	in_file.open("user_edges.txt");
	unsigned long outer_counter = 0;
	while(getline(in_file, line)){
		outer_counter++;
		if(outer_counter % 1000 == 0)
			cout << outer_counter << endl;
//		if(outer_counter % 1000000 != 0)
//			continue;
		stringstream ss(line);
		string word;
		unsigned long values[5];
		int count = 0;
		while(getline(ss, word, ',')){
			values[count++] = atof(word.c_str());
		}
		timestamps.push_back(make_pair(values[3], line));
	}
	in_file.close();
//	ofstream test_file;
//		test_file.open("test_user_edges.txt");
//		outer_counter = 0;
//		for(vector<pair<unsigned long, string> >::iterator it = timestamps.begin(); it != timestamps.end(); it++){
//			test_file << it->second << endl;
//			if(outer_counter++ % 1000 == 0)
//					cout << outer_counter << endl;
//		}
//	test_file.close();
	sort(timestamps.begin(),timestamps.end());
	ofstream out_file;
	out_file.open("ordered_user_edges.txt");
	outer_counter = 0;
	for(vector<pair<unsigned long, string> >::iterator it = timestamps.begin(); it != timestamps.end(); it++){
		out_file << it->second << endl;
		if(outer_counter++ % 1000 == 0)
				cout << outer_counter << endl;
	}
	out_file.close();
	cout << "Done." << endl;

}
