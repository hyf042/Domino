#ifndef __COMPONENT_H__
#define __COMPONENT_H__

namespace Domino {
	class Component {
	public:
		virtual void init() {}
		virtual void awake() {}
		virtual void start() {}
		virtual void update() {}
		virtual void render() {}
		virtual void onDestroy() {}
	};
}

#endif