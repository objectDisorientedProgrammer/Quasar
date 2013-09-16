// See ContactData.h for documentation.
#include "ContactData.h"

ContactData::ContactData(string firstName="", string lastName="", string phone="", string email="")
{
	this->firstName = sanitize_str(firstName);
	this->lastName = sanitize_str(lastName);
	this->phoneNumber = sanitize_str(phone);
	this->email = sanitize_str(email);
}

ContactData::~ContactData()
{
}

string ContactData::sanitize_str(string input){
	string result;
	for(string::iterator iter=input.begin(); iter!=input.end(); iter++)
		if(*iter != '¶') result += *iter;
	return result;
}
