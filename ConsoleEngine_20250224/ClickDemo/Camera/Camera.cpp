#include "Camera.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"
Camera::Camera(GameLevel* level)
    : gameLevel(level), toggle(false)
{
    // **화면 좌표는 설정하지 않는다.**
   // 처음 시작할 때 플레이어의 "월드 좌표"만 중앙쯤으로 지정
    SetWorldPosition(Vector2(
        static_cast<int>(level->GetWorldSize().x / 2),
        static_cast<int>(level->GetWorldSize().y / 2)
            )
    );
}

Camera::~Camera()
{

}


void Camera::Draw()
{

}

void Camera::Update(float deltaTime)
{

    Super::Update(deltaTime);

    Vector2 pos = GetWorldPosition();
    if (gameLevel->isSpace)
    {
        pos.x = gameLevel->GetPlayerPosition().x;
        pos.y = gameLevel->GetPlayerPosition().y;

    }
    // 키 입력으로 월드 좌표 이동
    if (Engine::Get().GetKey(VK_LEFT))
    {
        pos.x -= 1;
        if (pos.x < 0)
            pos.x = 0;
    }
    else if (Engine::Get().GetKey(VK_RIGHT))
    {
        pos.x += 1;
        if (pos.x >= gameLevel->GetWorldSize().x)
            pos.x = static_cast<int>(gameLevel->GetWorldSize().x) - 1;
    }

    if (Engine::Get().GetKey(VK_UP))
    {
        pos.y -= 1;
        if (pos.y < 0)
            pos.y = 0;
    }
    else if (Engine::Get().GetKey(VK_DOWN))
    {
        pos.y += 1;
        if (pos.y >= gameLevel->GetWorldSize().y)
            pos.y = static_cast<int>(gameLevel->GetWorldSize().y) - 1;
    }
    if (Engine::Get().GetKeyDown(VK_TAB))
    {
        OutputDebugStringA("탭\n");
        if (toggle)
        {
            pos = gameLevel->GetPlayerPosition();
            toggle = false;
        }
        else
        {
            pos = gameLevel->GetEndPosition();
            toggle = true;
        }
    }

    //if (Engine::Get().GetKeyDown(VK_SPACE))
    //{
    //    OutputDebugStringA("스페이스바\n");
    //    if (isSpace)
    //    {
    //        isSpace = false;
    //    }
    //    else
    //    {
    //        isSpace = true;
    //    }
    //}

    //if (isSpace && !gameLevel->AstarPath.empty())
    //{
    //    // if. player != end
    //    Vector2 v = GetWorldPosition();
    //    gameLevel->SetPlayerPosition(gameLevel->AstarPath[0]->GetPosition());

    //    gameLevel->AstarPath.erase(gameLevel->AstarPath.begin());
    //    //gameLevel->AstarPath.pop_front();
    //    Vector2 vs = GetWorldPosition();
    //}
    SetWorldPosition(pos);

}
