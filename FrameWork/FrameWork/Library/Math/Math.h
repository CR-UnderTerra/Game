/**
 * @file   Math.h
 * @author kotani
 */
#include <D3DX10.h>
#include <math.h>

#define MyLib_PI 3.14159265358979323846f

namespace Lib
{
	/**
	 * 計算系ライブラリ
	 */
	namespace Math
	{
		/**
		 * 2点間の距離を求める(2次元座標)
		 * @param[in] _pos1 1つ目の座標
		 * @param[in] _pos2 2つ目の座標
		 * @return 距離
		 */
		float GetDistance(const D3DXVECTOR2& _pos1, const D3DXVECTOR2& _pos2);

		/**
		 * 2点間の距離を求める(3次元座標)
		 * @param[in] _pos1 1つ目の座標
		 * @param[in] _pos2 2つ目の座標
		 * @return 距離
		 */
		float GetDistance(const D3DXVECTOR3& _pos1, const D3DXVECTOR3& _pos2);

		/**
		 * 2点間の角度を求める
		 * @param[in] _pos1 1つ目の座標
		 * @param[in] _pos2 2つ目の座標
		 * @return 角度
		 */
		float GetAngle(const D3DXVECTOR2& _pos1, const D3DXVECTOR2& _pos2);

		inline float ToDegree(float _radian)
		{
			return _radian * (180.0f / MyLib_PI);
		}

		inline float ToRadian(float _degree)
		{
			return _degree * (MyLib_PI / 180.0f);
		}

		/**
		 * 設定した角度の距離分の移動量を求める
		 * @param[in] _movement 移動量
		 * @param[in] _angle 角度
		 * @return 移動量
		 */
		D3DXVECTOR2 GetAngleMovePos(float _movement, float _angle);

	}
}