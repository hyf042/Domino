#ifndef __MESH_H__
#define __MESH_H__

#include "../Domino.h"

namespace Domino {
	using std::vector;

	struct Vector3;
	struct Vector2;
	struct Color;

	class Mesh : public Object {
	public:
		Mesh(vector<Vector3> vertices, vector<Color> colors, vector<Vector2> uvs, vector<uint32> elementArray) {
			init(vertices, colors, uvs, elementArray);
		}

		Mesh(vector<float> verticeData, vector<uint32> elementData) {
			this->verticeData = verticeData;
			this->elementData = elementData;
		}

		shared_ptr<Mesh> clone() const;

		const vector<float>& getVerticesData() {
			return verticeData;
		}
		const vector<uint32> getElementsData() {
			return elementData;
		}

		bool useIndex() const {
			return elementData.size() > 0;
		}
	private:
		void init(vector<Vector3> vertices, vector<Color> colors, vector<Vector2> uvs, vector<uint32> elementArray);

		vector<float> verticeData;
		vector<GLuint> elementData;
	};

	
	class MeshImporter{
	public:
		static shared_ptr<Mesh> sharedCubeMesh();
		static shared_ptr<Mesh> sharedSphereMesh();
		static shared_ptr<Mesh> sharedSurfaceMesh();
	};
}

#endif