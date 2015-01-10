#ifndef __OBJECT_H__
#define __OBJECT_H__

namespace Domino {
	class Object {
	protected:
		string name;
	public:
		string getName() const {
			return name;
		}
	};
}

#endif
