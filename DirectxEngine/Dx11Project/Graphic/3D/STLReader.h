#ifndef __STLREADER__
#define __STLREADER__
#include "windows.h"
#include "DirectXmath.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <unordered_map> 
#include <list>
using namespace DirectX;
typedef struct _S_STLVertex
{
	XMFLOAT3 Normal;
	XMFLOAT3 Pos;
#ifdef __cplusplus
	_S_STLVertex()
	{
		Normal = XMFLOAT3(0, 0, 0);
		Pos = XMFLOAT3(0, 0, 0);
	}
	_S_STLVertex(XMFLOAT3 _normal, XMFLOAT3 _Pos) :
		Normal(_normal), Pos(_Pos)
	{

	};
#endif
}S_STLVertex;


typedef struct _S_STLFileData
{
	XMFLOAT3 Normal;
	XMFLOAT3 Vertex1;
	XMFLOAT3 Vertex2;
	XMFLOAT3 Vertex3;

#ifdef __cplusplus
	_S_STLFileData() 
	{ 
		Normal = XMFLOAT3(0, 0, 0); 
		Vertex1 = XMFLOAT3(0, 0, 0);
		Vertex2 = XMFLOAT3(0, 0, 0);
		Vertex3 = XMFLOAT3(0, 0, 0);
	}
	_S_STLFileData(XMFLOAT3 _normal, XMFLOAT3 _vertex1, XMFLOAT3 _vertex2, XMFLOAT3 _vertex3) : 
		Normal(_normal), Vertex1(_vertex1), Vertex2(_vertex2), Vertex3(_vertex3)
	{

	};
#endif

}S_STLFileData;

//////////////////////////////////////////////////////////////////////////
class cSTLImplement
{
public:
	cSTLImplement();
	void Release();
	float ParseFloatFromByte();
	bool Open_Bin(const char *pPath);
	void getHeader_Bin(char* pHeader, int cnt);
	void getNTraingles_Bin(unsigned int *pNTrangles, int cnt);
	void ReadNormalVertex(S_STLFileData *pdata, int cnt);
	void ReadDummy_Bin(int cnt);
	std::ifstream m_FS;
};

//////////////////////////////////////////////////////////////////////////
class cSmoothSTL
{
public:
	cSmoothSTL();
	~cSmoothSTL();
	void Release();
	void AllocateBuffer(int cnt);
	DWORD RecordVertexToTable(XMFLOAT3 *pVertex, XMFLOAT3 *pNormal);
	DWORD RecordVertexToTable2(XMFLOAT3 *pVertex, XMFLOAT3 *pNormal, float sum);
	void AverageNormal();
	S_STLVertex *mTable;
	int *mNormalCnt;
	int mTableCnt;
	int mIndexCnt;
	std::unordered_map<float, std::list<int>> mUmap;
};
//////////////////////////////////////////////////////////////////////////

class cSTLReader
{
public:
	virtual void FileRead(const char* pPath, bool smooth) = 0;
	unsigned int getTrians();
	unsigned int getIndices();
	unsigned int getVertexes();
	char* getHeader();
	void *getVertexBuffer();
	void *getIndexBuffer();
	float *getCenterOfMass();
	void Release();
	cSTLReader();
	~cSTLReader();

protected:
	void CalCenterOfMass(S_STLVertex *Buffer, int cnt);
	cSTLImplement m_Imp;
	S_STLVertex *mVertexBuffer;
	cSmoothSTL mSmoothSTL;
	DWORD *mIndexBuffer;
	unsigned int m_nTriangles;
	unsigned int m_nIndices;
	unsigned int m_Vertexes;
	char m_Header[100];
	float m_COM[3]; // center of mass
};
//////////////////////////////////////////////////////////////////////////

class cSTLReaderBin: public cSTLReader
{
public:
	void FileRead(const char* pPath, bool smooth);
	cSTLReaderBin();
	~cSTLReaderBin();

private:

};
//////////////////////////////////////////////////////////////////////////

class cSTLReaderText : public cSTLReader
{
public:

};





#endif // __STLREADER__
