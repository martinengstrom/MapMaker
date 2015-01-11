using namespace std;
#include "common.h"

class MapFile {
public:
	MapFile(const string& filename);
	~MapFile();

	int write(const string& data);

private:
	int buffer;
};
