/********************************************************************
������:		2015/01/21  15:56	
�ļ���: 	E:\Cocos3.3_Project\PlaneGame\Classes\Common\AI.h 
��  ��:		alex(alex)
�޸��ڣ�	2015/01/21  15:56	

Ŀ  ��:		AI��
*********************************************************************/
#ifndef __AI_H__
#define __AI_H__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "../editor-support/cocostudio/CCArmature.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;

#define CREATE_AI(__TYPE__) \
static __TYPE__* create( BasePlane* pl ) \
{ \
	__TYPE__* plAi = new (std::nothrow) __TYPE__; \
	if (plAi) \
	{ \
		plAi->setTarget(pl); \
		plAi->init(); \
		plAi->autorelease(); \
		return plAi; \
	} \
	else \
	{ \
		CC_SAFE_DELETE(plAi); \
		return nullptr; \
	} \
} \

class BasePlane;

//�ɻ�����AI
class PlaneAI : public Node
{
public:
	PlaneAI()
	{
		m_ShootInterval = 4.5f + rand_minus1_1() * 0.2f;
	}
	void setSpeed(float speed){m_speed = speed;}
	virtual void StartAI(int lvl = 1) = 0;		//�ⲿ����AI�Ŀ�ʼ�ӿ�
	virtual void NextAction(){}
	virtual void DeathAction(){}
	virtual void FuncWhenTargetHpEmpry(){}

	float getShootInterval();

	//�����ӵ�
	void StartShoot();
	void shoot();

	void FixPositionBeforeNext();

protected:
	virtual bool init();

protected:
	CC_SYNTHESIZE(BasePlane*, m_target, Target);
	Size		m_winSize;
	float		m_speed;
	int			m_AIlvl;		//AI�ȼ�
	float		m_ShootInterval;	//������
};

//�з���ͨ�ɻ�AI NO.1������Ʈ��
class EnemyAiOfMoveDown : public PlaneAI
{
public:
	CREATE_AI(EnemyAiOfMoveDown);

	virtual bool init();
	virtual void StartAI(int lvl);
	void FloatDown(float dt);

private:
	float			m_direc;
};

//�з���ͨ�ɻ�AI NO.2���������ɻ�����
class EnemyAiOfFlyToTarget : public PlaneAI
{
public:
	CREATE_AI(EnemyAiOfFlyToTarget);
	virtual bool init();
	virtual void StartAI(int lvl);
	void FlyToTarget( float t );
};

//�з���ͨ�ɻ�AI NO.3:��ͣ+����
class EnemyAiOfHoverAttack : public PlaneAI
{
public:
	CREATE_AI(EnemyAiOfHoverAttack);
	virtual bool init();
	virtual void StartAI(int lvl);

	//��ͣ΢��
	void Hover();

	//��׼���ƶ�
	void AimMove();

	void AimMoveCallback();

	//����Ŀ��
	void MoveToMainPl();

private:
	Sprite*			m_aimSp;
	Point			m_aimPos;
};

//�з���ͨ�ɻ�AI NO.4:��ͣ�����������
class EnemyAiOfFloat : public PlaneAI
{
public:
	CREATE_AI(EnemyAiOfFloat);
	virtual bool init();
	virtual void StartAI(int lvl);

	void RandFloat();
private:
	Vec2		m_OriginPos;
};

//�з���ͨ�ɻ�AI NO.5����ֹ����������
class EnemyAiofStay : public PlaneAI
{
public:
	CREATE_AI(EnemyAiofStay);
	virtual bool init();
	virtual void StartAI(int lvl );

	void Stay();
};

//�з���ͨ�ɻ�AI NO.5:����Ļ�Ϸ��������
class EnemyAiofFree : public PlaneAI
{
public:
	CREATE_AI(EnemyAiofFree);
	virtual bool init();
	virtual void StartAI(int lvl );

	void MoveFree();

};

//BOSS��AI����
class BossAI : public PlaneAI
{
public:
	virtual void StartAI(int lvl = 1);
	
	virtual std::vector<int> initAction();
	virtual void SelectAction(int ActionId);
	virtual void NextAction();
	void InitActionVec();
	int getTag();
	Vec2 getBossMidPos();
	int getLeftHpNum();

	//��������ƶ�
	virtual ActionInterval* randMove();

	//�ƶ����м�ƫ��
	virtual ActionInterval* MoveToMidRight();

