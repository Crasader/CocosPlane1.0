#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__



#include "cocos2d.h"
#include "../CsvMgr/CsvMgr.h"
#include "sqlite3/include/sqlite3.h"



USING_NS_CC;
/************************************************************************/
/* ��Ϸ���ϵͳ����                                                  */
/************************************************************************/
	
// ��ϢID
#define MsgEventName_ToTaskBarLayer			"to taskbar"
#define MsgEventName_ToRoleLayer			"to Role"
#define MsgEventName_ToCardLayer			"to card"
#define MsgEventName_ToCardInfoLayer		"to cardInfo"
#define MsgEventName_ToUpgradeLayer			"to upgrader"
#define MsgEventName_ToShopLayer			"to shop"
#define MsgEventName_ToGoodsInfoLayer		"to goodsInfo"
#define MsgEventName_ToTaskLayer			"to task"
#define MsgEventName_ToSignInLayer			"to SignIn"
#define MsgEventName_ToLevelOptionLayer		"to LevelOption"
#define MsgEventName_ToVIPLayer				"to VIP"
#define MsgEventName_ToVIPPresentingLayer	"to VIPPresenting"
#define MsgEventName_ToSucResult			"to SucResult"
#define MsgEventName_ToFailResult			"to FailResult"
#define MsgEventName_ToGameMainLayer		"to MainLayer"
#define MsgEventName_ToGameFuHuo			"to FuHuo"
#define MsgEventName_ToRolePack				"to RolePack"


enum EProtocolID
{
	// �������˵�
	EProtocolID_ShowButtomBar = 1,
	EProtocolID_HideButtomBar,
	EProtocolID_UpdateGold,
	EProtocolID_UpdateTaskNum,



	//������
	EProtocolID_BuySuccessEffect,
	EProtocolID_UnlockRole,
	EProtocolID_BuyRolePackFinish,
	EProtocolID_BuyRolePackCancel,
	EProtocolID_VipBuyCallFunc,
	EProtocolID_UpdateRoleAtk,
	EProtocolID_HelpFeqPlay,
	EProtocolID_HelpFeqCard,


	// Vip��ȡ
	EProtocolID_VipRewardGet,


	// ħ����
	EProtocolID_UpgradeObject,

	// ����
	EProtocolID_UnlockCard,
	EProtocolID_HelpFeqStep2,


	// �̳�
	EProtocolID_BuyGoodsSucc,

	// ��Ʒ��Ϣ
	EProtocolID_RemoveGoodsInfo,

	// ��������ȡ
	EProtocolID_GetTaskReward,

	// �����������ɹ�
	EProtocolID_TyrantPackBuy,
	EProtocolID_DaZhaoBuy,
	EProtocolID_DaHudun,
	EProtocolID_FuHuoBuy,
	EProtocolID_PropPackBuy,

};

struct MakeMsgData
{
	EProtocolID id;
	std::string msg;

	MakeMsgData(std::string pmsg, EProtocolID pid)
	{
		msg = pmsg;
		id = pid;
	}
};

class CProtocolManager
{
public:
	static CProtocolManager* getInstance()
	{
		static CProtocolManager inst;
		return &inst;
	}

public: 
	void sendNotificationMsg(const std::string msg, EProtocolID id);

private:

};

/*******************************************
* ����ϵͳ
*******************************************/

// ����ͳ������
enum GamePropertyEnum
{
	GamePrKey_killMonNum,			// ��ɱ�л���
	GamePrKey_BGradeNum,			// ��ɵȼ���
	GamePrKey_AGradeNum,			// ��ɵȼ���
	GamePrKey_SGradeNum,			// ��ɵȼ���
	GamePrKey_SSGradeNum,			// ��ɵȼ���
	GamePrKey_getRedBallNum,		// �Ӻ�����
	GamePrKey_getBlueBallNum,		// ��������
	GamePrKey_getYellowBallNum,		// ��������
	GamePrKey_RedKillerNum,			// �����ɱ��
	GamePrKey_BlueKillerNum,		// �����ɱ��
	GamePrKey_YellowKillerNum,		// �����ɱ��
	GamePrKey_totalKm,				// ���Km
	GamePrKey_minKillBossTime,		// ��С��ɱbossʱ��
	GamePrKey_RedScore,				// ����ɼ�
	GamePrKey_BlueScore,			// ����ɼ�
	GamePrKey_YellowScore,			// ����ɼ�
	GamePrKey_DeadNum,				// ��������

