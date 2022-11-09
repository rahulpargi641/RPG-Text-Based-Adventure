#pragma once
#include"Main.h"
#include "Player.h"
#include "Enemy.h"
#include "Murloc.h"

class LevelManager
{
private:
	const int m_MaxLevels = 6;
	ELevels m_CurrentLevel;
	ETurn m_Turn;
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Enemy>> m_Enemies;

public:

	LevelManager();

	inline std::shared_ptr<Player>& GetPlayer() { return m_Player; }

	inline std::vector<std::shared_ptr<Enemy>>& GetEnemies() { return m_Enemies; }

	inline ETurn GetTurn() const { return m_Turn; }
	inline void SetTurn(ETurn& Turn) { m_Turn = Turn; }

	inline int GetMaxLevelNo() const { return m_MaxLevels; }

	void CreateLevel(int CurrentLevel);

	void CreateEnemies(int CurrentLevel);

	void PlayerPlaying();

	void EnemyAIPlaying();

	void SetCurrentLevel(int Level);

	void LevelComplete();

	void ShowInfo();
};
