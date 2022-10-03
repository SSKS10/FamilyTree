#include <bits/stdc++.h>
using namespace std;

class Person
{
	string name;
	string gender;
	vector<Person*> children;
	vector<Person*> spouse;

	public:
	Person()
	{
		this->name = "";
		this->gender = "";
	}

	Person(string name)
	{
		this->name = name;
		this->gender = "";
	}

	Person(string name, string gender)
	{
		this->name = name;
		this->gender = gender;
	}

	void setName(string name)
	{
		this->name = name;
	}

	string getName()
	{
		return this->name;
	}

	void setGender(string gender)
	{
		this->gender = gender;
	}

	string getGender()
	{
		return this->gender;
	}

	void setChildren(Person* child)
	{
		this->children.push_back(child);
	}

	void setSpouse(Person* person)
	{
		this->spouse.push_back(person);
	}

	vector<Person*> getChildren()
	{
		return this->children;
	}

	vector<Person*> getSpouse()
	{
		return this->spouse;
	}

	string decideGender(string relation)
	{
		if(relation == "father" || relation == "son" || relation == "husband" || relation == "brother")
			return "M";
		else
			return "F";
	}
};