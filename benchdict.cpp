/**
 *  Name: Niral Patel and Taylor Lew
 *  Date: October 20, 2016
 *  Overview: Tests the start and the end running times for each dictionary
 *						class.
 *  Assignement #:2 
 */

#include "util.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include <stdlib.h>
using namespace std;

/* Param: argc (the number of arguments)
 *				argv (arguments being passed in)
 * Return: int (how the program exited, 0 = success, -1 fail)
 * Tests the running times for each dictionary
 */
int main( int argc, char* argv[] ) {

	char * check;
	long min_size = strtol(argv[1], &check, 10);
	long step_size = strtol(argv[2], &check, 10);
	long num_iterations = strtol(argv[3], &check, 10);


	/*			Benchmarking DictionaryTrie			*/
	cout << endl << "DictionaryTrie " << endl;

	std::ifstream ifs;
	ifs.open(argv[4], std::ios::binary);

	int sizeOfFile = 0;

	DictionaryTrie* dt1 = new DictionaryTrie();
	//Timer
	Timer timer;

	//find the number of lines in the file
//	sizeOfFile = std::count(std::istreambuf_iterator<char>(ifs), 
//             std::istreambuf_iterator<char>(), '\n');

	sizeOfFile = 4315669;
	//go through num_iterations times
	for ( int i = 0; i < num_iterations; i++ ) {
		ifs.seekg( 0, ifs.beg );	
		//check how many words are left (min + i*step_size)
		//if there are fewer words in file
		if( ( (min_size + i*step_size) ) > sizeOfFile ) {
			cout << "Warning number of words in file is less than the number of" 
					 << "words that will be loaded." << endl;
		}
	
		//load from dictionary
		Utils::load_dict(*dt1,ifs, min_size + i*step_size );

		//sum of time
		float sum = 0.0;
		//num of nanoseconds find takes
		long long findTime;
		//num of find iterations
		int findNum = 100;
		//load array
		std::vector<std::string> dictArray;
		Utils::load_dict(dictArray, ifs, 100);

		for( int numFinds = 0; numFinds < findNum; numFinds++ ) { 

			timer.begin_timer();
			//read the next 100 words from the dictionary file
			for( int i = 0; i < 100; i++ ) {
				dt1->find(dictArray.at(i));
			}
			findTime = timer.end_timer();
			sum = sum + findTime;
		}
		
		//print out average
		cout << (min_size + (i*step_size)) << '\t'<< (sum/findNum) << endl;
	}
	delete dt1;	

	/*			Benchmarking DictionaryBST			*/
	cout << endl << "DictionaryBST " << endl;
		DictionaryBST* dbst1 = new DictionaryBST();


	//go through num_iterations times
	for ( int i = 0; i < num_iterations; i++ ) {
		ifs.seekg( 0, ifs.beg );	
		//check how many words are left (min + i*step_size)
		//if there are fewer words in file
		if( ( (min_size + i*step_size) ) > sizeOfFile ) {
			cout << "Warning number of words in file is less than the number of" 
					 << "words that will be loaded." << endl;
		}

		//load from dictionary
		Utils::load_dict(*dbst1,ifs, min_size + i*step_size );

		//sum of time
		float sum = 0.0;
		//num of nanoseconds find takes
		long long findTime;
		//num of find iterations
		int findNum = 100;
		//load array
		std::vector<std::string> dictArray;
		Utils::load_dict(dictArray, ifs, 100);

		for( int numFinds = 0; numFinds < findNum; numFinds++ ) { 

			timer.begin_timer();
			//read the next 100 words from the dictionary file
			for( int i = 0; i < 100; i++ ) {
				//cout << dictArray.at(i) << endl;
				dbst1->find(dictArray.at(i));
			}
		findTime = timer.end_timer();
		sum = sum + findTime;
		}
		
		//print out average
		cout << (min_size + (i*step_size)) << '\t'<< (sum/findNum) << endl;
	}
	delete dbst1;

	/*			Benchmarking DictionaryHashtable			*/
	cout << endl << "DictionaryHashtable " << endl;
	
		DictionaryHashtable* dht1 = new DictionaryHashtable();

	//go through num_iterations times
	for ( int i = 0; i < num_iterations; i++ ) {
		ifs.seekg( 0, ifs.beg );	
		//check how many words are left (min + i*step_size)
		//if there are fewer words in file
		if( ( (min_size + i*step_size) ) > sizeOfFile ) {
			cout << "Warning number of words in file is less than the number of" 
					 << "words that will be loaded." << endl;
		}

		//load from dictionary
		Utils::load_dict(*dht1,ifs, min_size + i*step_size );

		//sum of time
		float sum = 0.0;
		//num of nanoseconds find takes
		long long findTime;
		//num of find iterations
		int findNum = 100;
		//load array
		std::vector<std::string> dictArray;
		Utils::load_dict(dictArray, ifs, 100);

		for( int numFinds = 0; numFinds < findNum; numFinds++ ) { 
			timer.begin_timer();
			//read the next 100 words from the dictionary file
			for( int i = 0; i < 100; i++ ) {
				dht1->find(dictArray.at(i));
			}
			findTime = timer.end_timer();
			sum = sum + findTime;
		}
		
		//print out average
		cout << (min_size + (i*step_size)) << '\t' << (sum/findNum) << endl;
	}
	delete dht1;

	ifs.close();
}
