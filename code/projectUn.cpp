#include "projectUn.h"

USING_NS_CC;

cocos2d::Scene* projectUn::createScene()
{
    return projectUn::create();
}

bool projectUn::init()
{
    if (!Scene::init())return false;

    // ī�޶� �ʱ�ȭ
    camera = Camera::create();
    //userSprite->setCameraMask((unsigned short)CameraFlag::USER1);
    camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera);


    userSprite = Sprite::create("New/user/UserMain.png");
    userAnimIdle();
    userSprite->setPosition(Vec2(950, 223));
    userSprite->setScale(1.0f);
    this->addChild(userSprite);

    // ī�޶�� ����
    userSprite->setCameraMask((unsigned short)CameraFlag::USER1);

    //CreateSpadeMan(100, 200);
    //CreateSpadeMan(100, 200);
    //CreateSpadeMan(100, 200);
    createMonster( 850,223);
    //createMonster(750, 400);
    //createMonster(900, 350);
    //createMonster(1000, 350);
    //�Ѿ� ����
    createUserAmmo();
    monstrCreateBullet();

    GroundSprite = Sprite::create("New/BackGround/Ground.png");
    GroundSprite->setPosition(Vec2(200, 97));
    GroundSprite->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(GroundSprite);

    wellSprite = Sprite::create("New/Well/tex_tower1_1.png");
    wellSprite -> setPosition(Vec2(600, 223));
    wellSprite ->setCameraMask((unsigned short)CameraFlag::USER1);
    wellSprite->setFlippedX(true);
    this->addChild(wellSprite);

    log("%d", wellHp);


    this->scheduleUpdate();
    return true;
}

