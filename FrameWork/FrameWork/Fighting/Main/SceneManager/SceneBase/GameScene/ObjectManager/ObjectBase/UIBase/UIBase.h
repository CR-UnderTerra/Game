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
	UIBase() = default;

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

};


#endif
