/**
 * @file   Knife.h
 * @brief  Knifeクラスのヘッダファイル
 * @author kotani
 */
#ifndef KNIFE_H
#define KNIFE_H
#include "../../GameObjectBase.h"
#include "Animation/AnimUvController.h"
#include "Vertex2D/Vertex2D.h"
#include "../../../../../CollisionManager/CollisionData/CollisionData.h"

class Knife : public GameObjectBase
{
public:
	enum TARGET
	{
		LEFT_ENEMY,
		FRONT_ENEMY,
		RIGHT_ENEMY,
		PLAYER
	};
	
	/**
	 * コンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス
	 * @param[in] _pUvController 使用するUvのコントローラ
	 */
	Knife(int _textureIndex, Lib::AnimUvController* _pUvController);

	/**
	 * デストラクタ
	 */
	~Knife();

	/**
	 * ナイフを投げる
	 * @param[in] _pos 何処から飛ばすのかの座標
	 * @param[in] _target 何処に飛ばすのか?
	 * @param[in] _velocity 飛ばす速度
	 */
	void Throw(D3DXVECTOR2* _pos, TARGET _target, float _velocity);

	/**
	 * ナイフを投げる
	 * @param[in] _target 何処に飛ばすのか?
	 * @param[in] _velocity 飛ばす速度
	 */
	void Throw(TARGET _target, float _velocity);

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

	inline bool GetIsThrow()
	{
		return m_IsThrow;
	}

	inline bool GetIsCatch()
	{
		return m_IsCatch;
	}

private:
	static const D3DXVECTOR2	   m_Rect;
	static int					   m_IndexMax;			
	int							   m_Index;
	CollisionData*				   m_pCollisionData;	 //!< 何番のインデックスにセットされているか
	Lib::Vertex2D*				   m_pVertex;			 
	Lib::AnimUvController*		   m_pUvController;		 
	CollisionData::HIT_STATE	   m_OldHitState;		 
	D3DXVECTOR2					   m_Pos;				 
	bool						   m_IsThrow;			 //!< 投げられたか?(存在しているか？)
	bool						   m_IsCatch;			 //!< キャッチされたか？
	TARGET						   m_Target;			 //!< 狙う先
	float						   m_TargetDistance;	 //!< ターゲットまでの距離
	float						   m_ScaleAddValue;		 //!< スケールの増加量
	int							   m_ArriveFrame;		 //!< 何フレームで到達するか?
	float						   m_Velocity;			 //!< 速度
	float						   m_Angle;				 //!< 角度
	float						   m_Scale;				 //!< 拡縮率 1が最大
	float						   m_RectCollisionRatio; //!< 当たり判定の割合
	int							   m_TextureIndex;		 //!< テクスチャのインデックス

};


#endif
