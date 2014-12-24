#ifndef __SNACK_H__
#define __SNACK_H__

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>

#define override virtual

#include "Util/Debug.h"

#include "Struct/Vector.h"

#include "Core/Application.h"
#include "Core/GameObject.h"

#include "Component/Component.h"
#include "Component/Transform.h"

#include "Object/Mesh.h"
#include "Object/Shader.h"

#endif