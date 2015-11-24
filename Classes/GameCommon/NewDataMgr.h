#ifndef __NEW_ROLE_DATA_MGR__
#define __NEW_ROLE_DATA_MGR__

#include "cocos2d.h"
#include "../SQLite/sqlite3.h"

#include "../CsvMgr/CsvMgr.h"
#include "GameSystem.h"



USING_NS_CC;





// ��������ģ��
 #define SINGLETONDATA_DECLEAR( className )	public:\
 	static className	*getInstance(){ if( inst == NULL ) { inst = new (std::nothrow) className(); }	return inst; }\
 	static void			purgeInstance(){ if( inst != NULL ) { CC_SAFE_DELETE(inst);	inst = NULL; } }\
 										private:\
 										static className	*inst;


// ��������ģ�塣��cpp��ʼ����											
#define SINGLETONDATA_DEFINE( className )	className	*className::inst = NULL;

#define GameData_CardNum	9

/************************************************************************/
/* ��ɫ������ع���                                                     */
/************************************************************************/
#define  RoleGrade_Max		60
//������ʽ
#define RoleAtkFormula( grade, coe1, coe2, coe3, coe4 )						( coe1 * grade + coe2 * coe3 * coe4)
//��������ʽ
#define RoleWeaponNumFormula( grade, bass, coe )							( bass + grade/10 )
//������ʽ
#define RoleDefenseFormula( grade, bass, coe )								( coe * grade + bass)
//���˹�ʽ
#define RoleLuckFormula( grade, coe )										( coe * grade )
//���鹫ʽ
#define RoleExpFormula( grade, bass, coe1, coe2, coe3 )						( coe1 * grade * grade + coe3 * grade)
//HP��ʽ
#define RoleHpFormula( grade, bass, coe1, coe2, coe3, coe4 )				( coe1 * grade + bass + pow(coe2 , coe3) * coe4 )

/************************************************************************/
/* �齱���*/
/************************************************************************/
typedef enum RewardGoodsKey 
{
	RewardKey_1 = 1,			// ���4�ǿ���
	RewardKey_2,				// ���3�ǿ���
	RewardKey_3,				// ����ˮ��
	RewardKey_4,				// ���
	RewardKey_5,				// ���
	RewardKey_6,				// ���
	// ����Ϊ��Ϸ��

	// ����Ϊ��Ϸ��
	RewardKey_7,				// ���1�ǿ���
	RewardKey_8,				// ���2�ǿ���
	RewardKey_9,				// С����ˮ��
	RewardKey_10,				// �о���ˮ��
	RewardKey_11,				// ��̵���
	RewardKey_12,				// ���ܵ���
	RewardKey_13,				// ���е���

	// ������
	RewardKey_14,				// ���
	RewardKey_15,				// ���1~2�ǿ���
	RewardKey_16,				// �о���ˮ��
	RewardKey_17,				// �о���ˮ��
	RewardKey_18,				// �о���ˮ��
	RewardKey_19,				// ���2�ǿ���
	RewardKey_20,				// ���1~2�ǿ���
	RewardKey_21,				// ���
	RewardKey_22,				// ���
	RewardKey_23,				// ���
	RewardKey_24,				// ����ˮ��

};
	

typedef struct GameCard
{
	// use this data
	int cardID;			// ����ID 1-9
	int cardStarLv;		// �Ǽ� 1-5

}GameCard_S;

typedef struct  EntryGameConfig
{

	int		roleIndex;				// ��ɫ����

	GameCard_S	cardArr[3];			// ѡ�������Ϸ�����࿨Ƭ

}EntryGameConfig_S;

typedef enum
{
	CardDateKey_isLock,
}CardDateKey;

typedef enum
{
	RoleDateKey_isLock,
	RoleDateKey_CurExp,
	RoleDateKey_Grade,
	RoleDateKey_isOption

}RoleDateKey;

// ʱ��
enum SystemTime
{
	SystemTime_Normal,		// ��
	SystemTime_Year,		// ��
	SystemTime_Mon,			// ��
	SystemTime_Day,			// ��
	SystemTime_Hour,		// ʱ
	SystemTime_Min,			// ��
	SystemTime_Sec			// ��
};

// ��ƷID
enum GoodsID
{
	GoodsID_Gold	= 1,
	GoodsID_Life	= 4,
	GoodsID_DaZhao	= 2,
	GoodsID_HuDun	= 3,
	GoodsID_Box		= 5,// ����

	GoodsID_Role	= 6,
	GoodsID_Card	= 7,

};

// �û�����
typedef struct UserData
{
	int IsNewUser;
	int Life;
	int Gold;
	int Gem;
	int DaZhao;
	int HuDun;
}UserData;

