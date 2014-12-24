#ifndef __SNACK_H__
#define __SNACK_H__

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
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Util/Debug.h"
#include "Util/Time.h"
#include "Util/Mathf.h"

#include "Struct/Vector.h"
#include "Struct/Color.h"

#include "Core/Application.h"
#include "Core/GameObject.h"

#include "Component/Component.h"
#include "Component/Transform.h"
#include "Component/Render/Renderer.h"
#include "Component/Render/MeshRenderer.h"
#include "Component/Render/MeshFilter.h"

#include "Object/Object.h"
#include "Object/Shader.h"
#include "Object/Texture.h"
#include "Object/Material.h"
#include "Object/Mesh.h"

#endif