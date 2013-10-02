#ifndef COMMONS_HPP
#define COMMONS_HPP
#include "VBE/includes.hpp"
#include <queue>

namespace Utils {
	extern std::mt19937 mersenne;

	inline std::string toString(float num) {
		std::stringstream ss;
		ss << num;
		return ss.str();
	}

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


#endif // COMMONS_HPP
