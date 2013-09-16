// See NodeManager.h for documentation.
#include "NodeManager.h"

// Initialize pointers to null, initialize node codes, set all counts to zero, and create node structure.
NodeManager::NodeManager(string dbPath="Quasar.dat") : head(NULL), current(NULL), tail(NULL)
{
	this->nodeDBPath = dbPath;
	this->lastDocument = NULL;
	this->lastWebsite = NULL;
	this->lastPicture = NULL;
	this->lastContact = NULL;
	// Set counts to zero
	this->documentCount = 0;
	this->websiteCount = 0;
	this->pictureCount = 0;
	this->contactCount = 0;
	this->totalNodeCount = 0;
	makeHeadTail(); //creates head and tail nodes and assigns last nodes
	current = head; // sets outOfBounds condition
	// load savefile and create node structure
	_loadFile(dbPath);
}

NodeManager::~NodeManager()
{
	current = head;
	while(current != tail)
		deleteNode(current);
	delete current;
	delete tail;
}

/*
 * Saves node info to a text file.
 */
/*void NodeManager::saveNodeStructure()
{
	fstream fout;
	fout.open("C:\\Users\\Douglas\\Desktop\\QuasarSave.txt", fstream::out);
	if(fout.is_open())
	{
		current = head->next;
		// traverse the list and save all nodes in their respective form
		while(!outOfBounds())
		{			
			fout << current->getNodeCode() << endl;
			fout << current->getTitle() << endl;
			fout << current->getDescription() << endl;
			fout << current->getDate() << endl;
			fout << current->getKeywords() << endl;

			if(current->document != NULL)
			{
				fout << current->document->getPath() << endl;
			}
			if(current->website != NULL)
			{
				fout << current->website->getSiteURL() << endl;
			}
			if(current->picture != NULL)
			{
				fout << current->picture->getPath() << endl;
			}
			if(current->contact != NULL)
			{
				fout << current->contact->getFirstName() << endl;
				fout << current->contact->getLastName() << endl;
				fout << current->contact->getPhoneNumber() << endl;
				fout << current->contact->getEmail() << endl;
			}

			current = current->next;
		}
		fout.close();
	}
	else
		cout << "error in saveNodeStructure() opening save file." << endl;
}*/

// Save all entries to a file.
void NodeManager::_saveNodeStructure()
{
	fstream fout;
	fout.open(nodeDBPath, fstream::out);
	if(fout.is_open()){
		current = head->next;
		while(!outOfBounds()){
			fout << current->getOutput() << endl;
			current = current->next;
		}
		fout.close();
	}
	else
		cout << "error openning file\n";
}

/*
 * Loads a file from a previous save.
 *
 * Expects save file as:
 * 	line 1 - nodeCode
 * 	line 2 - filepath
 *
 * 	Contact:
 * 	line 1 - nodeCode
 * 	line 2 - first name
 * 	line 3 - last name
 * 	line 4 - phone number
 * 	line 5 - email
 *
 */
