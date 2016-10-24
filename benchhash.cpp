/**
 *  Name: Niral Patel and Taylor Lew
 *  Date: October 20, 2016
 *  Overview: Tests the start and the end running times for both hash 
 *						functions and analyse.
 *  Assignement #:2 
 */


#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include <vector>
using namespace std;

/* Source: http://stackoverflow.com/questions/98153/
 *				 whats-the-best-hashing-algorithm-to-use-on-a-stl-string
 *				 -when-using-hash-map
 * Param: String s is the key being put in the table
 *				unsigned int len is the size of the hashtable
 * Return: unsigned int- the hash key to be used to insert into the hashtable
 * Logic: Multiplies the string's first character's ascii value by 101 and 
 *				adds the length. Repeats string length number of times.
 */
  unsigned int hashIt( std::string s, int len ) {
			int sLen = s.length();
			std::string::iterator it = s.begin();
      unsigned long hash = *it;
      while (sLen) {
          hash = hash * 101  +  sLen--;
      }
      return hash % len;
  }

/* Source: http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx
 * 
 * Param: string key - string of the word
 *				int len - length of the table size
 * Return: unsigned int - hash key to be used to insert into the hashtable
 *
 * Bernstein hash
 * It multiplies 33 to the current hash and adds the ascii value of the
 *	 char.
 */

unsigned int djb_hash(std::string key, int len) {

    char charArray[key.size()];
    unsigned long h = 0;
    unsigned int i;

		//copy string into an array
		strcpy( charArray, key.c_str() );

    for (i = 0; i < key.size(); i++)
    {
        h = 33 * h + charArray[i];
    }

    return h % len;
}


/*
 * Param: argc - number of arguments passed int
 *				argv - the arguments being passed in
 *				argv[1] - string to input
 *				argv[2] - table length
 * Return: int - return value of either success or failed depending on status.
 */
int main( int argc, char* argv[] ) {

	char* check;

	/* initialising stuff to load */
	std::ifstream ifs;
	ifs.open(argv[1], std::ios::binary);

	//std::string str(argv[1]);
	float num_words = strtol( argv[2], &check, 10 );
	/* array of words to 'insert' / just call hashfunctions on */
	std::vector<std::string> dictArray;
	/* array keeping track of hits */ 
	int tableLength = 2*num_words;
	int countArray1[tableLength];
	int countArray2[tableLength];
	/* most hits */
	int max1 = 0;
	int max2 = 0;


	/* zero initialize countArrays */
	for( int i = 0; i < tableLength; i++ ) {
		countArray1[i] = 0;
		countArray2[i] = 0;
	}

	Utils::load_dict(dictArray, ifs, num_words);

	/* starting script */
	cout << "Printing the statistics for hashIt with hash table size " << 
			 tableLength << endl;

//cout << "Count1[]: " << countArray1[1] << " Count2[]: " << countArray2[1] << endl;
	/* counting hits using hash function */
	for( int num = 0; num < num_words; num++ ) {
		unsigned int result1 = hashIt( dictArray.at(num), tableLength );
		
		countArray1[result1] = countArray1[result1] + 1;
		
		unsigned int result2 = djb_hash( dictArray.at(num), tableLength );
		countArray2[result2] = countArray2[result2] + 1;

		if( countArray1[result1] > max1 ) {
			max1 = countArray1[result1];
		}

		if( countArray2[result2] > max2 ) {
			max2 = countArray2[result2];
		}
	}

	/* array for how many slots have x hits */
	int hits1[max1 + 1];
	
	/* zero initialize hits1 */
	for( int i = 0; i < max1 + 1; i++ ) {
		hits1[i] = 0;
	}

	/*start of calculating hits */
	cout << endl << "#hits " << "\t" << "#slots receiving the #hits" << endl;

	/* j is number of hits for a key */
	for( int j = 0; j <= max1; j++ ) {
		/* i is where in the countArray we are */
		for( int i = 0; i < tableLength; i++ ) {
			if( countArray1[i] == j ) {
				hits1[j]++;
			}
		}
		if( hits1[j] != 0 ) {
			cout << j << "\t" << hits1[j] << endl;
		}
	}


	/* calculating averages */

	float avg1;
	int indexSum;
	float totalSum = 0.0;
	/* sum all steps for all words */
	for( int s = 1; s < max1+1; s++ ) {
		indexSum = 0;
		for( int i = s; i < max1+1; i++ ) {
			indexSum += hits1[i];
		}
		hits1[s] = indexSum;
	}

	for( int j = 1; j < max1+1; j++ ) {
		totalSum += hits1[j]*j;
	}

	avg1 = float(totalSum / num_words);

	cout << endl << "The average number of steps for a successful search for hash " <<
						"would be " << avg1 << endl;

	/* printing worst case */
	cout << endl << "The worst case steps that would be needed to find a word is " << max1
		   << endl;


	
	
	/* starting script */
	cout << endl << "Printing the statistics for djb_hash with hash table size " << 
			 tableLength << endl;
			
	/* array for how many slots have x hits */
	int hits2[max2 + 1];

	/* zero initialize hits2 */
	for( int i = 0; i < max2 + 1; i++ ) {
		hits2[i] = 0;
	}
	/*start of calculating hits */
	cout << "#hits " << "\t" << "#slots receiving the #hits" << endl;

	/* j is number of hits for a key */
	for( int j = 0; j <= max2; j++ ) {
		/* i is where in the countArray we are */
		for( int i = 0; i < tableLength; i++ ) {
			if( countArray2[i] == j ) {
				hits2[j]++;
			}
		}
		if( hits2[j] != 0 ) {
			cout << j << "\t" << hits2[j] << endl;
		}
	}

	/* calculating averages */
	float avg2;
	totalSum = 0;
	/* sum all steps for all words */
	for( int s = 1; s < max2+1; s++ ) {
		//cout << "Current sum is " << avg2 << endl << endl; 
		//avg2 += (s+1)*sums2.at(s);
		indexSum = 0;
		for( int i = s; i < max2+1; i++ ) {
			indexSum += hits2[i];
		}
		/* reusing array */
		hits2[s] = indexSum; 
	}
	
	for( int j = 1; j < max2+1; j++ ) {
		totalSum += hits2[j]*j;
	}
	
	avg2 = (float)(totalSum / num_words);

	cout << endl << "The average number of steps for a successful search for djb_hash " <<
						"would be " << avg2 << endl;

	/* printing worst case */
	cout << endl << "The worst case steps that would be needed to find a word is " << max2
		   << endl;

}



/* 
 * Testing - copy to write up
 *
 * hashIt
 * - string - hi and tablesize = 3
 *   expected: 1
 *   got: 1
 *
 * - string - Niral and tablesize = 100
 *   expected: 93
 *   got: 93
 *
 * - string - Taylor and tablesize = 21
 *   expected: 3
 *   got: 3
 *
 * - string - *2016 and tablesize = 300
 *   expected: 57
 *   got: 57
 *   
 * 
 * djb_hash
 * - string - hi and tablesize = 3
 *   expected: 0
 *   got: 0
 *
 * - string - Niral and tablesize = 100
 *   expected: 78
 *   got: 78
 *
 * - string - *2016 and tablesize = 300
 *   expected: 75
 *   got:  75
 */ 
