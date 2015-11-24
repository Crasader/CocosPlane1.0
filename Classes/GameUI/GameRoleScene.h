#ifndef __GAME_ROLE_SCENE_H__
#define __GAME_ROLE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../GameCommon/NewDataMgr.h"
#include "CommonWidget.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

#define LocalZOrde_1000		1000
#define LocalZOrde_500		500

class ShowGoodsLayer;
class CommonLayer;
/*******************************************
/* �������
*******************************************/
class GameInterfaceMgr
{
public:
	enum InterfaceTag
	{

		InterfaceTag_None = 1888,			// ����
		InterfaceTag_Task,					// ����
		InterfaceTag_ShopBuy,				// �̵�
		InterfaceTag_Upgrade,				// ħ������
		InterfaceTag_CardOption,			// ����ѡ��
		InterfaceTag_Checkpoint,			// �ؿ�ѡ��
		InterfaceTag_SignIn,				// ǩ��
		InterfaceTag_LevelOption,			// �ؿ�
		InterfaceTag_VIPBuy,				// VIP
		InterfaceTag_VIPReward,				// VIP����
		InterfaceTag_ResoutSuc,				// �ɹ�����
		InterfaceTag_ResoutFail,			// ʧ�ܽ���
		InterfaceTag_RewardCard,			// ��������
	};
	
	static GameInterfaceMgr* getInstance(){
		static GameInterfaceMgr nGameInterfaceMgr;
		return &nGameInterfaceMgr;
	}
	// ���/���ø��ڵ�
	CC_SYNTHESIZE(Node*, _node, ParentNode);

	// �����һ������
	void addInterfaceToList( InterfaceTag tag , bool isShow = true, void* data = nullptr );
	// ��ʾ��һ������
	void showNextInterface( void );
	// �زŵ�ǰ����
	void closeCurInterface( void );
	// clean���н���
	void closeAllInterface( void );
	// ��õ�ǰ������
	int getCurInterfaceNum(void);
	// ���/���õ�ǰ����Tag

	CC_SYNTHESIZE(InterfaceTag, mCurInterfaceTag, CurInterfaceTag);

private:

private:
	// ��������
	void*	_data;	

	std::list<InterfaceTag>	_interfaceVector;
};


/*******************************************
* ������
*******************************************/
class MainPlaneShowLayer;
class GameRoleScene : public Layer, public CommonLayer
{
public:
	enum ButtonTag
	{
		Tag_BtnRole1,				// ѡ���ɫID
		Tag_BtnRole2,				// ѡ���ɫID
		Tag_BtnRole3,				// ѡ���ɫID

		Tag_BtnLeftRoll,			// ��ҳ
		Tag_BtnRightRoll,			// �ҷ�ҳ

		Tag_BtnVIP,					// �������
		Tag_BtnNewPack,				// �������
		Tag_SignIn,					// ǩ��
		Tag_Play,					// ��ʼ

	};

	GameRoleScene();
	~GameRoleScene();

	CREATE_FUNC(GameRoleScene);
	static Scene* createScene();


	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void onEnterTransitionDidFinish();


	static GameRoleScene* getGameRoleScene();
	void initInterface( void );

	// ��������
	void showPaySuccee(Ref* sender);
	void removeUpgradeAnim( Node* node );

	void playButtonPro( int roleid );

	// ����ɹ���Ч
	void buySucceedAction( void );
	void callFuncbuySucceed( Node* node );
	void callFuncDeleyTouch(Node* node);


	void playUnlockEffect( void );


	// Even Callfunc
	void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);
	void callFuncOptionCard(Ref* ref, Widget::TouchEventType touchType);
	void callFuncPageviewRole(Ref* ref, PageView::EventType eventType);
	void callFuncChangeRoleDemo(Node* node);

	// �˳���Ϸ
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event); 
	void callFuncExitGame( void );

	void updateOptionRole(ButtonTag tag);
	void updateRoleAtk(void);
	void updateDemoRole(void);

	//���Ž�����Ч
	void playUnlockRoleSound();
	//����ѡ����Ч
	void playOptionRoleSound();

	// ��¼�ж�
	bool signInJudge(void);
	// vip�ж�
	bool vipRewardJudge(void);
		