void projectUn::onEnter()
{
    Scene::onEnter();

    //�̺�Ʈ ������ ���
    _listener = EventListenerKeyboard::create();

    _listener->onKeyPressed = CC_CALLBACK_2(projectUn::onKeyPressed, this);
    _listener->onKeyReleased = CC_CALLBACK_2(projectUn::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void projectUn::onExit()
{
    // �̺�Ʈ ������ ����
    _eventDispatcher->removeEventListener(_listener);
    projectUn::onExit();
}

void projectUn::update(float dt)
{
    auto x = userSprite->getPositionX();

    //������ ����
    {
        if (_keyCodeX == 1)
        {
            userSprite->setPosition(Vec2(x - 2, userSprite->getPositionY()));
            if (spadeManEx.size() != 0)
            {
                for (int i = 0; i < spadeManEx.size(); i++)
                {
                    if (spadeManEx[i].state == 0 || spadeManEx[i].state == 1)
                        unitMove();

                         
                }
            }
                

        }       
        else if (_keyCodeX == 2)
        {
            userSprite->setPosition(Vec2(x + 2, userSprite->getPositionY()));
            if (spadeManEx.size() != 0)
            {
                for (int i = 0; i < spadeManEx.size(); i++)
                {
                    if (spadeManEx[i].state == 0 || spadeManEx[i].state == 1)
                        unitMove();
                        

                }
            }

        }
           
        camera->setPosition3D
        (Vec3(userSprite->getPositionX(), userSprite->getPositionY() +140, camera->getPositionZ()));
    

        userTime += dt;
        if (_keyCodeOrder == 4)
        {
            if (userTime >= FireTime && attackStart)
            {
                FireAmmo(x, userSprite->getPositionY());
                userTime = 0;
            }
        }

        

    }

    {
        // ��Ÿ ���� ���� (����)
        //if (wellHp < 4)
        // 
        //{
        //    spadeManBuild();
        //    wellBuildTime += dt;
        //    if (wellBuildTime > 3.0f)
        //        wellHp++;

        //    if (wellHp >= 4)
        //        spadeManIdle();
        //}
    }


    //���� ����
    {
        /*
        //���� ���� �Լ� �ε�..�ʹ� �����ϰ� �����ؼ� ���� ��ġ��
        for (int i = 0; i < monsterUnits.size(); i++)
        {
            //�Ÿ�
            if ((monsterUnits[i].sprite->getPositionX() - wellSprite->getPositionX()) <= 50
                && (monsterUnits[i].nextAc == false && monsterUnits[i].state == 1)
                && !breakWell)
            {
                monsterUnits[i].nextAc = true;
                monsterUnits[i].state = 2;
            }
            else if ((monsterUnits[i].sprite->getPositionX() - wellSprite->getPositionX()) >= 50
                && (monsterUnits[i].nextAc == false && monsterUnits[i].state == 2)
                && breakWell)
            {
                monsterUnits[i].nextAc = true;
                monsterUnits[i].state = 1;
            }

            //else
            //{
            //    for (int j = 0; j < playerUnits.size(); j++)
            //    {
            //        if (monsterUnits[i].sprite->getPositionX() - spadeManEx[i].sprtie->getPositionX() <= 50 &&
            //            (monsterUnits[i].nextAc == false && monsterUnits[i].state == 1))
            //        {
            //            monsterUnits[i].nextAc = true;
            //            monsterUnits[i].state = 2;
            //            monsterUnits[i].unitAttack = true;
            //        }
            //        else if (monsterUnits[i].sprite->getPositionX() - spadeManEx[i].sprtie->getPositionX() <= 50 &&
            //            (monsterUnits[i].nextAc == false && monsterUnits[i].state == 2))
            //        {
            //            monsterUnits[i].nextAc = true;
            //            monsterUnits[i].state = 1;
            //            monsterUnits[i].unitAttack = false;
            //        }
            //    }
            //}

            //-----
            //("Monster %d: state=%d, nextAc=%s", i, monsterUnits[i].state, monsterUnits[i].nextAc ? "true" : "false");
            if (monsterUnits[i].nextAc == true && monsterUnits[i].state == 1)
            {

                //todo----------------------������ ������
                //CCLOG("��");
                monsterUnits[i].state = 1;
                monsterUnits[i].nextAc = false;
                monsterMoveAnim();
            }
            else if (monsterUnits[i].nextAc == true && monsterUnits[i].state == 2)
            {
                monsterUnits[i].nextAc = false;
                monsterUnits[i].AttackTime += dt;
                monsterAttack();

            }


            //state �� 2��� (����) -hp
            if (monsterUnits[i].state == 2)
            {
                monsterUnits[i].AttackTime += dt;
                if (monsterUnits[i].AttackTime >= 1.0f)
                {
                    monsterUnits[i].AttackTime = 0;
                    wellHit();                
                }
            }

        }
        */

        //���� ���� �Լ� �ε�..�ʹ� �����ϰ� �����ؼ� ���� ��ġ��
        for (int i = 0; i < monsterUnits.size(); i++)
        {
            //�Ÿ�
            if ((monsterUnits[i].sprite->getPositionX() - wellSprite->getPositionX()) <= 50
                && (monsterUnits[i].nextAc == false && monsterUnits[i].state == 1)
                && !breakWell)
            {
                monsterUnits[i].nextAc = true;
                monsterUnits[i].state = 2;
            }
            else if ((monsterUnits[i].sprite->getPositionX() - wellSprite->getPositionX()) >= 50
                && (monsterUnits[i].nextAc == false && monsterUnits[i].state == 2)
                && breakWell)
            {
                monsterUnits[i].nextAc = true;
                monsterUnits[i].state = 1;
            }

            //else
            //{
            //    for (int j = 0; j < playerUnits.size(); j++)
            //    {
            //        if (monsterUnits[i].sprite->getPositionX() - spadeManEx[i].sprtie->getPositionX() <= 50 &&
            //            (monsterUnits[i].nextAc == false && monsterUnits[i].state == 1))
            //        {
            //            monsterUnits[i].nextAc = true;
            //            monsterUnits[i].state = 2;
            //            monsterUnits[i].unitAttack = true;
            //        }
            //        else if (monsterUnits[i].sprite->getPositionX() - spadeManEx[i].sprtie->getPositionX() <= 50 &&
            //            (monsterUnits[i].nextAc == false && monsterUnits[i].state == 2))
            //        {
            //            monsterUnits[i].nextAc = true;
            //            monsterUnits[i].state = 1;
            //            monsterUnits[i].unitAttack = false;
            //        }
            //    }
            //}

            //-----
            //("Monster %d: state=%d, nextAc=%s", i, monsterUnits[i].state, monsterUnits[i].nextAc ? "true" : "false");
            if (monsterUnits[i].nextAc == true && monsterUnits[i].state == 1)
            {

                //todo----------------------������ ������
                //CCLOG("��");
                monsterUnits[i].state = 1;
                monsterUnits[i].nextAc = false;
                monsterMoveAnim();
            }
            else if (monsterUnits[i].nextAc == true && monsterUnits[i].state == 2)
            {
                monsterUnits[i].nextAc = false;
                monsterUnits[i].AttackTime += dt;
                monsterAttack();

            }


            //state �� 2��� (����) -hp
            if (monsterUnits[i].state == 2)
            {
                monsterUnits[i].AttackTime += dt;
                if (monsterUnits[i].AttackTime >= 1.0f)
                {
                    monsterUnits[i].AttackTime = 0;
                    monsterFire(monsterUnits[i].sprite->getPositionX(), monsterUnits[i].sprite->getPositionY()
                    , monsterUnits[i]);
                }
            }

        }

    }
       


    //���� �����̴� �Լ�
    monsterMove();
}

void projectUn::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    bool wasIdle = (_keyCodeX == 0 );

    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            userLeft = true;
            Moveing = true;
            _keyCodeX |= 1;
            USpaceM = -35;

            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            userLeft = false;
            Moveing = true;
            _keyCodeX |= 2;
            USpaceM = 35; 
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            Moveing = false;
            _keyCodeX |= 8;
            userDesignate();
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            Moveing = false;
            _keyCodeX |= 16;
            break;
    }

    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_SPACE:
        attackStart = true;
        _keyCodeOrder |= 4;
        break;
    }

    if (wasIdle && _keyCodeX != 0)
    {
        userAnimMove();
        spadeManMove();
    }
        
    if (wasIdle && attackStart &&!Moveing)
        attackAnim();

}

