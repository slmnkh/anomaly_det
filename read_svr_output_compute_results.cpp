/*
 * read_svr_output_compute_results.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: root
 */

#include "generate_user_transaction_records.h"

using namespace std;


void read_svr_output_compute_results(){

	ifstream anomalous_results;
	ifstream negative_results;
	anomalous_results.open("anomalous_predictions.txt");
	negative_results.open("negative_predictions.txt");
	string line;
//	vector<pair<float, int> > results_map;
//	vector<pair<unsigned long, string> > timestamps;
	vector<pair<float, int> > results_map;
	int num_anomalous, num_negative;

	num_anomalous = 0;
	num_negative = 0;

	while(getline(anomalous_results, line)){

		list<float> values;
		string word;
//		cout << "Testing line : " << line << endl << endl ;
		stringstream liness(line);
		while(getline(liness, word, ' ')){
//			cout << "New word : " << word << endl;
			values.push_back(atof(word.c_str()));
		}
		float mean_error = 0;
		for(list<float>::iterator it = values.begin(); it != values.end(); it++){
			mean_error = mean_error + *it;
//			cout << *it << endl;
		}
//		cout << mean_error << endl;
		mean_error /= values.size();
//		cout << mean_error << endl;
		results_map.push_back(make_pair(mean_error, 1));
		num_anomalous++;

	}

	while(getline(negative_results, line)){

			list<float> values;
			string word;
			stringstream liness(line);
			while(getline(liness, word, ' ')){
				values.push_back(atof(word.c_str()));
			}
			float mean_error = 0;
			for(list<float>::iterator it = values.begin(); it != values.end(); it++){
				mean_error += *it;
//				cout << *it << endl;
			}
//			cout << mean_error << endl;
			mean_error /= values.size();
			results_map.push_back(make_pair(mean_error, 0));
			num_negative++;

	}

	ofstream pre_sort;
	pre_sort.open("pre_sort_results.txt");
	vector<pair<float, int> >::iterator res_it;
	for(res_it = results_map.begin(); res_it != results_map.end(); res_it++){

		pre_sort << res_it->first << " : " << res_it->second << endl;

	}

	sort(results_map.begin(),results_map.end());//, greater<float>());


	ofstream post_sort;
	post_sort.open("post_sort_results.txt");
	for(res_it = results_map.begin(); res_it != results_map.end(); res_it++){

		post_sort << res_it->first << " : " << res_it->second << endl;

	}

	cout << "Length of results = " << results_map.size() << endl;

	int true_positives = 0;
	//for (int i = num_negative+1; i < num_anomalous+num_negative; i++){
	  for(int i = 0; i < num_anomalous; i++){
		if (results_map[i].second == 1){
			true_positives++;
			cout << "here.. : " << true_positives << endl;
		}

	}
	cout << endl;
	cout << "Accuracy : " << (float)true_positives/(float)num_anomalous*100 << endl;


//	ofstream print_results;

}
