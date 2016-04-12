#ifndef BASE_STRING_H
#define BASE_STRING_H

class BaseString
{
	friend class ChildString;

private:
	char* _stringArray;  // строковый массив
	int   _stringLength; // длина строки без '\0'

public:
	BaseString();
	BaseString(const BaseString& sString);
	BaseString(const char* sString);
	~BaseString();

public:
	int GetLength();															// получение длины строки

	int Find(char* sFindString, int iStartPositionition = 0);						// поиск подстроки в строке
	void Replace(char* sOldString, char* sNewString, bool bRecurcive = false);	// замена подстрок в строке
	void Remove(char cSubSymbol);												// удаление символов в строке
	void Remove(int iStartPositionition, int iEndPositionition);							// удаление символов в строке

	void Trim(char cSubSymbol = ' ');											// удаление символов по краям строки
	void TrimRight(char cSubSymbol = ' ');										// удаление символов с конца строки

	int FindCloseBracket(int iOpenBracketPositionition);								// поиск закрывающей скобки
	void DeleteSingleComment();													// удаление однострочного комментария

	void Clear();

public:
	BaseString& operator =(const BaseString& sString);
	BaseString& operator =(const char* sString);

	operator char*();															// перегруженный оператор присваивания к типу char*

public:
	static bool Copy(BaseString& sResultString, const BaseString& sString);
	static bool Copy(BaseString& sResultString, const char* sString);
	static bool Copy(BaseString& sResultString, const char* sString, const int& iStartPositionition, const int& iEndPositionition);

	static bool Concat(BaseString& sResultString, const BaseString& sString1, const BaseString& sString2);
};

#endif // #ifndef BASE_STRING_H
