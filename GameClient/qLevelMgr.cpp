#include "pch.h"
#include "qLevelMgr.h"

#include "qLevel.h"
#include "qLevel_Stage01.h"

#include "qObj.h"

qLevelMgr::qLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{

}


qLevelMgr::~qLevelMgr()
{

}


void qLevelMgr::init()
{
	// ��� ���� ����
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new qLevel_Stage01;

	// ���� ���� ����
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// ������ ��ü �߰��ϱ�
	qObj* pObject = new qObj;
	pObject->SetPos(640.0f, 384.0f);
	pObject->SetScale(100.0f, 100.0f);

	m_pCurrentLevel->AddObject(pObject);
}

void qLevelMgr::progress()
{
	if (nullptr == m_pCurrentLevel)
		return;

	m_pCurrentLevel->tick();
	m_pCurrentLevel->finaltick();
	m_pCurrentLevel->render();
}