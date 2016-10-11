/**
 *  Name: Niral Patel and Taylor Lew
 *  Date: October 8, 2016
 *  Overview: methods for creating a dictionary with a Ternary Trie
 *  Assignement #:2 
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>
#include <unordered_map>

class DictionaryTrieNode;
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie {
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  // Add your own data members and methods here
   
	/* root node for trie */
	DictionaryTrieNode* root;

	/* helper method for find/insert */
	DictionaryTrieNode* helpFind( DictionaryTrieNode* current, 
																std::string word, unsigned int 
																index ) const;
};

/* Helper class for Trie Nodes 
 */
class DictionaryTrieNode {
public: 

	/* Create a new Dictionary Trie Node for the Multiway trie 
   */
	DictionaryTrieNode();

	/* Default destructor. Delete this node and all it's data.
   */
  ~DictionaryTrieNode();

	/** Methods needed for the node 
   */

	/* Traverse down the trie */
	DictionaryTrieNode* searchNext( char c );

	/* set of letters */
	std::unordered_map<char, DictionaryTrieNode *> letters;

	/* boolean for whether it is a word node or not */
	bool isWord;

	/* char pointing to this node */
	char myCharacter;

	/* frequency */
	unsigned int frequency;

private:
	
};	 
	 
#endif // DICTIONARY_TRIE_H
