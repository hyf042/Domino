#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include "../Domino.h"

namespace Domino {
	class Behaviour : public Component {
	protected:
		bool enabled;
	public:
		Behaviour():enabled(true) {}

		void setEnabled(bool enabled) {
			this->enabled = enabled;
		}

		bool getEnabled() {
			return enabled;
		}
	};
}

#endif