	//�ƶ����м�
	virtual ActionInterval* MoveToMid();

	//��һ���ƶ�����һ��
	virtual ActionInterval* MoveToEdge();

	//��������
	virtual ActionInterval* MoveToMainPl();

	//���³�
	virtual ActionInterval* MoveDown();

	//�õ�Ŀ�����BOOS��ľ���
	float getDis(const Vec2& pos);

	void playArmat(int idx, float speedScale = 1.0f);
	void playArmat(int idx,Ref *target, SEL_FrameEventCallFunc callFunc,float speedScale = 1.0f);

	//���򲻶�ʱ�ı�
	void changeDirect();
	void changeDirCB();

	//��������
	virtual void DeathAction();
	int getBossHurts();

	int getTagWithRate(const std::vector<int>& vec);
	virtual void MoveLR();

	Armature* getArmat();

	//������ͣN��
	void PauseArmat(float t);
	void ResumeArmat();
	virtual void NextActionDelay( float t );
protected:
	float						m_direct;
	std::vector<int>			m_ActionVec;
	std::vector<int>::iterator	m_it;
};

//BOSS1��AI
class IronManBossAI : public BossAI
{
public:
	CREATE_AI(IronManBossAI);
	virtual std::vector<int> initAction();
	virtual void SelectAction(int ActionId);

	//����1:������һ���ӵ�
	void Action1();
	
	//����2����̷�5���ӵ�
	void Action2();

	//����3��ͬʱ��3���ӵ�
	void Action3();

	//����4����Ŀ�꿳ɱ
	void Action4();
	void Action4_1();

	//����5�����¿�ɱ
	void Action5();

	//����6���������ı��ѵ�
	void Action6();

	//����7������������ѵ�
	void Action7();

private:
	//���·���һ�����｣
	void shoot1Sword();

	//���·�������ɢ״����
	void shoot3Dart();

	//���·���2��ɢ״����
	void shoot2Dart();

	//���·���һ��3����ɢ״���｣
	void shoot3Sword();

	//����Ļ���ķ���һ�����ѵ�
	void shootExplosionInMid();

	//����Ļ�����һ���㷢��һ�����ѵ�
	void shootExplosionRand();

	//����ĳ�ι�������
	void PlayArmatWith1Sword();		//����һ�����｣
	void PlayArmatWith3Sword();		//����3�����｣
	void PlayArmatWith3Dart();		//����3������
	void PlayArmatWith2Dart();		//����2������
	void PlayArmatWithReady();		//����ǰ��׼��
	void PlayArmatWithMvAttack1();	//�������ǳ��1
	void PlayArmatWithMvAttack2();	//�������ǳ��2
	void PlayArmatWithMvDown();		//���³��
	void PlayArmatWithMidExpl();	//����һ�����ı��ѵ�
	void PlayArmatWithRandExpl();	//����һ��������ѵ�

