#pragma once

struct QTINFO;
class QuadTree;
class QuadNode;
class Terrain
{
public:	
	void Init(int _patchCnt,char* _name);
	void InitVB(void);
	void InitIB(void);
	void Update(float dTime);
	void Render(void);
	void Release(void);

	float GetPlayerHeight(D3DXVECTOR3 _vPos);
	void TerrainUpDown(float dTime, bool bUP);

public:	
	void QuadTreeCreate(int _lev);
	void QuadCulling(D3DXVECTOR3 _vPos);
	
	static void SetQTIndex(QuadNode* pNode, QTINFO& data);
	void setUpDown(bool _TerrUpDown);

public:
	void initCircle(void);			//클래스로 만들기
	void UpdateCircle(void);
	void RenderCircle(void);
	void ReleaseCircle();
		
	bool Collison( D3DXVECTOR3 _vPos);	
	void LockVB();
	
	void CreateAlphaTexture(void);
	void RenderAlphaTexture(void);
	void UpdateAlphaTexture(void);

	void SetSize(int _size){m_iPatchCnt			= _size;
							m_iVertexCnt		= _size + 1;}

	void	SeteditMode(int neditMode) { m_ieditMode = neditMode; }
	void	SetQuadSize(float fQuadSize) { m_fQuadSize = fQuadSize; }

	D3DXVECTOR3 GetvMouse() const { return m_vMouse; }
	int GetVertexCnt() const {return m_iVertexCnt;}
	D3DFVF_XYZ_NORMAL_TEX1* GetTerrainVB() const { return  m_pTerrainVB; }

public:
	Terrain(void);
	virtual ~Terrain(void);

private:
	int							m_iPatchCnt;
	int							m_iVertexCnt;
	int							m_iTotalVertexCnt;
	int							m_iTotalFaceCnt;
	int							m_iQTTotalFaceCnt;
	int							m_TerrUpDown;
	int							m_iAlphaSize;
	int							m_iCircleCnt;
	int							m_ieditMode;
	float						m_fQuadSize;

	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;
	LPDIRECT3DTEXTURE9			m_pTexture;

	D3DFVF_XYZ_NORMAL_TEX1*		m_pTerrainVB;
	D3DINDEX*					m_pTerrainIB;

	LPDIRECT3DTEXTURE9			m_pSplatTexture;
	LPDIRECT3DTEXTURE9			m_pAlphaTexture;
	
	D3DXVECTOR3					m_vMouse;
	
	LPDIRECT3DVERTEXBUFFER9		m_pCircleVB;
	QuadTree*					m_pQuadTree;
	LPDIRECT3DINDEXBUFFER9		m_pQTIB;
	D3DINDEX*					m_pQTTerrainIB;
	QTINFO						m_pInfo;
	

};

