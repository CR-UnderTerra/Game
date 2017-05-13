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

	/**
	 * KnifeBarにナイフの速度と距離を設定する
	 */
	void SetKnifeDistance(float _distance, float _velocity, int _index);

	/**
	 * KnifeBarの有効かを設定する
	 */
	void SetKnifeBarIsEnable(int _index, bool _isEnable);

	/**
	 * DistanceGaugeUIのセット
	 */
	inline void SetDistanceGaugeUI(DistanceGaugeUI* _pDistanceGaugeUI)
	{
		m_pDistanceGaugeUI = _pDistanceGaugeUI;
	}

	/**
	 * ScoreUIのセット
	 */
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
