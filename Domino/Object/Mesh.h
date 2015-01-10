#ifndef __MESH_H__
#define __MESH_H__

#include "../Domino.h"

namespace Domino {
	using std::vector;
	using std::shared_ptr;

	class Mesh : public Object {
	public:
		Mesh(vector<Vector3> vertices, vector<Color> colors, vector<Vector2> uvs, vector<uint32> elements);

		Mesh(vector<float> verticeData, vector<uint32> elementData);

		shared_ptr<Mesh> clone() const;

		const vector<float>& getVerticesData();
		const vector<uint32> getElementsData();
		void getOriginVerticesData(
			vector<Vector3>& vertices, 
			vector<Color>& colors, 
			vector<Vector2>& uvs, 
			vector<uint32>& elements);
		void setOriginVerticesData(
			const vector<Vector3>& vertices, 
			const vector<Color>& colors,
			const vector<Vector2>& uvs, 
			const vector<uint32>& elements);

		bool useIndex() const;
	private:
		void init(vector<Vector3> vertices, vector<Color> colors, vector<Vector2> uvs, vector<uint32> elements);

		vector<float> verticeData;
		vector<GLuint> elementData;
	};

	
	class MeshImporter{
	public:
		static shared_ptr<Mesh> sharedCubeMesh();
		static shared_ptr<Mesh> sharedSphereMesh(uint32 slices = 20);
		static shared_ptr<Mesh> sharedSurfaceMesh();
		static shared_ptr<Mesh> createFromFBX(string filename);
	};
}

#endif