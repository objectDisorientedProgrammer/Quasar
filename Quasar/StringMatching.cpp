//---------------------------------------------------------------------
//
//	Filename:  StringMatching_rev2b.cpp
//	    Date:  21 April 2013
//
//	Project:  Quasar
//     Team:  Gamma
//
//   Author:  James Howard
//
//  Description:  StringMatching does the following:
//		1) Inputs a line of text using getline()
//
//		2) Scans the text and captures words that are in double quotes "  "
//		   and stores them as a phrase in a vector<string>
//
//		3) Identifies individual words that are not in double quotes
//		   and stores them in a set<string>
//
//		4) Returns a boolean=TRUE if a phrase in double "quotes" matches a phrase in the keyphrase
//
//	    5) Returns a boolean=TRUE if words being tested which are not in double "quotes" match words 
//         in the keyphrase
//      
//      6) Returns boolean=FALSE if there are no matches
//		
//	   
//---------------------------------------------------------------------

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <set>
using namespace std;

//Class Definitions

class SearchCriteria{
public:
	SearchCriteria(){}
	void clearData(){
		phrases.clear();
		exc_phrases.clear();
		words.clear();
		exc_words.clear();
	}
	void printData();
	void printVector(vector<string>&);
	void printSet(set<string>&);
	vector<string> phrases, exc_phrases;
	set<string> words, exc_words;
};

//Function Prototypes

void fillSet(set<string>&, string);
void clearData(vector<string>&, vector<string>&, set<string>&, set<string>&);
bool inSet(set<string>&, string);
void identifySearchCriteria(SearchCriteria&, string);
bool isMatched(SearchCriteria&, string);
string getString(string);

//load a complete keyphrase for testing the procedure

const string searchText = "The quick brown fox jumps over the lazy dog.";  //complete keyphrase


//-------------------------  Function identifySearchCriteria( ) ------------------------------
//
//  Parameters: 
//
//	string text - input line of text to be evaluated
//
//	vector<string> &phrases:  phrases = text in "quotes" that matches keywords 
//							  load phrases into vector<string> STL container = phrases.push_back()
//
//	set<string> &words:   words = text not in "quotes" but matches a keyword 
//						  load words into set<string> = words.insert()
//
//-------------------------------------------------------------------------------------


void identifySearchCriteria(SearchCriteria &sc, string text){
	unsigned quotePos = string::npos, phraseLength = 0;
	string word, phrase; char current;
	unsigned i=0;
	bool excWaiting = false;
	sc.clearData();					//init vector and set containers using STL clear() method

	while(i<text.length()){                        //loop through the line of text one char at a time		
		//ignore whitespace or + symbol
		while(i<text.length() && isspace(text[i]) || text[i] == '+') i++;
		//check if next word or phrase is to be excluded
		if((text[i]) == '-'){
			excWaiting = true;
			i++;
		}
		//ignore whitespace
		while(i<text.length() && isspace(text[i])) i++;
		//check for a phrase
		if (text[i]=='\"'){                 	//if char is a " we have the start of phrase
			quotePos = text.find("\"", i+1);    //get the text index location of the second "
			phraseLength = quotePos - i - 1;    //length of phrase = number of chars between "quotes"
			if(quotePos == string::npos) {				//if reached max length = -1 before a second " zero it out
				phraseLength = text.length() - i;
				quotePos = text.length() - 1;
			}
			phrase = text.substr(i+1, phraseLength);  //phrase = substring of text
			for(unsigned l=0; l<phrase.length(); l++) //loop through phrase chars using index = k
				phrase[l] = tolower(phrase[l]);       //make all phrase chars lower case, see <cctype> methods
			if(excWaiting) {
				excWaiting = false;
				if(phrase.length()) sc.exc_phrases.push_back(phrase);
			} else { if(phrase.length()) sc.phrases.push_back(phrase); }          //bingo - load phrase into key phrases vector
			phraseLength = 0;
			i = quotePos;
		} else { // assume the scanner has reached a word
			word = "";
			while(i < text.length() && !isspace(text[i])){
				word.push_back(tolower(text[i]));
				i++;
			}
			if(excWaiting){
				excWaiting = false;
				if(word.length()) sc.exc_words.insert(word);
			} else {
				if(word.length()) sc.words.insert(word);
			}
		}
		i++;  //incr index for char inside the line of text string
	}  //end while loop
}  //end identifySearchCriteria() function

