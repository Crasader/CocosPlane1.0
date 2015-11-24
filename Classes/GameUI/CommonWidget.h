#ifndef __COMMON_WIDGET_H__
#define __COMMON_WIDGET_H__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../GameCommon/NewDataMgr.h"
USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;


/*******************************************
*	widget���÷���
*******************************************/
class CommonLayer
{

public:

	enum soundType
	{
		SoundType_None,
		SoundType_Close,
		SoundType_Back,
		SoundType_ButtonStart,
		SoundType_Menu,
		SoundType_GameStart,
	}; 

	bool setButtonAction(Ref* ref, Widget::TouchEventType touchType, soundType sound = SoundType_Back);

	void setSoundType(soundType sound = SoundType_None);
	
private:

	//virtual void onMessageEvent(Ref* sender) = 0;
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback) = 0;
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType) = 0;

	
};

/************************************************************************/
/* ����С����                                                           */
/************************************************************************/

class CommonWidget : public Layer
{
public:
	CREATE_FUNC(CommonWidget);

	CommonWidget()
		:_commonWidget(nullptr)
		,eventListener(nullptr)
		,callFuncBtnExit(nullptr)
		,callFuncBtn1(nullptr)
		,callFuncBtn2(nullptr)
	{

	}
	~CommonWidget()
	{

	}
	enum ButtonTag
	{
		Tag_ExitWidget,			// �˳�
		Tag_Btn1,
		Tag_Btn2,
	};

	enum class EventKey
	{
		EventKey_Exit,
		EventKey_Btn1,
		EventKey_Btn2,
	};

	typedef std::function<void(void)> ccCommonWidgetBtnCallBack;
	typedef std::function<void(CommonWidget::EventKey)> ccCommonWidgetBtnEvent;


	// setting widget content string
	void setContent( const char* content1 = nullptr, const char* content2 = nullptr );

	void setCloseButtonState( bool state );

	// add click event listener
	void addEventListener(const ccCommonWidgetBtnEvent& callback );
	void addBtnExitClickEventListener( const ccCommonWidgetBtnCallBack& callback );
	void addBtn1ClickEventListener( const ccCommonWidgetBtnCallBack& callback );
	void addBtn2ClickEventListener( const ccCommonWidgetBtnCallBack& callback );

private:

	virtual bool init();
	virtual void onEnter();
	virtual void onExit(void);
	
	// show interface
	void initInterface( void );

	// Even Callfunc
	void callFuncButtonEvent( Ref* ref );

private:
	Node* _commonWidget;

	// ��ť�ص�����
	ccCommonWidgetBtnEvent	eventListener;
	ccCommonWidgetBtnCallBack callFuncBtnExit;	// exit
	ccCommonWidgetBtnCallBack callFuncBtn1;		// button1
	ccCommonWidgetBtnCallBack callFuncBtn2;		// button2

};




/*******************************************
*	������Ʒ�ڵ�
*******************************************/

class RewardGoodsNode : public Node, public Clonable
{
public:
	
	static RewardGoodsNode* create( RewardGoodsKey key );

	RewardGoodsNode()
		:_nodeTag(0)
	{

	}
	~RewardGoodsNode()
	{

	}
	
	virtual RewardGoodsNode* clone() const;

private:

	// show interface
	bool initWithKey( RewardGoodsKey key );


private:
	RewardGoodsKey _goodeskey;

	int _nodeTag;

};



/*******************************************
*	��Ʒչʾ
*******************************************/
class ShowGoodsLayer :public Layer, public CommonLayer
{
public:

	enum showInfoType
	{
		InfoType_NewPack = 0,		// �����������
		InfoType_OverflowPack,		// ����ֵ���
		InfoType_TyrantPack,		// �����������
		InfoType_BuyGold,			// ������
		InfoType_BuyShield,			// ���򻤶�
		InfoType_BuyDaZhao,			// �������
		InfoType_BuyLife,			// ��������

		InfoType_SignIn,			// ǩ��
		InfoType_TaskReward,		// ������
	};

	struct ItemStr
	{
		std::string name;
		showInfoType type;
		int num;
	};

	typedef enum ButtonTag
	{
		Tag_Close,			// �ر�
		Tag_Buy,			// ����


	};
	ShowGoodsLayer()
		:_myLayer(nullptr)
	{

	}

	~ShowGoodsLayer()
	{

	}

	static ShowGoodsLayer* getShowGoodsInfoLayer(void);
	virtual void onEnter();
	virtual void onExit();

	void setShowInfoType(int type, int data = 1);

	CREATE_FUNC(ShowGoodsLayer);

private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unusedEvent);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	void initInterface();
	void addItemInfoToList(showInfoType type, int num, std::string name);

	void updateInerface();

	std::string getGoodsImgPathWithType(showInfoType type);
	std::string getTitleImgPathWithType(showInfoType type);

