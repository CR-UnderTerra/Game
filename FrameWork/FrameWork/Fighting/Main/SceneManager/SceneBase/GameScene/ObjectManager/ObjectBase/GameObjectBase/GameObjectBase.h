/**
 * @file   GameObjectBase.h
 * @brief  GameObjectBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "../ObjectBase.h"

class GameObjectBase : public ObjectBase
{
public:
	/**
	 * コンストラクタ
	 */
	GameObjectBase() = default;

	/**
	 * デストラクタ
	 */
	virtual ~GameObjectBase() = default;

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
