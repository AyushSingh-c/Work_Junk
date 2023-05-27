#include <iostream>
#include <span>

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Hello world!" << endl;
	
	
	cout << argc << endl;

	for(int i=0;i<argc;i++)
	{
		cout<<argv[i]<<' '; 
	}

}