void projectUn::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        userLeft = true;
        Moveing = false;
        _keyCodeX ^= 1;
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        userLeft = false;
        Moveing = false;
        _keyCodeX ^= 2;
        break;
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        Moveing = false;
        _keyCodeX ^= 8;
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        Moveing = false;
        _keyCodeX ^= 16;
        break;
    }

    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_SPACE:
        attackStart = false;
        _keyCodeOrder ^= 4;
        break;
    }


    if(attackStart)
        attackAnim();
    else if (_keyCodeX == 0)
    {
        userAnimIdle();
        spadeManIdle();
    }
        
    
}
 
void projectUn::createUserAmmo()
{
    // �ʿ��� �Ѿ˸�ŭ �̸� ���� 
    for (int i = 0; i < 1000; ++i) {
        //�Ѿ� �̹���
        auto bullet = Sprite::create("New/object/gunAmmo.png");
        // ó���� ȭ�� �ۿ� ��ġ
        bullet->setPosition(Vec2(-100, -100));
        //������ ȭ�� ������ ����
        bullet->runAction(Hide::create());
        this->addChild(bullet);

        //�迭�� �ֱ�
        vBullet.push_back(bullet);

        bullet->setCameraMask((unsigned short)CameraFlag::USER1);
    }

}



void projectUn::FireAmmo(float x, float y)
{
    // �迭�� ���� �ε����� �ִ� �Ѿ��� �߻�
    auto bullet = vBullet.at(currentBulletIndex);
    bullet->setPosition(x, y);

    int moveBullet = 0;

    if(userLeft)
        moveBullet = -1000;
    else
        moveBullet = 1000;

    auto forward = MoveTo::create(0.5f, Vec2(x + moveBullet, y));

    auto seq = Sequence::create(
        Show::create(),
        forward,
        nullptr);
    bullet->runAction(seq);

    // �ε��� ��ȯ (�迭 ���� �����ϸ� ó������ ���ư�)
    currentBulletIndex = (currentBulletIndex + 1) % vBullet.size();
}

