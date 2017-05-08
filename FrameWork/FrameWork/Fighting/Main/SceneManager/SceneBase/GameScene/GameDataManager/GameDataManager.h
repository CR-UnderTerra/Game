/**
 * @file   GameDataManager.h
 * @brief  GameDataManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H
#include "Singleton.h"

class DistanceGaugeUI;
class ScoreUI;

class GameDataManager
{
	friend Lib::Singleton<GameDataManager>;
public:
	/**
	 * 制御関数
	 */
	void Update();

	/**
	 * 描画関数
	 */
	void Draw();

	inline void SetDistanceGaugeUI(DistanceGaugeUI* _pDistanceGaugeUI)
	{
		m_pDistanceGaugeUI = _pDistanceGaugeUI;
	}

	inline void SetScoreUI(ScoreUI* _pScoreUI)
	{
		m_pScoreUI = _pScoreUI;
	}

private:
	GameDataManager();
	~GameDataManager();

	DistanceGaugeUI* m_pDistanceGaugeUI;
	ScoreUI*		 m_pScoreUI;
};


#endif
