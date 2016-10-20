/**
 * Name: Niral Patel and Taylor Lew
 * Date: October 7, 2016
 * Overview: Tests the dictionaries
 * Assignment #: 2
 */

#include<iostream>
#include <sstream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include <fstream>
#define LETTERS 26
using namespace std;
using std::ifstream;
using std::istream;
using std::istringstream;

int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  words.push_back("auto");
 
	nope.insert("sirius");
	nope.insert("taylor");
	nope.insert("sus");
	nope.insert("tic tacs");
	nope.insert("hello");
  
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into " << 
								"Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
/*You are supposed to add more test cases in this file */
  /* Searching for inserted words */
  cout << "Finding in Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

	/* Searching for nonexistent words */
  cout << "Finding Nonexistents in Dictionaries..." << endl;

  nit = nope.begin();
  nen = nope.end();
  for(; nit != nen; ++nit)
    {
      cout << "Finding: \"" << *nit << "\"... ";
      t_bst = d_bst.find(*nit);
      t_ht = d_ht.find(*nit);
      tt = dt.find(*nit);
      cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(!t_bst && !t_ht && !tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }
/* Tests #2 */
  //Initialize words
  vector<std::string> words2;
  vector<string>::iterator wit2;
  vector<string>::iterator wen2;
  //initialize nonwords
  set<string> nope2;
  set<string>::iterator nit2;
  set<string>::iterator nen2;

  //Initialize data structures
  DictionaryBST d_bst2;
  DictionaryHashtable d_ht2;
  DictionaryTrie dt2;
  int t_bst2, t_ht2, tt2;

  words2.push_back("i");
  words2.push_back("just");
  words2.push_back("met");
  words2.push_back("this");
  words2.push_back("is");
  words2.push_back("crazy");
  words2.push_back("call");
  words2.push_back("me");
  words2.push_back("maybe");
 
	nope2.insert("rebecca");
	nope2.insert("may");
	nope2.insert("his");
	nope2.insert("call me");
	nope2.insert("sing");
  
  cout << "Inserting into Dictionaries..." << endl;

  wit2 = words2.begin();
  wen2 = words2.end();
  for(; wit2 != wen2; ++wit2)
    {
      cout << "Inserting: \"" << *wit2 << "\"... ";
      t_bst2 = d_bst2.insert(*wit2);
      t_ht2 = d_ht2.insert(*wit2);
      tt2 = dt2.insert(*wit2, 1);
      cout << t_bst2 << " " << t_ht2 << " "<< tt2 << "... ";
      if(!t_bst2)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht2)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt2)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst2 && t_ht2 && tt2)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into " << 
								"Dictionaries..." << endl;

  wit2 = words2.begin();
  wen2 = words2.end();
  for(; wit2 != wen2; ++wit2)
    {
      cout << "Inserting: \"" << *wit2 << "\"... ";
      t_bst2 = d_bst2.insert(*wit2);
      t_ht2 = d_ht2.insert(*wit2);
      tt2 = dt2.insert(*wit2, 0);
      if(t_bst2)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht2)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt2)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst2 && !t_ht2 && !tt2)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
