#include "SearchManager.h"

void SearchManager :: clearData() {
	phrases.clear();
	exc_phrases.clear();
	words.clear();
	exc_words.clear();
}

void SearchManager :: fillSet(set<string>& sp_words, string text){
	string word; char current;
	unsigned i=0;

	while(i<text.length()){       //scan thru chars in text
		current = text[i];
		if(!isspace(current)){ //&& !ispunct(current)){   //not space && not punct
			word.push_back(tolower(current));         //load to local string word
		} else if (isspace(current) && word != ""){
			sp_words.insert(word);                     //load word into set of keywords
			word = "";
		}
		i++;
	}  //end while

	if(word != "") sp_words.insert(word);    //if word is not empty string, load into set of keywords

}  //end function

void SearchManager :: populateStringPool()
{
	//clear stringPool vector
	stringPool.clear();

	stringPool.push_back(current->getTitle());
	stringPool.push_back(processDate(current->getDate()));
	stringPool.push_back(current->getDescription());
	stringPool.push_back(current->getKeywords());
	if(current->document){
		stringPool.push_back(current->document->getPath());
	}

	if(current->website){
		stringPool.push_back(current->website->getSiteURL());
	}

	if(current->picture){
		stringPool.push_back(current->picture->getPath());
	}

	if(current->contact){
		stringPool.push_back(current->contact->getFirstName());
		stringPool.push_back(current->contact->getLastName());
		stringPool.push_back(current->contact->getEmail());
		stringPool.push_back(current->contact->getPhoneNumber());
	}

}

bool SearchManager :: inSet(set<string> &aSet, string aString)		//flag = TRUE if aString in set<>
{
	for(set<string>::iterator iter = aSet.begin(); iter != aSet.end(); iter++)
		if(iter->find(aString) != string::npos)
			return true;
	return false;
	//set<string>::iterator iter = aSet.find(aString);
	//return (!(iter==aSet.end()));
}

void SearchManager :: identifySearchCriteria(string query)
{
	unsigned quotePos = string::npos, phraseLength = 0;
	string word, phrase;
	unsigned i=0;
	bool excWaiting = false;
	clearData();				//init vector and set containers using STL clear() method

	while(i<query.length())		//loop through the line of text one char at a time
	{
		//ignore whitespace or + symbol
		while(i<query.length() && isspace(query[i]) || query[i] == '+')
			i++;
		//check if next word or phrase is to be excluded
		if((query[i]) == '-')
		{
			excWaiting = true;
			i++;
		}
		//ignore whitespace
		while(i<query.length() && isspace(query[i]))
			i++;
		//check for a phrase
		if (query[i]=='\"')		//if char is a " we have the start of phrase
		{
			quotePos = query.find("\"", i+1);	//get the text index location of the second "
			phraseLength = quotePos - i - 1;	//length of phrase = number of chars between "quotes"
			if(quotePos == string::npos)		//if reached max length = -1 before a second " zero it out
			{
				phraseLength = query.length() - i;
				quotePos = query.length() - 1;
			}
			phrase = query.substr(i+1, phraseLength);	//phrase = substring of text
			for(unsigned l=0; l<phrase.length(); l++)	//loop through phrase chars using index = k
				phrase[l] = tolower(phrase[l]);			//make all phrase chars lower case, see <cctype> methods
			if(excWaiting)
			{
				excWaiting = false;
				if(phrase.length())
					exc_phrases.push_back(phrase);
			}
			else
			{
				if(phrase.length()) phrases.push_back(phrase);	//bingo - load phrase into key phrases vector
			}
			phraseLength = 0;
			i = quotePos;
		} else { // assume the scanner has reached a word
			word = "";
			while(i < query.length() && !isspace(query[i])){
				word.push_back(tolower(query[i]));
				i++;
			}
			if(excWaiting){
				excWaiting = false;
				if(word.length()) exc_words.insert(word);
			} else {
				if(word.length()) words.insert(word);
			}
		}
		i++;  //incr index for char inside the line of text string
	}  //end while loop
}

bool SearchManager :: isMatched(){
	set<string> sp_words;
	bool phraseCriteriaMet;
	populateStringPool();

	sp_words.clear();
	for(vector<string>::iterator spIter = stringPool.begin(); spIter != stringPool.end(); spIter++)
		fillSet(sp_words, *spIter);

	//printSet(sp_words);
	//printVector(stringPool);

//Check to see whether all specified words are included
	for(set<string>::iterator iter=words.begin(); iter != words.end(); iter++)  
		if(!(inSet(sp_words, *iter)))
			return false;   //if search param does not contain

//Check to see whether specified words are excluded
	for(set<string>::iterator iter=exc_words.begin(); iter != exc_words.end(); iter++)  
		if((inSet(sp_words, *iter))) return false;   //if search param does contain
													 //any text keywords return false 
//Verify that phrases are included
	for(vector<string>::iterator iter=phrases.begin(); iter!= phrases.end(); iter++){
		phraseCriteriaMet = false; //this condition must be disproven to proceed
		for(vector<string>::iterator spIter = stringPool.begin(); spIter != stringPool.end(); spIter++)
			if((*spIter).find(*iter) != string::npos) phraseCriteriaMet = true;
		if(!phraseCriteriaMet) return false;					//if search param does not match 
																//any phrase keywords return false
	}

//Verify that certain phrases are excluded
	for(vector<string>::iterator iter=exc_phrases.begin(); iter!= exc_phrases.end(); iter++)
		for(vector<string>::iterator spIter = stringPool.begin(); spIter != stringPool.end(); spIter++)
			if((*spIter).find(*iter) != string::npos) return false;

	return true;
}

string SearchManager::processDate(string input)
{
	string result = input;
	string addendum = " ";
	for(string::iterator iter=input.begin(); iter!=input.end(); iter++)
	{
		if(isalnum(*iter))
			addendum += *iter;
		else
			addendum += ' ';
	}
	return result;
}

void SearchManager :: printVector(vector<string> &aVec){          //print the contents of vector to screen
	unsigned i = aVec.size();
	for(vector<string>::iterator iter=aVec.begin(); iter!=aVec.end(); iter++)
		{ cout << *iter; if (--i) cout << ", ";	}
	cout << endl;
}

void SearchManager :: printSet(set<string> &aSet){               //print the contents of set to screen
	unsigned i = aSet.size();
	for(set<string>::iterator iter = aSet.begin(); iter != aSet.end(); iter++)
		{ cout << *iter; if (--i) cout << ", ";	}
	cout << endl;
}

void SearchManager :: printData(){
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