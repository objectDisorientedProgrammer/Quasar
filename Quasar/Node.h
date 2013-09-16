/*
 *  Node.h
 *	Authors: James Howard, Douglas Chidester
 *	Created: March 27, 2013
 *
 *	Last Update: 4/30/13 DC
 *
 *	Definition of the Node class.
 *
 * Prohibited input in fields: '¶' will be used to specify fields
 *
 *
 *
*/

#ifndef NODE_H
#define NODE_H

#include "ContactData.h"
#include "DocumentData.h"
#include "PictureData.h"
#include "WebsiteData.h"
#include "MarshalString.h"
#include <string>
using namespace std;
using namespace System;

class Node
{
private:
	static unsigned int count;	// count of all nodes
	unsigned int index;
	unsigned char typeOfNode;
	string nodeCode;
	string title;
	string date;
	string description;
	string keywords;
	string filepath;
	string src;
	string aux;
	bool isDoc;
	bool isWeb;
	bool isPic;
	bool isCont;

	char intToHEXChar(int);
	int HEXCharToInt(char);
	string sanitize_str(string);

public:
	Node *next, *prev;
	DocumentData *document;
	Node *nextDocument,*prevDocument;
	WebsiteData *website;
	Node *nextWebsite, *prevWebsite;
	PictureData *picture;
	Node *nextPicture, *prevPicture;
	ContactData *contact;
	Node *nextContact, *prevContact;

	Node();
	~Node();	// need to free any *Data objects being pointed to as well as this Node object

	static unsigned int getCount()	{ return count; }
	void decrementNodeCount() { count--; }
	unsigned int getIndex()			{ return index; }
	Node* getInstance()				{ return this; }
	unsigned char getNodeType()		{ return typeOfNode; }
	void setNodeType(unsigned char type) { typeOfNode = type; }
	
	string getNodeCode()				{ return nodeCode; }
	void setNodeCode(string nodeType)	{ this->nodeCode = nodeType; }

	void resetFlags();
	void setFlags();
	void getFlags();
	void setIndex(int value)			{ this->index = value; }
	void setTitle(string input)			{ this->title = sanitize_str(input); }
	void setDate(string input)			{ this->date = sanitize_str(input); }
	void setDescription(string input)	{ this->description = sanitize_str(input); }
	void setFilepath(string input)		{ this->filepath = sanitize_str(input); }
	void setSrc(string input)			{ this->src = sanitize_str(input); }
	void setKeywords(string input)		{ this->keywords = sanitize_str(input); }
	void setAux(string input)			{ this->aux = sanitize_str(input); }
	void set_isDoc() { isDoc = true; }
	void set_isWeb() { isWeb = true; }
	void set_isPic() { isPic = true; }
	void set_isCont() { isCont = true; }


	string getTitle()			{ return this->title; }
	string getDate()			{ return this->date; }
	string getDescription()		{ return this->description; }
	string getKeywords()		{ return this->keywords;}
	string getFilepath()		{ return this->filepath; }
	string getSrc(){return src;}
	string getAux(){return aux;}
	string getOutput();
	bool get_isDoc() { return this->isDoc; }
	bool get_isWeb() { return this->isWeb; } 
	bool get_isPic() { return this->isPic; }
	bool get_isCont() { return this->isCont; }
};

#endif