/*void NodeManager::loadFile(string file)
{
	string temp;
	int nodeCode = 0;
	DocumentData *document;
	WebsiteData *website;
	PictureData *picture;
	ContactData *contact;
	string c[4] = { "first", "last", "phone", "email" };
	Node *node;
	string title;
	string description;
	string date;
	string keywords;

	ifstream fin(file.c_str());
	if(fin.is_open())
	{
		while(getline(fin,temp))
		{
			stringstream ss(temp);
			if(ss >> nodeCode && ss.eof())
			{
				getline(fin, title);	// node title
				getline(fin, description);	// node desc
				getline(fin, date);	// node date
				getline(fin, keywords);	// node keywords

				// create and load node
				node = new Node;
				node->setTitle(title);
				node->setDescription(description);
				node->setDate(date);
				node->setKeywords(keywords);

				getline(fin, temp);	// path or first name for data obj

				switch(nodeCode)
			   {
			   case 1:	// document data
				   document = new DocumentData(temp);
				   node->setNodeCode("1");
				   node->setNodeType(1);
				   node->document = document;
				   addNode(node);
				   documentCount++;
				   break;
			   case 10:	// website data
				   website = new WebsiteData(temp);
				   node->setNodeCode("10");
				   node->setNodeType(2);
				   node->website = website;
				   addNode(node);
				   websiteCount++;
				   break;
			   case 100:	// picture data
				   picture = new PictureData(temp);
				   node->setNodeCode("100");
				   node->setNodeType(4);
				   node->picture = picture;
				   addNode(node);
				   pictureCount++;
				   break;
			   case 1000:	// contact data
				   c[0] = temp;	// first name
				   getline(fin, temp);
				   c[1] = temp;	// last name
				   getline(fin, temp);
				   c[2] = temp;	// phone
				   getline(fin, temp);
				   c[3] = temp;	// email
				   contact = new ContactData(c[0], c[1], c[2], c[3]);
   				   node->setNodeCode("1000");
				   node->setNodeType(8);
   				   node->contact = contact;
   				   addNode(node);
   				   contactCount++;
				   break;
			   case 11:	// website document
				   cout << "its a website document\n";
				   break;
			   case 101:	// picture of a document (pdf)
				   cout << "its a picture document\n";
				   break;
			   case 111:	// website with a picture of a document
				   cout << "its a website with a picture of a document\n";
				   break;

			   default: cout << "invalid\n"; break;
			   }
			}
		}
	}
	else
		cout << "error opening file";
	fin.close();
}*/

void NodeManager::_loadFile(string filename="Quasar.dat")
{
	//create node
	Node *newNode;
	string temp;
	ifstream fin(filename);
	if(fin.is_open())
	{
		while(!fin.eof())
		{
			newNode = new Node();
			getline(fin, temp);		// read a line
			if(temp == "")
				continue;
			setNode(temp, newNode);	// set node properties
			_addNode(newNode);		// add it to the list
		}
	}
	fin.close();
}

// get the head node
Node* NodeManager::getHead()
{
	return this->head;
}

Node* NodeManager::getCurrentNode()
{
	return this->current;
}

// get the tail node
Node* NodeManager::getTail()
{
	return this->tail;
}

// get the last node with data
Node* NodeManager::getLast()
{
	return this->last;
}

void NodeManager::goFirst()
{
	current = head->next;
}

void NodeManager::goFirst(int index)
{
	switch(index){
	case 0: //All Categories
		current = head->next;
		break;
	case 1: //Documents
		current = head->nextDocument;
		break;
	case 2: //Websites
		current = head->nextWebsite;
		break;
	case 3: //Pictures
		current = head->nextPicture;
		break;
	case 4: //Contacts
		current = head->nextContact;
		break;
	default:
		current = head->next;
	}
}

void NodeManager::goNext()
{
	if(current && current->next)
		current = current->next;
	else current = last;
}

void NodeManager::goNext(int index)
{
	switch(index){
	case 0: //All Categories
		goNext();
		break;
	case 1: //Documents
		goNextDocument();
		break;
	case 2: //Websites
		goNextWebsite();
		break;
	case 3: //Pictures
		goNextPicture();
		break;
	case 4: //Contacts
		goNextContact();
		break;
	default:
		goNext();
	}
}

void NodeManager::goPrev()
{
	if(current->prev)
		current = current->prev;
}

void NodeManager::goLast()
{
	if(tail->prev != NULL)
		current = tail->prev;
}

void NodeManager::goNextDocument()
{
	if(current->document != NULL)	// we're at a doc, go next doc
		current = current->nextDocument;
}

void NodeManager::goPrevDocument()
{
	if(current->prevDocument != NULL)
		current = current->prevDocument;
}

void NodeManager::goNextWebsite()
{
	if(current->website != NULL)	// we're at a web, go next web
		current = current->nextWebsite;
}

void NodeManager::goPrevWebsite()
{
	if(current->prevWebsite != NULL)
		current = current->prevWebsite;
}

void NodeManager::goNextPicture()
{
	if(current->picture != NULL)	// we're at a pic, go next pic
		current = current->nextPicture;
}

void NodeManager::goPrevPicture()
{
	if(current->prevPicture != NULL)
		current = current->prevPicture;
}

void NodeManager::goNextContact()
{
	if(current->contact != NULL)	// we're at a contact, go next
		current = current->nextContact;
}

