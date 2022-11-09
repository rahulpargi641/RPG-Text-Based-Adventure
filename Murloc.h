#pragma once
#include "Enemy.h"

enum class EAttack: unsigned char
{EA_GroundDash, EA_SpeedDash};

class Murloc : public Enemy
{
public:
	Murloc();

private:
	void Attack(std::shared_ptr<Player>& Player) override;
	void DealDamage(int Damage) override;
	int GroundSlash();
	int SpeedDash();
	void HealthRegeneration();
	EAttack Probablity();
};