typedef struct SignInRewardInfo 
{
	int gold;
	int life;
	int dazhao;
	int hudun;
	bool isBox;	// �Ƿ���

	SignInRewardInfo(int goldNum, int lifeNum, int dazhaoNum, int hudunNum, bool isbox)
	{
		gold = goldNum;
		life = lifeNum;
		dazhao = dazhaoNum;
		hudun = hudunNum;
		isBox = isbox;
	}

	std::string goodsDes;
};


class NewDataMgr : public Ref
{
public:

	//SINGLETONDATA_DECLEAR(NewDataMgr);
	static NewDataMgr* getInstance()
	{
		static NewDataMgr inst;
		return &inst;
	}

	NewDataMgr();

	~NewDataMgr();


public:
	// ��ʼ����ȡ���ݿ�
	void initGameData( void );
	// ��ʼ���û�����
	void initUserData( sqlite3* db );
	
	// ��ȡ/�����û���Ʒ
	void addGoodsNumWithID(GoodsID id, int num, bool isUpdateTab = true);
	int getGoodsNumWithID(GoodsID id);
	
	void setOptionRoleId(int id);

	bool getNewUserState(void);
	void setNewUserState(bool state);

	// ��ʼǩ����Ϣ
	void initSignInInfo( void );
	void getSignInReward(int day);
	SignInRewardInfo* getSignInRewardInfo(int day);

	// ���С�ֱ�
	csvEnemyPlanetype_s* getEnemyPlaneWithKey( int key = 1);
	// ����ӵ����ñ�
	csvBulletConfig_s* getBulletConfigWithId(int id);
	// ���boss���Ա�
	csvBossProConfig_s* getBossProConfigWithId(int id);


	// �Ƿ�ʹ�ù�����
	bool getCardUseState();
	void setCardUseState(bool state);

	// ���õ�һ�ν�����������
	bool getFirstEntryUpgradeState();
	void setFirstEntryUpgradeState(bool state);

	// ���õ�һ�ν���card����
	bool getFirstEntryCardState();
	void setFirstEntryCardState(bool state);

	// �ؿ��洢
	int  getCurMaxLevel(void);
	void setCurMaxLevel(int level);

	// �����ظ�ʱ��洢
	double  getHistoryLifeTime( void );
	void setHistoryLifeTime( double time );

	// ����ˢ��ʱ��洢
	double getScrollUpdateTime( void );
	void setScrollUpdateTime( double time );

	// ��ʷ�¸߳ɼ��洢
	int getHistoryHighResult( void );
	void setHistoryHighResult( int result );

	// vip��ȡ����
	int getVipGetDate(void);
	void setVipGetDate(int date);

	// vipʣ����
	int getVipDay(void);
	void setVipDay(int day);

	// ǩ��
	int getSignInDay(void);
	void setSignInDay(int day);

	// ��������׳�״̬
	bool getTyrantPackBuyState(void);
	void setTyrantPackBuyState(bool state);

	// �ؿ��Ǽ�
	void initLevelStarToMap(void);
	int getLevelStarGrade(int lv);
	int getLevelStarGradeForMap(int lv);
	void setLevelStarGrade(int lv,int grade);
	void conversionLevelGrade(int lv, int time);
	int getCountStarNum(void);

	void setLevelFinishState(int lv,bool state);
	bool getLevelFinishState(int lv);

	// ת���ַ���ʱ�䵽����
	double  convertTimeStrToNumber( std::string time ,SystemTime key = SystemTime_Normal);

	// ���XML�ַ���
	std::string getXmlStringWithKey( const char* key );

	CC_SYNTHESIZE(int, m_curLevel, CurLevel);
	CC_SYNTHESIZE(bool, mGuideNewUser, GuideNewUser);
	CC_SYNTHESIZE(bool, mGuideHunDun, GuideHunDun);
	CC_SYNTHESIZE(bool, mGuideCard, GuideCard);
	CC_SYNTHESIZE(bool, mGuideDaZhao, GuideDaZhao);
	CC_SYNTHESIZE(bool, mIsGuideIng, GuideState);
	CC_SYNTHESIZE(bool, mIsFirstEntry, FirstEntryState);


public:

	GameTaskSystem*		mGameTaskSystem;
	GameBuySystem*		mGameBuySystem;
	GameRoleSystem*		mGameRoleSystem;
	GameCardSystem*		mGameCardSystem;
	GameGradeMsg*		mGameGradeMsg;

	EntryGameConfig_S mRoleConfig;

	UserData	mUserData;
private:
	ValueMap _xmlString;

	std::map<int, SignInRewardInfo >		_signInInfoMap;
	std::map<int, int >						_levelStarMap;

	sqlite3*	_sqlitedb;


};









#endif
