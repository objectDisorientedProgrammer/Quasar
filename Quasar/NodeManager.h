/*
 * 	NodeManager.h
 * 	Authors: Douglas Chidester and James Howard
 * 	Created: March 31, 2013
 *
 *	Last Update: 5/20/13 JH
 *	
 *	
 */

#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include "Node.h"
#include "ContactData.h"
#include "DocumentData.h"
#include "PictureData.h"
#include "WebsiteData.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class NodeManager
{
private:
	string nodeDBPath;

	Node* head;		// head node in the list
	Node* current;	// current node
	Node* tail;		// tail node in the list
	Node* last;		// last node with data in the list

	int documentCount;
	int websiteCount;
	int pictureCount;
	int contactCount;
	int totalNodeCount;

	vector<string> fileContents;

	// Functions
	void loadFile(string);
	void _loadFile(string);
	char intToHEXChar(int);
	int HEXCharToInt(char);

	void decrementDocumentCount();
	void decrementWebsiteCount();
	void decrementPictureCount();
	void decrementContactCount();
	void decrementTotalNodeCount();

public:
	NodeManager(){NodeManager("Quasar.dat");}
	NodeManager(string);
	~NodeManager();
	
	void saveNodeStructure();	// saves list data to a file
	void _saveNodeStructure();

	// Pointers to keep track of the last instance of each node of each type
	Node* lastDocument;
	Node* lastWebsite;
	Node* lastPicture;
	Node* lastContact;

	// Node functions
	Node* getHead();
	Node* getCurrentNode();
	Node* getTail();
	Node* getLast();

	
	void makeHeadTail();
	void goFirst();		// current points to first node
	void goFirst(int);
	void goNext();		// current points to next node in the list
	void goNext(int);
	void goPrev();		// current points to prev node in the list
	void goLast();		// current points to last node
	void goNextDocument();
	void goPrevDocument();
	void goNextWebsite();
	void goPrevWebsite();
	void goNextPicture();
	void goPrevPicture();
	void goNextContact();
	void goPrevContact();
	void addNode(Node*);
	void deleteNode(Node*);
	void _addNode(Node*);
	void setNode(string, Node*); //this sets all properties associated with a node
	bool isEmpty()	// does the list have any nodes besides head and tail?
	{
		return (head->next == tail);
	}

	int getDocumentCount();
	int getWebsiteCount();
	int getPictureCount();
	int getContactCount();
	int getTotalNodeCount();
	bool outOfBounds() { return (current == head || current == tail); }
};

#endif
