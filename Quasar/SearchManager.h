#include "Node.h"
#include "DocumentData.h"
#include "WebsiteData.h"
#include "PictureData.h"
#include "ContactData.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <cctype>
using namespace std;

class SearchManager{
public:
	SearchManager(){ clearData(); }
	void clearData();
	void setCurrent(Node* current) { this->current = current; }
	void identifySearchCriteria(string);
	bool isMatched();

	void printData();
	void printVector(vector<string>&);
	void printSet(set<string>&);

private:
	vector<string> stringPool, phrases, exc_phrases;
	set<string> words, exc_words;
	Node* current;

	bool inSet(set<string>&, string);
	void fillSet(set<string>&, string);
	void populateStringPool();
	string processDate(string);
};
