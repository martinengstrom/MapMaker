using namespace std;
#include "common.h"
#include "mapfile.h"

class MapManager {
public:
	MapManager();
	~MapManager();

	int open(const string& filename);
	int remove(const string& filename);
	int write(const string& data);
	int close();

private:
	MapFile *mapFile = NULL;
};
