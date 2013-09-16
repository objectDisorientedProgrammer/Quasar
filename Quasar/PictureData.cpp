// See PictureData.h for documentation.
#include "PictureData.h"

PictureData::PictureData(string strPath)
{
	this->path = sanitize_str(strPath);
}

PictureData::~PictureData()
{
}

string PictureData::sanitize_str(string input){
	string result;
	for(string::iterator iter=input.begin(); iter!=input.end(); iter++)
		if(*iter != '¶') result += *iter;
	return result;
}
