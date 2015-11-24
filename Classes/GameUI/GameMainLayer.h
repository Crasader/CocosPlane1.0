#ifndef __GAME_MAIN_LAYER_H__
#define __GAME_MAIN_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../GameUI/CommonWidget.h"
#include "../GameCommon/NewDataMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

/************************************************************************/
/* ��Ϸս��������                                                        */
/************************************************************************/

class GameMainLayer : public Layer//, public CommonLayer
{
public:
	GameMainLayer()
		:_mainLayerRootNode(nullptr)
//		,_loadingBarEnergy(nullptr)
		,_countTime(0)
		,_countAddLifeNum(0)
		,_maxLifeBar(0)
		,_curMaxLifeBar(0)
		,_decayInterval(0)
		,_decayCountT(0)
		,m_fighting_shield_num(0)
		,m_fighting_skill_num(0)
		,m_fighting_shield_used(0)
		,m_fighting_skill_used(0)
		,m_HpLimit(100.0f)
		,_decayIng(false)	// Ĭ�Ϸ�˥����
		,m_isDead(false)
		,m_isCanBeHurt(true)
	{
		int curRole = NewDataMgr::getInstance()->mRoleConfig.roleIndex;
		m_HpLimit = 0;// NewDataMgr::getInstance()->getRoleHpWithId(curRole);
		m_CurHp = m_HpLimit;
	}

	~GameMainLayer()
	{
	}

	enum ButtonTag
	{
		Tag_DaZhao,
		Tag_HuDun,
		Tag_Pause,			// �ر�
	};

	CREATE_FUNC(GameMainLayer);

	void onMessageEvent(Ref* sender);


	void updateGoodsNum(void);

	// ����1������
	void consumeLife(void);
	// ����1������
	void consumeHudun(void);
	// ����1������
	void consumeDazhao(void);

    void changeLifeNum(int lifeNum);
    void changeHudunNUm(int hudunNum);
    void changeDazhaoNum(int dazhaoNum);

	// ���½��
	void updateUIGold( int goldnum );
	// ���³ɼ�
	void updateUIScore( int score );
	// ����Km
	void updataGamedistance( int km );


	//Ѫ����������
	void AddHp(float num);

	//���ܵ��˺�֮���һ��ʱ���ڣ������ܵ��˺�
	void WudiSometime(float dur = 1.0f);
	void WudiOver(Node* node);

	void GameFailed();
	bool isRealDead(){return m_isDead;}
	void SetRealDead(bool b);

	void showBuyFuHuoWidget( void );
	void showSettingWidget( void );

	static Node * seekNodeByName(Node* node, const std::string &name );
	static void DelayPuse(Node* node);
	void GamePause();


	// ����Զ���ɹ�
	void playPassSucceed( void );
	void callFuncGuang1( Node* node );
	void callFuncNodeMove( Node* node );
	void setDaZhaoState( bool state );
	void startDaZhaoSD( void );

	// ��ʼ����
	void startDaZhao();
	//�ͷŻ���
	void startHuDun();
	//��û���ʱ��û�б���ʱ�ͷ�
	void addHuDun();

	void helpFeqCard(void);
	void helpFeqHuDun(void);
	void helpFeqDaZhao(void);
	void showAddShieldEffect();
	void showAddSkillEffect();

	bool shieldIsEnough();
	bool skillIsEnough();
	void setUserItemNumWhenGameEnd(bool isWin);
private:
	void showAddEffect(Widget* node);

	virtual void onEnter();
	virtual bool init();
	virtual void onExit();

	// ��ʼ��������
	void initInterface( void );

	Node* createEnergyFullAnim( Vec2 ps );
	void removeEnergyAnim( Node* node );
	void callFuncRandAnim( float t );

	void playLifeBarWarning( void );

	void buyFuhuoBtnEvent(CommonWidget::EventKey key);
	void buyFuhuoCancel( void );
	void BuyFuHuoConfirm( void );

	void callbackPause( Ref* ref );
	// ����
	void callbackButtonHudun(Ref* ref);
	void callbackButtonPack(Ref* ref);
	void callbackDazhao( Ref* ref );
	void playDaZhaoCD( void );
	void callFuncDaZhaoCD( Node* node );
	void callFuncWidgetBuyDz( void );
	void callFuncWidgetBuyDzExit( void );
	void callWidgetGoldTips( void );

private:

//	LoadingBar* _loadingBarEnergy;


	Node*	_mainLayerRootNode;
	float	_countAddLifeNum;
	int		_countTime;
	float	_curMaxLifeBar;
	float	_maxLifeBar;
	
	float	_decayInterval;			// ˥����ʱ
	float	_decayCountT;			// ˥����ʱ��
	bool	_decayIng;				// ˥��״̬ ture˥����

	float	m_HpLimit;				//Ѫ����
	float	m_CurHp;				//��ǰѪ��ֵ
	bool	m_isDead;				//�Ƿ����
	bool	m_isCanBeHurt;
	int m_fighting_shield_num;
	int m_fighting_skill_num;

	int m_fighting_shield_used;
	int m_fighting_skill_used;
};



// ����
class BuyFuHuo : public Layer
{
public:

	enum ButtonTag
	{
		Tag_BuyFuhuo,		// ����
		Tag_Close,		// ����

	};

	BuyFuHuo()
		:_fuHuoLayout(nullptr)
	{

	}

	~BuyFuHuo()
	{

	}

	static void showLayout( Node* node );

	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC( BuyFuHuo );


private:
	void onMessageEvent(Ref* sender);

	void initInterface();

	// Even Callfunc
	void setEventForNode( Button* node, ButtonTag tag );
	void callFuncButtonEvent( Ref* ref );

	void buyFuhuoCancel( void );
	void BuyFuHuoConfirm( void );

	void callFuncAction1( Node* node );
	void callFuncEge(Node* node);
private:

	Node* _fuHuoLayout;


};



// ����
class SettingLayer : public Layer ,public CommonLayer
{
public:

	enum ButtonTag
	{
		Tag_ExitGame,		// �˳���Ϸ
		Tag_ContinueGame,	// ������Ϸ

	};

	SettingLayer()
		:_settingayout(nullptr)
	{

	}

	~SettingLayer()
	{

	}

	static void showLayout( Node* node );

	virtual void onEnter();

	void onMessageEvent(Ref* sender){};
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);
	CREATE_FUNC( SettingLayer );


private:

	void initInterface();

	// ������Ч
	void selectedMusicEvent(Ref* pSender,CheckBox::EventType type);
	void selectedSoundEvent(Ref* pSender,CheckBox::EventType type);
	
private:

	Node* _settingayout;


};

#endif
