#include <iostream>

using namespace std;

class Base{
public:
	int tag;

	Base(int t)
	: tag(t)
	{
	}
	virtual ~Base(){};

	int getTag(){
		return tag;
	}

	virtual string getLex() =0;
	virtual int getLex()=0;
};

class Derived : public Base{
public:
	string lex;

	Derived(int t, string l) : Base(t), lex(l){

	}


	string getLex(){
		return lex;
	}

};

class Derived2 : public Base{
public:
	int lex;

	Derived2(int t, int l) : Base(t), lex(l)
	{

	}


	int getLex(){
		return lex;
	}

};



int main(){
	Base b(1);
	Derived d(2,"bunda");
	cout << "B TAG " << b.getTag() << endl;
	b = d;
	cout << "B = D TAG " << b.getTag() << endl;
	cout << "++++++++++++++++"  << endl;
	Base *ptr = &b;
	cout << "ptr = &b TAG " << ptr->getTag() << endl;
	ptr = &d;
	cout << "ptr = &D LEX " << ptr->getLex() << endl;

}