void NodeManager::goPrevContact()
{
	if(current->prevContact != NULL)
		current = current->prevContact;
}

// adds a node to the end of the list and sets current to it.
void NodeManager::addNode(Node *newNode)
{
	if(head == NULL && tail == NULL)	// first node
	{
		head = newNode;
		tail = head;
		current = head;

		// assign head node's data to its proper type
		if(newNode->document != NULL)
		{
			head->nextDocument = newNode;
			newNode->prevDocument = head;
			lastDocument = newNode;
		}
		if(newNode->website != NULL)
		{
			head->nextWebsite = newNode;
			newNode->prevWebsite = head;
			lastWebsite = newNode;
		}
		if(newNode->picture != NULL)
		{
			head->nextPicture = newNode;
			newNode->prevPicture = head;
			lastPicture = newNode;
		}
		if(newNode->contact != NULL)
		{
			head->nextContact = newNode;
			newNode->prevContact = head;
			lastContact = newNode;
		}
	}
	else	// insert at the end of the list
	{
		tail->next = newNode;
		newNode->prev = tail;

		// assign newNode's data pointer
		if(newNode->document != NULL)
		{
			if(lastDocument == NULL)	// if no nodes with document data, set current to new
				lastDocument = newNode;
			else
			{
				// else make the currentDoc point to the next and update the currentDoc ptr
				lastDocument->nextDocument = newNode;
				newNode->prevDocument = lastDocument;
				lastDocument = newNode;
			}

		}
		if(newNode->website != NULL)
		{
			if(lastWebsite == NULL)
				lastWebsite = newNode;
			else
			{
				lastWebsite->nextWebsite = newNode;
				newNode->prevWebsite = lastWebsite;
				lastWebsite = newNode;
			}
		}
		if(newNode->picture != NULL)
		{
			if(lastPicture == NULL)
				lastPicture = newNode;
			else
			{
				lastPicture->nextPicture = newNode;
				newNode->prevPicture = lastPicture;
				lastPicture = newNode;
			}
		}
		if(newNode->contact != NULL)
		{
			if(lastContact == NULL)
				lastContact = newNode;
			else
			{
				lastContact->nextContact = newNode;
				newNode->prevContact = lastContact;
				lastContact = newNode;
			}
		}
		tail = tail->next;
		current = tail;
	}
	totalNodeCount++;
}

void NodeManager::decrementDocumentCount()
{
	if(documentCount > 0)
		documentCount--;
	else
		documentCount = 0;
}

void NodeManager::decrementWebsiteCount()
{
	if(websiteCount > 0)
		websiteCount--;
	else
		websiteCount = 0;
}

void NodeManager::decrementPictureCount()
{
	if(pictureCount > 0)
		pictureCount--;
	else
		pictureCount = 0;
}

void NodeManager::decrementContactCount()
{
	if(contactCount > 0)
		contactCount--;
	else
		contactCount = 0;
}

void NodeManager::decrementTotalNodeCount()
{
	if(totalNodeCount > 0)
		totalNodeCount--;
	else
		totalNodeCount = 0;
}

// delete the specified node
void NodeManager::deleteNode(Node* nodeToDel)
{
	if(nodeToDel->next && nodeToDel->prev){ //condition implies node in linked list and not head or tail
		nodeToDel->prev->next = nodeToDel->next;
		nodeToDel->next->prev = nodeToDel->prev;
		if(nodeToDel->document){
			nodeToDel->prevDocument->nextDocument = nodeToDel->nextDocument;
			nodeToDel->nextDocument->prevDocument = nodeToDel->prevDocument;
			decrementDocumentCount();
		}
		if(nodeToDel->website){
			nodeToDel->prevWebsite->nextWebsite = nodeToDel->nextWebsite;
			nodeToDel->nextWebsite->prevWebsite = nodeToDel->prevWebsite;
			decrementWebsiteCount();
		}
		if(nodeToDel->picture){
			nodeToDel->prevPicture->nextPicture = nodeToDel->nextPicture;
			nodeToDel->nextPicture->prevPicture = nodeToDel->prevPicture;
			decrementPictureCount();
		}
		if(nodeToDel->contact){
			nodeToDel->prevContact->nextContact = nodeToDel->nextContact;
			nodeToDel->nextContact->prevContact = nodeToDel->prevContact;
			decrementContactCount();
		}
	}
	decrementTotalNodeCount();
	if(last == nodeToDel){
		tail->prev = last = nodeToDel->prev;
		tail->prevDocument = lastDocument = nodeToDel->prevDocument;
		tail->prevWebsite = lastWebsite = nodeToDel->prevWebsite;
		tail->prevPicture = lastPicture = nodeToDel->prevPicture;
		tail->prevContact = lastContact = nodeToDel->prevContact;
	}
	delete nodeToDel;
}

