#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // 1. Tạo sprite từ ảnh nền
    auto background = Sprite::create("background.png");

    // 2. Đặt vị trí nền ở giữa màn hình
    background->setPosition(Director::getInstance()->getVisibleSize() / 2);

    // 3. Thêm vào scene (layer)
    this->addChild(background, -1);  // -1 để nó nằm phía sau các đối tượng khác
    // Lấy kích thước màn hình
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Tạo label hiển thị điểm
    _score = 0;
    _scoreLabel = Label::createWithTTF("Point: 0", "fonts/Marker Felt.ttf", 24);
    _scoreLabel->setPosition(Vec2(origin.x + visibleSize.width - 80, origin.y + visibleSize.height - 30));
    this->addChild(_scoreLabel, 1);

    // Tạo sprite chuột
    _mouse = Sprite::create("mouse.png");
    _mouse->setScale(0.5f);
    // Đặt vị trí ngẫu nhiên ban đầu
    float x = origin.x + CCRANDOM_0_1() * visibleSize.width;
    float y = origin.y + CCRANDOM_0_1() * visibleSize.height;
    _mouse->setPosition(Vec2(x, y));
    this->addChild(_mouse);

    // Bật sự kiện cảm ứng
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _mouse);

    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 locationInNode = _mouse->convertToNodeSpace(touch->getLocation());
    Size s = _mouse->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);

    // Kiểm tra chạm vào sprite chuột không
    if (rect.containsPoint(locationInNode))
    {
        // Tăng điểm
        _score++;
        // Cập nhật label điểm
        _scoreLabel->setString("Point: " + std::to_string(_score));

        // Đổi vị trí mới ngẫu nhiên cho chuột
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        float x = origin.x + CCRANDOM_0_1() * visibleSize.width;
        float y = origin.y + CCRANDOM_0_1() * visibleSize.height;
        _mouse->setPosition(Vec2(x, y));

        return true; // Đã xử lý chạm
    }

    return false; // Không xử lý chạm
}
