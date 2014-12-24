#ifndef __MESH_FILTER_H__
#define __MESH_FILTER_H__

#include "../../Domino.h"

namespace Domino {
	using std::shared_ptr;

	class MeshFilter : public Component{
	private:
		shared_ptr<Mesh> sharedMesh;
		shared_ptr<Mesh> mesh;

	public:
		MeshFilter() {}
		virtual ~MeshFilter() {}

		shared_ptr<Mesh> getMesh();

	public:
		static shared_ptr<MeshFilter> createCubeMesh();
		static shared_ptr<MeshFilter> createSphereMesh();
		static shared_ptr<MeshFilter> fromSharedMesh(shared_ptr<Mesh> sharedMesh);
		static shared_ptr<MeshFilter> fromMeshClone(shared_ptr<Mesh> mesh);
	};

}

#endif