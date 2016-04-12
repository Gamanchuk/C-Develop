#ifndef BASE_STRING_H
#define BASE_STRING_H

class BaseString
{
	friend class ChildString;

private:
	char* _stringArray;  // ��������� ������
	int   _stringLength; // ����� ������ ��� '\0'

public:
	BaseString();
	BaseString(const BaseString& sString);
	BaseString(const char* sString);
	~BaseString();

public:
	int GetLength();															// ��������� ����� ������

	int Find(char* sFindString, int iStartPositionition = 0);						// ����� ��������� � ������
	void Replace(char* sOldString, char* sNewString, bool bRecurcive = false);	// ������ �������� � ������
	void Remove(char cSubSymbol);												// �������� �������� � ������
	void Remove(int iStartPositionition, int iEndPositionition);							// �������� �������� � ������

	void Trim(char cSubSymbol = ' ');											// �������� �������� �� ����� ������
	void TrimRight(char cSubSymbol = ' ');										// �������� �������� � ����� ������

	int FindCloseBracket(int iOpenBracketPositionition);								// ����� ����������� ������
	void DeleteSingleComment();													// �������� ������������� �����������

	void Clear();

public:
	BaseString& operator =(const BaseString& sString);
	BaseString& operator =(const char* sString);

	operator char*();															// ������������� �������� ������������ � ���� char*

public:
	static bool Copy(BaseString& sResultString, const BaseString& sString);
	static bool Copy(BaseString& sResultString, const char* sString);
	static bool Copy(BaseString& sResultString, const char* sString, const int& iStartPositionition, const int& iEndPositionition);

	static bool Concat(BaseString& sResultString, const BaseString& sString1, const BaseString& sString2);
};

#endif // #ifndef BASE_STRING_H
