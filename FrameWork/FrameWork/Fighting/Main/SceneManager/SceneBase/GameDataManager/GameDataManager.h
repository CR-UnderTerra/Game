/**
 * @file   GameDataManager.h
 * @brief  GameDataManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H
#include "Singleton.h"
#include "Vertex2D/Vertex2D.h"
#include "../GameScene/ObjectManager/ObjectBase/UIBase/DistanceGaugeUI/DistanceGaugeUI.h"

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

	enum RESULT_STATE
	{
		CLEAR,
		FAILED
	};
	
	struct RESULT_SCORE
	{
		int GoodCount,AmazingCount,FantasticCount;
		int Minute,Second;
	};



	void Init();

	/**
	 * 制御関数
	 */
	void Update();

	/**
	 * KnifeBarにナイフの速度と距離を設定する
	 */
	void SetKnifeDistance(float _distance, float _velocity, int _index);

	/**
	 * KnifeBarの有効かを設定する
	 */
	void SetKnifeBarIsEnable(int _index, bool _isEnable);

	/**
	 * ナイフのキャッチの状態を判断する
	 * @param[in] 判断ナイフのインデックス
	 */
	JudgeGaugeUI::JUDGE KnifeJadge(int _index);

	inline void AddGoodCount()
	{
		m_Result.GoodCount++;
	}

	inline void AddAmazingCount()
	{
		m_Result.AmazingCount++;
	}

	inline void AddFantastiocCount()
	{
		m_Result.FantasticCount++;
	}

	inline RESULT_SCORE GetResult()
	{
		return m_Result;
	}

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

	/**
	 * ターゲットの座標を取得する
	 */
	inline D3DXVECTOR2 GetPos(TARGET _target)
	{
		return m_Pos[_target];
	}

	inline void SetClearTime(int _minute,int _second)
	{
		m_Result.Second = _second;
		m_Result.Minute = _minute;
	}

	/**
	 * ゲームオーバーかのフラグを取得する
	 */
	inline bool GetIsGameOver()
	{
		return m_IsGameOver;
	}

	inline bool SetIsGameOver(bool _IsGameOver)
	{
		m_IsGameOver = _IsGameOver;
	}

	inline RESULT_STATE GetResultState()
	{
		if (m_PlayerHp != 0)
		{
			return CLEAR;
		}
		else
		{
			return FAILED;
		}
	}

private:
	GameDataManager();
	~GameDataManager() = default;
	DistanceGaugeUI* m_pDistanceGaugeUI;
	ScoreUI*		 m_pScoreUI;
	int				 m_PlayerHp;
	D3DXVECTOR2		 m_Pos[TARGET_MAX];
	RESULT_SCORE     m_Result;
	RESULT_STATE	 m_ResultState;
	bool			 m_IsGameOver;

};


#endif
