#pragma once
#include "qComponent.h"
#include "qAnimation.h"

class qAnimation;
class qTexture;

class qAnimator : public qComponent
{
public:
	CLONE(qAnimator);

public:
	qAnimator();
	qAnimator(const qAnimator& _Other);
	~qAnimator();


	virtual void finaltick() override;
	void render();

	void CreateAnimation(const wstring& _AnimName, qTexture* _Atlas, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);
	qAnimation* FindAnimation(const wstring& _AnimName);
	void LoadAnimation(const wstring& _strRelativeFilePath);

	void Play(const wstring& _AnimName, bool _Repeat);

	bool IsFinish() { return m_CurAnim->IsFinish(); }

public:
	qAnimation* GetCurAnim() { return m_CurAnim; }


private:
	map<wstring, qAnimation*>	m_mapAnim;
	qAnimation*					m_CurAnim;
	bool						m_Repeat;



};

