#include "pch.h"
#include "qTileMap.h"

#include "qEngine.h"
#include "qDbgRender.h"

#include "qTexture.h"



qTileMap::qTileMap()
	: m_Row(1)
	, m_Col(1)
	, m_TileSize(Vec2(TILE_SIZE, TILE_SIZE))
	, m_AtlasTex(nullptr)
	, m_MaxImgRow(0)
	, m_MaxImgCol(0)
{
}

qTileMap::~qTileMap()
{
}

void qTileMap::finaltick()
{
}

void qTileMap::render()
{
	render_tile();

	if (qDbgRender::GetInst()->IsDbgRender())
	{
		render_grid();
	}
}




void qTileMap::render_grid()
{
	Vec2 vRenderPos = GetOwner()->GetRenderPos();

	USE_PEN(DC, PEN_TYPE::PEN_GREEN);
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

	for (UINT i = 0; i < m_Row; ++i)
	{
		for (UINT j = 0; j < m_Col; ++j)
		{
			Rectangle(DC, (int)(vRenderPos.x + m_TileSize.x * j), (int)(vRenderPos.y + m_TileSize.y * i),
				(int)(vRenderPos.x + m_TileSize.x * j + m_TileSize.x), (int)(vRenderPos.y + m_TileSize.y * i + m_TileSize.y));
		}
	}
}

void qTileMap::render_tile()
{
	if (nullptr == m_AtlasTex)
		return;

	Vec2 vRenderPos = GetOwner()->GetRenderPos();

	USE_PEN(DC, PEN_TYPE::PEN_GREEN);
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

	for (UINT i = 0; i < m_Row; ++i)
	{
		for (UINT j = 0; j < m_Col; ++j)
		{
			// 현재 i(행), j(열) 을 1차원 인덱스로 바꾸어서 렌더링하려는 타일의 정보를 Vector 에서 꺼내온다.
			int TileIdx = m_Col * i + j;

			// 해당 타일정보에서 이미지 인덱스를 확인하고, 아틀라스 텍스쳐에서 이미지 인덱스에 맞는 부위를 화면에 출력한다.
			UINT TileImgRow = m_vecTileInfo[TileIdx].ImgIdx / m_MaxImgCol;
			UINT TileImgCol = m_vecTileInfo[TileIdx].ImgIdx % m_MaxImgCol;

			// 해당 타일의 이미지 인덱스가 아틀라스가 보유한 타일 행, 열을 초과한 경우
			assert(!(m_MaxImgRow <= TileImgRow));

			BitBlt(DC, (int)(vRenderPos.x + m_TileSize.x * j)
				     , (int)(vRenderPos.y + m_TileSize.y * i)
				     , m_TileSize.x, m_TileSize.y
				     , m_AtlasTex->GetDC()
				     , TileImgCol * m_TileSize.x
				     , TileImgRow * m_TileSize.y, SRCCOPY);
		}
	}
}

void qTileMap::Clicked(Vec2 _vMousePos)
{
	// 마우스 좌표를 실제 게임 공간 좌표로 변경한다.
	_vMousePos = qCamera::GetInst()->GetRealPos(_vMousePos);

	// 클릭한 지점이 타일 영역을 벗어나 있으면 return 한다.
	Vec2 vObjPos = GetOwner()->GetPos();

	if (_vMousePos.x < vObjPos.x
		|| _vMousePos.y < vObjPos.y
		|| vObjPos.x + m_Col * m_TileSize.x < _vMousePos.x
		|| vObjPos.y + m_Row * m_TileSize.y < _vMousePos.y)
	{
		return;
	}

	// 타일 전체가 이동된 경우를 생각해서 마우스 위치를 보정해 준다.
	_vMousePos -= vObjPos;

	// 마우스로 클릭한 지점에 몇행 몇열인지 계산
	int ClickCol = (int)_vMousePos.x / m_TileSize.x;
	int ClickRow = (int)_vMousePos.y / m_TileSize.y;

	// 클릭한 지점의 타일을 1차원 인덱스로 변경해서 타일 벡터에서 해당 정보에 접근한다.
	int TileIdx = m_Col * ClickRow + ClickCol;

	// 해당 타일 정보에서 참조 이미지 인덱스를 1개 증가시킨다.
	m_vecTileInfo[TileIdx].ImgIdx += 1;

	// 만약 이미지 인덱스가, 아틀라스에서 제공하는 이미지 개수를 초과해서 참조하게 되면
	// 다시 첫번째 이미지를 참조하도록 이미지 인덱스를 0으로 설정한다.
	if (m_MaxImgCol * m_MaxImgRow <= m_vecTileInfo[TileIdx].ImgIdx)
	{
		m_vecTileInfo[TileIdx].ImgIdx = 0;
	}

}


void qTileMap::SetRow(UINT _Row)
{
	m_Row = _Row;
	m_vecTileInfo.clear();
	m_vecTileInfo.resize(m_Row * m_Col);
}

void qTileMap::SetCol(UINT _Col)
{
	m_Col = _Col;
	m_vecTileInfo.clear();
	m_vecTileInfo.resize(m_Row * m_Col);
}

void qTileMap::SetRowCol(UINT _Row, UINT _Col)
{
	m_Row = _Row;
	m_Col = _Col;

	m_vecTileInfo.clear();
	m_vecTileInfo.resize(m_Row * m_Col);
}

void qTileMap::SetAtlasTex(qTexture* _Atlas)
{
	m_AtlasTex = _Atlas;

	if (m_AtlasTex)
	{
		m_MaxImgCol = m_AtlasTex->GetWidth() / m_TileSize.x;
		m_MaxImgRow = m_AtlasTex->GetHeight() / m_TileSize.y;
	}
}


void qTileMap::SaveToFile(FILE* _File)
{
	fwrite(&m_Row, sizeof(UINT), 1, _File);
	fwrite(&m_Col, sizeof(UINT), 1, _File);
	fwrite(&m_TileSize, sizeof(Vec2), 1, _File);
	fwrite(m_vecTileInfo.data(), sizeof(tTileInfo), m_vecTileInfo.size(), _File);

	bool bAtlasTex = m_AtlasTex;
	fwrite(&bAtlasTex, sizeof(bool), 1, _File);

	if (bAtlasTex)
	{
		wstring strKey = m_AtlasTex->GetKey();
		wstring strRelativePath = m_AtlasTex->GetRelativePath();

		SaveWString(strKey, _File);
		SaveWString(strRelativePath, _File);
	}
}

void qTileMap::LoadPlatform(FILE* _File)
{
	fread(&m_Row, sizeof(UINT), 1, _File);
	fread(&m_Col, sizeof(UINT), 1, _File);
	fread(&m_TileSize, sizeof(Vec2), 1, _File);
	SetRowCol(m_Row, m_Col);
	fread(m_vecTileInfo.data(), sizeof(tTileInfo), m_vecTileInfo.size(), _File);

	bool bAtlasTex = m_AtlasTex;
	fread(&bAtlasTex, sizeof(bool), 1, _File);

	if (bAtlasTex)
	{
		wstring strKey, strRelativePath;

		LoadWString(strKey, _File);
		LoadWString(strRelativePath, _File);
		m_AtlasTex = qAssetMgr::GetInst()->LoadTexture(strKey, strRelativePath);

		SetAtlasTex(m_AtlasTex);
	}
}