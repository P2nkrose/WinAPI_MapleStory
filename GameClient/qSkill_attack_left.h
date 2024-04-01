#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qSkill_attack_left : public qObj
{
	CLONE(qSkill_attack_left);

public:
	qSkill_attack_left();
	qSkill_attack_left(const qSkill_attack_left& _Other);
	~qSkill_attack_left();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;


private:
	qAnimator* m_Animator;
	qCollider* m_Collider;
};
