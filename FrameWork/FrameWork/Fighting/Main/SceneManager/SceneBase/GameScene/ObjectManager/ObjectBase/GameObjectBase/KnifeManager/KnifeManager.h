/**
 * @file   KnifeManager.h
 * @brief  KnifeManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef KNIFEMANAGER_H
#define KNIFEMANAGER_H
#include <vector>
#include "../GameObjectBase.h"
#include "Animation/AnimUvController.h"
#include "Knife/Knife.h"
#include "Singleton.h"
#include "../../../../GameDataManager/GameDataManager.h"
#include "../../UIBase/DistanceGaugeUI/JudgeGaugeUI/JudgeGaugeUI.h"

class KnifeManager : public GameObjectBase
{
	friend Lib::Singleton<KnifeManager>;
public:
	/**
	 * 初期化処理
	 * @param[in] _textureIndex 使用するテクスチャのインデックス
	 */
	void Init(int _textureIndex);

	/**
	 * ナイフを投げる
	 * @param[in] _pos 何処から飛ばすのかの座標
	 * @param[in] _target 何処に飛ばすのか?
	 * @param[in] _arriveTime 何秒で到達するか
	 */
	void ThrowKnife(D3DXVECTOR2* _pos, GameDataManager::TARGET _target, float _arriveTime);

	/**
	 * 掴まれたナイフを投げる
	 * @param[in] _target 何処に飛ばすのか?
	 * @param[in] _arriveTime 何秒で到達するか
	 */
	void CatchThrowKnife(GameDataManager::TARGET _target, float _arriveTime);

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

	JudgeGaugeUI::JUDGE GetCatchKnifeState();

	static const int		m_KnifeMax; //!< ナイフの最大出現数.
private:
	/**
	 * コンストラクタ
	 */
	KnifeManager() = default;

	/**
	 * デストラクタ
	 */
	~KnifeManager();


	int					    m_TextureIndex;
	std::vector<Knife*>		m_pKnife;
	Lib::AnimUvController*  m_pPlayerKnifeUv[Knife::ANIM_MAX];
	Lib::AnimUvController*  m_pEnemyKnifeUv[Knife::ANIM_MAX];

};


#endif
