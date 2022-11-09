#include <iostream>
#include "Player.h"
#include "Enemy.h"

Player::Player()
{
	bMap = false;
	bSword = false;
	bShield = false;
	bArmour = false;
	bBow = false;
	bCriticalHit = false;
	bBlocker = false;
	bLifeSteal = false;
	bRangedAttack = false;
	bDead = false;
	bNotTakeDamage = false;

	m_MaxHealth = 500;
	m_Health = m_MaxHealth;
	m_Heal = 100;
	m_MeleeDamage = 90;
	m_RangedDamage = 30;
}

void Player::Attack(std::vector<std::shared_ptr<Enemy>>& Enemies)
{
	for (int i = Enemies.size()-1; i >=0 ; i--)
	{
			std::cout << "Geralt attacked Enemy " << i + 1 << "  ";

			if (bSword && bCriticalHit && Probablity() == ESpecialAbility::ESA_CriticalHit) Enemies[i]->DealDamage(CriticalHit()); 

			else if (bRangedAttack && bBow && Probablity() == ESpecialAbility::ESA_RangedAttack)
			{
				RangedAttackPower();	
				Enemies[i]->DealDamage(m_RangedDamage);
			}
			else
			{
				Enemies[i]->DealDamage(m_MeleeDamage);
				if (bArmour && bLifeSteal && Probablity() == ESpecialAbility::ESA_LifeSteal) LifeSteal(Enemies[i]); 
			}

			if (Enemies[i]->Dead())
			{
				Enemies.erase(Enemies.begin() + i);
				std::cout << "" << std::endl;
				//std::cout << "Geralt cleared Enemy " << i + 1 << std::endl;
			}
			break;
	}
	std::cout << "" << std::endl;
}

void Player::Heal()
{
	if (m_Health < m_MaxHealth)
	{
		m_Health += m_Heal;
		if (m_Health > m_MaxHealth) m_Health = m_MaxHealth;
		std::cout << "Geralt Healed" << ", now Health is: " << m_Health << std::endl;
		std::cout << "" << std::endl;
	}
	else
		std::cout << "Geralt's Health is Full!" << std::endl;
	
}

void Player::DealDamage(int Damage)
{
	if (bNotTakeDamage)
	{
		std::cout << "    Player Did not take any Damage because Player previously Preformed RangedAttack()!" << std::endl;
		bNotTakeDamage = false;
		return;
	}

	if (Probablity() == ESpecialAbility::ESA_Blocker && bShield && bBlocker) Block();
	else if (!(m_Health <= 0))
	{
		std::cout << "   ||   Damage Done: " << Damage << std::endl;
		std::cout << "" << std::endl;
		m_Health -= Damage;
		if (m_Health <= 0) bDead = true;
	}
}

void Player::IncreaseStats(const ELevels& CurrentLevel)
{
	std::cout << "----Player Stats Increased!----" << std::endl;
	switch (CurrentLevel)
	{
	case 1:
		m_MaxHealth = 600;
		m_Health = m_MaxHealth;
		m_MeleeDamage = 150;
		m_RangedDamage = 100;
		m_Heal = 200;

		bMap = true;
		std::cout << "----Player Recevied the Map!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 2:
		m_MaxHealth = 700;
		m_Health = m_MaxHealth;
		m_MeleeDamage = 200;
		m_RangedDamage = 150;
		m_Heal = 300;

		bCriticalHit = true;
		bSword = true;
		std::cout << "----2nd Special Ability critical Hit Unlocked! - Critical Hit!----" << std::endl;
		std::cout << "----Geralt Received the Swored!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 3:
		m_MaxHealth = 800;
		m_Health = m_MaxHealth;
		m_MeleeDamage = 250;
		m_RangedDamage = 200;
		m_Heal = 400;

		bBlocker = true;
		bShield = true;
		std::cout << "----3rd Special Ability Unlocked! - Blocker!----" << std::endl;
		std::cout << "----Geralt Received the Shield----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 4:
		m_MaxHealth = 900;
		m_Health = m_MaxHealth;
		m_MeleeDamage = 300;
		m_RangedDamage = 250;
		m_Heal = 500;

		bLifeSteal = true;
		bArmour = true;
		std::cout << "----4th Special Ability Unlocked! - Life Steal!----" << std::endl;
		std::cout << "----Geralt Received the Armour!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 5:
		m_MaxHealth = 1000;
		m_Health = m_MaxHealth;
		m_MeleeDamage = 350;
		m_RangedDamage =300;
		m_Heal = 600;

		bRangedAttack = true;
		bBow = true;
		std::cout << "----5th Special Ability Unlocked! - Ranged Attack!----" << std::endl;
		std::cout << "----Geralt Received the Bow!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	default:
		break;
	}
}

bool Player::Dead()
{
	if (bDead)
	{
		std::cout << "--Geralt: I'm dead!--" << std::endl;
		return true;
	}
	else
	return false;
}

int Player::CriticalHit()
{
	int CriticalDamage = m_MeleeDamage * 2;
	std::cout << "  ** Critical Hit! **";
	return CriticalDamage;
}

void Player::Block()
{
	std::cout << "   ***  Geralt Used Shield to Block the Attack!  ***" << std::endl;
	std::cout << "" << std::endl;
}

void Player::LifeSteal(std::shared_ptr<Enemy>& Enemy)
{
	if (!Enemy->Dead())
	{
		int StealedHealth = Enemy->GetHealth() / 3;
		Enemy->SetHealth(Enemy->GetHealth() - StealedHealth);
		m_Health += StealedHealth; // if geralt steals vitality, health can go greater then MaxHealth of the Geralt!
		std::cout << "" << std::endl;
		std::cout << "Geralt's Armour Stealed the vitality of the Enemy!" << std::endl;
	}
	else
		std::cout << "Enemy Dead, Can't Steal Vitality!" << std::endl;
}

void Player::RangedAttackPower()
{
	bNotTakeDamage = true;
	std::cout << "" << std::endl;
	std::cout << "Geralt Performed Ranged Attack!" <<std::endl;
}

ESpecialAbility Player::Probablity()
{
	srand((unsigned)time(NULL));
	int Value = rand();
	Value = rand() % 100 + 1;  //Generate random number 1 to 100

	if (Value >= 50)
	{
		if (Value <= 75) return ESpecialAbility::ESA_CriticalHit;
		else
			return ESpecialAbility::ESA_Blocker;
	}
	else
	{
		if (Value <= 25) return ESpecialAbility::ESA_LifeSteal;
		else
			return ESpecialAbility::ESA_RangedAttack;
	}
}

