#pragma once
#include <string>
#include <vector>
#include "Main.h"

class Enemy;

enum class ESpecialAbility: unsigned char 
{ ESA_CriticalHit = 1, ESA_Blocker, ESA_LifeSteal, ESA_RangedAttack };

class Player
{
private:
	bool bMap;
	bool bSword;
	bool bShield;
	bool bArmour;
	bool bBow;
	bool bCriticalHit; 
	bool bBlocker; 
	bool bLifeSteal; 
	bool bRangedAttack;
	bool bDead;
	bool bNotTakeDamage;

	const std::string m_Name = "Geralt";
	int m_Heal;
	int m_MaxHealth;
	int m_Health;
	unsigned int m_MeleeDamage;
	unsigned int m_RangedDamage;

private:
	int CriticalHit();
	void Block();
	void LifeSteal(std::shared_ptr<Enemy>& Enemy);
	void RangedAttackPower();
	ESpecialAbility Probablity();
	
public:
	Player();
	void Attack(std::vector<std::shared_ptr<Enemy>>& Enemies);
	void Heal();
	void DealDamage(int Damage);
	bool Dead();
	void IncreaseStats(const ELevels& CurrentLevel);
	inline int GetHealth() const { return m_Health; }
	inline int GetMeeleDamage() const { return m_MeleeDamage; }
	inline int GetRangedDamage() const { return m_RangedDamage; }
};

