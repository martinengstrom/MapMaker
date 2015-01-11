#include "mapfile.h"

MapFile::MapFile() {
}

MapFile::~MapFile() {

}

int MapFile::open(const string& filename) {
	/* Open a file, if it doesnt exist then create it. */
	std::FILE* yolo = fopen(filename.c_str(), "a+");
	return 0;
}


int MapFile::write(const string& data) {
	return 0;
}