	GamePrKey_FinishGameNum,		// ���ش���
	GamePrKey_BuyGoldTime,			// �����Ҵ���
	GamePrKey_UseDaZhao,			// ʹ�ô��д���
	GamePrKey_UseHuDun,				// ʹ�û��ܴ���
	GamePrKey_UpgradeObject,		// ������ħ��
	GamePrKey_GetStarNum,			// �������

	GamePrKey_Max,
};
#define TaskSystem_DayTaskNum		5		// ÿ����������











class GameTaskSystem
{
public:

	// ��ö����GameTaskConfig.csvһһ��Ӧ
	enum DayTaskTag
	{
		/*************** ÿ������ ********/
		DayTaskTag_Task1 = 101,		//����1�ν�Ҳ���
		DayTaskTag_Task2,			//ʹ��1����ʯ�������ɱ��
		DayTaskTag_Task3,			//����1�λ��ܡ�
		DayTaskTag_Task4,			//������ħ����Ŀ����1��������
		DayTaskTag_Task5,			//��ս���нӵ�30����ɫ������
		DayTaskTag_Task6,			//��ս���нӵ�30����ɫ������
		DayTaskTag_Task7,			//��ս���нӵ�30����ɫ������
		DayTaskTag_Task8,			//���3�δ��ء�
		DayTaskTag_Task9,			//��ɱ50�����ˡ�

		// �������ÿ������
		

		/*************** �ɾ�����********/
		DayTaskTag_Task10	= 201,		//ͨ����2�ء�
		DayTaskTag_Task11,				//ͨ����4�ء�
		DayTaskTag_Task12,				//ͨ����6�ء�
		DayTaskTag_Task13,				//ͨ����8�ء�
		DayTaskTag_Task14,				//ͨ����10�ء�
		DayTaskTag_Task15,				//ͨ����12�ء�
		DayTaskTag_Task16,				//ͨ����14�ء�
		DayTaskTag_Task17,				//ͨ����16�ء�
		DayTaskTag_Task18,				//����30�Ρ�
		DayTaskTag_Task19,				//����50�Ρ�
		DayTaskTag_Task20,				//����100�Ρ�
		DayTaskTag_Task21,				//����ȫ�����ǡ�
		DayTaskTag_Task22,				//�ۻ���ɱ500�����ˡ�
		DayTaskTag_Task23,				//�ۻ���ɱ1000�����ˡ�
		DayTaskTag_Task24,				//�ۻ���ɱ2000�����ˡ�
		DayTaskTag_Task25,				//����Ů��ﵽ������
		DayTaskTag_Task26,				//������ʯ������ﵽ������
		DayTaskTag_Task27,				//������Ҽӳɴﵽ������
		DayTaskTag_Task28,				//������ɫ������ﵽ������
		DayTaskTag_Task29,				//������ɫ������ﵽ������
		DayTaskTag_Task30,				//������ɫ������ﵽ������
		DayTaskTag_Task31,				//���9������
		DayTaskTag_Task32,				//���22������
		DayTaskTag_Task33,				//���35������
		DayTaskTag_Task34,				//���48������

		// ������ӳɾ�����
		DayTaskTag_AchiTaskEnd
	};

	struct DayTaskStr
	{
		int taskId;				// ����ID
		bool isFinish;			// �����Ƿ����
	};

	GameTaskSystem();

	~GameTaskSystem();

	void initGameProperty( void );

