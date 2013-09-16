// See WebsiteData.h for documentation.
#include "WebsiteData.h"

WebsiteData::WebsiteData(string url)
{
	this->siteURL = sanitize_str(url);
}

WebsiteData::~WebsiteData()
{
}

string WebsiteData::sanitize_str(string input){
	string result;
	for(string::iterator iter=input.begin(); iter!=input.end(); iter++)
		if(*iter != '¶') result += *iter;
	return result;
}