void NodeManager::makeHeadTail(){
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
		head->nextDocument = tail;
		head->nextWebsite = tail;
		head->nextPicture = tail;
		head->nextContact = tail;
		tail->prevDocument = head;
		tail->prevWebsite = head;
		tail->prevPicture = head;
		tail->prevContact = head;
		last = head;
		lastDocument = head;
		lastWebsite = head;
		lastPicture = head;
		lastContact = head;
}

void NodeManager::_addNode(Node *aNode){
	aNode->setIndex(totalNodeCount++);
	last->next = aNode;
	aNode->next = tail;
	aNode->prev = last;
	tail->prev = aNode;
	if(aNode->document){
		if(head->nextDocument == tail)
			head->nextDocument = aNode;
		lastDocument->nextDocument = aNode;
		aNode->nextDocument = tail;
		aNode->prevDocument = lastDocument;
		tail->prevDocument = aNode;
		lastDocument = aNode;
		documentCount++;
	}
	if(aNode->website){
		if(head->nextWebsite == tail)
			head->nextWebsite = aNode;
		lastWebsite->nextWebsite = aNode;
		aNode->nextWebsite = tail;
		aNode->prevWebsite = lastWebsite;
		tail->prevWebsite = aNode;
		lastWebsite = aNode;
		websiteCount++;
	}
	if(aNode->picture){
		if(head->nextPicture == tail)
			head->nextPicture = aNode;
		lastPicture->nextPicture = aNode;
		aNode->nextPicture = tail;
		aNode->prevPicture = lastPicture;
		tail->prevPicture = aNode;
		lastPicture = aNode;
		pictureCount++;
	}
	if(aNode->contact){
		if(head->nextContact == tail)
			head->nextContact = aNode;
		lastContact->nextContact = aNode;
		aNode->nextContact = tail;
		aNode->prevContact = lastContact;
		tail->prevContact = aNode;
		lastContact = aNode;
		contactCount++;
	}
	last = aNode;
}

int NodeManager::getDocumentCount()
{
	return this->documentCount;
}

int NodeManager::getWebsiteCount()
{
	return this->websiteCount;
}

int NodeManager::getPictureCount()
{
	return this->pictureCount;
}

int NodeManager::getContactCount()
{
	return this->contactCount;
}

int NodeManager::getTotalNodeCount()
{
	return this->totalNodeCount;
}

char NodeManager::intToHEXChar(int value){
	if(value / 10)
		return (char)(65 + value % 10);
	else
		return (char)(48 + value);
}
int NodeManager::HEXCharToInt(char hexValue){
	int value = (int)hexValue;
	if(value >= 97) value-=32;
	if(value >= 65)
		return (value-55);
	else
		return (value-48);
}

