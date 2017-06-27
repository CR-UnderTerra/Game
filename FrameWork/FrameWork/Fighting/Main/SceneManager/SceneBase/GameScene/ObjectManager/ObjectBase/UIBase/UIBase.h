/**
 * @file   UIBase.h
 * @brief  UIBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef UIBASE_H
#define UIBASE_H
#include "../ObjectBase.h"

class UIBase : public ObjectBase
{
public:
	/**
	 * コンストラクタ
	 */
	UIBase();
		

	/**
	 * デストラクタ
	 */
	virtual ~UIBase() = default;

	/**
	 * 制御関数
	 */
	virtual void Update() override = 0;

	/**
	 * 描画関数
	 */
	virtual void Draw() override = 0;

protected:
	void Vibration();

	float m_HeightVibValue;
	float m_WidthVibValue;

private:
	float m_VibRadius;
	float m_HeightVibAngle;
	float m_WidthVibAngle;
	float m_HeightTime;
	float m_WidthTime;

};


#endif
