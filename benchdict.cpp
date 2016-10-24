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
	
	std::string name;
	while( std::getline(ifs, name) ) {
		sizeOfFile++;
	} 
	ifs.close();
	ifs.open(argv[4], std::ios::binary);

	//go through num_iterations times
	for ( int i = 0; i < num_iterations; i++ ) {
		ifs.seekg( 0, ifs.beg );	
		//check how many words are left (min + i*step_size)
		//if there are fewer words in file
		if( ( (min_size + i*step_size) ) > sizeOfFile ) {
			cout << "Warning number of words in file is less than the number of" 
					 << " words that will be loaded." << endl;
		}
		
		long size = min_size + i*step_size;
		
		//load from dictionary
		if( size <= sizeOfFile && size > 0 ) {
			Utils::load_dict(*dt1,ifs, min_size + i*step_size );
		}

		//the size you want to load is bigger than the file size
		else if( size > sizeOfFile ) {
			Utils::load_dict(*dt1, ifs, size - sizeOfFile);
		}

		//size = 0
		else {
			break;
		}

		//sum of time
		long sum = 0;
		//num of nanoseconds find takes
		long long findTime;
		//num of find iterations
		int findNum = 100;
		//load array
		std::vector<std::string> dictArray;

		int find = 0;

		//there are 100 or more words left that can be loaded
		if( ( sizeOfFile - size ) >= 100 ) {
			Utils::load_dict(dictArray, ifs, 100);
			find = 100;
		}

		//if there are less than 100 words left but more than 0
		else if( ( ( sizeOfFile - size ) < 100 ) && 
						 ( sizeOfFile - size ) < 0 ) {
			Utils::load_dict(dictArray, ifs, ( sizeOfFile - size ));
			find = size - sizeOfFile;
		}

		//if there is nothing left to read
		else {
			find = 0;
			break;
		}

		for( int numFinds = 0; numFinds < findNum; numFinds++ ) { 

			timer.begin_timer();
			//read the next 100 words from the dictionary file
			for( int i = 0; i < find; i++ ) {
				dt1->find(dictArray.at(i));
			}
			findTime = timer.end_timer();
			sum = sum + findTime;
		}
		
		//print out average
		cout << (min_size + (i*step_size)) << '\t'<< (sum/findNum) << endl;
	}
	delete dt1;	
	ifs.close();


	/*			Benchmarking DictionaryBST			*/
	cout << endl << "DictionaryBST " << endl;
		DictionaryBST* dbst1 = new DictionaryBST();

	ifs.open(argv[4], std::ios::binary);

	//go through num_iterations times
	for ( int i = 0; i < num_iterations; i++ ) {
		ifs.seekg( 0, ifs.beg );	
		//check how many words are left (min + i*step_size)
		//if there are fewer words in file
		if( ( (min_size + i*step_size) ) > sizeOfFile ) {
			cout << "Warning number of words in file is less than the number of" 
					 << "words that will be loaded." << endl;
		}
	
		long size = min_size + i*step_size;
		
		//load from dictionary
		if( size <= sizeOfFile && size > 0 ) {
			Utils::load_dict(*dbst1,ifs, size );
		}

		//the size you want to load is bigger than the file size
		else if( size > sizeOfFile ) {
			Utils::load_dict(*dbst1, ifs, size - sizeOfFile);
		}

		//size = 0
		else {
			break;
		}

		//sum of time
		long sum = 0;
		//num of nanoseconds find takes
		long long findTime;
		//num of find iterations
		int findNum = 100;
		//load array
		std::vector<std::string> dictArray;
	
		int find = 0;

		//there are 100 or more words left that can be loaded
		if( ( sizeOfFile - size ) >= 100 ) {
			Utils::load_dict(dictArray, ifs, 100);
			find = 100;
		}

		//if there are less than 100 words left but more than 0
		else if( ( ( sizeOfFile - size ) < 100 ) && 
						 ( sizeOfFile - size ) < 0 ) {
			Utils::load_dict(dictArray, ifs, ( sizeOfFile - size ));
			find = size - sizeOfFile;
		}

		//if there is nothing left to read
		else {
			find = 0;
			break;
		}

		for( int numFinds = 0; numFinds < findNum; numFinds++ ) { 

			timer.begin_timer();
			//read the next 100 words from the dictionary file
			for( int i = 0; i < find; i++ ) {
				dbst1->find(dictArray.at(i));
			}
			findTime = timer.end_timer();
			sum = sum + findTime;
		}
		
		//print out average
		cout << (min_size + (i*step_size)) << '\t'<< (sum/findNum) << endl;
	}
	delete dbst1;
	ifs.close();

	/*			Benchmarking DictionaryHashtable			*/
	cout << endl << "DictionaryHashtable " << endl;
	
	DictionaryHashtable* dht1 = new DictionaryHashtable();
	ifs.open(argv[4], std::ios::binary);

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
		long size = min_size + i*step_size;
		
		//load from dictionary
		if( size <= sizeOfFile && size > 0 ) {
			Utils::load_dict(*dht1,ifs, min_size + i*step_size );
		}

		//the size you want to load is bigger than the file size
		else if( size > sizeOfFile ) {
			Utils::load_dict(*dht1, ifs, size - sizeOfFile);
		}

		//size = 0
		else {
			break;
		}

		//sum of time
		long sum = 0;
		//num of nanoseconds find takes
		long long findTime;
		//num of find iterations
		int findNum = 100;
		//load array
		std::vector<std::string> dictArray;

		int find = 0;

		//there are 100 or more words left that can be loaded
		if( ( sizeOfFile - size ) >= 100 ) {
			Utils::load_dict(dictArray, ifs, 100);
			find = 100;
		}

		//if there are less than 100 words left but more than 0
		else if( ( ( sizeOfFile - size ) < 100 ) && 
						 ( sizeOfFile - size ) < 0 ) {
			Utils::load_dict(dictArray, ifs, ( sizeOfFile - size ));
			find = size - sizeOfFile;
		}

		//if there is nothing left to read
		else {
			find = 0;
			break;
		}

		for( int numFinds = 0; numFinds < findNum; numFinds++ ) { 
			timer.begin_timer();
			//read the next 100 words from the dictionary file
			for( int i = 0; i < find; i++ ) {
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
