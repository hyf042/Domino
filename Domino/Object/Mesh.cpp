#include <fbxsdk.h>
#include "../Domino.h"

namespace Domino {
	using std::vector;

	/**
	 * Mesh
	 **/
	Mesh::Mesh(vector<Vector3> vertices, vector<Color> colors, vector<Vector2> uvs, vector<uint32> elements) {
		init(vertices, colors, uvs, elements);
	}

	Mesh::Mesh(vector<float> verticeData, vector<uint32> elementData) {
		this->verticeData = verticeData;
		this->elementData = elementData;
	}

	const vector<float>& Mesh::getVerticesData() {
		return verticeData;
	}
	const vector<uint32> Mesh::getElementsData() {
		return elementData;
	}

	void Mesh::getOriginVerticesData(vector<Vector3>& vertices, vector<Color>& colors, vector<Vector2>& uvs, vector<uint32>& elements) {
		uint32 segmentSize = (3 + 3 + 2);
		uint32 n = verticeData.size() / segmentSize;
		vertices.resize(n);
		colors.resize(n);
		uvs.resize(n);
		for (uint32 i = 0; i < n; i++) {
			vertices[i].x = verticeData[i * segmentSize + 0];
			vertices[i].y = verticeData[i * segmentSize + 1];
			vertices[i].z = verticeData[i * segmentSize + 2];
			colors[i].r = verticeData[i * segmentSize + 3];
			colors[i].g = verticeData[i * segmentSize + 4];
			colors[i].b = verticeData[i * segmentSize + 5];
			uvs[i].x = verticeData[i * segmentSize + 6];
			uvs[i].y = verticeData[i * segmentSize + 7];
		}
		elements.resize(elementData.size());
		for (uint32 i = 0; i < elementData.size(); i++) {
			elements[i] = elementData[i];
		}
	}

	void Mesh::setOriginVerticesData(const vector<Vector3>& vertices, const vector<Color>& colors, const vector<Vector2>& uvs, const vector<uint32>& elements) {
		init(vertices, colors, uvs, elements);
	}

	bool Mesh::useIndex() const {
		return elementData.size() > 0;
	}

	void Mesh::init(vector<Vector3> vertices, vector<Color> colors, vector<Vector2> uvs, vector<uint32> elements) {
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
		elementData.resize(elements.size());
		for (uint32 i = 0; i < elements.size(); i++) {
			elementData[i] = elements[i];
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

	shared_ptr<Mesh> MeshImporter::sharedSphereMesh(uint32 slices){
		static std::map<uint32, shared_ptr<Mesh> > meshs; 
		if(meshs.find(slices) == meshs.end()){
			float radius = 2.25f;

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
					uvs[i*(w+1)+j].setValue(0, 0);
				}
			}

			int triangleCount = (h-1)*(w+1)*2;
			vector<uint32> elements(triangleCount*3);
			uint32* p = &elements[0];
			for(i = 0; i < h-1; i++){
				for(j = 0; j < w; j++){
					(*(p++)) = (i+1)*(w+1)+j+1;
					(*(p++)) = i*(w+1)+j+1;
					(*(p++)) = i*(w+1)+j;
						
					(*(p++)) = i*(w+1)+j;
					(*(p++)) = (i+1)*(w+1)+j;
					(*(p++)) = (i+1)*(w+1)+j+1;
				}
					
				(*(p++)) = (i+1)*(w+1);
				(*(p++)) = i*(w+1);
				(*(p++)) = i*(w+1)+j;
					
				(*(p++)) = i*(w+1)+j;
				(*(p++)) = (i+1)*(w+1)+j;
				(*(p++)) = (i+1)*(w+1);
					
			}

			meshs[slices] = shared_ptr<Mesh>(new Mesh(vertices, colors, uvs, elements));
		}
		return meshs[slices];
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

	void importFBXNode(
		FbxNode *node, 
		vector<Vector3> &vertices, 
		vector<Color> &colors, 
		vector<Vector2> &uvs, 
		vector<Vector3> &normals,
		vector<uint32> &elements) {

		FbxNode *childNode = 0;
		int numKids = node->GetChildCount();
		for ( int i=0 ; i<numKids ; i++)
		{
			childNode = node->GetChild(i);
			FbxMesh *mesh = childNode->GetMesh();

			if ( mesh != NULL )
			{
				auto offset = node->GetGeometricTranslation(FbxNode::eSourcePivot);

				//================= Get Vertices ====================================
				int baseline = vertices.size();
				int numVerts = mesh->GetControlPointsCount();

				for ( int j=0; j<numVerts; j++)
				{
					FbxVector4 vert = mesh->GetControlPointAt(j);
					vertices.push_back(
						Vector3(vert.mData[0], vert.mData[1], vert.mData[2])
						/*+ Vector3(offset.mData[0], offset.mData[1], offset.mData[2])*/);
					colors.push_back(Vector3(1, 1, 1));
					uvs.push_back(Vector2(0, 0));
				}

				//================= Get Indices ====================================
				int numIndices=mesh->GetPolygonVertexCount();
				int *indicesRaw = mesh->GetPolygonVertices();
				for (int i = 0; i < numIndices; i++) {
					elements.push_back(indicesRaw[i] + baseline);
				}

				int cnt = 0;
				int polygonCount = mesh->GetPolygonCount();
				for (int i = 0; i < polygonCount; ++i) {

					FbxLayerElementArrayTemplate<FbxVector2>* uvVertices= 0;
					mesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

					for (int j = 0; j < mesh->GetPolygonSize(i); ++j) {

						FbxVector2 uv = (*uvVertices)[mesh->GetTextureUVIndex(i, j)];

						uvs[indicesRaw[cnt] + baseline].x = uv[0];
						uvs[indicesRaw[cnt] + baseline].y = uv[1];
						cnt++;
					}
				}
			}

			importFBXNode(childNode, vertices, colors, uvs, normals, elements);
		}
	}

	shared_ptr<Mesh> MeshImporter::createFromFBX(string filename) {
		FbxManager *manager = FbxManager::Create();

		FbxIOSettings *ioSettings = FbxIOSettings::Create(manager, IOSROOT);
		manager->SetIOSettings(ioSettings);

		FbxImporter *importer = FbxImporter::Create(manager, "");
		importer->Initialize(filename.c_str(), -1, manager->GetIOSettings());

		FbxScene *scene = FbxScene::Create(manager, "tempName");

		importer->Import(scene);
		importer->Destroy();

		FbxNode* rootNode = scene->GetRootNode();

		if(rootNode) {
			vector<Vector3> vertices;
			vector<Color> colors;
			vector<Vector2> uvs; 
			vector<Vector3> normals;
			vector<uint32> elements;
			importFBXNode(rootNode, vertices, colors, uvs, normals, elements);
			return shared_ptr<Mesh>(new Mesh(vertices, colors, uvs, elements));
		}

		return nullptr;
	}

}