void projectUn::userDesignate()
{
    if (spadeManEx.size() <= 0)
        return;

    if (userSprite->getPositionX() <= wellSprite->getPositionX())
    {
     
        WellUnits.push_back(spadeManEx[0]);
        spadeManEx.erase(spadeManEx.begin());

        //spadeManEx[wellCount].sprtie->setPosition(wellSprite->getPositionX(), wellSprite->getPositionY());
        //spadeManEx[wellCount].wellBack = true;
        //spadeManEx[wellCount].state = 3;
        auto UnitX = wellSprite->getPositionX() - (USpaceM * (wellCount + 1));

        WellUnits[wellCount].sprtie->setPosition(Vec2(UnitX, wellSprite->getPositionY()));
        WellUnits[wellCount].wellBack = true;
        WellUnits[wellCount].state = 3;

        wellCount++;

    }
}

void projectUn::userAnimIdle()
{
    if (attackStart)
        return;
    userSprite->stopAllActions();  // ���� ���� ���� �׼� ����

    // �ܺ� ���α׷��� ����Ͽ� ���� plist ���� �ҷ�����
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("New/user/user.plist");

    Vector<SpriteFrame*> animFrames;
    for (int i = 0; i < 6; i++)
    {
        // StringUtils::format()=>������ �������� ���ڿ� ����
        std::string _frames = StringUtils::format("tex_hero2_idle_%02d.png", i + 1);

        // ������ ���ڿ��� �̿��Ͽ� plist ���� SpriteFrame ������ �����´�.
        SpriteFrame* frame = cache->getSpriteFrameByName(_frames);

        // ������ SpriteFrame�� ����
        animFrames.pushBack(frame);
    }

    // �ִϸ��̼� ����
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = Animate::create(animation);
    auto rep = RepeatForever::create(animate);

    userSprite->setFlippedX(userLeft);

    // ���� ��������Ʈ�� �ִϸ��̼� ����
    userSprite->runAction(rep);

}

void projectUn::userAnimMove()
{
    userSprite->stopAllActions();  // ���� ���� ���� �׼� ����

    // �ܺ� ���α׷��� ����Ͽ� ���� plist ���� �ҷ�����
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("New/user/user.plist");

    Vector<SpriteFrame*> animFrames;

    for (int i = 0; i < 8; i++)
    {
        std::string _frames = StringUtils::format("tex_hero2_walk_%02d.png", i + 1);

        SpriteFrame* frame = cache->getSpriteFrameByName(_frames);

        //������ SpriteFrame�� ����
        animFrames.pushBack(frame);
    }

    // �ִϸ��̼� ����
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = Animate::create(animation);
    auto rep = RepeatForever::create(animate);

    userSprite->setFlippedX(userLeft);
    // ���� ��������Ʈ�� �ִϸ��̼� ����
    userSprite->runAction(rep);
}

void projectUn::attackAnim()
{
    userSprite->stopAllActions();  // ���� ���� ���� �׼� ����

    // �ܺ� ���α׷��� ����Ͽ� ���� plist ���� �ҷ�����
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("New/user/user.plist");

    Vector<SpriteFrame*> animFrames;

    for (int i = 0; i < 3; i++)
    {
        std::string _frames = StringUtils::format("tex_hero2_fire_%02d.png", i + 1);

        SpriteFrame* frame = cache->getSpriteFrameByName(_frames);

        //������ SpriteFrame�� ����
        animFrames.pushBack(frame);
    }

    // �ִϸ��̼� ����
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = Animate::create(animation);
    auto rep = RepeatForever::create(animate);

    userSprite->setFlippedX(userLeft);
    // ���� ��������Ʈ�� �ִϸ��̼� ����
    userSprite->runAction(rep);
}


