/*
	TODO: use C++ ifstream instead of C fopen
*/

#include "mapfile.h"

MapFile::MapFile() {
}

MapFile::~MapFile() {

}

int MapFile::open(const string& filename) {
	fp = fopen(filename.c_str(), "a+");
	if (!fp)
		return 1;

	fseek(fp, 0, SEEK_SET);
	return 0;
}


int MapFile::write(const string& data) {
	if (!fp)
		return 1;

	try {
		long current_pos = ftell(fp);
		std::fseek(fp, 0, SEEK_END);
		string tmp = data + '\n';
		fputs(tmp.c_str(), fp);
		fseek(fp, current_pos, SEEK_SET);
		return 0;
	}
	catch (int e) {
		return 1;
	}
}

void MapFile::close() {
	if (fp) {
		fclose(fp);
		fp = NULL;
	}
}

string MapFile::read() {
	// Read a single line
	if (fp) {
		string buffer;

		/*
		char *lineBuffer = (char *)malloc(sizeof(char) * 4096);
		if (lineBuffer == NULL)
			return "";
		*/

		char ch = fgetc(fp);
		while ((ch != '\n') && (ch != EOF)) {
			buffer += ch;
			ch = fgetc(fp);
		}

		return buffer;
	}
	else {
		return "";
	}
}