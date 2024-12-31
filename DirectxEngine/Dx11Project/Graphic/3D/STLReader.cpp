#include "STLReader.h"

//////////////////////////////////////////////////////////////////////////
cSTLReader::cSTLReader(): m_nTriangles(0),m_Header(""), m_Vertexes(0),
						m_nIndices(0), mVertexBuffer(NULL), mIndexBuffer(NULL)
{
	for (int i = 0; i < 3; i++)
	{
		m_COM[i] = 0.0;
	}
}

cSTLReader::~cSTLReader() 
{
	this->Release();
}

unsigned int cSTLReader::getTrians()
{
	return m_nTriangles;
}

unsigned int cSTLReader::getIndices()
{
	return m_nIndices;
}

unsigned int cSTLReader::getVertexes()
{
	return m_Vertexes;
}

char* cSTLReader::getHeader()
{
	return m_Header;
}

void * cSTLReader::getVertexBuffer()
{
	if (mVertexBuffer)
		return (void*)mVertexBuffer;
	else
		return NULL;
}

void * cSTLReader::getIndexBuffer()
{
	if (mIndexBuffer)
		return (void*)mIndexBuffer;
	else
		return NULL;
}

float *cSTLReader::getCenterOfMass()
{
	return m_COM;
}

void cSTLReader::CalCenterOfMass(S_STLVertex *Buffer, int cnt)
{
	m_COM[0] = 0;
	m_COM[1] = 0;
	m_COM[2] = 0;

	for (int i = 0; i < cnt; i++)
	{
		m_COM[0] += Buffer[i].Pos.x;
		m_COM[1] += Buffer[i].Pos.y;
		m_COM[2] += Buffer[i].Pos.z;
	}
	m_COM[0] /= cnt;
	m_COM[1] /= cnt;
	m_COM[2] /= cnt;
}

void cSTLReader::Release()
{
	if (mVertexBuffer)
		free(mVertexBuffer);

	if (mIndexBuffer)
		free(mIndexBuffer);

	mSmoothSTL.Release();

	m_Imp.Release();
}

//////////////////////////////////////////////////////////////////////////
cSTLReaderBin::cSTLReaderBin(): cSTLReader()
{

}
cSTLReaderBin:: ~cSTLReaderBin()
{

}



void cSTLReaderBin::FileRead(const char* pPath, bool smooth)
{
	Release();
	
	if (!m_Imp.Open_Bin(pPath))
	{
		return;
	}
	
	m_Imp.getHeader_Bin(m_Header, 80);
	m_Imp.getNTraingles_Bin(&m_nTriangles, 4);
	
	m_nIndices = m_nTriangles * 3;
	S_STLFileData data;
	int idx[3] = { 0,2,1 };
	if (smooth)
	{
		mSmoothSTL.AllocateBuffer(m_nIndices);
		mIndexBuffer = (DWORD *)malloc(m_nIndices * sizeof(DWORD));
		memset(mIndexBuffer, 0, m_nIndices * sizeof(DWORD));
		
		for (int i = 0; i < static_cast<int>(m_nTriangles); i++)
		{
			m_Imp.ReadNormalVertex(&data, 48);
			m_Imp.ReadDummy_Bin(2);
			XMFLOAT3 *l_VertexTmp[3] = { &data.Vertex1, &data.Vertex2, &data.Vertex3 };

			data.Normal.x = -data.Normal.x;
			for (int j = 0; j < 3; j++)
			{
				l_VertexTmp[j]->x = -l_VertexTmp[j]->x;
				float l_sum = l_VertexTmp[j]->x + l_VertexTmp[j]->y + l_VertexTmp[j]->z;
				//mIndexBuffer[mSmoothSTL.mIndexCnt++] = mSmoothSTL.RecordVertexToTable2(l_VertexTmp[j], &data.Normal, l_sum);
				
				mIndexBuffer[mSmoothSTL.mIndexCnt + idx[j]] = mSmoothSTL.RecordVertexToTable2(l_VertexTmp[j], &data.Normal, l_sum);
				
				//mIndexBuffer[mSmoothSTL.mIndexCnt++] = mSmoothSTL.RecordVertexToTable(l_VertexTmp[j], &data.Normal);
			}
			mSmoothSTL.mIndexCnt += 3;
		}
		
		mSmoothSTL.AverageNormal();
		mVertexBuffer = (S_STLVertex*)malloc(mSmoothSTL.mTableCnt * sizeof(S_STLVertex));
		memcpy(mVertexBuffer, mSmoothSTL.mTable, mSmoothSTL.mTableCnt * sizeof(S_STLVertex));
		m_Vertexes = mSmoothSTL.mTableCnt;

		// calculate center of mass 
		CalCenterOfMass(mSmoothSTL.mTable, mSmoothSTL.mTableCnt);
	}
	else
	{
		mVertexBuffer = (S_STLVertex*)malloc(m_nIndices * sizeof(S_STLVertex));
		
		for (int i = 0; i < static_cast<int>(m_nTriangles); i++)
		{
			m_Imp.ReadNormalVertex(&data, 48);
			m_Imp.ReadDummy_Bin(2);
			XMFLOAT3 *l_VertexTmp[3] = { &data.Vertex1, &data.Vertex2, &data.Vertex3 };
			data.Normal.x = -data.Normal.x;
			for (int j = 0; j < 3; j++)
			{
				l_VertexTmp[j]->x = -l_VertexTmp[j]->x;

				mVertexBuffer[i * 3 + idx[j]].Normal = data.Normal;
				mVertexBuffer[i * 3 + idx[j]].Pos = *l_VertexTmp[j];
			}
		}
		m_Vertexes = m_nIndices;

		// calculate center of mass 
		CalCenterOfMass(mVertexBuffer, m_nIndices);
	}
	
}