void projectUn::userShout()
{
    for (int i = 0; i < playerUnits.size(); i++)
    {
        playerUnits[i]->stopAllActions();
        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile("New/spadeMan/spadeMan.plist");

        Vector<SpriteFrame*>animFrames;

        for (int i = 0; i < 6; i++)
        {
            std::string _frames = StringUtils::format("tex_hero2_command_%02d", i + 1);

            SpriteFrame* frame = cache->getSpriteFrameByName(_frames);

            //������ SpriteFrame�� ����
            animFrames.pushBack(frame);
        }

        //�ִϸ��̼� ����
        auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
        auto animate = Animate::create(animation);
        auto rep = RepeatForever::create(animate);

        //�÷��̾ �ٶ󺸴� ���⿡ ���� �ִϸ��̼� �ø�
        playerUnits[i]->setFlippedX(userLeft);

        playerUnits[i]->runAction(rep);
    }
}

void projectUn::spadeManIdle()
{
    for (int i = 0; i < spadeManEx.size(); i++)
    {
        if(spadeManEx[i].state == 0 || spadeManEx[i].state == 3)
            continue;

        spadeManEx[i].sprtie->stopAllActions();
        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile("New/spadeMan/spadeMan.plist");

        Vector<SpriteFrame*>animFrames;

        for (int j = 0; j < 6; j++)
        {
            std::string _frames = StringUtils::format("tex_digger_idle1_%02d.png", j + 1);

            SpriteFrame* frame = cache->getSpriteFrameByName(_frames);

            //������ SpriteFrame�� ����
            animFrames.pushBack(frame);
        }

        //�ִϸ��̼� ����
        auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
        auto animate = Animate::create(animation);
        auto rep = RepeatForever::create(animate);

        //�÷��̾ �ٶ󺸴� ���⿡ ���� �ִϸ��̼� �ø�
        spadeManEx[i].sprtie->setFlippedX(userLeft);

        spadeManEx[i].sprtie->runAction(rep);
        spadeManEx[i].state = 0;

    }

}

void projectUn::spadeManMove()
{  

    for (int i = 0; i < spadeManEx.size(); i++)
    {
        if (spadeManEx[i].state == 1 || spadeManEx[i].state == 4)
            continue;

        spadeManEx[i].sprtie->stopAllActions();
        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile("New/spadeMan/spadeMan.plist");

        Vector<SpriteFrame*>animFrames;

        for (int j = 0; j < 8; j++)
        {
            std::string _frames = StringUtils::format("tex_digger_walk_%02d.png", j + 1);

            SpriteFrame* frame = cache->getSpriteFrameByName(_frames);

            //������ SpriteFrame�� ����
            animFrames.pushBack(frame);
        }

        //�ִϸ��̼� ����
        auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
        auto animate = Animate::create(animation);
        auto rep = RepeatForever::create(animate);
        

        spadeManEx[i].sprtie->setFlippedX(userLeft);

        spadeManEx[i].sprtie->runAction(rep);
        spadeManEx[i].state = 1;
    }


}

void projectUn::spadeManAttack()
{
    for (int i = 0; i < spadeManEx.size(); i++)
    {
        if (spadeManEx[i].state != 5 )
            continue;
        //Attack
        spadeManEx[i].sprtie->stopAllActions();

        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile("New/spadeMan/spadeMan.plist");

        Vector<SpriteFrame*>animFrames;

        for (int j = 0; j < 6; j++)
        {
            std::string _frames = StringUtils::format("tex_digger_attack1_%02d.png", j + 1);

            SpriteFrame* frame = cache->getSpriteFrameByName(_frames);

            //������ SpriteFrame�� ����
            animFrames.pushBack(frame);
        }

        //�ִϸ��̼� ����
        auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
        auto animate = Animate::create(animation);
        auto rep = RepeatForever::create(animate);

        spadeManEx[i].sprtie->setFlippedX(userLeft);

        spadeManEx[i].sprtie->runAction(rep);
    }

}

