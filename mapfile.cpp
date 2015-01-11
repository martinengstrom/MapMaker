#include "mapfile.h"

MapFile::MapFile(const string& filename) {
	/* Open a file, if it doesnt exist then create it. */
	std::FILE* yolo = fopen(filename.c_str(), "a+");
}

MapFile::~MapFile() {

}

int MapFile::write(const string& data) {
	return 0;
}