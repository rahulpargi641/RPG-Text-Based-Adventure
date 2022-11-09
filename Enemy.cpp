#include <iostream>
#include "Enemy.h"
#include "Player.h"

int Enemy::EnemyCount = 0;

Enemy::Enemy()
{
	bDead = false;
	Enemy::EnemyCount++;
	m_Health = 100;
	m_Damage = 50;
	m_Defese = 50;
}

void Enemy::Attack(std::shared_ptr<Player>& Player)
{
	Player->DealDamage(m_Damage);
}

bool Enemy::Defended()
{
	srand((unsigned) time(NULL));
	int Defense = rand();
	Defense = rand() % 100 + 1;  //Generate random number 1 to 100
	if (Defense <= 20) //20% probability 
	{
		std::cout << "" << std::endl;
		std::cout << "---Enemy Defended!--- No Damage Done!" << std::endl;
		return true;
	}
	else
		return false;
}

void Enemy::DealDamage(int Damage)
{
	if (!(m_Health <= 0))
	{
		if (Defended()) return;

		std::cout << "   ||   Damage Done: " << Damage << std::endl;
		m_Health -= Damage;
		if (m_Health <= 0)
		{
			EnemyCount--;
			std::cout << "--Enemy: now, I'm dead :(-----" << std::endl;
			bDead = true;
		}
	}
}

bool Enemy::Dead() const
{
	if (bDead) return true;
	else 
		return false;
}




