/*----------------------------------------------
	
	Filename:  WebsiteData.h
	
	Author : Douglas Chidester
	Created: April 22, 2013

	Last Update:  4/28/2013 DC
				  5/2/2013 sc

	Descrip:  WebsiteData class properties
	siteURL - URL to the website



----------------------------------------------*/

#ifndef WEBSITEDATA_H
#define WEBSITEDATA_H

#include <string>
using namespace std;

class WebsiteData
{
public:
	WebsiteData(string="");
	~WebsiteData();

	//set method
	void setSiteURL(string input)	{ this->siteURL = sanitize_str(input); }
	
	//get method
	string getSiteURL()	{ return this->siteURL; }

private:
	string siteURL;

	string sanitize_str(string);
};

#endif