private:
	Node* _myLayer;

	Size	_winSize;

	int _lastOptionRoleId;
	int	_curOptionRoleId;
	MainPlaneShowLayer* _showLayer;
};

/*******************************************
* �����涥���͵ײ���
*******************************************/
class MainSceneTaskBar : public Layer, public CommonLayer
{
public:
	enum ButtonTag
	{
		Tag_BtnUpgrade,			// ����
		Tag_BtnCard,			// ����
		Tag_BtnMain,			// ������
		Tag_BtnShop,			// �̳�
		Tag_BtnVIP,				// VIP
		Tag_BgMusic,			// ��������
		Tag_SoundEff,			// ��Ч

		Tag_BuyGole,
		Tag_None,

	};
	MainSceneTaskBar();
	~MainSceneTaskBar();



	static void showLayout(Node* node, bool parm = true);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(MainSceneTaskBar);

private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);

	void callFuncDeleyTouch(Node* node);

	// ������Ч
	void selectedMusicEvent(Ref* pSender, CheckBox::EventType type);
	void selectedSoundEvent(Ref* pSender, CheckBox::EventType type);

	void initInterface();
	void updataShowData(void);

	void checkTaskFinish(void);

	void MsgProShowButtomBar(Ref* sender);
	void MsgProHideButtomBar(Ref* sender);
	void MsgProChangeGemGold(Ref* sender);

private:
	Node*	_mainSceneTaskBar;

	bool _isShowButtomBar;

};

/*******************************************
* ħ����
*******************************************/
class UpgradeLayer :public Layer, public CommonLayer
{
public:
	enum ButtonTag
	{
		Tag_Back,			// ����
		Tag_Upgrade,		// ����

		Tag_ItemRole,
		Tag_ItemDaZhao,
		Tag_ItemGold,
		Tag_ItemRedBall,
		Tag_ItemBlueBall,
		Tag_itemYellowBall,

	};
	UpgradeLayer ()
		:_myLayer(nullptr)
		, _isGuideUpGrade(false)
	{

	}

	~UpgradeLayer ()
	{

	}

	static void showLayout( Node* node, int tag );
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(UpgradeLayer);

private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);
	void callFuncOptionItemEvent(Ref* ref, Widget::TouchEventType touchType);


	void initInterface();

	void upgradeItemPro(int tag);
	void updateInterface( void );
	void updateObjectInfo();

	void playUpgradeAnim(void);
	void removeUpgradeAnim(Node* node);
	void callFuncRemoveFlash(Node* node);

private:
	Node*	_myLayer;

	int _curOptionItemId;

	bool	_isGuideUpGrade;

};

/*******************************************
* ����ѡ�����
*******************************************/
class CardOptionLayout : public Layer, public CommonLayer
{
public:
	enum ButtonTag
	{
		Tag_Back,			// ����
		Tag_Card1,			// ����1
		Tag_Card2,			// ����2
		Tag_Card3,			// ����3


		Tag_CloseOption,	// �ر�ѡ�����
		Tag_Confirm,		// 
	};

	CardOptionLayout()
		:OptionCardTouchListener(nullptr)
		,_touchLayer(nullptr)
		,_curSelectCardType(0)
		, _lastSelectCardType(0)
		, _isOption(false)
		, _isGuideUseCard(false)
	{

	}

	~CardOptionLayout()
	{

	}

	static void showLayout( Node* node, int tag );

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	CREATE_FUNC(CardOptionLayout);


private:

	void initInterface();