//---------------------------------------------------------------------------------------------

string getString(string prompt){
	string result;
	cout << prompt;
	getline(cin, result);
	return result;
}

//----------------------------  Function fillSet( ) -----------------------------------
//
//  Descrip:  Fill set<string> t_words with the individual words inside string text param
//
//  Parameters: 
//
//	string text - input string to be evaluated
//
//	set<string> & t_words:  t_words = text not in "quotes" but matches a keyword 
//						    load words into set<string> = words.insert()
//
//-------------------------------------------------------------------------------------


void fillSet(set<string>& t_words, string text){
	string word; char current;
	unsigned i=0;

	while(i<text.length()){       //scan thru chars in text
		current = text[i];
		if(!isspace(current) && !ispunct(current)){   //not space && not punct
			word.push_back(tolower(current));         //load to local string word
		} else if (isspace(current) && word != ""){
			t_words.insert(word);                     //load word into set of keywords
			word = "";
		}
		i++;
	}  //end while

	if(word != "") t_words.insert(word);    //if word is not empty string, load into set of keywords

}  //end function

bool inSet(set<string> &aSet, string aString){       //flag = TRUE if aString in set<>
	set<string>::iterator iter = aSet.find(aString);
	return (!(iter==aSet.end()));
}

//-----------------------------  Function  isMatched( ) ------------------------------
//
//  Descrip:  Looking for word matches in set<string>; phrase matches in vector<string>
//            Uses the STL container methods and iterators to scan entire contents 
//            in set and vector, e.g. words.begin()
//
//---------------------------------------------------------------------------------------------

bool isMatched(SearchCriteria &sc, string search){
	set<string> t_words;
	fillSet(t_words, search);    //load up set of t_words identified in string search

	for(unsigned i=0; i<search.length(); i++)   //convert all search param chars to lowercase
		search[i] = tolower(search[i]);

	//checks that words are included
	for(set<string>::iterator iter=sc.words.begin(); iter != sc.words.end(); iter++)  
		if(!(inSet(t_words, *iter))) return false;   //if search param does not contain
	                                                 //any text keywords return false 
	//checks that certain words are excluded
	for(set<string>::iterator iter=sc.exc_words.begin(); iter != sc.exc_words.end(); iter++)  
		if((inSet(t_words, *iter))) return false;   //if search param does contain
	                                                 //any text keywords return false 
	//checks that phrases are included
	for(vector<string>::iterator iter=sc.phrases.begin(); iter!=sc.phrases.end(); iter++)
		if(search.find(*iter) == string::npos) return false;  //if search param does not match 
	                                                          //any phrase keywords return false 
	//checks that certain phrases are excluded
	for(vector<string>::iterator iter=sc.exc_phrases.begin(); iter!=sc.exc_phrases.end(); iter++)
		if(search.find(*iter) != string::npos) return false;  //if search param does match 
	                                                          //any phrase keywords return false 
	return true;
}

void SearchCriteria :: printVector(vector<string> &aVec){          //print the contents of vector to screen
	unsigned i = aVec.size();
	for(vector<string>::iterator iter=aVec.begin(); iter!=aVec.end(); iter++)
		{ cout << *iter; if (--i) cout << ", ";	}
}

void SearchCriteria :: printSet(set<string> &aSet){               //print the contents of set to screen
	unsigned i = aSet.size();
	for(set<string>::iterator iter = aSet.begin(); iter != aSet.end(); iter++)
		{ cout << *iter; if (--i) cout << ", ";	}
	cout << endl;
}

void SearchCriteria :: printData(){
		cout << "Search Criteria:" << endl;       

		cout << "vector<string> phrases[" << phrases.size() << "] content:" << endl;
		printVector(phrases);    //printout phrases that have been identified
		cout << endl;

		cout << "vector<string> exc_phrases[" << exc_phrases.size() << "] content:" << endl;
		printVector(exc_phrases);    //printout phrases that have been identified
		cout << endl;

		cout << "set<string> words[" << words.size() << "] content:" << endl;
		printSet(words);         //printout words that have been identified
		cout << endl;

		cout << "set<string> exc_words[" << exc_words.size() << "] content:" << endl;
		printSet(exc_words);         //printout words that have been identified
		cout << endl;
}
