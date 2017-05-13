#ifndef KNIFEBAR_H
#define KNIFEBAR_H
#include "../../UIBase.h"
#include "Animation/AnimUvController.h"

class KnifeBar : public UIBase
{
public:
	/**
	 * コンストラクタ
	 * @param[in] _TextureIndex 使用するテクスチャのインデックス
	 * @param[in] _GaugeTopPos 上の座標
	 */
	KnifeBar(int m_TextureIndex, D3DXVECTOR2* _GaugeTopPos);

	/**
	 * デストラクタ
	 */
	~KnifeBar();

	/**
	 * 制御関数
	 */
	void Update() override;

	/**
	 * 描画関数
	 */
	void Draw() override;

	/**
	 * ナイフの距離と速度を設定する
	 */
	inline void SetKnifeState(float _distance,float _velocity)
	{
		m_Distance = _distance;
		m_Velocity = _velocity;
		m_AddValue = (500.f / (m_Distance / m_Velocity));
	}

	/**
	 * 有効かの設定
	 * @param[in] _enable 見えるかのフラグ
	 */
	void SetIsEnable(bool _enable);


private:
	static const D3DXVECTOR2 m_Rect;
	Lib::AnimUvController*   m_pAnimUvController;
	Lib::Vertex2D*			 m_pVertex;
	bool					 m_IsEnable;
	int						 m_TextureIndex;
	D3DXVECTOR2				 m_GaugeTopPos;
	D3DXVECTOR2				 m_OffsetPos; //!< 距離ゲージの一番上からどれくらい動くか?.
	float					 m_AddValue;
	float					 m_Distance;
	float					 m_Velocity;

};


#endif