void projectUn::spadeManBuild()
{
    //Build
    spadeManSprite->stopAllActions();

    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("New/spadeMan/spadeMan.plist");

    Vector<SpriteFrame*>animFrames;

    for (int i = 0; i < 8; i++)
    {
        std::string _frames = StringUtils::format("tex_digger_build_%02d.png", i + 1);

        SpriteFrame* frame = cache->getSpriteFrameByName(_frames);

        //������ SpriteFrame�� ����
        animFrames.pushBack(frame);
    }

    //�ִϸ��̼� ����
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    auto animate = Animate::create(animation);
    auto rep = RepeatForever::create(animate);

    spadeManSprite->setFlippedX(userLeft);

    spadeManSprite->runAction(rep);
}

void projectUn::CreateSpadeMan(float x, float y)
{
    spadeManSprite = Sprite::create("New/spadeMan/spadeManMain.png");
    int unitState = 0;

    spadeManSprite->setPosition(Vec2(x, y));

    spadeManSprite->setScale(1.0f);
    this->addChild(spadeManSprite);

    //�迭�� �߰�
    //playerUnits.push_back(spadeManSprite);

    spadeManSprite->setCameraMask((unsigned short)CameraFlag::USER1);

    SpadeManUnit spade;
    spade.sprtie = spadeManSprite;
    spade.state = unitState;

    spadeManEx.push_back(spade);
}

void projectUn::wellTypeImg(int imgNum)
{
    switch (imgNum)
    {
    case 5:
        wellSprite->setTexture("New/Well/tex_tower1_1.png");
        break;
    case 4:
        wellSprite->setTexture("New/Well/tex_tower1_2.png");
        break;
    case 3:
        wellSprite->setTexture("New/Well/tex_tower1_3.png");
        break;
    case 2:
        wellSprite->setTexture("New/Well/tex_tower1_4.png");
        break;
    case 1:
        wellSprite->setTexture("New/Well/tex_tower1_5.png");
        break;
    }


    if (imgNum <= 1)
        breakWell = true;
    else
        breakWell = false;

}

void projectUn::wellHit()
{
    //�� 0?���� ����?
    log("%d", wellHp);
    wellHp--;
    log("%d", wellHp);
    wellTypeImg(wellHp);
    //if (wellHp <= 0)
    //{
    //    wellSprite->stopAllActions();
    //    breakWell = true;
    //    wellSprite->runAction(Hide::create());
    //}
}

void projectUn::unitMove()
{
    for (int i = 0; i < spadeManEx.size(); i++)
    {
        if (spadeManEx[i].state == 0 || spadeManEx[i].state == 3)
            continue;
        auto UnitX = userSprite->getPositionX() - (USpaceM * (i+1) );

        spadeManEx[i].sprtie->setPosition(Vec2(UnitX - 2, userSprite->getPositionY()));
    }
}

void projectUn::createMonster(float x, float y)
{
    monsterSprite = Sprite::create("New/monster/Monster_1.png");
    monsterSprite->setPosition(Vec2(x, y));

    monsterSprite->setScale(1.0f);
    this->addChild(monsterSprite);

    int monsterState = 1;
    bool monsterNextAcRd = true;

    monsterSprite->setCameraMask((unsigned short)CameraFlag::USER1);

    // MonsterUnit ����ü �ν��Ͻ� ����
    MonsterUnit monster;
    monster.sprite = monsterSprite;
    monster.nextAc = monsterNextAcRd; // �׼��� �ݺ� ����� �������� ���� 
    monster.state = monsterState;  // ���⼭ ���¸� ���� (0: Idle, 1: Move, 2: Attack)

    // vector�� �߰�
    monsterUnits.push_back(monster);

}

