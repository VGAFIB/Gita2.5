#ifndef TOOLS_HPP
#define TOOLS_HPP

#ifdef __DEBUG
  #define VBE_ASSERT(expression, string) do \
	{ \
		if(!(expression)) { \
			std::cout << "ASSERT FAILED, STOPPING " << std::endl;\
			std::cout << "Reason: " << string << std::endl; \
			assert(expression); \
			std::exit(-1); \
		} \
	} while (0);
#else
  #define VBE_ASSERT(expression, string)
#endif
#ifdef __LOG
  #define VBE_LOG(log) std::cout << log << std::endl;
#else
  #define VBE_LOG(log)
#endif
#ifdef __DLOG
  #define VBE_DLOG(log) VBE_LOG(log)
#else
  #define VBE_DLOG(log)
#endif

//OpenGL (Open Graphics Library)
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h> //core

//SFML (Simple Fast Media Library)
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//STL (Standard Toolkit Library)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include <cmath>
#include <cstring>
#include <random>

//GLM (openGL Math)
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4 (core)
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective

//math typedefs
typedef glm::detail::tvec4<int> vec4i;
typedef glm::detail::tvec4<float> vec4f;
typedef glm::detail::tvec4<double> vec4d;
typedef glm::detail::tvec4<uint> vec4ui;
typedef glm::detail::tvec3<int> vec3i;
typedef glm::detail::tvec3<float> vec3f;
typedef glm::detail::tvec3<double> vec3d;
typedef glm::detail::tvec3<uint> vec3ui;
typedef glm::detail::tvec2<int> vec2i;
typedef glm::detail::tvec2<float> vec2f;
typedef glm::detail::tvec2<double> vec2d;
typedef glm::detail::tvec2<uint> vec2ui;
typedef glm::detail::tmat2x2<float> mat2f;
typedef glm::detail::tmat3x3<float> mat3f;
typedef glm::detail::tmat4x4<float> mat4f;
typedef glm::detail::tmat2x2<double> mat2d;
typedef glm::detail::tmat3x3<double> mat3d;
typedef glm::detail::tmat4x4<double> mat4d;

//prototype misc functions here (define in tools.cpp) and inlines.
std::string toString(float num);

//defines (global settings and constants)
#define WINDOW_TITLE "Engine"
#define CONTEXT_SETTINGS_OPENGL sf::ContextSettings(32,32,0,4,2)
#define DEG_TO_RAD ((2*M_PI)/360.0f)

//frustum settings
#define FOV 60.0f //degrees
#define ZNEAR 0.1f
#define ZFAR 10000.0f

//global variables
extern int SCRWIDTH;
extern int SCRHEIGHT;
extern bool WINDOWFOCUS;
extern sf::Clock GLOBALCLOCK;

namespace Utils {
	extern std::mt19937 mersenne;

	inline int randomInt() {
		return (mersenne() & 0x7FFFFFFF);
	}

	inline void seedRandom(int seed) {
		mersenne.seed(seed);
	}

	//Returns random float in [min, max)
	inline float randomFloat(float min, float max) {
		return (randomInt() / float(0x7FFFFFFF))*(max-min)+min;
	}

	//Returns random between [min, max]
	inline int randomInt(int min, int max) {
		if (min >= max) return min;
		return (randomInt()%((max-min)+1)) + min;
	}

	inline bool randomBool(int prob) {
		return randomInt(0, 99) < prob;
	}

	inline float toRad(float deg) {
		return deg/180.0*M_PI;
	}

	inline float toDeg(float rad) {
		return rad*180.0/M_PI;
	}
}

#endif // TOOLS_HPP