//////////////////////////////////////////////////////////////////////////
cSTLImplement::cSTLImplement(): m_FS()
{
	
}
void cSTLImplement::Release()
{
	if (m_FS)
		m_FS.close();
}

float cSTLImplement::ParseFloatFromByte()
{
	char l_Float_Buf[sizeof(float)];
	m_FS.read(l_Float_Buf, 4);
	float* l_FloatValue = (float*)l_Float_Buf;
	return *l_FloatValue;
}

bool cSTLImplement::Open_Bin(const char *pPath)
{
	m_FS.open(pPath, std::ios::in | std::ios::binary);
	if (!m_FS)
	{
		MessageBoxA(NULL, "Cannot Open STL Bin File", "Cadceus3D", MB_OK);
		return false;
	}
	return true;
}
void cSTLImplement::getHeader_Bin(char* pHeader, int cnt)
{
	char *l_Header = (char*)malloc(cnt * sizeof(char));
	m_FS.read(l_Header, cnt);
	memcpy(pHeader, l_Header, cnt);
	free(l_Header);
}

void cSTLImplement::getNTraingles_Bin(unsigned int *pNTrangles, int cnt)
{
	char *l_Triangles = (char*)malloc(cnt * sizeof(char));
	m_FS.read(l_Triangles, cnt);
	unsigned int* n = (unsigned int*)l_Triangles;
	*pNTrangles = *n;
	free(l_Triangles);
}

void cSTLImplement::ReadNormalVertex(S_STLFileData *pdata, int cnt)
{
	m_FS.read((char*)pdata, cnt);
}

void cSTLImplement::ReadDummy_Bin(int cnt)
{
	char *l_dummy = (char*)malloc(cnt * sizeof(char));
	m_FS.read(l_dummy, cnt);
	free(l_dummy);
}

cSmoothSTL::cSmoothSTL(): mTable(NULL), mNormalCnt(NULL), mTableCnt(0), mIndexCnt(0)
{
	mUmap.clear();
}

cSmoothSTL::~cSmoothSTL()
{
	this->Release();
}

void cSmoothSTL::Release()
{
	if (mTable)
		free(mTable);

	if (mNormalCnt)
		free(mNormalCnt);

	mUmap.clear();

	mTableCnt = 0;
	mIndexCnt = 0;
}

void cSmoothSTL::AllocateBuffer(int cnt)
{
	mTable = (S_STLVertex*)malloc(cnt * sizeof(S_STLVertex));
	memset(mTable, 0, cnt * sizeof(S_STLVertex));

	mNormalCnt = (int*)malloc(cnt * sizeof(int));
	memset(mNormalCnt, 0, cnt * sizeof(int));
}

DWORD cSmoothSTL::RecordVertexToTable(XMFLOAT3 *pVertex, XMFLOAT3 *pNormal)
{
	for (int i = 0; i < mTableCnt; i++)
	{
		if ((pVertex->x == mTable[i].Pos.x) &&
			(pVertex->y == mTable[i].Pos.y) &&
			(pVertex->z == mTable[i].Pos.z))
		{
			mTable[i].Normal.x += pNormal->x;
			mTable[i].Normal.y += pNormal->y;
			mTable[i].Normal.z += pNormal->z;
			mNormalCnt[i]++;
			return i;
		}
	}

	mTable[mTableCnt].Pos.x = pVertex->x;
	mTable[mTableCnt].Pos.y = pVertex->y;
	mTable[mTableCnt].Pos.z = pVertex->z;

	mTable[mTableCnt].Normal.x = pNormal->x;
	mTable[mTableCnt].Normal.y = pNormal->y;
	mTable[mTableCnt].Normal.z = pNormal->z;

	mNormalCnt[mTableCnt]++;
	mTableCnt++;

	return (mTableCnt - 1);
}

DWORD cSmoothSTL::RecordVertexToTable2(XMFLOAT3 *pVertex, XMFLOAT3 *pNormal, float sum)
{
	if (mUmap.count(sum) > 0)
	{
		std::list<int> tmp = mUmap[sum];
		for (int element : tmp)
		{
			if ((pVertex->x == mTable[element].Pos.x) &&
				(pVertex->y == mTable[element].Pos.y) &&
				(pVertex->z == mTable[element].Pos.z))
			{
				mTable[element].Normal.x += pNormal->x;
				mTable[element].Normal.y += pNormal->y;
				mTable[element].Normal.z += pNormal->z;
				mNormalCnt[element]++;
				return element;
			}
		}
	}

	mUmap[sum].push_back(mTableCnt);
	
	mTable[mTableCnt].Pos.x = pVertex->x;
	mTable[mTableCnt].Pos.y = pVertex->y;
	mTable[mTableCnt].Pos.z = pVertex->z;

	mTable[mTableCnt].Normal.x = pNormal->x;
	mTable[mTableCnt].Normal.y = pNormal->y;
	mTable[mTableCnt].Normal.z = pNormal->z;

	mNormalCnt[mTableCnt]++;
	mTableCnt++;

	return (mTableCnt - 1);

}

void cSmoothSTL::AverageNormal()
{
	for (int i = 0; i < mTableCnt; i++)
	{
		mTable[i].Normal.x /= mNormalCnt[i];
		mTable[i].Normal.y /= mNormalCnt[i];
		mTable[i].Normal.z /= mNormalCnt[i];
	}
}
