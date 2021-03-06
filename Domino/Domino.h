#ifndef __DOMINO_H__
#define __DOMINO_H__

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef int int32;
typedef short int16;

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <GL/glew.h>
#include <GL/glut.h>

#include "PreDefine.h"

#include "Util/Debug.h"
#include "Util/Time.h"
#include "Util/Mathf.h"
#include "Util/Strings.h"

#include "Struct/Vector.h"
#include "Struct/Color.h"
#include "Struct/Quaternion.h"

#include "Object/Object.h"
#include "Object/Shader.h"
#include "Object/Texture.h"
#include "Object/Material.h"
#include "Object/Mesh.h"

#include "Core/GameObject.h"

#include "Component/Component.h"
#include "Component/Transform.h"
#include "Component/Render/Camera.h"
#include "Component/Render/MeshFilter.h"
#include "Component/Render/Renderer.h"
#include "Component/Render/MeshRenderer.h"
#include "Component/Behaviour.h"
#include "Component/MonoBehaviour.h"

#include "Object/Scene.h"
#include "Core/Input.h"
#include "Core/Application.h"

#endif