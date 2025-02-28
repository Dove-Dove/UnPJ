#pragma once
#include "cocos2d.h"

struct MonsterUnit 
{
	cocos2d::Sprite* sprite;
	bool nextAc ;
	int state;  // 0: Idle, 1: Move, 2: Attack
	float AttackTime = 0.0f;
	bool unitAttack = false;
	bool monsterAttack = false;
	int monsterHp = 5;
};

struct SpadeManUnit
{
	cocos2d::Sprite* sprtie;
	//���� ������ ����
	int state = 0; 
	//���� ���� 0:idle(����ٴ�)  1:move(����ٴ�)  3:idle(�� ��ġ) 4:move(�� ��ġ) 5.���� 6 ���� 7 �ƹ��͵� �ƴ� ����
	bool wellBack = false;
	float attackTime = 0.0f;
	bool unitLeft = true;
	int hp = 7;
};

class projectUn : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void onEnter();
	void onExit();

	//������Ʈ
	virtual void update(float dt) override;
	

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_FUNC(projectUn);



private:

	//ī�޶� 
	cocos2d::Camera* camera;

	//��������Ʈ

	//�÷��̾� ��������Ʈ
	cocos2d::Sprite* userSprite;
	//�÷��̾� �Ʊ� ���� ��������Ʈ (�� �� ����)
	cocos2d::Sprite* spadeManSprite;
	//���� ���� ��������Ʈ 
	cocos2d::Sprite* monsterSprite;

	//�� ��������Ʈ 
	cocos2d::Sprite* GroundSprite;

	//�μ����� �� ��������Ʈ 
	cocos2d::Sprite* wellSprite;


	//�÷��̾ ���󰡴� ����'��'
	std::vector<cocos2d::Sprite*> playerUnits;
	//���� �Ǵ� ���͵�
	std::vector<MonsterUnit> monsterUnits;
	//���� ����  TODO----------------------------
	std::vector<SpadeManUnit> spadeManEx; //�ӽ� ���� �۵� ����� �Ǹ� ����
	//���� ���� �Ǵ� ����  --------------�̰Ŵ� �Ⱦ��� ���� (�ٸ�������� ��)
	std::vector<SpadeManUnit> WellUnits;
	

	//�̺�Ʈ ������ (Ű ���� �̺�Ʈ)
	cocos2d::EventListenerKeyboard* _listener;

	//Ű������ ������
	int _keyCodeX;
	int _keyCodeOrder;
	bool userLeft = true;

	//���� 
	bool attackStart = false;
	//�����̴� ��
	bool Moveing = false;
	//�߻� �ð�
	float FireTime = 0.5f;

	//�ð� ����
	float userTime = 0.0f;

	int currentBulletIndex;
	int currentUintIndex;
	int currentMonsterBulletIndex;


	//�Ѿ� (������Ʈ Ǯ��)�� ���� ����
	std::vector<cocos2d::Sprite*>vBullet;

	std::vector<cocos2d::Sprite*>monsterVBullet;

	//���� ����
	//�Ѿ� ����
	void createUserAmmo();

	// ���� ��ȣ �ۿ�---
	//�Ѿ� �߻�
	void FireAmmo(float x, float y);

	void userDesignate();

	

	//�ִϸ��̼� .����----
	void userAnimIdle();
	void userAnimMove();
	void attackAnim();
	void userShout();

	

	// �Ʊ� ���� ����
	// �Ʊ��� ���� ������ �Ÿ��� �ֱ� ���� ����
	float USpaceM = 35;

	// �Ʊ� ����----------------
	//�� ü�� ����
	int wellHp = 5;
	float wellBuildTime = 0.0f;
	int wellCount = 0;
	//�� ��� ���������� ���Ѱ�
	bool breakWell = false;
	
	
	
	//�� ���� �ִϸ��̼�
	void spadeManIdle();
	void spadeManMove();
	void spadeManAttack();
	void spadeManBuild();

	void CreateSpadeMan(float x, float y);

	void wellTypeImg(int imgNum);
	void wellHit();
	

	//���� �����̰� ����
	void unitMove();

	//�� ���� 
	//���� ����
	float monstreSpawnTime = 0.0f;

	//�� ����
	void createMonster(float x, float y);
	//�ִϸ��̼�
	void monsterMoveAnim();
	//�Ϲ� ������
	void monsterMove();
	void monsterAttack();
	void monsterColision(float dt);
	//���� ���� �߻�
	void monstrCreateBullet();
	void monsterFire(int x, int y, MonsterUnit monster);

	///���� ����
	void monsterSpawnPoint(float x, float y, float time);
	

};