void projectUn::monsterMoveAnim()
{

    for (int i = 0; i < monsterUnits.size(); i++)
    {
        if (monsterUnits[i].state != 1)
        {
            CCLOG("���� ���� ������");
            continue;
        }
         

        monsterUnits[i].sprite->stopAllActions();

        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile("New/monster/monster1.plist");

        Vector<SpriteFrame*>animFrames;

        for (int j = 0; j < 8; j++)
        {
            std::string _frames = StringUtils::format("tex_monster10_walk1_%02d.png", j + 1);

            SpriteFrame* frame = cache->getSpriteFrameByName(_frames);

            //������ SpriteFrame�� ����
            animFrames.pushBack(frame);
        }

        //�ִϸ��̼� ����
        auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
        auto animate = Animate::create(animation);
        auto rep = RepeatForever::create(animate);

        monsterUnits[i].sprite->setFlippedX(true);


        monsterUnits[i].sprite->runAction(rep);

        
    }

}

void projectUn::monsterMove()
{
    for (int i = 0; i < monsterUnits.size(); i++)
    {
        if (monsterUnits[i].state != 1)
            continue;

        auto x = monsterUnits[i].sprite->getPositionX();
        if (x > 0)
            monsterUnits[i].sprite->setPosition(Vec2(x - 1.0f, monsterUnits[i].sprite->getPositionY()));
        //else
           // monsterUnits[i].sprite->setPosition(Vec2(x - 2, monsterSprite->getPositionY()));

    }

}

void projectUn::monsterAttack()
{
    for (int i = 0; i < monsterUnits.size(); i++)
    {
        if (monsterUnits[i].state != 2)
        {
            continue;
        }

        monsterUnits[i].sprite->stopAllActions();

        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile("New/monster/monster1.plist");

        Vector<SpriteFrame*>animFrames;

        for (int j = 0; j < 8; j++)
        {
            std::string _frames = StringUtils::format("tex_monster10_attack_%02d.png", j + 1);

            SpriteFrame* frame = cache->getSpriteFrameByName(_frames);

            //������ SpriteFrame�� ����
            animFrames.pushBack(frame);
        }


        //�ִϸ��̼� ����
        auto animation = Animation::createWithSpriteFrames(animFrames, 0.13f);
        auto animate = Animate::create(animation);
        auto rep = RepeatForever::create(animate);

        monsterUnits[i].sprite->setFlippedX(true);

        monsterUnits[i].sprite->runAction(rep);
    }
}

void projectUn::monstrCreateBullet()
{
    for (int i = 0; i < 100; i++)
    {
        auto bullet = Sprite::create("New/object/gunAmmo.png");
        // ó���� ȭ�� �ۿ� ��ġ
        bullet->setPosition(Vec2(-100, -100));
        //������ ȭ�� ������ ����
        bullet->runAction(Hide::create());
        this->addChild(bullet);

        //�迭�� �ֱ�
        monsterVBullet.push_back(bullet);

        bullet->setCameraMask((unsigned short)CameraFlag::USER1);
    }
}

void projectUn::monsterFire(int x, int y, MonsterUnit monster)
{

    auto bullet = monsterVBullet.at(currentMonsterBulletIndex);

    bullet->setPosition(x, y);

    //Todo ���ư����� Ȯ�� �� ����
    auto forward = MoveTo::create(2.0f, Vec2(x - 100, y));

    auto seq = Sequence::create(
        Show::create(),
        forward,
        nullptr);
    bullet->runAction(seq);
    // �ε��� ��ȯ (�迭 ���� �����ϸ� ó������ ���ư�)
    currentMonsterBulletIndex = (currentMonsterBulletIndex + 1) % monsterVBullet.size();

    this->schedule(schedule_selector(projectUn::monsterColision));
}

void projectUn::monsterColision(float dt)
{
    for (auto bulletIt = monsterVBullet.begin(); bulletIt != monsterVBullet.end(); )
    {
        auto bullet = *bulletIt;
        
        if (bullet->getBoundingBox().intersectsRect(wellSprite->getBoundingBox()))
        {
            bullet->stopAllActions();
            wellHit();
            bullet->setPosition(-100, -100);
            bullet->runAction(Hide::create());
  
        }

        else
        {
            ++bulletIt;
        }
    }

}



void projectUn::monsterSpawnPoint(float x, float y, float time)
{
    monstreSpawnTime += time;
    if (monstreSpawnTime >= 4.0f)
    {
        createMonster(x, y);
    }
}


