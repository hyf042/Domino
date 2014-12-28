#ifndef __STRINGS_H__
#define __STRINGS_H__

#include <sstream>

namespace Domino {
	using std::string;

	class Strings {
	public:
		static string int2Str(int val) {
			std::stringstream ss;
			ss << val;
			return ss.str();
		}

		static int str2Int(string val) {
			std::stringstream ss;
			ss << val;
			int ret;
			ss >> ret;
			return ret;
		}
	};
}

#endif