private:
	Node*	_myLayer;

	int _curShowType;
	int _curBuyType;
	int _data;

	std::list<ItemStr>	_goodsInfoList;

};

/*******************************************
*	���չʾ
*******************************************/
class PackShowLayer :public Layer, public CommonLayer
{
public:

	enum PackType
	{
		InfoType_OverflowPack,		// ����ֵ���
		InfoType_TyrantPack,		// �����������
		InfoType_PropPack,			// ����������

		InfoType_BuyGold,			// ������
		InfoType_BuyShield,			// ���򻤶�
		InfoType_BuyDaZhao,			// �������
		InfoType_BuyLife,			// ��������
	};

	struct ItemStr
	{
		std::string name;
		PackType type;
		int num;
	};

	typedef enum ButtonTag
	{
		Tag_Close,			// �ر�
		Tag_Buy,			// ����


	};
	PackShowLayer()
		:_myLayer(nullptr)
	{

	}

	~PackShowLayer()
	{

	}

	static PackShowLayer* getPackShowLayer(void);
	virtual void onEnter();
	virtual void onExit();

	void setShowInfoType(int type, int data = 1);

	CREATE_FUNC(PackShowLayer);

private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);
	void initInterface();
	void addItemInfoToList(PackType type, int num, std::string name);

	void updateInerface();

	std::string getPackTitlePathWithType(PackType type);
	std::string getPackIcoPathWtihType(PackType type);

private:
	Node*	_myLayer;

	int _curShowType;
	int _curBuyType;
	int _data;

	std::list<ItemStr>	_goodsInfoList;

};

/*******************************************
*	Ů�����
*******************************************/
class ShowRolePackLayer :public Layer, public CommonLayer
{
public:	

	typedef enum ButtonTag
	{
		Tag_Close,			// �ر�
		Tag_Buy,			// ����


	};
	ShowRolePackLayer()
		:_myLayer(nullptr)
	{

	}

	~ShowRolePackLayer()
	{

	}

	static ShowRolePackLayer* getRolePackLayer(void);
	virtual void onEnter();
	virtual void onExit();


	CREATE_FUNC(ShowRolePackLayer);

private:
	virtual void onMessageEvent(Ref* sender);
	virtual void setEventForNode(Button* node, int tag, const Widget::ccWidgetTouchCallback& callback);
	virtual void callFuncButtonEvent(Ref* ref, Widget::TouchEventType touchType);
	void initInterface();
	
private:
	Node*	_myLayer;

};


/*******************************************
*	����ָ��
*******************************************/
class HelpFeqLayer :public Layer
{
public:

	enum HelpFeqType
	{
		HelpFeqType_SignIn,
		HelpFeqType_ChuJi1,
		HelpFeqType_ChuJi2,
		HelpFeqType_CardTips,
		HelpFeqType_UseHudun,
		HelpFeqType_UseDazhao,


		HelpFeqType_Upgrade1,
		HelpFeqType_Upgrade2,
		HelpFeqType_Upgrade3,

		HelpFeqType_CardStep1,	// ���Ƶ�һ�׶�
		HelpFeqType_CardStep2,	// ���Ƶڶ��׶�
		HelpFeqType_CardStep3,	// ���Ƶ����׶�
		HelpFeqType_Card1_1,
		HelpFeqType_Card1_2,
		HelpFeqType_Card1_3,

		HelpFeqType_Card2_1,
		HelpFeqType_Card2_2,
		HelpFeqType_Card2_3,
		HelpFeqType_Card2_4,
	};

	HelpFeqLayer()
		:_myLayer(nullptr),
		misInversion(false),	
		mGuideNode(nullptr)
	{

	}

	~HelpFeqLayer()
	{

	}
	static void showHelpFeq(HelpFeqType type, Node* node = nullptr);

	static HelpFeqLayer* getHelpFeqLayerLayer(void);
	virtual void onEnter();

	void setShowInfoType(int type);
	void setTipsArrowsPos(Vec2 pos);

	void checkAddList();

	CREATE_FUNC(HelpFeqLayer);

	CC_SYNTHESIZE(HelpFeqType, mHelpFeqType, HelpType)
	CC_SYNTHESIZE(Vec2, mArrowsPos, ArrowsPos);
	CC_SYNTHESIZE(bool, misInversion, IsInversion);
	CC_SYNTHESIZE(bool, mIsShowArrows, IsShowArrows);
	CC_SYNTHESIZE(Node*, mGuideNode, GuideNode);

private:
	void initInterface();
	void setTipsText(HelpFeqType type);

	void delayRemoveSelf(Node* node);

private:
	Node*	_myLayer;

	Vec2	_arrowsPos;
	bool	_isInversion;

	std::list<HelpFeqType> _helpFeqList;
};
#endif
