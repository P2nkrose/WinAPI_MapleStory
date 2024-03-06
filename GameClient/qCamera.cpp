#include "pch.h"
#include "qCamera.h"

#include "qEngine.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"

#include "qObj.h"

qCamera::qCamera()
	: m_CamSpeed(500.f)
	, m_FadeTex(nullptr)
{
}

qCamera::~qCamera()
{
}

void qCamera::init()
{
	Vec2 vResol = qEngine::GetInst()->GetResolution();
	m_LookAt = Vec2(vResol.x * 0.5f, vResol.y * 0.5f);

	//// 윈도우 해상도랑 동일한 크기의 검은색 텍스쳐를 생성
	m_FadeTex = qAssetMgr::GetInst()->CreateTexture(L"FadeTexture", (UINT)vResol.x, (UINT)vResol.y);

	//// 윈도우 해상도랑 동일한 크기의 붉은색 텍스쳐를 생성
	//m_RedTex = qAssetMgr::GetInst()->CreateTexture(L"RedTexture", (UINT)vResol.x, (UINT)vResol.y);

	//// Red Texture 에 Red Brush로 Rectangle 을 그린다.
	//USE_BRUSH(m_RedTex->GetDC(), BRUSH_TYPE::BRUSH_RED);
	//Rectangle(m_RedTex->GetDC(), -1, -1, (UINT)vResol.x + 1, (UINT)vResol.y + 1);

	//for (UINT Row = 0; Row < vResol.y; ++Row)
	//{
	//	for (UINT Col = 0; Col < vResol.x; ++Col)
	//	{
	//		SetPixel(m_RedTex->GetDC(), Col, Row, RGB(255, 0, 0));
	//	}
	//}
}

void qCamera::tick()
{
	// 카메라가 캐릭터 따라다니게 하기
	m_LookAt.x = m_Owner->GetPos().x;
	//m_LookAt.y = m_Owner->GetPos().y / 1.5f;

	// 카메라 이동
	Move();
	
	// 해상도 중심과 카메라가 바라보고 있는 지점 간의 차이값
	Vec2 vResol = qEngine::GetInst()->GetResolution();
	m_Diff = m_LookAt - Vec2(vResol.x * 0.5f, vResol.y * 0.5f);

	// 카메라 효과
	CameraEffect();
}

void qCamera::render()
{
	if (m_EffectList.empty())
		return;

	CAM_EFFECT_INFO& info = m_EffectList.front();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)info.Alpha;
	bf.AlphaFormat = 0;

	AlphaBlend(DC, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight()
		, m_FadeTex->GetDC(), 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), bf);
}


void qCamera::Move()
{
	if (KEY_PRESSED(KEY::W))
		m_LookAt.y -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::S))
		m_LookAt.y += DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::A))
		m_LookAt.x -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::D))
		m_LookAt.x += DT * m_CamSpeed;
}

void qCamera::CameraEffect()
{
	while (true)
	{
		if (m_EffectList.empty())
			return;

		CAM_EFFECT_INFO& info = m_EffectList.front();
		info.Time += DT;

		if (info.Duration < info.Time)
		{
			m_EffectList.pop_front();
		}
		else
		{
			break;
		}
	}

	CAM_EFFECT_INFO& info = m_EffectList.front();

	if (CAM_EFFECT::FADE_IN == info.Effect)
	{
		info.Alpha = (1.f - (info.Time / info.Duration)) * 255.f;
	}
	else if (CAM_EFFECT::FADE_OUT == info.Effect)
	{
		info.Alpha = (info.Time / info.Duration) * 255.f;
	}
}

void qCamera::SetCameraEffect(CAM_EFFECT _Effect, float _Duration)
{
	CAM_EFFECT_INFO info = {};

	info.Effect = _Effect;
	info.Duration = _Duration;
	info.Time = 0.f;
	info.Alpha = 0.f;

	m_EffectList.push_back(info);
}
