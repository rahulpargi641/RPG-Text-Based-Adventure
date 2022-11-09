#include <iostream>
#include <memory>
#include "LevelManager.h"

LevelManager::LevelManager()
{
	m_CurrentLevel = ELevels::EL_Default;
	m_Turn = ETurn::ET_Player;
	m_Player = std::make_unique<Player>();
}

void LevelManager::CreateLevel(int CurrentLevel)
{
	SetCurrentLevel(CurrentLevel);
	CreateEnemies(CurrentLevel);
}

void LevelManager::CreateEnemies(int CurrentLevel)
{
	if (CurrentLevel != ELevels::EL_BossLevel)
	{
		for (int i = 0; i < CurrentLevel; i++)
		{
			std::shared_ptr<Enemy> Enemy = std::make_unique<class Enemy>();
			m_Enemies.push_back(Enemy);
			//std::cout << i + 1 << " Enemy Created!" << std::endl;
		}
		std::cout << "" << std::endl;
	}
	else
	{
		std::shared_ptr<Murloc> m_Murloc = std::make_unique<class Murloc>();
		m_Enemies.push_back(m_Murloc);
		std::cout << "Boss Level!" << std::endl;
	}
}

void LevelManager::PlayerPlaying()
{
	char Input;
	ShowInfo();
	std::cout << "" << std::endl;
	std::cout << "Geralt's Turn!      ||     ";
	std::cout << "Press 'A' to Attack, Press 'H' to Heal" << std::endl;
	
	do
	{
		std::cin >> Input;
		if (Input == 'A' || Input == 'a')
		{
			std::system("cls");
			std::cout << "" << std::endl;
			m_Player->Attack(m_Enemies);
			break;
		}
		else if (Input == 'H' || Input == 'h')
		{
			std::system("cls");
			std::cout << "" << std::endl;
			m_Player->Heal();
			break;
		}
		else
		{
			std::cout << "" << std::endl;
			std::cout << "Wrong Input, Press 'A' or Press 'H' " << std::endl;
		} 

	} while (!(Input == 'A' || Input == 'H'));
	
}

void LevelManager::EnemyAIPlaying()
{
	std::cout << "" << std::endl;
	std::cout << "Enemy AI playing....." << std::endl;
	//std::cout << "--------------------------------------" << std::endl;
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		std::cout << "Enemy " << i + 1 << " Attacked Geralt!";
		m_Enemies[i]->Attack(m_Player);
	}
	std::cout << "" << std::endl;
	
}

void LevelManager::SetCurrentLevel(int CurrentLevel)
{
	switch (CurrentLevel)
	{
	case 1:
		m_CurrentLevel = ELevels::EL_First;
		break;
	case 2:
		m_CurrentLevel = ELevels::EL_Second;
		break;
	case 3:
		m_CurrentLevel = ELevels::EL_Third;
		break;
	case 4:
		m_CurrentLevel = ELevels::EL_Fourth;
		break;
	case 5:
		m_CurrentLevel = ELevels::EL_Fifth;
		break;
	case 6:
		m_CurrentLevel = ELevels::EL_BossLevel;
	default:
		break;
	}
}

void LevelManager::LevelComplete()
{
	if (m_CurrentLevel == ELevels::EL_BossLevel) return;
	m_Player->IncreaseStats(m_CurrentLevel);
}

void LevelManager::ShowInfo()
{
	std::cout << "" << std::endl;
	std::cout << "GAME INFO:" << std::endl;
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "Current Game Level: " << (int)m_CurrentLevel << std::endl;
	std::cout << "Geralt's Health: " << m_Player->GetHealth();
	std::cout << "   |   Meele Damage: " << m_Player->GetMeeleDamage() << "   |   Ranged Damage: " << m_Player->GetRangedDamage() << std::endl;
	std::cout << "No. of Enemies: " << m_Enemies.size()<< "   |   ";

		for (int i = 0; i < m_Enemies.size(); i++)
		std::cout << "Enemy " << i + 1 << " Health: " << m_Enemies[i]->GetHealth() << "   ||   ";
		std::cout << " " << std::endl;
	std::cout << "-----------------------------------------------------------------" << std::endl;
}






