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
	
	Player��position�� �ϴ� camera������ ��ũ����ǥ�� ��ŭ �ȿ� ���Ӵ���üũ�� 
89�����ϰ� ���������� player�� ���� ��ǥ�� mouse�� ������ǥ��� ��ũ����ǥ�踦 ���ϰ� ��ũ�� ��ǥ�迡�� ���콺 ��ư�� ���� ��ġ�� �Ÿ��� ��ŭ���� ã�� ���� �� �Ÿ���ŭ ���� ��ǥ�� ���� �̵��������

�÷��̾ ȭ��(Camera View) �ȿ� �ִ��� Ȯ��
���콺 ��ġ�� ȭ��(Screen Space) ��ǥ���� ��������
���콺 Ŭ�� ��ġ�� ȭ�� �߽�(�÷��̾�)���� �󸶳� ������ �ִ��� ���
����� �Ÿ���ŭ �÷��̾��� ���� ��ǥ �̵�
	*/

	if (Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		gameLevel->isSpace = false;
		// ���� ī�޶� ���� ������ ���� ��� ��ǥ ��������
		Vector2 cameraTopLeft = gameLevel->GetCameraTopLeft();
		Vector2 cameraBottomRight = cameraTopLeft + gameLevel->GetScreenSize();

		Vector2 playerWorldPos = GetWorldPosition();

		// �÷��̾ ���� ī�޶� ȭ�� �ȿ� �ִ��� Ȯ��
		//if (playerWorldPos.x < cameraTopLeft.x || playerWorldPos.x > cameraBottomRight.x ||
		//	playerWorldPos.y < cameraTopLeft.y || playerWorldPos.y > cameraBottomRight.y)
		//{
		//	return; // ȭ�� ���̸� �̵� �Ұ���
		//}

		// ���� ���콺 ��ǥ(Screen Space) ��������
		Vector2 mouseScreenPos = Engine::Get().MousePosition();

		// �÷��̾��� ��ũ�� ��ǥ(Screen Space) ���
		Vector2 playerScreenPos = playerWorldPos - cameraTopLeft;

		// ���콺 Ŭ�� ��ġ�� �÷��̾� ��ġ ���� �Ÿ� ���
		Vector2 moveOffset = mouseScreenPos - playerScreenPos;

		// �̵� �Ÿ� �����Ͽ� ���ο� ���� ��ǥ ���
		Vector2 targetWorldPos = playerWorldPos + moveOffset;

		// Ŭ���ؼ� �̵��ؾ��� �Ÿ��� ���� ��� �̵� ���ϰ� ����
		if (gameLevel->map->maze[targetWorldPos.x][targetWorldPos.y] == '#')
		{
			return;
		}

		aStar = new AStar(gameLevel);

		gameLevel->DeleteAstarRoute();

		// ���� ��ǥ�� ȭ�鿡�� Ŭ���� ��ġ�� �̵�
		SetWorldPosition(targetWorldPos);
		gameLevel->flagIsPlayerButton = true;

		gameLevel->AstarPath = aStar->FindPath(gameLevel->map->maze);

		if (gameLevel->AstarPath.size() > 0)
		{
			// ã�� ����� actor�߰�
			gameLevel->AddAstarRouteActor(gameLevel->AstarPath);
			OutputDebugStringA("���  ã��\n");
		}
		else
		{
			OutputDebugStringA("��� �� ã��\n");
		}
	}
	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{

		gameLevel->isSpace = false;
		// ���� ī�޶� ���� ������ ���� ��� ��ǥ ��������
		Vector2 cameraTopLeft = gameLevel->GetCameraTopLeft();
		Vector2 cameraBottomRight = cameraTopLeft + gameLevel->GetScreenSize();


		Vector2 EndWorldPos = gameLevel->GetEndPosition();

		// �÷��̾ ���� ī�޶� ȭ�� �ȿ� �ִ��� Ȯ��
		//if (playerWorldPos.x < cameraTopLeft.x || playerWorldPos.x > cameraBottomRight.x ||
		//	playerWorldPos.y < cameraTopLeft.y || playerWorldPos.y > cameraBottomRight.y)
		//{
		//	return; // ȭ�� ���̸� �̵� �Ұ���
		//}


		// ���� ���콺 ��ǥ(Screen Space) ��������
		Vector2 mouseScreenPos = Engine::Get().MousePosition();

		// �÷��̾��� ��ũ�� ��ǥ(Screen Space) ���
		Vector2 endScreenPos = EndWorldPos - cameraTopLeft;

		// ���콺 Ŭ�� ��ġ�� �÷��̾� ��ġ ���� �Ÿ� ���
		Vector2 moveOffset = mouseScreenPos - endScreenPos;

		// �̵� �Ÿ� �����Ͽ� ���ο� ���� ��ǥ ���
		Vector2 targetWorldPos = EndWorldPos + moveOffset;

		// Ŭ���ؼ� �̵��ؾ��� �Ÿ��� ���� ��� �̵� ���ϰ� ����
		if (gameLevel->map->maze[targetWorldPos.x][targetWorldPos.y] == '#')
		{
			return;
		}


		aStar = new AStar(gameLevel);

		gameLevel->DeleteAstarRoute();

		// ���� ��ǥ�� ȭ�鿡�� Ŭ���� ��ġ�� �̵�
		gameLevel->SetEndPosition(targetWorldPos);

		gameLevel->flagIsPlayerButton = false;
		gameLevel->AstarPath = aStar->FindPath(gameLevel->map->maze);

		if (gameLevel->AstarPath.size() > 0)
		{
			// ã�� ����� actor�߰�
			gameLevel->AddAstarRouteActor(gameLevel->AstarPath);
			OutputDebugStringA("���  ã��\n");
		}
		else
		{
			OutputDebugStringA("��� �� ã��\n");
		}
	}
	


}
//
//void Player::Draw()
//{
//}
