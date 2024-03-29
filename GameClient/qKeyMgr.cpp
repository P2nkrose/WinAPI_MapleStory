#include "pch.h"
#include "qKeyMgr.h"

#include "qEngine.h"



UINT g_RealKey[(UINT)KEY::KEY_END] =
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',

	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,

	VK_RETURN,
	VK_SPACE,
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_ESCAPE,

	VK_LBUTTON,
	VK_RBUTTON,
};

qKeyMgr::qKeyMgr()
{

}

qKeyMgr::~qKeyMgr()
{

}

void qKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::KEY_END; ++i)
	{
		tKeyInfo info = {};
		info.eKey = (KEY)i;
		info.eKeyState = KEY_STATE::NONE;
		info.bPressed = false;

		m_vecKeyInfo.push_back(info);
	}
}


void qKeyMgr::tick()
{

	// Main Window 가 포커싱 상태이다.
	if (qEngine::GetInst()->GetMainWnd() == GetFocus())
	{
		for (UINT i = 0; i < (UINT)m_vecKeyInfo.size(); ++i)
		{
			// 지금 키가 눌려있는지 체크
			if (0x8001 & GetAsyncKeyState(g_RealKey[(UINT)m_vecKeyInfo[i].eKey]))
			{
				// 이전에도 눌려있었는지
				if (m_vecKeyInfo[i].bPressed)
				{
					m_vecKeyInfo[i].eKeyState = KEY_STATE::PRESSED;
				}
				else
				{
					m_vecKeyInfo[i].eKeyState = KEY_STATE::TAP;
				}

				m_vecKeyInfo[i].bPressed = true;
			}

			// 키가 안눌려있음
			else
			{
				// 이전에는 눌려있었음
				if (m_vecKeyInfo[i].bPressed)
				{
					m_vecKeyInfo[i].eKeyState = KEY_STATE::RELEASED;
				}
				else
				{
					m_vecKeyInfo[i].eKeyState = KEY_STATE::NONE;
				}

				m_vecKeyInfo[i].bPressed = false;
			}
		}

		// 마우스 좌표 계산
		m_PrevMousePos = m_MousePos;

		POINT ptMousePos = {};
		GetCursorPos(&ptMousePos);
		ScreenToClient(qEngine::GetInst()->GetMainWnd(), &ptMousePos);
		m_MousePos = ptMousePos;
		m_DragDir = m_MousePos - m_PrevMousePos;

	}

	// 윈도우 포커싱 해제됨
	else
	{
		for (UINT i = 0; i < (UINT)m_vecKeyInfo.size(); ++i)
		{
			if (m_vecKeyInfo[i].eKeyState == KEY_STATE::TAP || m_vecKeyInfo[i].eKeyState == KEY_STATE::PRESSED)
			{
				m_vecKeyInfo[i].eKeyState = KEY_STATE::RELEASED;
			}
			else
			{
				m_vecKeyInfo[i].eKeyState = KEY_STATE::NONE;
			}

			m_vecKeyInfo[i].bPressed = false;
		}
	}


	
}
