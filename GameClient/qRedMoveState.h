#pragma once
#include "qState.h"

class qRedMoveState : public qState
{
public:

	CLONE(qRedMoveState);

	qRedMoveState();
	~qRedMoveState();

public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	Vec2		m_CenterPos;
	float		m_MaxDistance;
	float		m_Dir;
};

