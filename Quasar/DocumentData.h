/*----------------------------------------------
	
	Filename: DocumentData.h
	Author:   Douglas Chidester
	Created: April 22, 2013

	Last Update: 4/28/2013  DC
	             5/2/2013 sc

	Descrip:  DocumentData class properties
	   path - directory path to the document
	pageNum - page number inside the document
	pubDate - publication date
	 author - author of the document
	

----------------------------------------------*/

#ifndef	DOCUMENTDATA_H
#define DOCUMENTDATA_H

#include <string>
using namespace std;

class DocumentData
{
public:
	DocumentData(string="");
	~DocumentData();

	//set methods
	void setPath(string input)	{ this->path = sanitize_str(input); }
	void setPageNum(string input){ this->pageNum = sanitize_str(input); }
	void setPubDate(string input){ this->pubDate=sanitize_str(input); }
	void setAuthor(string input){ this->author=sanitize_str(input); }
	void setAux(string input){ this->aux = sanitize_str(input); }

	//get methods
	string getPath() { return this->path; }
	string getPageNum() { return this->pageNum; }
	string getPubDate() { return this->pubDate; }
	string getAuthor() { return this->author; }
	string getAux() { return this->aux; }

private:
	string path;
	string pageNum;
	string pubDate;
	string author;
	string aux;
	string sanitize_str(string);
};

#endif
