#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "../Domino.h"

namespace Domino {
	using std::string;

	typedef shared_ptr<Transform> TransformPtr;

	class Transform :
		public Component,
		public std::enable_shared_from_this<Transform> {
	public:
		Vector3 localPosition;
		Vector3 localRotation;
		Vector3 localScale;
	private:
		TransformPtr parent;
		vector<TransformPtr> children;
	protected:
		Vector3 worldPosition;
		Vector3 worldRotation;
		Vector3 worldScale;
	public:
		Transform();
		virtual ~Transform() {}

		void updateTransform();

		TransformPtr find(string name);
		TransformPtr findChild(string name);
		bool isChildOf(shared_ptr<Transform> transform);

		void setParent(TransformPtr parent) {
			if (parent) {
				parent->addChild(TransformPtr(shared_from_this()));
			} else {
				removeSelf();
			}
		}
		TransformPtr getParent() const {
			return parent;
		}

		const vector<TransformPtr>& getChildren() const {
			return children;
		}
		int getChildrenCount() const {
			return children.size();
		}

		Vector3 position() const {
			return worldPosition;
		}
		Vector3 rotation() const {
			return worldRotation;
		}
		Vector3 scale() const {
			return worldScale;
		}

	private:
		void addChild(TransformPtr child);
		void removeChild(TransformPtr child);
		void removeSelf();
	};
}

#endif