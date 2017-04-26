/**
 * @file   AnimFileParser.h
 * @brief  AnimFileParserクラスのヘッダファイル
 * @author kotani
 */
#ifndef ANIMFILEPARSER_H
#define ANIMFILEPARSER_H
#include <Windows.h>
#include <vector>
#include <string>

namespace Lib
{
	class AnimFileParser
	{
	public:
		AnimFileParser(){};
		~AnimFileParser();

		/**
		 * ファイル読み込み
		 * @param[in] _pFileName 読み込むセーブデータのファイルパス
		 */
		void FileLoad(LPCTSTR _pFileName);

		/**
		 * グループ名を指定してその中からデータを読み込む
		 * @param[in] _pGroupName 読み込みたいデータの名前
		 * @param[out] _pData 読み込みたいデータ
		 * @return グループが存在すればtrue無ければfalse
		 */
		bool ReadData(LPCTSTR _pGroupName, std::vector<float>* _pData);

	private:

		/**
		 * 読み込みバッファの開放
		 */
		void ReleaseLoadBuffer();

		FILE*		m_pFile;
		std::string m_StrBuffer;//!<書き込み用バッファ
		TCHAR*		m_pBuffer; //!<読み込んだ時の文字列が入っている
		TCHAR*		m_pTmpBuffer;//!<一時保存用バッファ
		long		m_FileSize;

	};
}


#endif