void NodeManager::setNode(string input, Node* aNode)
{
	int value = HEXCharToInt(input[0]);
	if(value < 0 || value > 15) return;
	aNode->setNodeType(input[0]);

	size_t pos, nextPos, length;
	//This code has a lot of error handling but, hopefully, will make the db more robust
	
	//Primary Node properties
	pos = input.find('¶');
	nextPos = input.find('¶',pos+1);
	length = (nextPos-pos)-1;
	if(pos==string::npos) return;
	if(nextPos==string::npos) { aNode->setTitle(input.substr(pos+1)); return; }
	else aNode->setTitle(input.substr(pos+1,length));

	pos = nextPos;
	nextPos = input.find('¶',pos+1);
	length = (nextPos-pos)-1;
	if(pos==string::npos) return;
	if(nextPos==string::npos) { aNode->setDescription(input.substr(pos+1)); return; }
	else aNode->setDescription(input.substr(pos+1,length));

	pos = nextPos;
	nextPos = input.find('¶',pos+1);
	length = (nextPos-pos)-1;
	if(pos==string::npos) return;
	if(nextPos==string::npos) { aNode->setDate(input.substr(pos+1)); return; }
	else aNode->setDate(input.substr(pos+1,length));

	pos = nextPos;
	nextPos = input.find('¶',pos+1);
	length = (nextPos-pos)-1;
	if(pos==string::npos) return;
	if(nextPos==string::npos) { aNode->setKeywords(input.substr(pos+1)); return; }
	else aNode->setKeywords(input.substr(pos+1,length));

	//Check for DataObject fields
	pos = nextPos;
	nextPos = input.find('¶',pos+1);
	length = (nextPos-pos)-1;
	if(length!=1) return; //condition would imply improperly formatted fields
	if(input[pos+1] == 'd'){ //document 
		if(!aNode->document) aNode->document = new DocumentData;
		aNode->set_isDoc();
		pos = nextPos;
		nextPos = input.find('¶',pos+1);
		length = (nextPos-pos)-1;
		if(pos==string::npos) return;
		if(nextPos==string::npos) { aNode->document->setPath(input.substr(pos+1)); return; }
		else aNode->document->setPath(input.substr(pos+1,length));
		pos = nextPos;
		nextPos = input.find('¶',pos+1);
		length = (nextPos-pos)-1;
	}
	if(length!=1) return;
	if(input[pos+1] == 'w'){ //website
		if(!aNode->website) aNode->website = new WebsiteData;
		aNode->set_isWeb();
		pos = nextPos;
		nextPos = input.find('¶',pos+1);
		length = (nextPos-pos)-1;
		if(pos==string::npos) return;
		if(nextPos==string::npos) { aNode->website->setSiteURL(input.substr(pos+1)); return; }
		else aNode->website->setSiteURL(input.substr(pos+1,length));
		pos = nextPos;
		nextPos = input.find('¶',pos+1);
		length = (nextPos-pos)-1;
	}
	if(length!=1) return;
	if(input[pos+1] == 'p'){ //picture
		if(!aNode->picture) aNode->picture = new PictureData;
		aNode->set_isPic();
		pos = nextPos;
		nextPos = input.find('¶',pos+1);
		length = (nextPos-pos)-1;
		if(pos==string::npos) return;
		if(nextPos==string::npos) { aNode->picture->setPath(input.substr(pos+1)); return; }
		else aNode->picture->setPath(input.substr(pos+1,length));
		pos = nextPos;
		nextPos = input.find('¶',pos+1);
		length = (nextPos-pos)-1;
	}
	if(length!=1) return;
	if(input[pos+1] != 'c') return;
	if(!aNode->contact) aNode->contact = new ContactData;
	aNode->set_isCont();
	pos = nextPos;
	nextPos = input.find('¶',pos+1);
	length = (nextPos-pos)-1;
	if(pos==string::npos) return;
	if(nextPos==string::npos) { aNode->contact->setFirstName(input.substr(pos+1)); return; }
	else aNode->contact->setFirstName(input.substr(pos+1,length));
	
	pos = nextPos;
	nextPos = input.find('¶',pos+1);
	length = (nextPos-pos)-1;
	if(pos==string::npos) return;
	if(nextPos==string::npos) { aNode->contact->setLastName(input.substr(pos+1)); return; }
	else aNode->contact->setLastName(input.substr(pos+1,length));
	
	pos = nextPos;
	nextPos = input.find('¶',pos+1);
	length = (nextPos-pos)-1;
	if(pos==string::npos) return;
	if(nextPos==string::npos) { aNode->contact->setPhoneNumber(input.substr(pos+1)); return; }
	else aNode->contact->setPhoneNumber(input.substr(pos+1,length));

	pos = nextPos;
	nextPos = input.find('¶',pos+1);
	length = (nextPos-pos)-1;
	if(pos==string::npos) return;
	if(nextPos==string::npos) { aNode->contact->setEmail(input.substr(pos+1)); return; }
	else aNode->contact->setEmail(input.substr(pos+1,length));

	//this version assumes no other data will be read in
}