/*You are supposed to add more test cases in this file */
  /* Searching for inserted words */
  cout << "Finding in Dictionaries..." << endl;

  wit2 = words2.begin();
  wen2 = words2.end();
  for(; wit2 != wen2; ++wit2)
    {
      cout << "Finding: \"" << *wit2 << "\"... ";
      t_bst2 = d_bst2.find(*wit2);
      t_ht2 = d_ht2.find(*wit2);
      tt2 = dt2.find(*wit2);
      cout << t_bst2 << " " << t_ht2 << " "<< tt2 << "... ";
      if(!t_bst2)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht2)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt2)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst2 && t_ht2 && tt2)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

	/* Searching for nonexistent words */
  cout << "Finding Nonexistents in Dictionaries..." << endl;

  nit2 = nope2.begin();
  nen2 = nope2.end();
  for(; nit2 != nen2; ++nit2)
    {
      cout << "Finding: \"" << *nit2 << "\"... ";
      t_bst2 = d_bst2.find(*nit2);
      t_ht2 = d_ht2.find(*nit2);
      tt2 = dt2.find(*nit2);
      cout << t_bst2 << " " << t_ht2 << " "<< tt2 << "... ";
      if(t_bst2)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(t_ht2)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(tt2)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(!t_bst2 && !t_ht2 && !tt2)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }



	//commented out because we deleted the dictionary folder for space
	/* Testing Trie dictionary */
	std::ifstream ifs;
	ifs.open("freq1.txt", std::ios::binary);
  DictionaryTrie* dt1 = new DictionaryTrie();
	int resultTrie = 0;
  Utils::load_dict(*dt1,ifs, 500000);

	//find words in trie dictionary
	resultTrie = dt1->find("a baby and she");
	if(!resultTrie) {
		cout << "Test failed- a baby and she" << endl;
	}
	else {
		cout << "Passed :D" << endl;
	}
	
	resultTrie = dt1->find("a bargain compared with");
	if(!resultTrie) {
		cout << "Test failed" << endl;
	}
	else {
		cout << "Passed :D" << endl;
	}

	resultTrie = dt1->find("a broad view");
	if(!resultTrie) {
		cout << "Test failed" << endl;
	}
	else {
		cout << "Passed :D" << endl;
	}

	resultTrie = dt1->find("a buddhist temple");
	if(!resultTrie) {
		cout << "Test failed b" << endl;
	}
	else {
		cout << "Passed :D" << endl;
	}

//////////* Testing AutoComplete Function */
/////////vector<std::string> ourAnswers = dt1->predictCompletions("aa", 3);
/////////vector<std::string> rightAnswers;
/////////
/////////cout << "Testing autocomplete function...";
///////////fill rightAnswers vector
/////////rightAnswers.push_back("aah");
/////////rightAnswers.push_back("aaron");
/////////rightAnswers.push_back("aan");
/////////
///////////check vector
/////////
///////////failed 
/////////if( !( ourAnswers == rightAnswers ) ) {
/////////	
/////////	cout << "failed for aa..." << endl;
/////////}
/////////
/////////else {
/////////	cout << "PASSED! :D " << endl;
/////////}
/////////	ifs.close(); 

	/* Testing Hashtable dictionary */
	std::ifstream ifs2;
	ifs2.open("freq1.txt", std::ios::binary);
	DictionaryHashtable* dh1 = new DictionaryHashtable();
	int resultHash = 0;
  Utils::load_dict(*dh1,ifs2,9000);

	//find words in hash dictionary
	resultHash = dh1->find("a cherry tree");
	if(!resultHash) {
		cout << "Test failed" << endl;
	}
	else {
		cout << "Passed :D" << endl;
	}
	
	resultHash = dh1->find("a chemical or biological");
	if(!resultHash) {
		cout << "Test failed" << endl;
	}
	else {
		cout << "Passed :D" << endl;
	}

	resultHash = dh1->find("a child of privilege");
	if(!resultHash) {
		cout << "Test failed" << endl;
	}
	else {
		cout << "Passed :D" << endl;
	}
	ifs.close(); 
	
	/* Testing BST dictionary */
	std::ifstream ifs3;
	ifs3.open("freq1.txt", std::ios::binary);
	DictionaryBST* db1 = new DictionaryBST();
	int resultBST = 0;
  Utils::load_dict(*db1,ifs3, 11000);

	//find words in BST dictionary
	resultBST = db1->find("a cia officer");
	if(!resultBST) {
		cout << "Test failed" << endl;
	}
	else {
		cout << "Passed :D" << endl;
	}
	
	resultBST = db1->find("a clear sky");
	if(!resultBST) {
		cout << "Test failed" << endl;
	}
	else {
		cout << "Passed :D" << endl;
	}

	resultBST = db1->find("a complete and accurate");
	if(!resultBST) {
		cout << "Test failed" << endl;
	}
	else {
		cout << "Passed :D" << endl;
	} 


  return 0;
}
