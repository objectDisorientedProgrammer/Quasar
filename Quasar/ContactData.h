/*----------------------------------------------
	ContactData.h
	Author : Douglas Chidester
	Created: April 22, 2013

	Last Update: 5/17/2013 DC
				 5/2/2013 sc

	Descrip:  ContactData class properties

	firstName   - first name
	lastName    - last name
	phoneNumber - phone number
	email       - email address


----------------------------------------------*/

#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include <string>
using namespace std;

class ContactData
{
public:
	ContactData() {}
	ContactData(string, string, string, string);
	~ContactData();

	// set methods
	void setFirstName(string input){ this->firstName = sanitize_str(input); }
	void setLastName(string input){ this->lastName = sanitize_str(input); }
	void setPhoneNumber(string input){ this->phoneNumber = sanitize_str(input); }
	void setEmail(string input){ this->email = sanitize_str(input); }
	void setAux(string input){ this->aux = sanitize_str(input); }

	//get functions
	string getFirstName(){return firstName;}
	string getLastName(){return lastName;}   
	string getPhoneNumber(){return phoneNumber;}
	string getEmail(){return email;}
	string getAux(){return aux;}

private:
	string firstName;
	string lastName;
	string phoneNumber;
	string email;
	string aux;

	string sanitize_str(string);
};

#endif