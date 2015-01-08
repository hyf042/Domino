#include "../../Domino.h"

namespace Domino {
	shared_ptr<Mesh> MeshFilter::getMesh() {
		if (sharedMesh) {
			return sharedMesh;
		}
		else {
			return mesh;
		}
	}

	shared_ptr<MeshFilter> MeshFilter::createCubeMesh() {
		return fromSharedMesh(MeshImporter::sharedCubeMesh());
	}

	shared_ptr<MeshFilter> MeshFilter::createSphereMesh(uint32 slices) {
		return fromSharedMesh(MeshImporter::sharedSphereMesh(slices));
	}

	shared_ptr<MeshFilter> MeshFilter::createSurfaceMesh() {
		return fromSharedMesh(MeshImporter::sharedSurfaceMesh());
	}

	shared_ptr<MeshFilter> MeshFilter::fromSharedMesh(shared_ptr<Mesh> sharedMesh) {
		shared_ptr<MeshFilter> meshFilter = shared_ptr<MeshFilter>(new MeshFilter());
		meshFilter->sharedMesh = sharedMesh;
		return meshFilter;
	}
	shared_ptr<MeshFilter> MeshFilter::fromMeshClone(shared_ptr<Mesh> mesh) {
		shared_ptr<MeshFilter> meshFilter = shared_ptr<MeshFilter>(new MeshFilter());
		meshFilter->mesh = mesh->clone();
		return meshFilter;
	}
}