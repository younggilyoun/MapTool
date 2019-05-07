//
// SWRender Basic FrameWork
//
// Grid.h : ������� ��ġ�� Ȯ���ϱ� ���� �׸���
//
// ==================================================================//
// 2012.7.23
//
#pragma once

// �׸��� ���� //
struct GRIDINFO
{
	int			_w;
	int			_h;
	float		_scale;
	D3DXCOLOR	_color;
};

class Grid
{
private:
	LPDIRECT3DVERTEXBUFFER9			m_pVB;
	D3DXMATRIX						m_mTM;

	D3DFVF_XYZ_COLOR*				m_pVertex;
	GRIDINFO						m_Info;

	int								m_iLineCount;

public:
	void		Init_Grid(GRIDINFO pGrid);
	void		Render_Grid(void);

public:
	Grid(void);
	virtual ~Grid(void);
};
