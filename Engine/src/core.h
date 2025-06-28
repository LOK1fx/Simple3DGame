#pragma once

#include <sstream>
#include <iostream>
#include <stdexcept>

#define OGL3D_ERROR(msg)\
{\
std::stringstream m;\
m << "OpenGL3D Error: " << msg << std::endl;\
throw std::runtime_error(m.str());\
}

#define OGL3D_WARNING(msg) { std::wclog << "OpenGL3D Warning: " << msg << std::endl; }
#define OGL3D_INFO(msg) { std::wclog << "OpenGL3D Info: " << msg << std::endl; }


#ifdef _DEBUG
	#define ENGINE_ASSERT(x, msg) { if(!(x)) { OGL3D_ERROR(msg); __debugbreak(); } }
#else
	#define ENGINE_ASSERT(x, msg)
#endif