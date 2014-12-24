#ifndef __COMPONENT_H__
#define __COMPONENT_H__

namespace Domino {
	class Component {
	public:
		virtual void init() {}
		virtual void start() {}
		virtual void update() {}
	};
}

#endif