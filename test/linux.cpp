/*
	Test the linux library
*/

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <cstring>


using namespace std;

void *handle;
typedef int (*RVExtension_fnc_ptr)(char*, int, const char*);
int (*RVExtension)(char *, int, const char*);

/*
	-----------------------------------------------------------------------------------------------------
*/
string execute(string command) {
	char *output = new char[4096];
	char *function = new char[2048];

	snprintf(function, 2048, command.c_str());
	RVExtension(output, 4096, function);

	string result(output);
	delete[] output;
	delete[] function;

	return result;
}

int load(string filename) {
	char *error;
	handle = dlopen (filename.c_str(), RTLD_LAZY);
	if (!handle) {
		//fputs (dlerror(), stderr);
		return 1;
	}

	RVExtension = (RVExtension_fnc_ptr)dlsym(handle, "RVExtension");
	if ((error = dlerror()) != NULL) {
		//fputs(error, stderr);
		return 1;
	}

	return 0;
}
/*
	-----------------------------------------------------------------------------------------------------
*/


int main( int argc, const char* argv[] ) {
	if (load("./mapmaker.so") > 0)
		if (load("../mapmaker.so") > 0) {
			cout << "Unable to properly load mapmaker.so" << endl;
			exit(1);
		}

	cout << "Library invoked on " << execute("datetime") << endl << endl;

	if (argc > 1) {
		char command[1024] = "";
		strcat(command, "openRead;");
		strcat(command, argv[1]);
		execute(command);
		string result = execute("read");
		while (result != "[]") {
			cout << result << endl;
			result = execute("read");
		}
	} else {
		string command;
		cout << "> ";
		getline(cin, command);
		while (!command.empty()) {
			cout << execute(command) << endl;
			cout << "> ";
			getline(cin, command);
		}
	}

	return 0;
}