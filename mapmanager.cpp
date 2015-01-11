#include "mapmanager.h"

MapManager::MapManager() {
	//thread_running = false;
	//	em = new EventManager;
}

MapManager::~MapManager() {
	//delete em;
	//delete queueThread;
}

int MapManager::open(const string& filename) {
	if (!mapFile)
		mapFile = new MapFile();
	else {
		delete mapFile;
		mapFile = new MapFile();
	}

	return mapFile->open(filename);
}

int MapManager::remove(const string& filename) {
	return 0;
}

int MapManager::write(const string& data) {
	if (mapFile) {
		return mapFile->write(data);
	} else
		return 1;
}

int MapManager::close() {
	if (mapFile)
		mapFile->close();
	return 0;
}

string MapManager::read() {
	/* FORMAT THE RESULT FORM MAPFILE! */

	if (mapFile) {
		string res = "[" + mapFile->read() + "]";
		replaceAll(res, ";", ",");
		return res;
	} 
	else
		return "";
}

// http://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string/3418285#3418285
void MapManager::replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}