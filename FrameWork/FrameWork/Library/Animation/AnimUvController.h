/**
 * @file   AnimUvController.h
 * @brief  AnimUvControllerクラスのヘッダファイル
 * @author kotani
 */
#ifndef TEXTUREANIM_H
#define TEXTUREANIM_H
#include <Windows.h>
#include <D3DX10.h>

namespace Lib
{
	class AnimFileParser;

	enum ANIM_OPERATION
	{
		ANIM_LOOP,   //!< アニメーションをループする。
		ANIM_NORMAL  //!< 再生が終わると停止する 
	};

	// TODO 下に続いているアニメーションも対応したい
	/**
	 * 1つのテクスチャアニメーションを管理するクラス(実装途中)
	 *
	 * ファイルの構造
	 * TextureSize // テクスチャのサイズ (名前固定)
	 * {
	 *		1, // テクスチャの横幅
	 *      2  // テクスチャの横幅
	 * }
	 *
	 * Test //アニメーションの名前
	 * {
	 *		1, // 左上のテクスチャX座標
	 *		2, // 左上のテクスチャY座標
	 *      3, // テクスチャの横幅
	 *      4, // テクスチャの立幅
	 *      5  // アニメーションの数
	 * }
	 */
	class AnimUvController
	{
	public:
		AnimUvController();
		~AnimUvController();
		
		/**
		 * アニメーションファイルの読み込み
		 * @param[in] _pFileName ファイルの名前
		 * @param[in] _pAnimName アニメーションの名前
		 * @return 成功したらtrue
		 */
		bool LoadAnimation(LPCTSTR _pFileName, LPCTSTR _pAnimName);

		/**
		 * 何フレーム目でアニメーションを進めるか設定する
		 * @param[in] _scrollFrame アニメーションを進めるフレーム数
		 */
		inline void SetAnimFrame(int _scrollFrame)
		{
			m_ScrollFrame = _scrollFrame;
		}

		/**
		 * アニメーションをリセットする
		 */
		void ResetAnim();

		/**
		 * テクスチャのスクロール値を取得する
		 */
		inline D3DXVECTOR2 GetScrollUV() const
		{
			return D3DXVECTOR2(m_ScrollUV.x * m_AnimCount, 0);
		}

		/**
		 * UVの値を取得する
		 */
		inline D3DXVECTOR2* GetUV()
		{
			return m_NowUV;
		}

		/**
		 * アニメーションの数を取得する
		 */
		inline int GetAnimNum() const
		{
			return m_AnimData.AnimNum;
		}

		/**
		 * 現在のアニメーション番号を取得する
		 */
		inline int GetAnimCount() const
		{
			return m_AnimCount;
		}

		/**
		 * アニメーションのカウントを指定する
		 * 最大数より大きい場合最大数が設定される
		 */
		void SetAnimCount(int _animCount);

		/**
		 * アニメーション制御
		 * @param[in] _isReverse 逆再生するか？
		 * @param[in] _playOperation 再生設定
		 * @return アニメーションが最後ならtrue
		 */
		bool Control(bool _isReverse, ANIM_OPERATION _playOperation);

	private:
		struct Anim
		{
			float LeftUpX;
			float LeftUpY;
			float Width;
			float Height;
			int	  AnimNum;
		};

		/**
		 * アニメーションの再生処理
		 * @param[in] 再生設定
		 */
		bool NormalControl(ANIM_OPERATION _playOperation);

		/**
		 * アニメーションの逆再生処理
		 * @param[in] 再生設定
		 */
		bool ReverseControl(ANIM_OPERATION _playOperation);

		AnimFileParser* m_pAnimFileParser;
		Anim			m_AnimData;
		D3DXVECTOR2		m_TextureSize;
		D3DXVECTOR2		m_ScrollUV;
		D3DXVECTOR2		m_UV[4];
		D3DXVECTOR2		m_NowUV[4];
		int				m_AnimCount;
		int				m_ScrollFrame;
		int				m_Count;

	};

}


#endif
