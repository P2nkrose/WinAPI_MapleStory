#pragma once

enum class KEY
{
	_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	LEFT, RIGHT, UP, DOWN,

	ENTER,
	SPACE,
	ALT,
	CTRL,
	SHIFT,
	ESC,

	LBTN,
	RBTN,

	KEY_END,
};


enum class KEY_STATE
{
	TAP,			// 막 눌렀을때
	PRESSED,		// 눌려있을때
	RELEASED,		// 막 뗐을때
	NONE,
};



struct tKeyInfo
{
	KEY			eKey;			// 키의 종류
	KEY_STATE	eKeyState;		// 키의 상태값
	bool		bPressed;		// 지금 눌려있는지

};

class qKeyMgr
{
	SINGLE(qKeyMgr);

public:
	void init();
	void tick();

public:
	KEY_STATE GetKeyState(KEY _Key){return m_vecKeyInfo[(UINT)_Key].eKeyState;	}
	Vec2 GetMousePos() { return m_MousePos; }
	Vec2 GetDragDir() { return m_DragDir; }

private:
	vector<tKeyInfo>	m_vecKeyInfo;

	Vec2				m_MousePos;
	Vec2				m_PrevMousePos;
	Vec2				m_DragDir;

};