	// Even Callfunc
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);
	void callFuncCardTypeOptionEvent(Ref* ref, Widget::TouchEventType touchType);
	void callFuncCardOptionEvent(Ref* ref, Widget::TouchEventType touchType);

	void runButtonAction( Node* node );


	void showConfirmOption( void );

	void optionCardTypePro(int type);

	void updateOptionCard(void);
	void updateCardList(void);

	void callFuncChangeOptionCard(bool isUse);
	void callFuncRemoveCardFlash(Node* node);

	bool checkCardIsUnlock(void);
	void setOptionState(Node* node, int tag);
private:

	Layer*	_touchLayer;

	Node* _myLayer;

	Button* _cardBtn[3];

	// ȷ�Ͽ���ѡ����津��
	EventListenerTouchOneByOne *OptionCardTouchListener;

	int		_lastSelectCardType;	//	1-3
	int		_curSelectCardType;		//	1-3
	int		_curSelectCardID;		//	1-9	

	bool	_isOption;
	bool	_isGuideUseCard;
};

/*******************************************
*	������Ϣ����
*******************************************/
class CardInformatLayer :public Layer, public CommonLayer
{
public:

	typedef enum ButtonTag
	{
		Tag_Close,			// �ر�

		Tag_Confirm,		// 
	};
	CardInformatLayer()
		:_myLayer(nullptr)
		, _curSelectCardID(1)
		, _confirmCallFunc(nullptr)
		, mGuideState(false)
	{

	}

	~CardInformatLayer()
	{

	}
	typedef std::function<void(bool)> ccConfirmCallBack;

	static CardInformatLayer* getCardInformatLayer(void);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(CardInformatLayer);

	void setCardIndex(int index);
	void addConfirmCallFunc(const ccConfirmCallBack& callfunc);

	CC_SYNTHESIZE(bool, mGuideState, GuideState);
private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);

	void initInterface();

	void updateSingleCardInfo(void);
	void setCardRolePos();

	void playCardUnlockAnim(void);
private:
	Node*	_myLayer;

	int _curSelectCardID;

	ccConfirmCallBack	_confirmCallFunc;
};

/*******************************************
*	����
*******************************************/
class TaskListView : public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate, public CommonLayer
{
public:
	enum ListType
	{
		ListType_DayTask,
		ListType_AchiTask,
	};
	virtual bool init(void);

	CC_SYNTHESIZE(ListType, mlistType, MyListType);

	static TaskListView* create(ListType type);
	CREATE_FUNC(TaskListView);

	void initTaskList(void);

	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback){}
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType){}

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);

	void callFuncGetRewardEvent(Ref* ref, Widget::TouchEventType touchType);
	std::string getGoodsResWithID(int id);

	void updateTableItem(TableViewCell *cell, int taskid);

private:
	std::map<int, int>		_taskMap;

};


class GameTaskList :public Layer,public CommonLayer
{
public:
	
	typedef enum ButtonTag
	{
		Tag_Back,			// ����
		Tag_Close,			// �ر�

		Tag_LabelDayTask,	// ������
		Tag_LabelAchTask,	// �ɾ����� 
	};
	GameTaskList ()
		:_mylayer(nullptr)
	{

	}

	~GameTaskList ()
	{

	}

	static void showLayout( Node* node, int tag );
	virtual void onEnter();
	virtual void onExit();


	CREATE_FUNC( GameTaskList );

private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);
	void callFuncLabelEvent(Ref* ref, Widget::TouchEventType touchType);
	void callFuncGetRewardEvent(Ref* ref, Widget::TouchEventType touchType);

	void initInterface();
	void addTaskItemToDayList(void);
	void addTaskItemToAchiList(void);

	void checkTaskFinish(void);

	std::string getGoodsResWithID(int id);

	void changeTaskLable(int id);
private:
	Node*	_mylayer;

	int _curGetTaskID;
};

/*******************************************
*	�̵�
*******************************************/
class ShopBuyLayer :public Layer, public CommonLayer
{
public:

	enum ButtonTag
	{
		Tag_Back,			// ����

