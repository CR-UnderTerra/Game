#ifndef HTTPCONNECT_H
#define HTTPCONNECT_H
#include <windows.h>
#include <Wininet.h>
#include <string>
#define URLBUFFER_SIZE		(4096)
#define	READBUFFER_SIZE		(4096)

//#pragma comment( lib, "Wininet.lib" )

/**
 * http接続クラス(実装中)
 */
class HttpConnect
{
public:
	enum METHOD
	{
		GET_METHOD,
		POST_METHOD
	};
	HttpConnect();
	~HttpConnect();

	/**
	 * httpに接続してリクエストを返す
	 * @param[in] _method httpメソッド
	 * @param[in] _url アクセスするURL
	 * @param[out] _pResultStr urlのリザルト
	 * @return 成功すればtrue
	 */
	bool Connect(METHOD _method,std::string _url,std::string* _pResultStr);

private:
	HINTERNET			m_hInternetOpen;
	HINTERNET			m_hInternetConnect;
	HINTERNET			m_hInternetRequest;

};


#endif
