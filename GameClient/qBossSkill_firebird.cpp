#include "pch.h"
#include "qBossSkill_firebird.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qTaskMgr.h"

qBossSkill_firebird::qBossSkill_firebird()
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation �߰�
	qTexture* BossSkillFirebird = qAssetMgr::GetInst()->LoadTexture(L"BossSkillFirebird", L"texture\\boss_skill\\firebird\\firebird.png");

	// �ִϸ��̼� CREATE
	m_Animator->CreateAnimation(L"BossSkillFirebird", BossSkillFirebird, Vec2(0.f, 0.f), Vec2(700.f, 400.f), 20, 10);

	// �ִϸ��̼� SAVE
	m_Animator->FindAnimation(L"BossSkillFirebird")->Save(L"animation\\boss_skill\\firebird\\");

	// �ִϸ��̼� LOAD
	m_Animator->LoadAnimation(L"animation\\boss_skill\\firebird\\BossSkillFirebird.anim");

	m_Animator->Play(L"BossSkillFirebird", false);




	// �ݶ��̴�
	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(10.f, 3.f));
	//m_Collider->SetScale(Vec2(450.f, 300.f));
	m_Collider->SetScale(Vec2(0.f, 0.f));

}

qBossSkill_firebird::~qBossSkill_firebird()
{
}

void qBossSkill_firebird::tick()
{
	qObj::tick();

	if (m_Animator->GetCurAnim()->GetCurFrmIdx() == 12)
	{
		m_Collider->SetScale(Vec2(450.f, 300.f));
	}


	if (L"BossSkillFirebird" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}

void qBossSkill_firebird::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}