		Tag_OverflowPack,	// ��ֵ
		Tag_TyrantPack,		// ����
		Tag_BuyGold,
		Tag_BuyShield,
		Tag_BuyDaZhao,
		Tag_BuyPropPack,

	};
	ShopBuyLayer()
		:_widgetLayer(nullptr)
		, _showGoodsInfoLayer(nullptr)
	{

	}

	~ShopBuyLayer()
	{

	}

	static void showLayout(Node* node, int tag);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(ShopBuyLayer);

	CC_SYNTHESIZE(int, _optionLabel, optionLabel);			//��ǩҳ��

private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);

	void initInterface();
	void showGoodsInfo(int tag);

private:
	Node*	_widgetLayer;

	PackShowLayer* _showGoodsInfoLayer;

};


/*******************************************
*	ǩ������
*******************************************/
class SignInLayer :public Layer, public CommonLayer
{
public:

	typedef enum ButtonTag
	{
		Tag_Close,			// �ر�
		Tag_GetReward,		// ��ȡ


	};
	SignInLayer()
		:_myLayer(nullptr)
	{

	}

	~SignInLayer()
	{

	}

	static void showLayout(Node* node, int tag);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(SignInLayer);



private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);

	void initInterface();

	void addToRewardTips(void);
private:
	Node*	_myLayer;


};

/*******************************************
*	�ؿ�ѡ��
*******************************************/
class LevelOptionLayer :public Layer, public CommonLayer
{
public:

	typedef enum ButtonTag
	{
		Tag_Back,			// �ر�

		Tag_Start,			// ��ʼ
		Tag_NewPack,		// �������
		Tag_ThPack,			// �������

		Tag_LeftPage,		// ��ҳ
		Tag_RightPage,		// �ҷ�ҳ
	};
	LevelOptionLayer()
		:_myLayer(nullptr)
	{

	}

	~LevelOptionLayer()
	{

	}

	static void showLayout(Node* node, int tag);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(LevelOptionLayer);



private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);
	virtual void callFuncLevelButtonEvent(Ref* ref, Widget::TouchEventType touchType);


	void callFuncPageviewRole(Ref* ref, PageView::EventType eventType);

	void showPackInfoWithTag(int tag);
	void updateScrollPageButton(void);
	void setOptionLevelBut(int level);
	void updateAnimWithLevel(int level);
	void callFuncScrollTo(Node* node);
	void initInterface();
	std::string getLevelStateRes(int lv);

private:
	Node*	_myLayer;


};

/*******************************************
*	VIP����
*******************************************/
class VipLayer :public Layer, public CommonLayer
{
public:

	typedef enum ButtonTag
	{
		Tag_Close,			// �ر�

		Tag_Buy,			// ����
	};
	VipLayer()
		:_myLayer(nullptr)
	{

	}

	~VipLayer()
	{

	}

	static void showLayout(Node* node, int tag);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(VipLayer);

private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);

	void initInterface();

private:
	Node*	_myLayer;


};

/*******************************************
*	VIPÿ������
*******************************************/
class VipPresentingLayer :public Layer, public CommonLayer
{
public:

	typedef enum ButtonTag
	{
		Tag_Close,			// �ر�

		Tag_Get,			// ��ȡ
	};
	VipPresentingLayer()
		:_myLayer(nullptr)
	{

	}

	~VipPresentingLayer()
	{

	}

	static void showLayout(Node* node, int tag);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(VipPresentingLayer);

private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);

	void initInterface();

private:
	Node*	_myLayer;

};

/*******************************************
*	������������
*******************************************/
class RewardCardLayer :public Layer
{
public:

	typedef enum ButtonTag
	{

	};
	RewardCardLayer()
		:_myLayer(nullptr)
	{

	}

	~RewardCardLayer()
	{

	}

	static void showLayout(Node* node, int tag);
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(RewardCardLayer);

private:

	void initInterface();
	void callFuncFront(Node* node);
	void callFuncReverse(Node* node);

private:
	Node*	_myLayer;

};
#endif
