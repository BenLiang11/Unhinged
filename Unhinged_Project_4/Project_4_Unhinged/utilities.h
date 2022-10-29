#ifndef UTIL
#define UTIL

#include "provided.h"

struct cmp {
	bool operator()(const int& a, const int& b) const {
		return (a > b);
	}
};

struct cmpS {
	bool operator()(const AttValPair& a, const AttValPair& b) const {
		return (a.attribute + a.value) < (b.attribute + b.value);
	}
};





#endif