#include "Mesh.h"

namespace Domino {
	using std::vector;

	/**
	 * Mesh
	 **/
	void Mesh::init(vector<Vector3> vertices, vector<Color> colors, vector<Vector2> uvs, vector<uint32> elementArray) {
		uint32 n = vertices.size();
		uint32 segmentSize = (3 + 3 + 2);
		verticeData.resize(n * (3 + 3 + 2));
		for (uint32 i = 0; i < n; i++) {
			verticeData[i * segmentSize + 0] = vertices[i].x; 
			verticeData[i * segmentSize + 1] = vertices[i].y;
			verticeData[i * segmentSize + 2] = vertices[i].z;
			verticeData[i * segmentSize + 3] = colors[i].r;
			verticeData[i * segmentSize + 4] = colors[i].g;
			verticeData[i * segmentSize + 5] = colors[i].b;
			verticeData[i * segmentSize + 6] = uvs[i].x;
			verticeData[i * segmentSize + 7] = uvs[i].y;
		}
		elementData.resize(elementArray.size());
		for (uint32 i = 0; i < elementArray.size(); i++) {
			elementData[i] = elementArray[i];
		}
	}

	shared_ptr<Mesh> Mesh::clone() const {
		return shared_ptr<Mesh>(new Mesh(verticeData, elementData));
	}

	/**
	 * MeshImporter
	 **/

	void buildSphereVertex(float radius, float a, float b, Vector3 &vertex, Vector3 &normal){
		float sina = sinf(a);
		vertex = Vector3(radius*sina*cosf(b), 
						radius*sina*sinf(b),
						radius*cosf(a));
		normal = vertex;
		normal.normalize();
	}

	shared_ptr<Mesh> MeshImporter::sharedCubeMesh(){
		static shared_ptr<Mesh> mesh;
		if(!mesh){
			Vector3 v[8] = {
				Vector3(0.5f,0.5f,0.5f),	//0
				Vector3(-0.5f,0.5f,0.5f),	//1
				Vector3(-0.5f,-0.5f,0.5f),	//2
				Vector3(0.5f,-0.5f,0.5f),	//3
				Vector3(0.5f,-0.5f,-0.5f),	//4
				Vector3(0.5f,0.5f,-0.5f),	//5
				Vector3(-0.5f,0.5f,-0.5f),	//6
				Vector3(-0.5f,-0.5f,-0.5f)		//7
			};

			float half4 = 0.25f,
				half2 = 0.5f,
				half43 = 0.75f,
				half3 = 1.0f/3,
				half32 = 2.0f/3;
			

			Vector3 n[6] = {
				Vector3(0,0,1),//0
				Vector3(1,0,0),//1
				Vector3(0,1,0),	//2
				Vector3(-1,0,0),	//3
				Vector3(0,-1,0),	//4
				Vector3(0,0,-1),//5
			};

			//vertices
			int triangleCount = 12;
			int vertexCount = 36;
		    vector<Vector3> vertices(vertexCount);
			Vector3 *mv = &vertices[0];

			uint32 idx = 0;
			//front
			mv[idx++] = v[0]; mv[idx++] = v[1]; mv[idx++] = v[2];
			mv[idx++] = v[2]; mv[idx++] = v[3]; mv[idx++] = v[0];
			//right
			mv[idx++] = v[0]; mv[idx++] = v[3]; mv[idx++] = v[4];
			mv[idx++] = v[4]; mv[idx++] = v[5]; mv[idx++] = v[0];
			//top
			mv[idx++] = v[0]; mv[idx++] = v[5]; mv[idx++] = v[6];
			mv[idx++] = v[6]; mv[idx++] = v[1]; mv[idx++] = v[0];
			//left
			mv[idx++] = v[1]; mv[idx++] = v[6]; mv[idx++] = v[7];
			mv[idx++] = v[7]; mv[idx++] = v[2]; mv[idx++] = v[1];
			//bottom
			mv[idx++] = v[7]; mv[idx++] = v[4]; mv[idx++] = v[3];
			mv[idx++] = v[3]; mv[idx++] = v[2]; mv[idx++] = v[7];
			//back
			mv[idx++] = v[4]; mv[idx++] = v[7]; mv[idx++] = v[6];
			mv[idx++] = v[6]; mv[idx++] = v[5]; mv[idx++] = v[4];


			//UV
			idx=0;

			vector<Vector2> uvs(vertexCount);
			Vector2 *muv = &uvs[0];
			muv[idx++].setValue(1, 1); muv[idx++].setValue(0, 1); muv[idx++].setValue(0, 0); 
			muv[idx++].setValue(0, 0); muv[idx++].setValue(1, 0); muv[idx++].setValue(1, 1); 

			muv[idx++].setValue(0, 1); muv[idx++].setValue(0, 0); muv[idx++].setValue(1, 0);
			muv[idx++].setValue(1, 0); muv[idx++].setValue(1, 1); muv[idx++].setValue(0, 1);

			muv[idx++].setValue(1, 0); muv[idx++].setValue(1, 1); muv[idx++].setValue(0, 1);
			muv[idx++].setValue(0, 1); muv[idx++].setValue(0, 0); muv[idx++].setValue(1, 0);

			muv[idx++].setValue(1, 1); muv[idx++].setValue(0, 1); muv[idx++].setValue(0, 0);
			muv[idx++].setValue(0, 0); muv[idx++].setValue(1, 0); muv[idx++].setValue(1, 1); 

			muv[idx++].setValue(0, 0); muv[idx++].setValue(1, 0); muv[idx++].setValue(1, 1);
			muv[idx++].setValue(1, 1); muv[idx++].setValue(0, 1); muv[idx++].setValue(0, 0);

			muv[idx++].setValue(0, 0); muv[idx++].setValue(1, 0); muv[idx++].setValue(1, 1);
			muv[idx++].setValue(1, 1); muv[idx++].setValue(0, 1); muv[idx++].setValue(0, 0);

			//color
			vector<Color> colors(vertexCount);
			for(int i=0;i<vertexCount;i++){
				colors[i].setValue(1,1,1);
			}

			//not use index
			vector<uint32> elements;

			mesh = shared_ptr<Mesh>(new Mesh(vertices, colors, uvs, elements));
		}
		return mesh;
	}

