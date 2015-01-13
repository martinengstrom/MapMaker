using namespace std;
#include "common.h"
#include "mapfile.h"

class MapManager {
public:
	MapManager();
	~MapManager();

	int openRead(const string& filename);
	int openWrite(const string& filename);
	int remove(const string& filename);
	int write(const string& data);
	string read();
	int close();

private:
	int open(bool write, const string& filename);
	MapFile *mapFile = NULL;
	void replaceAll(std::string& str, const std::string& from, const std::string& to);
};
