#include "pch.h"
#include "qLevel_stage1.h"

#include "qKeyMgr.h"
#include "qForce.h"

#include "qLevelMgr.h"
#include "qCollisionMgr.h"
#include "qPlayer.h"
#include "qMonster.h"
#include "qPlatform.h"
#include "qBackground_stage1.h"

#include "qSound.h"

qLevel_stage1::qLevel_stage1()
{
	SetName(L"Stage1");
}

qLevel_stage1::~qLevel_stage1()
{
}

void qLevel_stage1::begin()
{
	qLevel::begin();

	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\stage1.wav");
	pSound->SetVolume(50.f);
	pSound->Play();

	// 페이드 인 페이드 아웃
	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.7f);
	//qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 1.f);


}

void qLevel_stage1::tick()
{
	qLevel::tick();

	//if (KEY_TAP(KEY::LBTN))
	//{
	//	Vec2 vMousePos = qKeyMgr::GetInst()->GetMousePos();
	//	Vec2 vPos = qCamera::GetInst()->GetRenderPos(vMousePos);

	//	qForce* pForce = new qForce();
	//	pForce->SetPos(vPos);
	//	pForce->SetForce(1000.f, 500.f, 2.f);
	//	SpawnObject(this, LAYER_TYPE::FORCE, pForce);
	//}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	if (KEY_TAP(KEY::Z))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_02);
	}
}

void qLevel_stage1::Enter()
{
	

	// 레벨에 오브젝트 추가
	// 
	// Background
	qObj* pBack = new qBackground_stage1;
	pBack->SetName(L"Stage1");
	pBack->SetPos(0.0f, 0.f);
	pBack->SetScale(1.3f, 1.3f);
	AddObject(LAYER_TYPE::BACKGROUND, pBack);
	

	// Player
	qObj* pObject = new qPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(1400.f, 745.f);
	pObject->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::PLAYER, pObject);

	// 플레이어 클론
	//qObj* pPlayerClone = pObject->Clone();
	//pPlayerClone->SetPos(800.f, 400.f);
	//m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pPlayerClone);


	//// 레벨에 몬스터 추가하기
	//pObject = new qMonster;
	//pObject->SetName(L"Monster");
	//pObject->SetPos(800.0f, 200.0f);
	//pObject->SetScale(100.0f, 100.0f);
	//AddObject(LAYER_TYPE::MONSTER, pObject);

	//// 한마리 더!
	//pObject = new qMonster;
	//pObject->SetName(L"Monster");
	//pObject->SetPos(100.0f, 100.0f);
	//pObject->SetScale(100.0f, 100.0f);
	//AddObject(LAYER_TYPE::MONSTER, pObject);

	// 플랫폼 생성
	pObject = new qPlatform;
	pObject->SetName(L"Platform");
	pObject->SetPos(Vec2(640.f, 700.f));
	AddObject(LAYER_TYPE::PLATFORM, pObject);

	// 콜라이더 읽어오기
	LoadFromFile(L"platform\\platform.plat");


	// 레벨 충돌 설정하기
	qCollisionMgr::GetInst()->CollisionCheckClear();
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);


	
}

void qLevel_stage1::Exit()
{
	

	pSound->SetVolume(50.f);
	pSound->Stop();

	// 레벨에 있는 모든 오브젝트 삭제한다.
	DeleteAllObjects();

	//qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 1.f);
}
