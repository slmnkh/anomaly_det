////=======================================================================
//// Edited: 2014 October by Salman Khokhar
////
//// - The file reads bitcoin transaction data (user_edges.txt) to construct a graph
//// - Format of user_edges.txt:
//// 		Each line has 5 columns. In order : transaction id (unique), sender id, receiver id, amount in BTC, date and time
//// 		The sender and receiver ids are not public hashes but unique user ids computed from the bitcoin tools provided with the data
//// 		Note that the tools are not obsolete since they work on an older database version of bitcoin, so this data cannot be regenerated from the bitcoin blockchain
//// - Graph is used to compute groups of nodes in strongly connected components
//// - The purpose of identifying these nodes is to identify nodes involved in money laundering
//// - The file saves the results in a file "componets.txt" each line of components.txt contains two numbers
//// 		The first number is the node index, the second number is the index of the component that it belongs to
////
////=======================================================================

////=======================================================================
//// Original file: Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee,
////
//// Distributed under the Boost Software License, Version 1.0. (See
//// accompanying file LICENSE_1_0.txt or copy at
//// http://www.boost.org/LICENSE_1_0.txt)
////=======================================================================
//
//
//
//
//

#include "generate_user_transaction_records.h"

using namespace std;
using namespace boost;

void get_SCCs()
{

  typedef adjacency_list < vecS, vecS, directedS > Graph; // we use an adjacency list representation for a graph
  const unsigned long N = 6336769;
  unsigned long danger_counter = 0;
  Graph G(N);

  std::ifstream myReadFile;
  myReadFile.open("ordered_user_edges.txt"); // side note: it does not matter here whether we read in "user_edges.txt" or "ordered_user_edges.txt
  unsigned long counter = 0;
  unsigned long outer_count = 0;
  string line;
  if (myReadFile.is_open()) {
  while (std::getline(myReadFile, line)) {
    std::stringstream ssline ( line );
    unsigned long values[3];
    counter = 0;
    string word;
    //    std::cout << line << std::endl;
    while (getline(ssline, word, ',')){

      //    	cout << "Current line : " << line << endl;
      //    	cout << "Current word : " << word << endl;
      if (counter > 2) break;
      values[counter] = atoi(word.c_str());
      counter++;

    }

//      std::cout<< values[0] << ", " << values[1] << ", " << values[2] << std::endl;
    outer_count++;
    if (values[1] > N || values[2] > N)
      {
	cout << "Danger";
	danger_counter++;
      }
    if (values[1]==values[2] || (values[1] > N) || (values[2] > N)){
      //    	  std::cout << "same indices found here\n";
      continue;
    }
    add_edge(values[1], values[2], G);
//      std::cout << "*********** \n\n";
    if (outer_count % 100 == 0)
      cout << outer_count << "\n";
  }
  }
  cout << "Done with error checking.";
  cout << endl << "Danger counter : " << danger_counter << endl;
  myReadFile.close();
//  t = clock() - t;
//  std::cout << "It took time : " << t;
  vector<unsigned long> c(N);

  int num = strong_components(G, make_iterator_property_map(c.begin(), get(vertex_index, G), c[0]));

  cout << "Total number of components: " << num << endl;
  vector < unsigned long >::iterator i;
  ofstream savefile;
  savefile.open ("components.txt");
  for (i = c.begin(); i != c.end(); ++i){
    //std::cout << "Vertex " << i - c.begin()
    // << " is in component " << *i << std::endl;
    savefile << i - c.begin() << ", " << *i << "\n";
  }
  savefile.close();
  //cout << "It took graph conn comp time : " << t;
}
