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
	int openWrite(const string& filename);
	int openRead(const string& filename);

private:
	int open(const string& fmode, const string& filename);
	int buffer;
	std::FILE *fp;
};
