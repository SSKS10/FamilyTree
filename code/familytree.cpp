#include <bits/stdc++.h>
#include "person.cpp"
using namespace std;

class FamilyTree : public Person
{
	Person* head;
	Person* bufferPerson1;
	Person* bufferPerson2;
	string bufferRelation1, bufferRelation2;

	void setPartners(Person* person1, Person* person2)
	{
		person1->setSpouse(person2);
		person2->setSpouse(person1);
	}

	vector<string> splitstr(string str, char deli = ' ')
	{
	   vector<string> split;

	    for (int j = 0, k = 0; j < str.length(); j++) {
	        if (str[j] == deli) {
	            string ch = str.substr(k, j - k);
	            k = j+1;
	            split.push_back(ch);
	        }
	        if (j == str.length() - 1) {
	            string ch = str.substr(k, j - k+1);
	            split.push_back(ch);
	        }
	    }
	   return split;
	}

	Person* findPerson(Person* person,string name)
	{
		if(person->getName()==name)
			return person;

		vector<Person*> children = person->getChildren();
		for(int i=0;i<children.size();i++)
		{
			findPerson(children[i],name);
		}
		return NULL;
	}

	int getChildrenCount(string name, string gender)
	{
		set<string> child;
		Person* person = findPerson(this->head, name);

		if(person==NULL)
			return -1;

		vector<Person*> children = person->getChildren();
		for(int p=0; p<children.size();p++)
		{
			if(children[p]->getGender() == gender)
				child.insert(children[p]->getName());
		}
		return child.size();
	}

	int getSonCount(string name)
	{
		return getChildrenCount(name, "M");
	}

	int getDaughterCount(string name)
	{
		return getChildrenCount(name, "F");
	}

	int getWifeCount(string name)
	{
		Person* person = findPerson(this->head, name);
		if(person==NULL)
			return -1;

		return person->getSpouse().size();
	}

	int decideCount(vector<string> split)
	{
		string name = "";
		for(int i=4;i<split.size();i++)
		{
			name.append(split[i]);
			name.append(" ");
		}
		if(split[2]=="sons")
			return getSonCount(name);
		else if(split[2]=="daughters")
			return getDaughterCount(name);
		else if(split[2]=="wives")
			return getWifeCount(name);
	}

	Person* findFather(Person* person,string name, Person* father)
	{
		if(person->getName()==name)
			return father;

		vector<Person*> children = person->getChildren();
		for(int i=0;i<children.size();i++)
		{
			findFather(children[i], name, person);
		}
		return NULL;
	}

	Person* getFather(string name)
	{
		return findFather(this->head, name, NULL);
	}

	void addBufferPerson(vector<string> split)
	{
		string name="";
		for(int i=2;i<split.size();i++)
		{
			name.append(split[i]);
			name.append(" ");
		}

		if(bufferPerson1 == NULL)
			bufferPerson1 = new Person(name);
		else if(bufferPerson2 == NULL)
			bufferPerson2 = new Person(name);
		else
		{
			bufferPerson1 = new Person(name);
			bufferPerson2 = NULL;
		}
	}

	string addBufferPersonConnect(vector<string> split)
	{
		string name1="";
		int i=2;
		for(;i<split.size();i++)
		{
			if(split[i]=="as")
				break;
			name1.append(split[i]);
			name1.append(" ");
		}
		string relation = split[++i];
		string name2="";
		for(i=i+2;i<split.size();i++)
		{
			name2.append(split[i]);
			name2.append(" ");
		}
		
		if(bufferPerson1 == NULL || bufferPerson1->getName() != name1)
			bufferPerson1 = new Person(name1);
		else if(bufferPerson2 == NULL || bufferPerson2->getName() != name2)
			bufferPerson2 = new Person(name2);

		return relation;
	}

	string decideGender(string relation)
	{
		if(relation == "father" || relation == "son" || relation == "husband" || relation == "brother")
			return "M";
		else
			return "F";
	}
	
	public:
	FamilyTree()
	{
		this->head = NULL;
		bufferRelation1 = "";
		bufferRelation2 = "";
	}

	FamilyTree(Person* person)
	{
		this->head = new Person(person->getName(), person->getGender());
		bufferRelation1 = "";
		bufferRelation2 = "";
	}

	string inputDecide(string str)
	{
		vector<string> split;
		split = splitstr(str);

		if(split[1]=="add" && split[2]=="relationship")
		{
			if(bufferRelation1 == "")
				bufferRelation1 = split[3];
			else if(bufferRelation2 == "")
				bufferRelation2 = split[3];
			else
			{
				bufferRelation1 = "";
				bufferRelation2 = "";
			}
		}
		else if(split[1]=="add")
		{
			addBufferPerson(split);
			Person* P1 = new Person(this->bufferPerson1->getName(), this->bufferPerson1->getGender());
			if(this->head == NULL)
				this->head = P1;
		}

		if(split[1]=="connect")
		{
			string relation = addBufferPersonConnect(split);

			this->bufferPerson1->setGender(decideGender(relation));

			if(this->bufferRelation1 != relation)
				this->bufferPerson2->setGender(decideGender(this->bufferRelation1));
			else
				this->bufferPerson2->setGender(decideGender(this->bufferRelation2));

			if(relation == "son" || relation == "daughter")
			{
				Person* P1 = new Person(this->bufferPerson1->getName(), this->bufferPerson1->getGender());

				if(this->head->getName() == P1->getName())
				{
					this->head = new Person(this->bufferPerson2->getName(), this->bufferPerson2->getGender());
					this->head->setChildren(P1);
				}
				else
					findPerson(this->head, bufferPerson2->getName())->setChildren(P1);
			}
			else if(relation == "father" || relation == "mother")
			{
				Person* P2 = new Person(this->bufferPerson2->getName(), this->bufferPerson2->getGender());

				if(this->head->getName() == P2->getName())
				{	
					this->head = new Person(this->bufferPerson1->getName(), this->bufferPerson1->getGender());
					this->head->setChildren(P2);
				}
				else
					findPerson(this->head, this->bufferPerson1->getName())->setChildren(P2);
			}
			else if(relation == "husband" || relation == "wife")
			{
				Person* P1 = findPerson(this->head, this->bufferPerson1->getName());
				Person* P2 = findPerson(this->head, this->bufferPerson2->getName());
				if(P1 == NULL)
				P1 = new Person(this->bufferPerson1->getName(), this->bufferPerson1->getGender());
				if(P2 == NULL)
				P2 = new Person(this->bufferPerson2->getName(), this->bufferPerson2->getGender());
				setPartners(P1, P2);
			}

		}

		if(split[1]=="count")
		{
			int count = decideCount(split);
			stringstream stream;  
		  	stream<<count;  
		  	string strCount;  
		  	stream>>strCount;  
			return strCount;
		}
		else if(split[1]=="father")
		{
			string name = "";
			for(int i=3;i<split.size();i++)
			{
				name.append(split[i]);
				name.append(" ");
			}
			return getFather(name)->getName();
		}
		
		return "";
	}
};