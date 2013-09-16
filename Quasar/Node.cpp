// See Node.h for documentation.
#include "Node.h"
unsigned int Node::count = 0;

// On creation, set all pointers to null, assign an index number, and set the type to 0 (no type).
Node::Node()
{
	this->next = NULL;
	this->prev = NULL;
	this->document = NULL;
	this->nextDocument = NULL;
	this->prevDocument = NULL;
	this->website = NULL;
	this->nextWebsite = NULL;
	this->prevWebsite = NULL;
	this->picture = NULL;
	this->nextPicture = NULL;
	this->prevPicture = NULL;
	this->contact = NULL;
	this->nextContact = NULL;
	this->prevContact = NULL;

	isDoc = false;
	isWeb = false;
	isPic = false;
	isCont = false;

	index = 0;
	typeOfNode = 0;
	nodeCode = "0";
	resetFlags();
}

Node::~Node()
{
	if(document) delete document;
	if(website) delete website;
	if(picture) delete picture;
	if(contact) delete contact;
}

void Node::resetFlags(){
	isDoc = false;
	isWeb = false;
	isPic = false;
	isCont = false;
}

void Node::setFlags(){
	int value = 0;
	if(this->contact){
		isCont=true;
		value += 8;
	}
	if(this->picture){
		isPic=true;
		value += 4;
	}
	if(this->website){
		isWeb=true;
		value += 2;
	}
	if(this->document){
		isDoc=true;
		value += 1;
	}
	typeOfNode = intToHEXChar(value);
}

void Node::getFlags(){
	int value = HEXCharToInt(typeOfNode);
	if(value == 8)	// >=
	{
		isCont = true;
		value-=8;
	}
	if(value == 4)	// >=
	{
		isPic = true;
		value-=4;
	}
	if(value == 2)	// >=
	{
		isWeb = true;
		value-=2;
	}
	if(value == 1)
		isDoc = true;
}

char Node::intToHEXChar(int value){
	if(value / 10)
		return (char)(65 + value % 10);
	else
		return (char)(48 + value);
}
int Node::HEXCharToInt(char hexValue){
	int value = (int)hexValue;
	if(value >= 97) value-=32;
	if(value >= 65)
		return (value-55);
	else
		return (value-48);
}

string Node::sanitize_str(string input){
	string result;
	for(string::iterator iter=input.begin(); iter!=input.end(); iter++)
		if(*iter != '¶') result += *iter;
	return result;
}

string Node::getOutput(){
	string result;
	resetFlags();
	setFlags();
	result  = typeOfNode;	result += '¶';
	result += title;		result += '¶';
	result += description;	result += '¶';
	result += date;			result += '¶';
	result += keywords;

	if(isDoc == true){	result+="¶d¶";		result+=document->getPath();	}
	if(isWeb == true)
	{
		result+="¶w¶";
		result+=website->getSiteURL();
	}
	if(isPic == true){	result+="¶p¶";		result+=picture->getPath();		}
	if(isCont == true){
		result+="¶c¶";
		result+=contact->getFirstName();	result+='¶';
		result+=contact->getLastName();		result+='¶';
		result+=contact->getPhoneNumber();	result+='¶';
		result+=contact->getEmail();
	}
	return result;
}
