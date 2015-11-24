/********************************************************************
������:		2014/11/26  11:05	
�ļ���: 	E:\Cocos3.3_Project\MyGame\Classes\PhysicsUnit.h 
��  ��:		alex(alex)
�޸��ڣ�	2014/11/26  11:05	

Ŀ  ��:		���и����������Եľ���Ļ���
*********************************************************************/

#ifndef _PHYSICS_UNIT_H_
#define _PHYSICS_UNIT_H_

#include "cocos2d.h"
#include "Buff.h"
#include "../GameCommon/GameDefine.h"

USING_NS_CC;

#define RemoveTag		150929

//BUFF�ṹ��
typedef struct BuffStruct
{
	BuffId	buffId;
	float	durarion;
	BuffStruct()
	{
		buffId = BuffId::Buff_default;
		durarion = 0.0;
	}
	BuffStruct(BuffId id, float t)
	{
		buffId = id;
		durarion = t;
	}
}BuffStruct;

//��Ʒ����
struct DropReward
{
	float					HpPercent;	//Ѫ���ٷֱ�
	int						nums;			//��������
	DropGoodsType			DropTp;			//������Ʒ����
	DropReward()
	{
		HpPercent = 0.0f;
		nums = 1;
		DropTp = DropGoodsType::DropGoods_Default;
	}

	DropReward(float p, int num, const DropGoodsType& tp)
	{
		HpPercent = p;
		nums = num;
		DropTp = tp;
	}
};

typedef struct BasePro
{
	CC_SYNTHESIZE(int,		id,					Id);
	CC_SYNTHESIZE(int,		hurts,				Hurts);
	CC_SYNTHESIZE(int,		defense,			Defense);	
	CC_SYNTHESIZE(int,		curHP,				CurHp);
	CC_SYNTHESIZE(int,		maxHp,				MaxHp);
	CC_SYNTHESIZE(int,		isInvincible,		IsInvincible);
	CC_SYNTHESIZE(int,		isIgnoreScreenEdge,	IsIgnoreScreenEdge);
	CC_SYNTHESIZE(int,		isInvincibleAbsolutely,	IsInvincibleAbsolutely);
	CC_SYNTHESIZE(UnitId,	myId,				MyId);
	CC_SYNTHESIZE(UnitId,	belongTo,			BelongTo);
	CC_SYNTHESIZE_PASS_BY_REF(Vec2,	  contactPos,	ContactPos);

	BasePro()
	{
		id = -1;
		hurts = 0;
		defense = 0;
		curHP = 1;
		maxHp = 1;
		isInvincible = 0;
		isIgnoreScreenEdge = 0;
		isInvincibleAbsolutely = 0;
		myId = UnitId::DefaultIdx;
		belongTo = UnitId::DefaultIdx;
		contactPos = Vec2(360,640);		//��ʼֵ������Ļ���룬���ڹ۲�
	}
}UPro;

//��������
enum class DeadType
{
	Dead_default,
	Dead_Nature,		//��Ȼ����
	Dead_Force,			//ǿ������
	Dead_Kill,			//��ɱ����
};

class PhysicsUnit : public Sprite
{
public:
	PhysicsUnit();
	static PhysicsUnit* createWithFrameName(const std::string name);
	static PhysicsUnit* createWithFile(const std::string file);
	static PhysicsUnit* create();
	virtual void onEnter();
	virtual void onExit();

	virtual void initBody();
	virtual void FuncAfterEnter(){}
	virtual void PlayMusicWhenContact(){}		//��ײ��Ч
	virtual void PlayMusicWhenDead(){}			//������Ч
	virtual void AnimationWhenDead(){}			//������Ч

	//���Լ�������ײʱ,�ı��Լ�������
	void ChangeProperty(const BasePro& pro);
	virtual void OtherDealWhenContact(const BasePro& rs){}	//������ײӰ�죨�����������������ɾ���Լ��Ĳ�����
	virtual void DoSomethingBeforeDead(){}					//����֮ǰҪ������

	//��ײ����Ӱ��
	virtual void ImpactOfHp(const BasePro& pro);				//Ѫ��Ӱ��
	virtual void DeathImpactOfDrops(){}							//�����÷�
	virtual void DeathImpactOfDropReward(){}					//��Ѫ������ָ������ʱ������ָ����Ʒ
	virtual void FuncWhenHpChanged(){}
	virtual void FuncHpEmpty(const BasePro& pro);

	float getHpPercent();		//�õ���ǰѪ���İٷֱ�

	void DeathForce();

	void setInvincible(int invincible );
	void setUnitId(const UnitId& idx);
	void setBelongTo(const UnitId& idx);
	void setCantContact();
	void setMaxHp(int max);
	void setInvincibleAtEdge(int b = 1);
	void setInvincibleAbsolutely(int b = 1);
	bool isScreenEdge(const BasePro& pro);
	BasePro& getBasePro(){return m_BasePro;}
	void setBasePro(const BasePro& pro){m_BasePro = pro;}
	std::vector<DropReward> getDropVec(const std::vector<DropReward>& vec);

protected:
	virtual void autoCheckChance();
public:
	virtual void RemoveMyself();

	//
//	//<<*****************����ɫ��*********************/
//public:
//	float getHue();
//	void setHue(float hue);	//0~2��
//
//protected:
//	float _hue;
//	GLfloat _mat[3][3];
//
//	bool initWithTexture(cocos2d::Texture2D *texture);
//	bool initWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect& rect);
//	virtual bool initWithTexture(cocos2d::Texture2D *texture, const cocos2d::Rect &rect, bool rotated);
//	virtual bool initWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
//
//	void setupDefaultSettings();
//	void initShader();
//	const GLchar* shaderBody();
//	virtual void updateColor();
//	void updateColorMatrix();
//	void updateAlpha();
//	GLfloat getAlpha();
//
//	void hueUniformCallback(cocos2d::GLProgram *p, cocos2d::Uniform *u);
//
//	//*****************����ɫ��*********************>>/

protected:
	Size				m_WinSize;
	CC_SYNTHESIZE(DeadType,		m_DeadType,	DeadType);		//������ʽ
	BasePro						m_BasePro;
	int							m_CurChance;
	CC_SYNTHESIZE(float,		m_delayRemoveTime, DelayRemoveTime);
	CC_SYNTHESIZE(int,			m_MaxChance,	MaxChance);
	bool						m_isDead;
	bool						m_isRemoving;
};


#endif