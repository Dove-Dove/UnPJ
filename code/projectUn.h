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
	//현제 유닛의 순번
	int state = 0; 
	//유닛 상태 0:idle(따라다님)  1:move(따라다님)  3:idle(벽 배치) 4:move(벽 배치) 5.공격 6 빌드 7 아무것도 아닌 상태
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

	//업데이트
	virtual void update(float dt) override;
	

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_FUNC(projectUn);



private:

	//카메라 
	cocos2d::Camera* camera;

	//스프라이트

	//플레이어 스프라이트
	cocos2d::Sprite* userSprite;
	//플레이어 아군 유닛 스프라이트 (삽 든 유닛)
	cocos2d::Sprite* spadeManSprite;
	//몬스터 유닛 스프라이트 
	cocos2d::Sprite* monsterSprite;

	//땅 스프라이트 
	cocos2d::Sprite* GroundSprite;

	//부서지는 벽 스프라이트 
	cocos2d::Sprite* wellSprite;


	//플레이어를 따라가는 유닛'들'
	std::vector<cocos2d::Sprite*> playerUnits;
	//스폰 되는 몬스터들
	std::vector<MonsterUnit> monsterUnits;
	//유닛 관련  TODO----------------------------
	std::vector<SpadeManUnit> spadeManEx; //임시 변수 작동 제대로 되면 수정
	//벽에 배정 되는 유닛  --------------이거는 안쓰면 삭제 (다른방식으로 함)
	std::vector<SpadeManUnit> WellUnits;
	

	//이벤트 리스너 (키 관련 이벤트)
	cocos2d::EventListenerKeyboard* _listener;

	//키값으로 움직임
	int _keyCodeX;
	int _keyCodeOrder;
	bool userLeft = true;

	//공격 
	bool attackStart = false;
	//움직이는 중
	bool Moveing = false;
	//발사 시간
	float FireTime = 0.5f;

	//시간 저장
	float userTime = 0.0f;

	int currentBulletIndex;
	int currentUintIndex;
	int currentMonsterBulletIndex;


	//총알 (오브젝트 풀링)을 위한 백터
	std::vector<cocos2d::Sprite*>vBullet;

	std::vector<cocos2d::Sprite*>monsterVBullet;

	//유저 관련
	//총알 생성
	void createUserAmmo();

	// 유저 상호 작용---
	//총알 발사
	void FireAmmo(float x, float y);

	void userDesignate();

	

	//애니메이션 .유저----
	void userAnimIdle();
	void userAnimMove();
	void attackAnim();
	void userShout();

	

	// 아군 유닛 관련
	// 아군과 유닛 사이의 거리를 주기 위한 변수
	float USpaceM = 35;

	// 아군 유닛----------------
	//벽 체력 관련
	int wellHp = 5;
	float wellBuildTime = 0.0f;
	int wellCount = 0;
	//벽 사용 가능한지에 관한것
	bool breakWell = false;
	
	
	
	//삽 유닛 애니메이션
	void spadeManIdle();
	void spadeManMove();
	void spadeManAttack();
	void spadeManBuild();

	void CreateSpadeMan(float x, float y);

	void wellTypeImg(int imgNum);
	void wellHit();
	

	//유닛 움직이게 설정
	void unitMove();

	//적 관련 
	//몬스터 스폰
	float monstreSpawnTime = 0.0f;

	//적 생성
	void createMonster(float x, float y);
	//애니메이션
	void monsterMoveAnim();
	//일반 움직임
	void monsterMove();
	void monsterAttack();
	void monsterColision(float dt);
	//몬스터 관련 발사
	void monstrCreateBullet();
	void monsterFire(int x, int y, MonsterUnit monster);

	///몬스터 스폰
	void monsterSpawnPoint(float x, float y, float time);
	

};