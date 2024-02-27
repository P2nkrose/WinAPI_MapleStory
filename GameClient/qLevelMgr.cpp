#include "pch.h"
#include "qLevelMgr.h"

#include "qCollisionMgr.h"

#include "qLevel.h"
#include "qLevel_Stage01.h"

#include "qPlayer.h"
#include "qMonster.h"
#include "qPlatform.h"

qLevelMgr::qLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{

}


qLevelMgr::~qLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);
}


void qLevelMgr::init()
{
	// 모든 레벨 생성
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new qLevel_Stage01;

	// 현재 레벨 지정
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// 레벨에 물체 추가하기
	qObj* pObject = new qPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(640.0f, 384.0f);
	pObject->SetScale(100.0f, 100.0f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pObject);

	//qObj* pPlayerClone = pObject->Clone();
	//pPlayerClone->SetPos(800.f, 400.f);
	//m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pPlayerClone);


	// 레벨에 몬스터 추가하기
	pObject = new qMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(800.0f, 200.0f);
	pObject->SetScale(100.0f, 100.0f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::MONSTER, pObject);
	
	// 한마리 더!
	pObject = new qMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(100.0f, 100.0f);
	pObject->SetScale(100.0f, 100.0f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::MONSTER, pObject);

	// 플랫폼 생성
	pObject = new qPlatform;
	pObject->SetName(L"Platform");
	pObject->SetPos(Vec2(640.f, 700.f));
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLATFORM, pObject);


	// 레벨 충돌 설정하기
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	
	// 레벨 시작 (플레이)
	m_pCurrentLevel->begin();
}

void qLevelMgr::progress()
{
	if (nullptr == m_pCurrentLevel)
		return;

	m_pCurrentLevel->tick();
	m_pCurrentLevel->finaltick();

}

void qLevelMgr::render()
{
	m_pCurrentLevel->render();
}
