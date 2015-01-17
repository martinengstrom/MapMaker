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

	WHEN COMPILING WITH MINGW/GCC
	Change sprintf_s to snprintf
	If on windows, change RVExtension to _RVExtension
*/

/* Make a platform check here */
#include <boost/predef.h>

#if BOOST_OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0601
#include <windows.h>
#elif BOOST_OS_LINUX
#endif

#define PLUGIN_VERSION "0.3"

#include "common.h"
#include "mapmanager.cpp"
#include "time.cpp"


using namespace std;

/* global var */
MapManager *mapManager = NULL;

#if BOOST_OS_WINDOWS
extern "C" int APIENTRY DllMain(HINSTANCE hinstDLL, DWORD ul_reason_for_call, LPVOID lpvReserved)
{

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		//break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif

string not_implemented() {
	return "[]";
}

void write_response(char *output, int outputSize, const string& data) {
	#if BOOST_COMP_MSVC
		sprintf_s(output, outputSize-1, "%s", data.c_str());
	#elif BOOST_COMP_GNUC
		snprintf(output, outputSize-1, "%s", data.c_str());
	#endif
}


/* A little messy, declare the exported function depending on compiler and OS */
#if BOOST_OS_WINDOWS
	#if BOOST_COMP_GNUC
		extern "C" __declspec(dllexport) void __stdcall _RVExtension(char *output, int outputSize, const char *function)
	#elif BOOST_COMP_MSVC
		extern "C" __declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function)
	#endif
#elif BOOST_OS_LINUX
	extern "C" void RVExtension(char *output, int outputSize, const char *function)
#endif
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
		string data = mapManager->read();	// reads the current line
		write_response(output, outputSize, data);
	}
	/* close - closes the current opened file (takes no arguments) */
	else if (s_function == "close") {
		mapManager->close();
		write_response(output, outputSize, "[true]");
	}
	/* Report a version to ARMA so scripts can detect our presence */
	else if (s_function == "version") {
		write_response(output, outputSize, PLUGIN_VERSION);
	}
	else if (s_function == "datetime") {
		write_response(output, outputSize, MultiPlatform::getDate());
	}
	else {
		/* Format of function should be function name;data*/
		string function_ = s_function.substr(0, s_function.find(';'));
		string data = s_function.substr(s_function.find(';') + 1, s_function.length());

		/* open - opens a file or creates one if it doesnt exist */
		if (function_ == "openRead") {
			if (mapManager->openRead(data) == 0)
				write_response(output, outputSize, "[true]");
			else
				write_response(output, outputSize, "[false]");
		}
		if (function_ == "openWrite") {
			if (mapManager->openWrite(data) == 0)
				write_response(output, outputSize, "[true]");
			else
				write_response(output, outputSize, "[false]");
		}
		/* write - appends a line to the current opened file */
		else if (function_ == "write") {
			if (mapManager->write(data) == 0)
				write_response(output, outputSize, "[true]");
			else
				write_response(output, outputSize, "[false]");
		}
		/* delete - deletes a file */
		else if (function_ == "delete") {
			write_response(output, outputSize, not_implemented());
		}
		else {
			/* Bad call. return an empty SQF array */
			write_response(output, outputSize, not_implemented());
		}
	}
}
