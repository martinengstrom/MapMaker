/*
	MapMaker plugin
	Purpose:
	Get a pre-formatted string from arma and save it to a text file
	Retreive line from file and replace ; with , and add [ and ] to the end.
	A single procedure call returns a single line, maintain a file pointer and use getNext
	
	A function to create a file with filename
	Append a line to the current file
	Close the current file
	A function to open a file
	A function to list files
	A function to delete a file
*/

/*
	NOTES FOR CROSS COMPAT.
	Check for GCC or MSVS to change between sprintf_s and snprintf
*/

// Perhaps we shouldnt use this and use the safe msvs functions instead
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/* Make a platform check here */
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0601
#include <windows.h>
#include "common.h"
#include "mapmanager.h"

using namespace std;

/* global var */
MapManager *mapManager = NULL;

extern "C" int APIENTRY DllMain(HINSTANCE hinstDLL, DWORD ul_reason_for_call, LPVOID lpvReserved)
{

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

/* Note for gcc based compilers prepend an underscore to the exported function */
string not_implemented() {
	return "[]";
}

void write_response(char *output, int outputSize, const string& data) {
	//nprintf(output, outputSize, "%s", data);
	sprintf_s(output, outputSize, "%s", data);
}

extern "C" void __stdcall RVExtension(char *output, int outputSize, const char *function)
{	
	/* init MapManager */
	if (!mapManager)
		mapManager = new MapManager();

	string s_function(function);

	/* list - lists all files (takes no arguments) */
	if (s_function == "list") {
		write_response(output, outputSize, not_implemented());
	}
	/* read - reads one line (takes no arguments) */
	else if (s_function == "read") {

	}
	else {
		/* Format of function should be function name;data*/
		string function_ = s_function.substr(0, s_function.find(';'));
		string data = s_function.substr(s_function.find(';') + 1, s_function.length());

		/* open - opens a file or creates one if it doesnt exist */
		if (function_ == "open") {
			if (mapManager->open(data))
				write_response(output, outputSize, "[true]");
			else
				write_response(output, outputSize, "[false]");
		}
		/* write - appends a line to the current opened file */
		else if (function_ == "write") {

		}
		/* close - closes the current opened file */
		else if (function_ == "close") {

		}
		/* delete - deletes a file */
		else if (function_ == "delete") {

		}
		else {
			/* Bad call. return an empty SQF array */
			write_response(output, outputSize, not_implemented());
		}
	}
}