	// ��ȡ/������������
	int getTaskDate( void );
	void setTaskDate( int date );

	int getSignInDate(void);
	void setSignInDate(int date);


	void initGameTask( sqlite3* db );
	void initDayTaskTable( void );
	void initTaskState(void);
	void createDayTaskList();
	void createAchiTaskList();

	void saveGameAboutData( void );
	void saveGamePropertyData( void );
	void saveDayTaskData( void );
	void saveAchiTaskData(void);

	void getTaskRewardWithTaskId(int id);
	void setTaskStateToTable(int taskid);
	void delTaskStateToTable(int taskid);


	std::vector<int> getDayTaskList( void );
	std::vector<int> getAchiTaskList(void);
	int getDayTaskFinishNum( void );
	int getAchiTaskFinishNum(void);


	// �����������������ֵ
	void setGameTaskProperty(int *data);
	void addTaskPropertyWithKey(GamePropertyEnum key, int num);

	csvGameTaskConfig_s* getGameTaskListWithID( int id );

	int					_GamePropertyArr[GamePrKey_Max];

private:
	void updateDayTaskData(void);
	void updateAchiTaskData(void);

	void cleanTaskProperty( void );

private:
	sqlite3*			_sqlitedb;

	// ÿ�������б�
	std::vector<int>	_dayTaskList;
	// �ɾ������б�
	std::vector<int>	_achiTaskList;


};



/*******************************************
* ��ɫϵͳ
*******************************************/
class GameRoleSystem
{
public:
	enum TableKey
	{
		TableKey_LockState,
		TableKey_Grade,
	};

	GameRoleSystem(sqlite3* db);

	~GameRoleSystem(){}

	// ��ʼ����ɫ�б�
	void initRoleInfo( sqlite3* db );

	// ��ý�ɫ�����Ϣ
	csvRoleUpgrade_s* getRoleConfigWithID(int id);

	// ��ý�ɫ�ȼ�
	int getRoleGradeWithID(int id);
	
	// ��ý�ɫ�۸�
	int getRolePriceWithID(int id);

	// ���ý�ɫ����״̬
	void setRoleLockState(int id, bool state);
	
	// ���±�����
	void updateTable(TableKey key,int id, int data);
private:

	sqlite3* _sqlite;
};


/*******************************************
* ����ϵͳ
*******************************************/
class GameCardSystem
{
public:
	GameCardSystem(sqlite3* db);
	~GameCardSystem()
	{

	}

	void initCardInfo(sqlite3* db);
	// ��ʼ���ϴ�ѡ����
	void initCardOption(sqlite3* db);

	int getCardPriceWithID(int id);
	bool buyCardWithID(int id);
	
	void updateCardLock(void);
	void setCardLockWithId(int cardid);
	void setOptionCard(int cardType, int cardid);
	void unLockCard2();
	void firstBuyUnlockCard(void);
	csvCardAtkPConfig_s* getCardConfigWithId(int id);

	CC_SYNTHESIZE(int, mNewUnlockCard, NewUnlockCard);
private:
	sqlite3* _sqlite;

	int _curOptionCardId;

};



/*******************************************
* ��Ʒ����ϵͳ
*******************************************/

enum BuyType
{
	BuyType_Gold = 1,		// ���
	BuyType_RMB = 2,		// �����
	BuyType_Free = 3		// ���
};

enum BuyKey
{
	BuyKey_NULL					= 0,
	BuyKey_Role2				= 101, //ϣ��÷����
	BuyKey_Role3				= 102, //����˹

	BuyKey_BlueCard				= 201, //��ɫƷ�ʿ���
	BuyKey_VioletCard			= 202, //��ɫƷ�ʿ���
	
	BuyKey_UpgradeRole			= 301,	// ����Ů��
	BuyKey_UpgradeDaZhao		= 401,	// ��������
	BuyKey_UpgradeGold			= 501,	// �������
	BuyKey_UpgradeRedBall		= 601,	// ��������
	BuyKey_UpgradeBlueBall		= 701,	// ��������
	BuyKey_UpgradeYellowBall	= 801,	// ��������

