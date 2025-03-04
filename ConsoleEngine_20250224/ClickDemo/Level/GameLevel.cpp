#include "Engine/Engine.h"
#include "GameLevel.h"

#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"

#include "Map/Map.h"
#include "Camera/Camera.h"

#include "Actor/Wall.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Actor/AstarRoute.h"

GameLevel::GameLevel()
    :   screenSize(Engine::Get().ScreenSize().x, Engine::Get().ScreenSize().y),
        worldSize(200,200)
{

    map = new Map(worldSize.x, worldSize.y);
    // 모든 맵의 액터를 추가해 
    AddMapActor();

    end = new Start(this);
    AddActor(end);

    player = new Player(this);
    AddActor(player);

    camera = new Camera(this);
    AddActor(camera);
}

GameLevel::~GameLevel()
{

}

void GameLevel::Draw()
{

    // 카메라의 기준(=screenTopLeft)을 플레이어 월드 좌표 중심으로 둠
    currentCameraWorldPos = camera->GetWorldPosition();

    screenTopLeft = Vector2(
        currentCameraWorldPos.x - (screenSize.x / 2),
        currentCameraWorldPos.y - (screenSize.y / 2)
    );

    // 맵 범위를 벗어나지 않도록 보정
    if (screenTopLeft.x < 0)
    {
        screenTopLeft.x = 0;
    }
    // 맵의 오른쪽 끝: mapSize.x - 화면 너비
    if (screenTopLeft.x > (worldSize.x - screenSize.x))
    {
        screenTopLeft.x = (worldSize.x - screenSize.x);
    }

    if (screenTopLeft.y < 0)
    {
        screenTopLeft.y = 0;
    }

    if (screenTopLeft.y > (worldSize.y - screenSize.y))
    {
        screenTopLeft.y = (worldSize.y - screenSize.y);
    }
    // Actor 전부에 대해서 월드 → 화면 변환 & Draw
    for (Actor* actor : actors)
    {
        // DrawableActor가 아니면 패스
        auto drawable = actor->As<DrawableActor>();
        if (!drawable || !drawable->IsAcive())
            continue;

        // 월드 좌표
        Vector2 actorWorldPos = drawable->GetWorldPosition();

        // 일단, 현재 카메라 범위 안에 있는지 확인
        if (actorWorldPos.x >= screenTopLeft.x &&
            actorWorldPos.x < screenTopLeft.x + screenSize.x &&
            actorWorldPos.y >= screenTopLeft.y &&
            actorWorldPos.y < screenTopLeft.y + screenSize.y)
        {
            // 월드 → 화면 변환
            Vector2 screenPos = actorWorldPos - screenTopLeft;

            // 실제 콘솔에 그릴 위치를 SetPosition
            drawable->SetPosition(screenPos);

            // Draw
            drawable->Draw();
        }
    }
    //DrawBound();
}

void GameLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    if (Engine::Get().GetKeyDown(VK_SPACE))
    {
        OutputDebugStringA("스페이스바\n");
        if (isSpace)
        {
            isSpace = false;
        }
        else
        {
            isSpace = true;
        }
    }

    if (isSpace && !AstarPath.empty())
    {
        const float Interval = 0.3f;
        static float moveTimer = 0.0f;

        moveTimer += deltaTime;
        if (moveTimer >= Interval)
        {
            // if. player != end
            Vector2 v = GetPlayerPosition();
            player->SetWorldPosition(AstarPath[0]->GetPosition());
            for (Actor* actor : actors)
            {
                auto beforeRoute = actor->As<AstarRoute>();
                if (beforeRoute &&
                    AstarPath[0]->GetPosition().x == beforeRoute->GetWorldPosition().x &&
                    AstarPath[0]->GetPosition().y == beforeRoute->GetWorldPosition().y)
                {
                    //delete beforeRoute;
                    beforeRoute->Destroy();
                }

            }
            AstarPath.erase(AstarPath.begin());
            

            Vector2 vs = GetPlayerPosition();

            moveTimer = 0.0f;
        }
    }
    end->Update(deltaTime);
    player->Update(deltaTime);

}

void GameLevel::AddMapActor()
{
    for (int ix = 0; ix < worldSize.y; ++ix)
    {
        for (int jx = 0; jx < worldSize.x; ++jx)
        {
            if (map->maze[ix][jx] == '#')
            {
                Wall* wall = new Wall(ix, jx);
                AddActor(wall);
            }
        }
    }
}

Vector2 GameLevel::GetPlayerPosition()
{
    return player->GetWorldPosition();
}

Vector2 GameLevel::GetEndPosition()
{
    return end->GetWorldPosition();
}

void GameLevel::SetPlayerPosition(Vector2 newPosition)
{
    player->SetWorldPosition(newPosition);
}

void GameLevel::DeleteAstarRoute()
{
    for (Actor* actor : actors)
    {
        // AstarRoute면
        auto beforeRoute = actor->As<AstarRoute>();
        if (beforeRoute)
        {
            //delete beforeRoute;
            beforeRoute->Destroy();
        }
      
    }

    //for (int ix = 0; ix < actors.size();)
    //{
    //    auto route = actors[ix]->As<AstarRoute>();
    //    if (route)
    //    {
    //        delete actors[ix];
    //        actors[ix] = nullptr;
    //        actors.erase(actors.begin() + ix);
    //        continue;
    //    }

    //    ++ix;
    //}
}

void GameLevel::AddAstarRouteActor(std::vector<Node*> path)
{

    for (int ix = 0; ix < path.size(); ++ix)
    {
        if ((path[ix]->GetPosition().x == player->GetWorldPosition().x && path[ix]->GetPosition().y == player->GetWorldPosition().y)
            || (path[ix]->GetPosition().x == end->GetWorldPosition().x && path[ix]->GetPosition().y == end->GetWorldPosition().y)
            )
        {
            continue;
        }
        aStarRoute = new AstarRoute(path[ix]->GetPosition().x, path[ix]->GetPosition().y);

        AddActor(aStarRoute);

    }
}

void GameLevel::DrawBound()
{

    // 화면 테두리 그리기
    for (int ix = 0; ix < screenSize.x; ++ix)
    {
        for (int jx = 0; jx < screenSize.y; ++jx)
        {
            // 왼/오른쪽 테두리
            if (ix == 0 || ix == screenSize.x - 1)
            {
                Engine::Get().Draw(Vector2(ix, jx), "*", Color::Red);
            }
            // 위/아래 테두리
            else if (jx == 0 || jx == screenSize.y - 1)
            {
                Engine::Get().Draw(Vector2(ix, jx), "*", Color::Red);
            }
        }
    }
}

void GameLevel::SetEndPosition(Vector2 newPosition)
{
    end->SetWorldPosition(newPosition);
    
}
