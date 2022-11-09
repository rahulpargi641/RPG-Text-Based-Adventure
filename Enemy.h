#pragma once
#include <memory>

class Player;

class Enemy
{
private:
	static int EnemyCount;
protected:
	bool bDead;
	int m_Health;
	int m_Damage;
	int m_Defese;

	virtual bool Defended();
	
public:
	Enemy();
	virtual void Attack(std::shared_ptr<Player>& Player);
	virtual void DealDamage(int Damage);
	virtual bool Dead() const;
	inline int GetHealth() const { return m_Health; }
	inline void SetHealth(int Health) { m_Health = Health; }
	inline int GetDamage() const { return m_Damage; }
};

