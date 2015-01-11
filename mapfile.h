using namespace std;
#include "common.h"

class MapFile {
public:
	MapFile();
	~MapFile();

	int open(const string& filename);
	int write(const string& data);

private:
	int buffer;
};
