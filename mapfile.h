using namespace std;
#include "common.h"

class MapFile {
public:
	MapFile();
	~MapFile();

	int open(const string& filename);
	void close();
	int write(const string& data);
	string read();

private:
	int buffer;
	std::FILE *fp;
};
