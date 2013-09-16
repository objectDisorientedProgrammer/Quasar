// See DocumentData.h for documentation.
#include "DocumentData.h"

DocumentData::DocumentData(string pathToFile)
{
	this->path = sanitize_str(pathToFile);
}

DocumentData::~DocumentData()
{
}

string DocumentData::sanitize_str(string input){
	string result;
	for(string::iterator iter=input.begin(); iter!=input.end(); iter++)
		if(*iter != '¶') result += *iter;
	return result;
}
