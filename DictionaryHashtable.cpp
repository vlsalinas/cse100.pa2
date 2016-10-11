/**
 * Name: Niral Patel and Taylor Lew
 * Date: October 7, 2016
 * Overview: Creates a dictionary with a hashtable.  Implements find and insert.
 * Assignment #: 2
 */

#include "util.h"
#include "DictionaryHashtable.h"
#include <unordered_set>

/* Param: None
 * Return: None
 * Create a new Dictionary that uses a Hashset back end 
 */
DictionaryHashtable::DictionaryHashtable() {

	//create an unordered set for hashtable
	hashDict =
			 new std::unordered_set<std::string>;
}

/* Param: String word (word to be inserted)
 * Return: true or false if it was inserted
 * Insert a word into the dictionary. 
 */
bool DictionaryHashtable::insert(std::string word) {	
	//return value for insert
	bool inserted = false; 

	//insert a word into a hashtable
	inserted = hashDict->insert(word).second;
	return inserted;

}

/* Param: String word (word to be found)
 * Return: true or false if the word is found in the dictionary
 * Finds the word that is passed in in the dictionary
 */
bool DictionaryHashtable::find(std::string word) const {
	//iterator to be returned by find
	std::unordered_set<std::string>::const_iterator found;

	//find the word in the hashtable
	found = hashDict->find(word);

	//check if the word was found
	if( found == hashDict->end() ) {
		return false;
	}

	//word is found
	else {
		return true;
	}
}

/* Param: None
 * Return: None
 * Destructor 
 */
DictionaryHashtable::~DictionaryHashtable(){

	//go through the hashtable and delete
	delete hashDict;
}
