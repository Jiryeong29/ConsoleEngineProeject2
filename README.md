콘솔 엔진을 이용한 미니 프로젝트 구현 내용

맵 생성 (DFS, txt 저장) 
상하좌우 클릭 : 카메라를 움직여 맵 탐색 
Tap클릭 : 시점 전환( 플레이어 ↔ 목적지 ) 
tap을 누르면 camera pos = Start
다시 누르면 camera pos = End
좌측/우측 클릭 : A*알고리즘을 이용한 경로 생성
Space 클릭 : A*알고리즘을 이용한 경로 애니메이션 
 

맵을 일일이 그려주고 싶지 않아서…맵을 자동으로 만들어주는 코드가 있으면 좋을 것 같아 구현하게 되었다.

맵의 미로는 DFS로 구현하였다.

처음에는 재귀호출 방식으로 구현하였으나, 맵의 사이즈가 90* 90 정도가 넘어가면 스택이 깊어져서 스택오버플로우가 발생하였다. 따라서 재귀호출 부분을 반복문으로 바꿔주었더니 맵 크기를 더 크게 확장시킬 수 있었다.

Map의 데이터를 txt파일로 생성

360x360
 

맵을 일일이 그려주고 싶지 않아서…맵을 자동으로 만들어주는 코드가 있으면 좋을 것 같아 구현하게 되었다.

맵의 미로는 DFS로 구현하였다.

처음에는 재귀호출 방식으로 구현하였으나, 맵의 사이즈가 90* 90 정도가 넘어가면 스택이 깊어져서 스택오버플로우가 발생하였다. 따라서 재귀호출 부분을 반복문으로 바꿔주었더니 맵 크기를 더 크게 확장시킬 수 있었다.

Map의 데이터를 txt파일로 생성

게임을 시작할 때마다 맵을 랜덤으로 다시 새롭게 만들기 때문에, 한 번 게임을 다시 실행하면 기존의 맵을 잃어버리게 된다. 맵 데이터를 생성한 후 txt파일로 저장하는 기능을 추가하였다.

 

원래는 희소행렬의 데이터를 저장할 때 모든 행렬을 다 저장하는 방식이 아닌 0이 아닌 값을 인덱스만 (이런식으로 <행번호, 열번호, 값>)으로 추출하여 txt파일로 저장하고 다시 그 파일을 읽어와서 데이터를 사용하려 하였다. 그러나 막상 저장하고 읽는건 문제가 안 됐으나 그 데이터를 이용하려고 하니 머리가 아파져서… 포기하고 맵을 배열에 맵사이즈만큼 값을 저장하는 방식으로 채택하였다.

 

더보기
반복문 방식 코드(개선코드)

더보기
Class의 관계

1월 프로젝트에는 맵과 카메라의 기능들을 모두 gamelevel에 두어서 관리가 어렵다고 느껴졌었고 추가된 기능이 있어서 2월 프로젝트에는 Map클래스와 Camera클래스를 따로 구성하였다.

 

Map 사이즈를 확장 및 카메라 구현방법 변경을 하려 하였으나..
화면 녹화 중 2025-02-27 121207.mp4
2.67MB
 

방향키를 눌렀을 시 카메라는 고정되어있는 상태에서 Level에 있는 actor들 이동하는 방식으로 구현하고 싶었으나 이미 카메라는 고정이 아니라 이동을 해야 한다는 관념이 박혀있어 생각의 틀을 깨고 방법을 고안해내는 것이 어려웠다. 이걸 고민하고 구현까지 완료하기엔 프로젝트 기간이 끝나있을 거 같아서 기존의 방식을 유지하였다.

기존의 방식: world공간을 카메라가 이동하면서 비추는 방식

~~변경하고 싶었던 방식 : 카메라는 고정되어있는 상태에서 actor들과 Level이 이동하는 방식~~

→ 이 부분은 잘못 이해했었다. 기존의 내가 생각했던 방법이 맞다고 한다.

 

Map 사이즈를 확장 및 카메라 구현 방법
기존 엔진에서는 스크린 사이즈를 정해놓고 스크린 사이즈만큼 맵을 제작해 맵을 띄운다.

기본 아이디어


 

엔진에 월드 좌표계를 하나 추가하여 액터가 그 좌표 공간을 돌아다니게 하고 스크린 범위에 들어오는 액터들만 화면에 보이게 하면 맵도 만들어지고 카메라도 만들어지지 않을까 생각하였다.

구현 개요

스크린에 액터들을 보이게 하는 코드들은 GameLevel 클래스의 Draw함수에 구현해주었다.

 

