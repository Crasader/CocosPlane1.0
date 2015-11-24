/********************************************************************
������:		2015/01/05  10:19	
�ļ���: 	E:\Cocos3.3_Project\MyGame\Classes\ContactManager.h 
��  ��:		alex(alex)
�޸��ڣ�	2015/01/05  10:19	

Ŀ  ��:		���������������ײ�¼����¼�����ַ����������
*********************************************************************/
#ifndef __ContactManager_h__
#define __ContactManager_h__


#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

/************************************************************************/
/* 
��ײ������
*/
/************************************************************************/
class PhysicsUnit;
class ContactManager : public Layer
{
public:
	CREATE_FUNC(ContactManager);
	virtual void onEnter();
	virtual void onExit();
	bool onContactBegin(const PhysicsContact& contact);
private:
	EventListenerPhysicsContact* m_contactListener;
};


class PhysicsUnitManager
{
public:
	static PhysicsUnitManager* getInstance()
	{
		static PhysicsUnitManager instance;
		return &instance;
	}

	void AddUnit(PhysicsUnit* pu);
	void DelUnit(PhysicsUnit* pu);
	void DelUnit(int id);

	void ClearUnits();
private:
	Map<int, PhysicsUnit*>	m_PhysicsUnitVec;
	int						m_id;
};



#endif // ContactManager_h__