/* コピー禁止マクロ */
#define NON_COPYABLE(Class) Class(const Class &); \
                        void operator=(const Class &)
namespace Lib
{

	/**
	 * delete処理
	 */
	template <class Type>
	inline void SafeDelete(Type*& p)
	{
		delete p;
		p = nullptr;
	}

	/**
	 * delete処理(配列版)
	 */
	template <class Type>
	inline void SafeArrayDelete(Type*& p)
	{
		delete[] p;
		p = nullptr;
	}
}