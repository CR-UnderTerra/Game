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
	 * @param[in] _velocity 飛ばす速度
	 */
	void ThrowKnife(D3DXVECTOR2* _pos, Knife::TARGET _target, float _velocity);

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

	/**
	 * キャッチされたナイフのポインタを返す
	 * @return キャッチしたナイフ
	 */
	Knife* const GetCatchKnife();

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
	Lib::AnimUvController*  m_pAnimUvController;

};


#endif
