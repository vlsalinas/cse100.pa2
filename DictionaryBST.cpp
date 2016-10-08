/**
 * Name: Niral Patel and Taylor Lew
 * Date: October 7, 2016
 * Overview: Creates a dictionary with a BST.  Implements insert and find.
 * Assignment #: 2
 */

#include "util.h"
#include "DictionaryBST.h"
#include <set>

/* Params: None.
 * Return: None.
 * Create a new Dictionary that uses a BST back end 
 */
DictionaryBST::DictionaryBST(){
	setBST = new std::set<std::string>;
}

/* Params: String word (word to be inserted)
 * Return: true or false on whether it was inserted successfully
 * Insert a word into the dictionary. 
 */
bool DictionaryBST::insert(std::string word) {
	//return value for insert
	bool inserted = false; 

	//insert a word into a BST
	inserted = setBST->insert(word).second;
	return inserted;
}

/* Params: String word (word being searched for)
 * Return: true or false on whether the word was found
 * Return true if word is in the dictionary, and false otherwise 
 */
bool DictionaryBST::find(std::string word) const {
	//iterator to be returned by find
	std::set<std::string>::const_iterator found;

	//find the word in the BST
	found = setBST->find(word);

	//check if the word was found
	if( found == setBST->end() ) {
		return false;
	}

	//word is found
	return true;
}

/* Params: None.
 * Return: None.
 * Destructor 
 */
DictionaryBST::~DictionaryBST() {
	//go through the BST and delete
	setBST->~set();
	delete setBST;
}
