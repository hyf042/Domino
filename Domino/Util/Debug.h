#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "../Domino.h"

namespace Domino {
	using std::string;

	class Debug {
	public:
		static void log(string msg) {
			std::cout << msg << std::endl;
		}
	};
}

#endif