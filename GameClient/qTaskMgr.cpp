#include "pch.h"
#include "qTaskMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qObj.h"

qTaskMgr::qTaskMgr()
{

}

qTaskMgr::~qTaskMgr()
{

}


void qTaskMgr::tick()
{
	ClearGC();

	ExcuteTask();
}


void qTaskMgr::ClearGC()
{
	Safe_Del_Vec(m_GC);
}

void qTaskMgr::ExcuteTask()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::SPAWN_OBJECT:
		{
			qLevel* pSpawnLevel = (qLevel*)m_vecTask[i].Param1;
			LAYER_TYPE Layer = (LAYER_TYPE)m_vecTask[i].Param2;
			qObj* pObj = (qObj*)m_vecTask[i].Param3;

			if (qLevelMgr::GetInst()->GetCurrentLevel() != pSpawnLevel)
			{
				delete pObj;
			}
			pSpawnLevel->AddObject(Layer, pObj);
		}
		break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			qObj* pObject = (qObj*)m_vecTask[i].Param1;
			pObject->m_bDead = true;

			// GC ���� ����
			m_GC.push_back(pObject);
		}

		break;
		case TASK_TYPE::CHANGE_LEVEL:
			break;
		}
	}

	m_vecTask.clear();
}
