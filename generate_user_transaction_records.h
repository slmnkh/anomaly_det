/*
 * generate_user_transaction_records.h
 *
 *  Created on: Oct 6, 2014
 *      Author: root
 */
#include <string>
#include <iostream>
#include <boost/config.hpp>
#include <vector>
#include <iostream>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <list>
#include <map>
#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

#ifndef GENERATE_USER_TRANSACTION_RECORDS_H_
#define GENERATE_USER_TRANSACTION_RECORDS_H_

void get_SCCs();
void sort_user_edges();
void save_each_users_transactions();
void identify_anomalous_users();
void save_anomalous_transaction_histories();
void convert_an_tr_file_to_svr_format();
void get_negative_testing_file();
void read_svr_output_compute_results();
float sum_up_positive(string);
float get_user_out_transactions(list<string>, unsigned long);
float get_SCC_transaction_total(list<string>, list<unsigned long>);

void get_negative_model_training_file();

#endif /* GENERATE_USER_TRANSACTION_RECORDS_H_ */
