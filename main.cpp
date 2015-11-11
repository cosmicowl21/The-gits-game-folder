#include <iostream>
#include<string>

using namespace std;

int main()
{
	string name;
	int age;
	cout << "Hello there how are you." << endl;
	cout << "Please enter your name" << " " << endl;
	cin >> name;
	cout << "your name is " << " " << name << endl;
	cout << name << " " << "Please enter your age" << endl;
	cin >> age;
	cout << "Your age is " << " " << age << endl;
	if (age <= 10)
	{
		cout << "sorry you cant play along" << endl;



	}
	else
	{
		cout << "yay you can play" << endl;
	}
	system("PAUSE");
	return 0;
}