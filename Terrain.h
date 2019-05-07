#pragma once

struct QTINFO;
class QuadTree;
class QuadNode;
class Terrain
{
public:
	int							m_iPatchCnt;
	int							m_iVertexCnt;
	int							m_iTotalVertexCnt;
	int							m_iTotalFaceCnt;

	int							g_TerrUpDown;

	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;
	LPDIRECT3DTEXTURE9			m_pTexture;

	D3DFVF_XYZ_NORMAL_TEX1*		m_pTerrainVB;
	D3DINDEX*					m_pTerrainIB;
	
	void Init(int _patchCnt,char* _name);
	void InitVB(void);
	void InitIB(void);
	void Update(float dTime);
	void Render(void);
	void Release(void);

	float GetPlayerHeight(D3DXVECTOR3 _vPos);
	void TerrainUp(float dTime);

public:
	QuadTree*					m_pQuadTree;
	int							m_iQTTotalFaceCnt;
	LPDIRECT3DINDEXBUFFER9		m_pQTIB;
	D3DINDEX*					m_pQTTerrainIB;

	void QuadTreeCreate(int _lev);
	void QuadCulling(D3DXVECTOR3 _vPos);
	QTINFO						m_pInfo;

	static void SetQTIndex(QuadNode* pNode, QTINFO& data);

	int						m_ieditMode;
	float					g_fQuadSize;

	void setUpDown(bool _TerrUpDown);

public:
	void initCircle(void);			//클래스로 만들기
	void UpdateCircle(void);
	void RenderCircle(void);
	void ReleaseCircle();
	
	int m_iCircleCnt;
	LPDIRECT3DVERTEXBUFFER9			m_pCircleVB;
	bool Collison( D3DXVECTOR3 _vPos);
	D3DXVECTOR3		m_vMouse;
	void LockVB();
public:
	LPDIRECT3DTEXTURE9			m_pSplatTexture;
	LPDIRECT3DTEXTURE9			m_pAlphaTexture;
	int							m_iAlphaSize;
	void CreateAlphaTexture(void);
	void RenderAlphaTexture(void);
	void UpdateAlphaTexture(void);

	void SetSize(int _size){m_iPatchCnt			= _size;
							m_iVertexCnt		= _size + 1;}
public:
	Terrain(void);
	virtual ~Terrain(void);
};