	shared_ptr<Mesh> MeshImporter::sharedSphereMesh(){
		static shared_ptr<Mesh> mesh;
		if(!mesh){
			float radius = 0.5f;

			uint32 slices = 8;

			int w=2*slices, h=slices;
			float hStep = 180.0 / (h-1);
			float wStep = 360.0 / w;

			int vertexCount = h*(w+1);
			vector<Vector3> vertices(vertexCount);
			vector<Vector3> normals(vertexCount);
			vector<Color> colors(vertexCount);
			vector<Vector2> uvs(vertexCount);

			float a,b;
			int i = 0, j = 0;
			for(a=0.0,i=0;i<h;i++,a+=hStep){
				for(b=0.0,j=0;j<=w;j++,b+=wStep){
					buildSphereVertex(radius, Mathf::deg2Rad(a), Mathf::deg2Rad(b), vertices[i*(w+1)+j], normals[i*(w+1)+j]);
					colors[i*(w+1)+j].setValue(1,1,1);
					uvs[i*(w+1)+j].x = 1-b/360.0f;
					uvs[i*(w+1)+j].y = a/180.0f;
				}
			}

			int triangleCount = (h-1)*(w+1)*2;
			vector<uint32> elements(triangleCount*3);
			uint32* p = &elements[0];
			for(i = 0; i < h-1; i++){
				for(j = 0; j < w; j++){
					(*(p++)) = (i+1)*w+j+1;
					(*(p++)) = i*w+j+1;
					(*(p++)) = i*w+j;
						
					(*(p++)) = i*w+j;
					(*(p++)) = (i+1)*w+j;
					(*(p++)) = (i+1)*w+j+1;
				}
					
				(*(p++)) = (i+1)*w;
				(*(p++)) = i*w;
				(*(p++)) = i*w+j;
					
				(*(p++)) = i*w+j;
				(*(p++)) = (i+1)*w+j;
				(*(p++)) = (i+1)*w;
					
			}

			mesh = shared_ptr<Mesh>(new Mesh(vertices, colors, uvs, elements));
		}
		return mesh;
	}

	shared_ptr<Mesh> MeshImporter::sharedSurfaceMesh() {
		static shared_ptr<Mesh> mesh;
		if(!mesh){
			int vertexCount = 4;
			vector<Vector3> vertices(vertexCount);
			vector<Color> colors(vertexCount);
			vector<Vector2> uvs(vertexCount);

			vertices[0].setValue(-0.5f, 0.5f, 0.0f);
			vertices[1].setValue(0.5f, 0.5f, 0.0f);
			vertices[2].setValue(0.5f, -0.5f, 0.0f);
			vertices[3].setValue(-0.5f, -0.5f, 0.0f);
			colors[0].setValue(1, 1, 1, 1);
			colors[1].setValue(1, 1, 1, 1);
			colors[2].setValue(1, 1, 1, 1);
			colors[3].setValue(1, 1, 1, 1);
			uvs[0].setValue(0, 0);
			uvs[1].setValue(1, 0);
			uvs[2].setValue(1, 1);
			uvs[3].setValue(0, 1);
			
			int triangleCount = 2;
			vector<uint32> elements(triangleCount*3);
			elements[0] = 0;
			elements[1] = 1;
			elements[2] = 2;
			elements[3] = 2;
			elements[4] = 3;
			elements[5] = 0;

			mesh = shared_ptr<Mesh>(new Mesh(vertices, colors, uvs, elements));
		}
		return mesh;
	}
}