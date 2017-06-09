/**
 * @file   JudgeCountWindow.h
 * @brief  JudgeCountWindowクラスのヘッダファイル
 * @author kotani
 */
#ifndef JUDGECOUNTWINDOW_H
#define JUDGECOUNTWINDOW_H
#include "Vertex2D/Vertex2D.h"
#include "CountDisplayBase/CountDisplayBase.h"
#include <array>

class JudgeCountWindow
{
public:
	JudgeCountWindow(int _textureIndex);
	~JudgeCountWindow();

	bool Update();

	void Draw();

private:
	static const float				  m_DisplayTime; //!< 何秒で表示するか
	D3DXVECTOR2						  m_Pos;
	std::array<CountDisplayBase*, 3>  m_pCountDisplayBase;
	float							  m_Alpha;
	float							  m_AddAlphaValue;

};


#endif
