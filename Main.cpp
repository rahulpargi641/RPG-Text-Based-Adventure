#include <iostream>
#include <memory>
#include <vector>
#include "Main.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelManager.h"

int main()
{
	bool bGameLoop;
	bool bLevelLoop;

	std::unique_ptr<LevelManager> LevelManager = std::make_unique<class LevelManager>();
	std::vector<std::shared_ptr<Enemy>>& Enemies = LevelManager->GetEnemies();
    std::shared_ptr<Player>& Player = LevelManager->GetPlayer();
	ETurn Turn = LevelManager->GetTurn();
	int MaxLevelNo = LevelManager->GetMaxLevelNo();

	std::cout << "Text Based RPG Adventure!" << std::endl;
	std::cout << "" << std::endl;
	bGameLoop = true;
	while (bGameLoop)
	{
		for (int i = 1; i < MaxLevelNo +1; i++)
		{
			if (bGameLoop == false) break;
			std::cout << "Level " << i<<  " Loaded!" << std::endl;
			LevelManager->CreateLevel(i);
			bLevelLoop = true;

			while (bLevelLoop)
			{
				if (Turn == ETurn::ET_Player)
				{
					LevelManager->PlayerPlaying();
					if (Enemies.empty())
					{
						if (i == MaxLevelNo) break;
						std::cout << "All Enemies are dead, Loading Next Level........" << std::endl;
						std::cout << "-----------------------------------------------------------" << std::endl;
						std::cout << "" << std::endl;
						LevelManager->LevelComplete();
						bLevelLoop = false;
					}
					else
					{
						Turn = ETurn::ET_AIEnemy;
						LevelManager->SetTurn(Turn);
					}		
				}
				else
				{
					LevelManager->EnemyAIPlaying();
					if (Player->Dead())
					{
						bLevelLoop = false;
						bGameLoop = false;
					}
					else
					{
						Turn = ETurn::ET_Player;
						LevelManager->SetTurn(Turn);
					}
				}
			}
		}
		bGameLoop = false;
	}
	
	std::cout << "Game Over!" << std::endl;
}

