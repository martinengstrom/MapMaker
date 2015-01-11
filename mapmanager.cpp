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
	return 0;
}

int MapManager::close() {
	return 0;
}