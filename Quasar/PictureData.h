/*----------------------------------------------

    Filename: PictureData.h

	Author : Douglas Chidester
	Created: April 22, 2013

	Last Update: 4/28/2013 DC
	             5/2/2013 sc

	Descrip:  PictureData class properties
	publisher - publisher of the picture
	path      - directory path to picture file

----------------------------------------------*/

#ifndef PICTUREDATA_H
#define PICTUREDATA_H

#include <string>
using namespace std;

class PictureData
{
public:
	PictureData(string="");
	~PictureData();

	//set methods
	void setPublisher(string input){publisher = input;}
	void setPath(string input){this->path = sanitize_str(input);}
	void setAux(string input){aux = input;}
	void setWidth(int w)	{ this->width = w; }
	void setHeight(int h)	{ this->height = h; }
	
	//get methods
	string getPublisher(){return publisher;}
	string getPath(){return path;}
	string getAux(){return aux;}
	int getWidth()		{ return width; }
	int getHeight()	{ return height; }

private:
	string publisher;
	string path;
	string aux;
	int width;
	int height;

	string sanitize_str(string);
};

#endif
