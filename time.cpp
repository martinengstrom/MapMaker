#include "time.h"

using namespace std;
using namespace boost::posix_time;

namespace MultiPlatform {
	string getDate() {
		boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
		stringstream ss;
		time_facet *facet = new time_facet("%Y-%m-%d_%H:%M:%S");
		ss.imbue(std::locale(std::locale::classic(), facet));
		ss << now;
		return ss.str();
	}
}