	BuyKey_NewPack				= 901,	// �����������
	BuyKey_OverflowPack			= 1001,	// ����ֵ���
	BuyKey_TyrantPack			= 1101,	// �����������
	BuyKey_BuyGold				= 1201,	// ������
	BuyKey_BuyShield			= 1301,	// ���򻤶�
	BuyKey_BuyDaZhao			= 1401,	// �������
	BuyKey_BuyLife				= 1501,	// ��������
	BuyKey_BuyVIP				= 1601,	// ����VIP����

	BuyKey_BuyVIPPre			= 1602,	// ����VIPÿ������
	BuyKey_BuyFuHuo				= 1701,	// ���򸴻�

	BuyKey_BuyPropPack			= 1801, // �������
	BuyKey_BuyRolePack			= 1901, // Ů�����

};


// vip��Ч����
#define VIPValid_Day		30

typedef struct PackGoodsInfo
{
	BuyKey key;
	int gold;
	int life;
	int dazhao;
	int hudun;

	PackGoodsInfo(int goldnum, int lifenum, int dazhaonum, int hudunnum)
	{
		gold = goldnum;
		life = lifenum;
		dazhao = dazhaonum;
		hudun = hudunnum;
	}
}PackGoodsInfo;



class GameBuySystem :public Node
{
public:
	GameBuySystem();
	~GameBuySystem();

	void initBuyData( sqlite3* db );

	void initGoodsData( sqlite3* db );
	void addGoodsNumWithKey( int key, int num );
	void updateGoodsNumConfig(int key);
	void checkFirstBuyPackState(void);


	// �����Ʒ����
	csvBuyList_s* getBuyGoodsDataWithID(int id);

	bool buyGoodsWithKey( int key , int num = 1, bool isFree = false);
	bool buyGoodsWithPrice(int goodsprice);
	void firstBuyPackPrc(void);
	std::string getGoodsPayCodeWithKey(int key);

	PackGoodsInfo* getPackGoodsInfoWithKey(int key);
	void sendBuySuccessMsg(void);
	 
	CC_SYNTHESIZE(bool, m_NotionState, NotionState);
	CC_SYNTHESIZE(bool, mIsFree, FreeState);
private:
	// �������Ե�����֪ͨ
	void updateNotion(float t);

	void showBuyTips( BuyType type, int needGold );

	void callFuncBuyWidget(void);



private:
	sqlite3*			_sqlitedb;

	std::map<int, PackGoodsInfo >		_packInfoMap;

	int _curBuykey;

};


/*******************************************
* �ȼ����� 
*******************************************/
struct gradeStr
{
	int curGrade;
	int maxGrade;
};
class GameGradeMsg
{
public:
	enum ObjectType
	{
		ObjectType_Role = 1,
		ObjectType_DaZhao,
		ObjectType_Gold,
		ObjectType_RedBall,
		ObjectType_BlueBall,
		ObjectType_YellowBall
	};

	GameGradeMsg(sqlite3* db)
	{
		_sqlite = db;
		initGradeInfo();
	}
	~GameGradeMsg()
	{
	}

	void initGradeInfo(void);
	
	//��ö���ȼ�
	gradeStr* getObjectGradeWithType(int type);

	// ���ö���ȼ�
	void setObjectGradeWithType(int type, int grade);

	void buyObjectGradeWithType(int type, bool isFree = false);
	void upgradeobjectWithType(int type);
	// ��ö���������������
	csvBuyList_s getObjectUpgradePriceWithType(int type);

	int getRewardGoldWithLv(float goldNum);
	float  getObjectAtkWithCurLv( int type );

private:
	int _curUpgradeType;
	sqlite3* _sqlite;

	std::map<int, gradeStr* >		_objectGradeMap;

};



#endif