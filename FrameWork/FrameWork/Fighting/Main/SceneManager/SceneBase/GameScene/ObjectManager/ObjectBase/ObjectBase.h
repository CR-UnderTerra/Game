/**
 * @file   ObjectBase.h
 * @brief  ObjectBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECTBASE_H
#define OBJECTBASE_H
#include <memory>
#include "Vertex2D/Vertex2D.h"

/**
 * ゲームのオブジェクトの基底クラス
 */
class ObjectBase
{
public:
	/**
	 * コンストラクタ
	 */
	ObjectBase() = default;

	/**
	 * デストラクタ
	 */
	virtual ~ObjectBase() = default;

	/**
	 * 更新関数
	 */
	virtual void Update() = 0;

	/**
	 * 描画関数
	 */
	virtual void Draw() = 0;

protected:

};


#endif
