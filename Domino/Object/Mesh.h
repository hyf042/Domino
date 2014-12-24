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

		Mesh(vector<float> vertexData, vector<uint32> elementData) {
			this->vertexData = vertexData;
			this->elementData = elementData;
		}

		shared_ptr<Mesh> clone() const;

		const vector<float>& getVerticesData() {
			return vertexData;
		}
		const vector<uint32> getElementsData() {
			return elementData;
		}

		bool useIndex() const {
			return elementData.size() > 0;
		}
	private:
		void init(vector<Vector3> vertices, vector<Color> colors, vector<Vector2> uvs, vector<uint32> elementArray);

		vector<float> vertexData;
		vector<GLuint> elementData;
	};

	
	class MeshImporter{
	private:
		static void buildSphereVertex(float radius, float a, float b, Vector3 &vertex, Vector3 &normal);
	public:
		static shared_ptr<Mesh> sharedCubeMesh();
		static shared_ptr<Mesh> sharedSphereMesh();
		static shared_ptr<Mesh> sharedSurfaceMesh();
	};
}

#endif