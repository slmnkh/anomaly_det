anomaly_det
===========

// readme for the entire project :

to run any of the codes include the files mentioned below.

step 1: get_SCCc.cpp -- 
input : user_edges.txt
output : components.txt
this function is to read the user_edges.txt file and get SCCs. This is done by main_boost.cpp (renamed to get_SCCs.cpp) .. the file saved by this is compopnents.txt

step 2: sort_user_edges.txt -- 
input : user_edges.txt
output : ordered_user_edges.txt
sort the transaction data (sort_user_edges.cpp) which will save the file salman_user_edges.txt

step 3: save_each_users_transactions.cpp
input : ordered_user_edges.txt
output : all_users_transactions.txt, stats.txt
save_each_users_transactions.cpp -- user ordered_user_edges.txt, read each line and accumulate each users transactions. save them in user_transactions.txt . this is done by save_each_users_transactions.cpp

step 4: identify_anomalous_users.cpp -- 
input : components.txt, all_users_transactions.txt
output : anomalous_users.txt, component_size_dist.txt
loop over components and save the ids of nodes in anomalous SCCs.

step 5: save_anomalous_transaction_histories.cpp 
input : all_users_transactions.txt, anomalous_users.txt
output : anomalous_users_transactions.txt
collect transaction data of anomalous users and save in text file anomalous_users_transactions.txt


---- convert_an_tr_file_to_svr_format.cpp
input : anomalous_user_transactions.txt
output : anomalous_users_svr_training.txt, anomalous_users_svr_testing.txt
read in the input and save the files to be used for svr training and testing in the right format

---- get_negative_testing_file.cpp
input : all_users_transactions.txt, anomalous_users.txt
output : negative_users_svr_testing.txt
read in the input text files and prepare file for svr testing.

---- read_svr_output_compute_results.cpp
input : read in the files output by svr testing and compute single anomaly numbers,
decide which are anomalous.



