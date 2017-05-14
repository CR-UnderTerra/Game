/**
 * @file   GameDataManager.h
 * @brief  GameDataManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H
#include "Singleton.h"
#include "Vertex2D/Vertex2D.h"

class DistanceGaugeUI;
class ScoreUI;
class HpGaugeUI;

class GameDataManager
{
	friend Lib::Singleton<GameDataManager>;
public:
	enum TARGET
	{
		PLAYER_TARGET,
		LEFT_ENEMY_TARGET,
		FRONT_ENEMY_TARGET,
		RIGHT_ENEMY_TARGET,
		TARGET_MAX
	};

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

	/**
	 * プレイヤーのHpをセットする
	 */
	inline void SetPlayerHp(int _PlayerHp)
	{
		m_PlayerHp = _PlayerHp;
	}

	/**
	 * プレイヤーのHpを取得する
	 */
	inline int GetPlayerHp()
	{
		return m_PlayerHp;
	}

	inline D3DXVECTOR2 GetPos(TARGET _target)
	{
		return m_Pos[_target];
	}

private:
	GameDataManager();
	~GameDataManager();

	DistanceGaugeUI* m_pDistanceGaugeUI;
	ScoreUI*		 m_pScoreUI;
	int				 m_PlayerHp;
	D3DXVECTOR2		 m_Pos[TARGET_MAX];

};


#endif
