#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;

class MyExceptions : public exception {
	public:
		MyExceptions() : msg("Bad Input. Please read README.txt and try again."){}

		void showErr(){
			cout << msg << endl;
		}
	
	private:
		string msg;
};

#endif