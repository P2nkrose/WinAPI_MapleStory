#include "pch.h"
#include "qStart.h"

#include "qLevelMgr.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"

#include "qButton.h"


void ButtonCallBackFunc()
{
	//qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	//qStart* pStart = dynamic_cast<qStart*>(pLevel);
	//if (nullptr == pStart)
	//	return;

	ChangeLevel(LEVEL_TYPE::STAGE_01);
}


qStart::qStart()
{
}

qStart::~qStart()
{
}

void qStart::begin()
{
}

void qStart::Enter()
{
	// 화면 해상도
	Vec2 vResol = qEngine::GetInst()->GetResolution();

	// UI 추가
	qButton* pUI = new qButton;

	pUI->SetCallBack(&ButtonCallBackFunc);
	pUI->SetScale(Vec2(200.f, 100.f));
	pUI->SetPos(Vec2(vResol.x - (pUI->GetScale().x + 10), 10.f));
	AddObject(LAYER_TYPE::UI, pUI);
}

void qStart::Exit()
{
}