	void onFrameEventOfIdex0(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	//֡�¼����������
	void onFrameEventOf3Dart(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	void onFrameEventOf2Dart(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	//֡�¼����������｣
	void onFrameEventOf1Sword(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	void onFrameEventOf3Sword(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	void onFrameEventOfAttack1(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	void onFrameEventOfAttack2(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	//���³�̹���
	void onFrameEventOfMoveDown(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	//֡�¼������䱬�ѵ�,����λ��
	void onFrameEventOfMidExpl(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	//֡�¼������䱬�ѵ�,���λ��
	void onFrameEventOfRandExpl(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	void setGunRotate(float r);
	Vec2 getShootPos();
	Vec2 getGunPos();
private:

	float						m_OriginRotate;
	Sprite*						m_Huohua;		//��
	int							m_level;		//AI�ȼ�
};

//����BOSS��AI
class BoneWarriorAI : public BossAI
{
public:
	CREATE_AI(BoneWarriorAI);
	virtual void StartAI(int lvl);

	virtual std::vector<int> initAction();
	virtual void SelectAction(int ActionId);

	void FixPos();
	//��������ƶ�
	virtual ActionInterval* randMove();

	//����2�������ӵ�
	void shoot2BezierBullet();

	//����1������
	void shoot1JumpBullet();

	void ActionRest();
	void Action1();		//�����߷��䷴����
	void Action2();		//������䷴����
	void Action3();		//����6�ŷ�����
	void Action4();		//���߷�����
	void Action5();		//�����Ƿ��䷴����

	//��������
	//virtual void DeathAction();
	//virtual void DeadArmature();

	//�������ƶ���ͬʱ��ͬʱ�����߷���һ�������ӵ�
	void ShootReboundDown();

	//���һ�������Ϸ���һ�ŷ����ӵ�
	void ShootReboundRandom();

	//���������߸��������������ӵ�
	void Shoot6Rebound();

	//�����Ƿ���һ�ŷ����ӵ�
	void ShootReboundToMainPlane();

	//����/�ұ߷���һ������
	void ShootLiudanL();
	void ShootLiudanR();

private:
	void changeDirect();
	void changeDirCB();


	int		m_times;			//�����ظ�����
};

//������BOSS��AI
class PhysicsUnit;
class RenzheBossAI : public BossAI
{
public:
	RenzheBossAI()
	{
		m_Dart = nullptr;
		m_shootDirect = -1;
		m_sandanCount = 0;
	}
	CREATE_AI(RenzheBossAI);
	virtual void StartAI(int lvl);
	virtual std::vector<int> initAction();
	virtual void SelectAction(int ActionId);

	void ActionRest();
	void ActionShootDart1();
	void ActionShootDart2();
	void ActionShootDart3();
	void ActionShootDart4();
	void ActionShootExecration();

	virtual ActionInterval* MoveToMidRight();
	virtual ActionInterval* MoveToMid();

	//ȷ�����ڵĳ�ʼλ��
	Vec2 getDartLocalPos();
	Vec2 getDartWorldPos();

	//��������
	PhysicsUnit* CreateDart(bool isWudi = false);

	//���ڹ켣�ĵ�
	PointArray* getPointArray1();		//���ڵ�λ�õ����ɻ��Ĺ켣�㣨��ת��Ϊ�������꣩
	PointArray* getPointArray2();

	//�켣1:����
	void DartAction1();

	//�켣2��������
	void DartAction2();

	//�켣3�������Ǵ�
	void DartAction3();

	//��������2�����ڣ�һ��ʱ����߱���������
	void DartAction4();

	//����ɢ��
	void ShootSandan();

	//����һƬ��
	void addCloud();
	void setArmatFunc(cocos2d::Ref *target, SEL_FrameEventCallFunc callFunc, float speed = 1.0);

	//����ʱ������
	void ExecrationParticle();
	void removeExecrationParticle();

	void pauseArmat();
	void resumeArmat();
	Vec2 getReadyOffset();

	void Ready(Ref* obj, SEL_CallFunc func);				//׼������
	void Ready1();
	void Ready2();
	void Ready3();
	void Ready4();

	void PlayArmatRest();		//��Ϣ����
	void PlayArmatKeep(float speed = 1.0f);		//���ֶ�������

	void PlayArmatShoot1();		//����켣1���ڶ���
	void PlayArmatShoot2();		//����켣2���ڶ���
	void PlayArmatShoot3();		//����켣3���ڶ���
	void PlayArmatCall2Darts();	//�ٻ�2�����ڶ���
	void PlayArmatExecration();	//���䶯��
	void PlayArmatHuishou();	//���շ��ڶ���

	//����֡�¼�
	void onFrameEventOfShoot1(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		//�켣1
	void onFrameEventOfShoot2(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		//�켣2
	void onFrameEventOfShoot3(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		//�켣3
	void onFrameEventOfCall2Darts(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);	//�ٻ�2������
	void onFrameEventOfExecration(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);	//����
	void onFrameEventOfHuishou(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);	//����
	void onFrameEventOfKeep(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		//��������
	void onFrameEventOfRest(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		//��Ϣ
	void onFrameEventOfReady(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		//׼��

	virtual void DeathAction();
	Vec2 getExecrationPos();

private:
	PhysicsUnit*				m_Dart;
	int					m_shootDirect;
	float				m_action1Time;
	float				m_action2Time;
	float				m_action3Time;
	float				m_action4Time;
	float				m_sandanSpeed;
	float				m_sandanNum;		//ɢ������
	int					m_sandanCount;		//ɢ���������
	int					m_sandanCountMax;	//ɢ�������������
};

//����AI
class PoseidonBossAI : public BossAI
{
public:
	CREATE_AI(PoseidonBossAI);
	virtual void StartAI(int lvl);
	virtual std::vector<int> initAction();
	virtual void SelectAction(int ActionId);

	void Action0();
	void Action1();	//һ�����ӵ�
	void Action2();	//��2�б���������
	void Action3();	//�ӵײ�Ʈ��һ��ˮ�ݣ���ը
	void Action4();	//��BOSS�ܱ�����3��ˮ��
	void Action5();	//������תͷ���ӵ�
	void Action6();	//�����������ӵ�

	/******�����ӵ�*****/

	//һ�����ӵ�
	void ShootOneLineBullet();

	//��2�б���������
	void ShootTwoBezierBulletL();
	void ShootTwoBezierBulletR();

	//�ӵײ�Ʈ��һ��ˮ�ݣ���ը
	void ShootOneShuiPaoBullet();

	//��BOSS�ܱ�����3��ˮ��
	void Shoot3ShuiPaoBullet();

	//������תͷ���ӵ�
	void ShootRotateBullet();

	//�����������ӵ�
	void SHootTriangleBullet(float angle);

	void ShootTriangBulletSomeTimes();

	/***************���Ź�������**************/
	void PlayAnimation1();
	void PlayAnimation2L();
	void PlayAnimation2R();
	void PlayAnimation3();
	void PlayAnimation4();
	void PlayAnimation5();
	void PlayAnimation6();
	void PlayAnimationRest();
	void PlayAnimationRest(float dur);

	/***************��������֡����*************/
	void onFrameEventOfShoot1(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfShoot2L(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfShoot2R(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfShoot3(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfShoot4(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfShoot5(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfShoot6(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		

	void PauseDur(float dt);
	void pauseArmat();
	void resumeArmat();
	void changeSpeed(float scale);

	Vec2 getLeftHandPos();
	Vec2 getRightHandPos();
private:
	int			m_bezierTimes;		//���䱴���������ӵ�����
};


//Ůǹ
class DirectBullet;
class FemaleGunBossAi : public BossAI
{
public:
	CREATE_AI(FemaleGunBossAi);
	virtual void StartAI(int lvl);

	virtual std::vector<int> initAction();
	virtual void SelectAction(int ActionId);

	virtual void FuncWhenTargetHpEmpry();

	//����1���ƶ������·����ӵ���ѭ��N��
	void ActionShootDown();

	//����2������Ļ�м䣬����ɨ��N��
	void ActionSaoShe();

	//����3���ƶ��������Ƿ���ɢ��
	void ActionShootAmmi();

	//����4�����һ����һ������Ŀ��
	void ActionShootWingOneByOne();

	//����5�����2����2������Ŀ��
	void ActionShootWing2By2();

	//����6��2��������Ŀ���ͬʱ�������Ƿ���ɢ��
	void ActionCombine();

private:
	//���һ������,���·���
	void addWeaponShootDown(bool isleft);

	//���һ������������ɨ��
	void addWeaponSaoShe();

	//��ǹ����Ŀ�����
	void JiqiangShoot();

	Bone* getGun();

	//֡�¼�
	void onFrameEventOfShootDown(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfSaoShe(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		

	void playArmatShootDown();
	void playArmatSaoShe();

	void StopSaoShe();
	void CreateJiqiang();
	void StopJiqiang();
	void ShootWingOneByOne();
	void ShootWing2By2();
	void ShootWing2By2WithSandan();
	void CreateWing();

	void setArmatWingsHide(bool b);
	void ShowArmatWings();
	void HideArmatWings();

	Bone* getWing(int idx);
	void NextActionDelay( float t );
private:
	int			m_shootDownTimes;
	int			m_shootBulletCounts;
	int			m_SaoSheTimes;
	Sprite*		m_Gun;
	int			m_WingId;
	std::string	m_bulletFrameName;
	std::vector<DirectBullet*>	m_WingVec;
};

//�۾�BOSS��AI
class EyeOfBoss;
class EyeBossAi : public BossAI
{
public:
	CREATE_AI(EyeBossAi);
	virtual void StartAI(int lvl);

	virtual std::vector<int> initAction();
	virtual void SelectAction(int ActionId);
	virtual void FuncWhenTargetHpEmpry();

	//��Ϣ
	void ActionRest();

	//����1�����·���Ʈ��+�����ӵ�
	void ActionShootFallingBullet();

	//����2�����·���ɨ�伤��
	void ActionShootSaosheLaser();

	//����3���������� + �����ӵ�
	void Action3LaserAnd2Bullet();

	//����4�����䳯��Ŀ��������ӵ�
	void ActionShootBezierBullet();

	//����5��5������
	void Action5Laser();

	//����6��������������
	void ActionShootTelescopicLaser();

	//����7�������
	void ActionWujiaoxing();

	void shootFallingBullet();
	void shootTelescopicLaser();
	void shootBezierBullet();
	void shootSaosheLaser();
	void shootMidLaser();
	void shootMidLaser1();

	void shootJiaochaEye1();
	void shootJiaochaEye2();

	void DelayShootZhixianEye1();
	void DelayShootZhixianEye2();

	void shootZhixianEye1();
	void shootZhixianEye2();

	void shootZhixianEye0();
	void shootZhixianEye3();

	void SwitchEyeState(int id, bool isOpen);

	//��ʼ���۾�
	void InitEyes();
	void setEyesVisible(bool b);

	Bone* getBone(const std::string& boneName);
	Armature* getArmature();
	Vec2 getBonePos(const std::string& boneName);

	EyeOfBoss* getEye(int idx);
	virtual void MoveLR();
	void MoveLRSlowly();
private:
	std::vector<EyeOfBoss*>		m_EyeVec;
	int							m_TelescopicLaserTimes;
	int							m_BezierBulletTimes;
};

class YizhiBossAI : public BossAI
{
public:
	CREATE_AI(YizhiBossAI);
	virtual void StartAI(int lvl);

	virtual std::vector<int> initAction();
	virtual void SelectAction(int ActionId);

	//����1��������½������5���Ա���
	void ActionShoot5AutoExpl();

	//����2��½�����������������ظ�2��
	void ActionShoot4Missile();

	//����3��ͬʱ����5�����ٵ�
	void ActionShoot5SpeedUpBullet();

	//����4�������Ƿ����Ա�����ͬʱ��������������
	void ActionSootAutoExplAndMissile();

	//����5����Ļ
	void ActionDanmu();

	//����6��������
	void ActionHuiXuan();

	//�����Ƿ���һ���Ա��ӵ�
	void shootOneAutoExposion();

	//������������
	void shootOneSpiralMissile(const std::string& boneName);

	//�����Ա��ӵ�(����������)
	void shootOneAutoExposion(const std::string& boneName, float angle, float t);

	//���䵯Ļ
	void shootDanmu(const std::string& boneName);

	//���������Ļ
	void shootHuiXuan();

	void CreateGun();
	void GunRotation(float r);
	Vec2 getGunShootPos();

	Armature* getArmature();
	Bone* getBone(const std::string& boneName);

	void onFrameEventOfSpiralMissile1(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfSpiralMissile2(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfSpiralMissile3(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfSpiralMissile4(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
	void onFrameEventOfSpeedUpBullet(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	void onFrameEventOfDanmu1(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfDanmu2(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfDanmu3(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfDanmu4(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	cocos2d::Vec2 getBonePos( const std::string& boneName );

	virtual void NextActionDelay(float t);
private:
	Sprite*			m_Gun;
	int				m_ShootAutoExplTimes;
	int				m_ShootMissileTimes;
	int				m_ShootMissileMaxTimes;
	int				m_ShootExplAndMissile;
	int				m_action3Count;

};

//˫ǹBOSS��AI
class DoubleGunBossAI : public BossAI
{
public:
	CREATE_AI(DoubleGunBossAI);
	virtual void StartAI(int lvl);

	virtual std::vector<int> initAction();
	virtual void SelectAction(int ActionId);

	//����1��
	void Action1();
	void Action2();
	void Action3();
	void Action4();
	void Action5();
	void Action6();
	void Action7();
	void Action8();

		
	//��һ�׶���
	void onFrameEventOfReady(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfShoot(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfEnd(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);	

	//�ڶ��׶���
	void onFrameEventOfReady2(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfShoot2(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfEnd2(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);	

	//�ڶ��׶�������Ůǹ����
	void onFrameEventOfReady2_1(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfShoot2_1(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);		
	void onFrameEventOfEnd2_1(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);	

	//˫ǹ����
	void onFrameEventOfTwoGuns(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);	

	void addDanmuWithConfig(const std::string& id, const Vec2& pos, bool isAmmi = false);

private:
	int			m_MaxTimes;
	int			m_CurTimes;
	std::string	m_DanmuId;

};

//AI����
class PlaneAIFactory : public Ref
{
public:
	static PlaneAIFactory* create();
	void purge();

	bool init();

	PlaneAI* AddEnemyAiByIdx(BasePlane* pl, int id);


};

#endif // __AI_H__