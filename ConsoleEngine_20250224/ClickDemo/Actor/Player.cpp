#include "Player.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"

#include "Algorithm/AStar.h"

Player::Player(GameLevel* level)
	: DrawableActor("p") , gameLevel(level)
{
	color = Color::Blue;

	SetWorldPosition(Vector2(
		static_cast<int>(level->GetWorldSize().x / 2),
		static_cast<int>(level->GetWorldSize().y / 2)
	)
	);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	/*
	
	Player의position이 일단 camera주위로 스크린좌표계 만큼 안에 들어왓는지체크를 
89먼저하고 들어와있으면 player의 월드 좌표를 mouse의 월드좌표계로 스크린좌표계를 구하고 스크린 좌표계에서 마우스 버튼이 눌린 위치의 거리가 얼만큼인지 찾은 다음 그 거리만큼 월드 좌표계 에서 이동시켜줘야

플레이어가 화면(Camera View) 안에 있는지 확인
마우스 위치를 화면(Screen Space) 좌표에서 가져오기
마우스 클릭 위치가 화면 중심(플레이어)에서 얼마나 떨어져 있는지 계산
계산한 거리만큼 플레이어의 월드 좌표 이동
	*/

	if (Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		gameLevel->isSpace = false;
		// 현재 카메라가 보는 영역의 좌측 상단 좌표 가져오기
		Vector2 cameraTopLeft = gameLevel->GetCameraTopLeft();
		Vector2 cameraBottomRight = cameraTopLeft + gameLevel->GetScreenSize();

		Vector2 playerWorldPos = GetWorldPosition();

		// 플레이어가 현재 카메라 화면 안에 있는지 확인
		//if (playerWorldPos.x < cameraTopLeft.x || playerWorldPos.x > cameraBottomRight.x ||
		//	playerWorldPos.y < cameraTopLeft.y || playerWorldPos.y > cameraBottomRight.y)
		//{
		//	return; // 화면 밖이면 이동 불가능
		//}

		// 현재 마우스 좌표(Screen Space) 가져오기
		Vector2 mouseScreenPos = Engine::Get().MousePosition();

		// 플레이어의 스크린 좌표(Screen Space) 계산
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

		aStar = new AStar(gameLevel);

		gameLevel->DeleteAstarRoute();

		// 월드 좌표를 화면에서 클릭한 위치로 이동
		SetWorldPosition(targetWorldPos);
		gameLevel->flagIsPlayerButton = true;

		gameLevel->AstarPath = aStar->FindPath(gameLevel->map->maze);

		if (gameLevel->AstarPath.size() > 0)
		{
			// 찾은 경로의 actor추가
			gameLevel->AddAstarRouteActor(gameLevel->AstarPath);
			OutputDebugStringA("경로  찾음\n");
		}
		else
		{
			OutputDebugStringA("경로 못 찾음\n");
		}
	}
	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{

		gameLevel->isSpace = false;
		// 현재 카메라가 보는 영역의 좌측 상단 좌표 가져오기
		Vector2 cameraTopLeft = gameLevel->GetCameraTopLeft();
		Vector2 cameraBottomRight = cameraTopLeft + gameLevel->GetScreenSize();


		Vector2 EndWorldPos = gameLevel->GetEndPosition();

		// 플레이어가 현재 카메라 화면 안에 있는지 확인
		//if (playerWorldPos.x < cameraTopLeft.x || playerWorldPos.x > cameraBottomRight.x ||
		//	playerWorldPos.y < cameraTopLeft.y || playerWorldPos.y > cameraBottomRight.y)
		//{
		//	return; // 화면 밖이면 이동 불가능
		//}


		// 현재 마우스 좌표(Screen Space) 가져오기
		Vector2 mouseScreenPos = Engine::Get().MousePosition();

		// 플레이어의 스크린 좌표(Screen Space) 계산
		Vector2 endScreenPos = EndWorldPos - cameraTopLeft;

		// 마우스 클릭 위치와 플레이어 위치 사이 거리 계산
		Vector2 moveOffset = mouseScreenPos - endScreenPos;

		// 이동 거리 적용하여 새로운 월드 좌표 계산
		Vector2 targetWorldPos = EndWorldPos + moveOffset;

		// 클릭해서 이동해야할 거리가 벽일 경우 이동 못하게 막기
		if (gameLevel->map->maze[targetWorldPos.x][targetWorldPos.y] == '#')
		{
			return;
		}


		aStar = new AStar(gameLevel);

		gameLevel->DeleteAstarRoute();

		// 월드 좌표를 화면에서 클릭한 위치로 이동
		gameLevel->SetEndPosition(targetWorldPos);

		gameLevel->flagIsPlayerButton = false;
		gameLevel->AstarPath = aStar->FindPath(gameLevel->map->maze);

		if (gameLevel->AstarPath.size() > 0)
		{
			// 찾은 경로의 actor추가
			gameLevel->AddAstarRouteActor(gameLevel->AstarPath);
			OutputDebugStringA("경로  찾음\n");
		}
		else
		{
			OutputDebugStringA("경로 못 찾음\n");
		}
	}
	


}
//
//void Player::Draw()
//{
//}
