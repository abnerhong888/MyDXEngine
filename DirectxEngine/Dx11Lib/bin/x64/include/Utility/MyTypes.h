#ifndef __MYTYPES_H__
#define __MYTYPES_H__

#include "windows.h"
//#include "assert.h"
#include <string>
// My Type
namespace MT {

	//	static void assertString(const char *msg, const char *File, unsigned Line)
	//	{
	//		std::string str;
	//		str += "Assertion Failed! \n\n";
	//		str += "Expression : " + std::string(msg) + "\n\nFile: " + std::string(File) + "\nLine: " + std::to_string(Line);
	//		std::wstring wide_string(str.begin(), str.end());
	//		MessageBoxW(NULL, wide_string.c_str(), L"Error -  _MTAssert", MB_ICONERROR);
	//		exit(-1);
	//	}
	//#define _MTAssert(expression) (void)(						  \
	//            (!!(expression)) ||								  \
//			(assertString(#expression, __FILE__, __LINE__),0)\
//			)

#define STRUCT1(type) struct{type x;}; struct{type r;}
#define STRUCT2(type) struct{type x, y;}; struct{type r, g;}; struct{type w, h;}
#define STRUCT3(type) struct{type x, y, z;}; struct{type r, g, b;}
#define STRUCT4(type) struct{type x, y, z, w;}; struct{type r, g, b, a;}; struct{type rx, ry, rw, rh;}
#define STRUCT_MEMBER(type, n) STRUCT##n(type)

#define STRUCT_INIT1(type, name) name(const type _x):x(_x) {}
#define STRUCT_INIT2(type, name) name(const type _x,type _y):x(_x), y(_y) {}
#define STRUCT_INIT3(type, name) name(const type _x,type _y, type _z):x(_x), y(_y), z(_z) {}
#define STRUCT_INIT4(type, name) name(const type _x,type _y, type _z, type _w):x(_x), y(_y), z(_z), w(_w) {}
#define STRUCT_INIT_DECLARE(type, name, n) STRUCT_INIT##n(type, name)

#define STRCUT_NAME(type, n) vec_##type##n

//#define OP_ADD +
//#define OP_SUB -
//#define OP_MUL *
//#define OP_DIV /
//
//#define MEMBER_LOOP_SAME(n, op ,__assert) for (int i = 0; i < n; i++) { __assert; v[i] = (v[i] op p.v[i]); } return *this
//#define MEMBER_LOOP(n, op ,type, __assert) for (int i = 0; i < n; i++) { __assert; v[i] = static_cast<type>(v[i] op p); } return *this

#define TYPDEF_VEC_STRCUT(type, n)	\
struct STRCUT_NAME(type, n){		\
	union{							\
	STRUCT_MEMBER(type, n);			\
	type v[n];						\
	};								\
	STRUCT_INIT_DECLARE(type, STRCUT_NAME(type, n), n)\
	STRCUT_NAME(type, n)() {ZeroMemory(this, sizeof(STRCUT_NAME(type, n)));}\
};									\
typedef STRCUT_NAME(type, n)

/*
STRCUT_NAME(type, n) &operator =  (const STRCUT_NAME(type, n) &in) { memcpy(this, &in, sizeof(vec_##type##n)); return *this; }\
STRCUT_NAME(type, n) &operator +  (const STRCUT_NAME(type, n) &p) { MEMBER_LOOP_SAME(n, OP_ADD, 0); } \
STRCUT_NAME(type, n) &operator += (const STRCUT_NAME(type, n) &p) { MEMBER_LOOP_SAME(n, OP_ADD, 0); } \
STRCUT_NAME(type, n) &operator -  (const STRCUT_NAME(type, n) &p) { MEMBER_LOOP_SAME(n, OP_SUB, 0); } \
STRCUT_NAME(type, n) &operator -= (const STRCUT_NAME(type, n) &p) { MEMBER_LOOP_SAME(n, OP_SUB, 0); } \
STRCUT_NAME(type, n) &operator *  (const STRCUT_NAME(type, n) &p) { MEMBER_LOOP_SAME(n, OP_MUL, 0); } \
STRCUT_NAME(type, n) &operator *= (const STRCUT_NAME(type, n) &p) { MEMBER_LOOP_SAME(n, OP_MUL, 0); } \
STRCUT_NAME(type, n) &operator /  (const STRCUT_NAME(type, n) &p) { MEMBER_LOOP_SAME(n, OP_DIV, _MTAssert(p.v[i] != 0)); } \
STRCUT_NAME(type, n) &operator /= (const STRCUT_NAME(type, n) &p) { MEMBER_LOOP_SAME(n, OP_DIV, _MTAssert(p.v[i] != 0)); } \
template<typename T> STRCUT_NAME(type, n) &operator +  (const T &p) { MEMBER_LOOP(n, OP_ADD, type, 0); } \
template<typename T> STRCUT_NAME(type, n) &operator += (const T &p) { MEMBER_LOOP(n, OP_ADD, type, 0); } \
template<typename T> STRCUT_NAME(type, n) &operator -  (const T &p) { MEMBER_LOOP(n, OP_SUB, type, 0); } \
template<typename T> STRCUT_NAME(type, n) &operator -= (const T &p) { MEMBER_LOOP(n, OP_SUB, type, 0); } \
template<typename T> STRCUT_NAME(type, n) &operator *  (const T &p) { MEMBER_LOOP(n, OP_MUL, type, 0); } \
template<typename T> STRCUT_NAME(type, n) &operator *= (const T &p) { MEMBER_LOOP(n, OP_MUL, type, 0); } \
template<typename T> STRCUT_NAME(type, n) &operator /  (const T &p) { MEMBER_LOOP(n, OP_DIV, type, _MTAssert(p != static_cast<type>(0))); } \
template<typename T> STRCUT_NAME(type, n) &operator /= (const T &p) { MEMBER_LOOP(n, OP_DIV, type, _MTAssert(p != static_cast<type>(0))); } \
};						\
typedef STRCUT_NAME(type, n)
*/

	typedef unsigned int uint;
	typedef unsigned char uchar;

	TYPDEF_VEC_STRCUT(int, 2) int2;
	TYPDEF_VEC_STRCUT(int, 3) int3;
	TYPDEF_VEC_STRCUT(int, 4) int4;

	TYPDEF_VEC_STRCUT(uint, 2) Uint2;
	TYPDEF_VEC_STRCUT(uint, 3) Uint3;
	TYPDEF_VEC_STRCUT(uint, 4) Uint4;

	TYPDEF_VEC_STRCUT(char, 2) char2;
	TYPDEF_VEC_STRCUT(char, 3) char3;
	TYPDEF_VEC_STRCUT(char, 4) char4;

	TYPDEF_VEC_STRCUT(uchar, 2) uchar2;
	TYPDEF_VEC_STRCUT(uchar, 3) uchar3;
	TYPDEF_VEC_STRCUT(uchar, 4) uchar4;

	TYPDEF_VEC_STRCUT(float, 2) float2;
	TYPDEF_VEC_STRCUT(float, 3) float3;
	TYPDEF_VEC_STRCUT(float, 4) float4;

	TYPDEF_VEC_STRCUT(double, 2) double2;
	TYPDEF_VEC_STRCUT(double, 3) double3;
	TYPDEF_VEC_STRCUT(double, 4) double4;
	
	

} // namespace 

#endif