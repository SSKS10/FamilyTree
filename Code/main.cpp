#include <bits/stdc++.h>
#include "familytree.cpp"
using namespace std;

int main()
{
	FamilyTree F;
	while(1)
	{
		try
		{
			//Reading the input string
			string input_string;
			getline(cin, input_string);

			//Calling FamilyTree method to decide action based on input string
			cout<<F.inputDecide(input_string);
		}
		catch(...)
		{
			cout<<"Exception Occured!";
			break;
		}
	}
	return 0;
}