GameLevel의 Draw함수코드

더보기
이렇게 하니 액터들의 클래스에서 좌표를 변경할 때 스크린 좌표를 신경쓰지 않아도 월드좌표만 신경 써주기만하면 알아서 액터들을 부분적으로 Draw해주니 편했다.

코드 흐름도

월드 맵에서 어떤 영역을 카메라에 비출건지 계산하기 위해 카메라의 현재 위치를 받아온다.
월드 좌표상에서 스크린에 비출 영역을 계산하기 위해, 가장 맨 왼쪽 상단의 위치를 현재 받아온 위치에서 (스크린사이즈/ 2)만큼 빼주어 구해준다.
screenTopLeft = Vector2(
        currentCameraWorldPos.x - (screenSize.x / 2),
        currentCameraWorldPos.y - (screenSize.y / 2)
    );


스크린에서 비출 영역이 월드 맵의 범위를 벗어나지 않도록 보정한다.
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


모든 액터들을 순회하여 액터가 월드맵 공간상에 스크린에 비춰질 영역 안에 있으면 해당 액터들만 Draw해준다.
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


 

월드 좌표계를 스크린 좌표계로 변환하는 Full 코드

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
 

회고

카메라 class를 따로 구현해주었는데 월드좌표를 스크린좌표로 계산하여 해당 영역을 그려주는 기능을 GameLevel에서 동작하게 하니 아이러니하다는 생각을 하였다. 하지만 카메라에 이 기능들을 구현해주려면 Level을 상속 받아야 하고 카메라는 액터이기 때문에 카메라의 역할은 단지 비출 영역의 중심 좌표를 가지고 있기만하는 기능을 넣어주기만해도 충분하다고 생각한다……………….

Actor
화면에 시각화되는 모든 것은 Actor

맵 데이터를 화면에 그려주려하니…
맵을 생성한 후 생각해보니 카메라가 화면을 비추는 방식은 월드 공간에서 일부 영역에 있는 액터들만 스크린에 비추는 것이었다. 그러기 위해는 맵 데이터에 있는 장애물 하나하나가 모두 액터여야 한다.

따라서 DrawableActor를 상속받는 Wall클래스를 생성하였다.

그리고 GameLevel클래스의 생성자에 맵 데이터를 생성 하는 함수를 호출함 뒤 다 생성되면 맵데이터를 모두 순회하여 모든 장애물들을 Wall클래스 타입의 액터로 만들어주었다.


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
우측 클릭 좌측 클릭

우측 클릭과 좌측 클릭을 할 때 클릭한 위치로 Player와 End액터들이 이동하게 해줘야 한다. 이렇게 하기 위해서는 또 좌표계산을 해야했다.

계산 방법

마우스 위치를 화면 좌표에서 가져오기
마우스 클릭 위치가 화면 중심(플레이어)에서 얼마나 떨어져 있는지 계산
계산한 거리만큼 플레이어의 월드 좌표 이동

// 현재 카메라가 보는 영역의 좌측 상단 좌표 가져오기
Vector2 cameraTopLeft = gameLevel->GetCameraTopLeft();
Vector2 cameraBottomRight = cameraTopLeft + gameLevel->GetScreenSize();

Vector2 playerWorldPos = GetWorldPosition();

// 현재 마우스 좌표 가져오기
Vector2 mouseScreenPos = Engine::Get().MousePosition();

// 플레이어의 스크린 좌표 계산
Vector2 playerScreenPos = playerWorldPos - cameraTopLeft;

// 마우스 클릭 위치와 플레이어 위치 사이 거리 계산
Vector2 moveOffset = mouseScreenPos - playerScreenPos;

// 이동 거리 적용하여 새로운 월드 좌표 계산
Vector2 targetWorldPos = playerWorldPos + moveOffset;

// 클릭해서 이동해야할 거리가 벽일 경우 이동 못하게 막기
if (gameLevel->map->maze[targetWorldPos.x][targetWorldPos.y] == '#')
{
	return;
}
Astar 경로 생성: Actor생성 및 해제

스페이스 버튼을 누르면 Player가 end위치까지 따라가도록 구현하였다.

Player가 end를 따라갈 때 경로 액터들도 Player의 위치가 변경될 때마다 delete되어줘야 이동하기전 경로가 화면에 보이지 않기 때문에 Player의 위치가 변경 될때마다 이동 전 위치의 경로 액터들을 delete해주었다.

const float Interval = 0.3f;
static float moveTimer = 0.0f;

moveTimer += deltaTime;
if (moveTimer >= Interval)
{
    // if. player != end
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

    moveTimer = 0.0f;
}
