#include "../ClassesHeaders/BaseString.h"

#include <string.h>

BaseString::BaseString()
{
	_stringArray = 0; // ��������� ������
	_stringLength = 0; // ����� ������ ��� '\0'
}

BaseString::BaseString(const BaseString& sString)
{
	_stringArray = 0; // ��������� ������
	_stringLength = 0; // ����� ������ ��� '\0'

	BaseString::Copy(*this, sString);
}

BaseString::BaseString(const char* sString)
{
	_stringArray = 0; // ��������� ������
	_stringLength = 0; // ����� ������ ��� '\0'

	BaseString::Copy(*this, sString);
}

BaseString::~BaseString()
{
	Clear();
}

// ��������� ����� ������
int BaseString::GetLength()
{
	return _stringLength;
}

// ����� ��������� � ������
int BaseString::Find(char* sFindString, int iStartPositionition /* =0 */)
{
	if ((!_stringArray) || (!sFindString) || (iStartPositionition >= _stringLength))
		return -1;

	if (iStartPositionition  <0)
		iStartPositionition = 0;

	char* searchString = strstr(_stringArray + iStartPositionition, sFindString); // ����� ����������
	if (!searchString) // ����� ���������� ���������� ���� ���� ���� ���������� ���
		return -1;

	return (int)searchString - (int)_stringArray;
}

// ������ �������� � ������
void BaseString::Replace(char* sOldString, char* sNewString, bool bRecurcive /* = false */)
{
	BaseString resultString;
	if (!_stringArray)
		return;

	BaseString::Copy(resultString, *this);

	int oldStringLength = static_cast<int>(strlen(sOldString)); // ����� ���������� ������ ������
	int newStringLength = static_cast<int>(strlen(sNewString)); // ����� ���������� ����� ������
	int searchPositionition = 0; // �������, � ������� ���������� ����� ����������
	while (true)
	{
		char* searchString = strstr(resultString._stringArray + searchPositionition, sOldString); // ����� ����������
		if (!searchString) // ����� ���������� ���������� ���� ���� ���� ���������� ���
			break;

		char* tempStr = new char[resultString._stringLength - oldStringLength + newStringLength + 1];
		int startPositionition = static_cast<int>(searchString - resultString._stringArray); // ��������� �������
		int endPositionition = startPositionition + oldStringLength - 1; // �������� �������
		int k = 0;
		for (int i = 0; i<resultString._stringLength; ++i)
		{
			if ((i < startPositionition) || (i > endPositionition))
			{
				tempStr[k] = resultString._stringArray[i];
				++k;
			}
			if (i == endPositionition)
			{ // ��� ������ ���� �������� ������ �������
				for (int l = 0; l<newStringLength; ++l)
				{
					tempStr[k] = sNewString[l];
					++k;
				}
				if (!bRecurcive)
					searchPositionition = k;
			}
		}
		tempStr[k] = '\0';
		resultString = tempStr;
		delete[] tempStr;
	}
	BaseString::Copy(*this, resultString);
}

// �������� �������� � ������
void BaseString::Remove(char cSubSymbol)
{
	BaseString resultString = "";
	if (_stringArray)
	{
		char* tempStr = new char[_stringLength + 1];
		int j = -1;
		for (int i = 0; i < _stringLength; ++i)
		{
			if (_stringArray[i] != cSubSymbol)
				tempStr[++j] = _stringArray[i];
		}
		tempStr[j + 1] = '\0';
		resultString = tempStr;
		delete[] tempStr;
	}
	else
		resultString = "";

	BaseString::Copy(*this, resultString);
}

// �������� �������� � ������
void BaseString::Remove(int iStartPositionition, int iEndPositionition)
{
	if ((_stringArray) && (iEndPositionition >= iStartPositionition))
	{
		char* tempStr = new char[_stringLength - (iEndPositionition - iStartPositionition + 1) + 1];

		int i = 0;
		for (; i < iStartPositionition; ++i)
			tempStr[i] = _stringArray[i];

		for (int j = iEndPositionition + 1; j<_stringLength; ++i, ++j)
			tempStr[i] = _stringArray[j];
		tempStr[i] = '\0';

		BaseString::Copy(*this, tempStr);

		delete[] tempStr;
	}
}

// �������� �������� �� ����� ������
void BaseString::Trim(char cSubSymbol /* =' ' */)
{
	if (!_stringArray)
		return;

	BaseString resultString = _stringArray;

	// ��������� ������� ������� ������� �����, ��������� �� �����������
	int startPosition = 0;
	bool isSubSymbol = false;
	for (int i = startPosition; i < _stringLength; ++i)
	{
		if (_stringArray[i] != cSubSymbol)
		{
			startPosition = i;
			break;
		}
		isSubSymbol = true;
	}

	// ���� ������ ������� ������ �� ���������� ��������
	if ((isSubSymbol) && (startPosition == 0))
	{
		Clear();
		return;
	}

	// ��������� ������� ������� ������� ������, ��������� �� �����������
	int endPosition = resultString._stringLength - 1;
	for (int i = endPosition; i >= 0; --i)
	{
		if (resultString._stringArray[i] != cSubSymbol)
		{
			endPosition = i;
			break;
		}
	}

	// ����������� ������ ����� ����������� �����������
	BaseString::Copy(*this, resultString._stringArray, startPosition, endPosition);
}

// �������� �������� � ����� ������
void BaseString::TrimRight(char cSubSymbol /* =' ' */)
{
	if (!_stringArray)
		return;

	BaseString resultString = _stringArray;

	// ��������� ������� ������� ������� ������, ��������� �� �����������
	int endPosition = resultString._stringLength - 1;
	for (int i = endPosition; i >= 0; --i)
	{
		if (resultString._stringArray[i] != cSubSymbol)
		{
			endPosition = i;
			break;
		}
	}

	// ����������� ������ ����� ����������� �����������
	BaseString::Copy(*this, resultString._stringArray, 0, endPosition);
}

// ����� ����������� ������
int BaseString::FindCloseBracket(int iOpenBracketPositionition)
{
	if (_stringArray[iOpenBracketPositionition] != '(')
		return -1;

	int bracketsCount = 1;
	for (int i = iOpenBracketPositionition + 1; i<_stringLength; ++i)
	{
		if (_stringArray[i] == '(')
			++bracketsCount;
		else if (_stringArray[i] == ')')
			--bracketsCount;

		if (bracketsCount == 0)
			return i;
	}

	return -1;
}

// �������� ������������� �����������
void BaseString::DeleteSingleComment()
{
	BaseString resultString;
	if (!_stringArray)
		return;

	BaseString::Copy(resultString, *this);

	int endPositionition = Find("//"); // ��������� ������� �����������
	if (endPositionition > -1)
		BaseString::Copy(*this, resultString, 0, endPositionition - 1);
}

void BaseString::Clear()
{
	if (_stringArray)
		delete[] _stringArray;

	_stringArray = 0; // ��������� ������
	_stringLength = 0; // ����� ������ ��� '\0'
}

BaseString& BaseString::operator =(const BaseString& sString)
{
	BaseString::Copy(*this, sString);

	return *this;
}

BaseString& BaseString::operator =(const char* sString)
{
	BaseString::Copy(*this, sString);

	return *this;
}

// ������������� �������� ������������ � ���� char*
BaseString::operator char*()
{
	if (_stringLength>0)
		return _stringArray;
	else
		return "\0";
}

bool BaseString::Copy(BaseString& sResultString, const BaseString& sString)
{
	if (&sResultString == &sString)
		return true;

	sResultString.Clear();

	if (sString._stringLength == 0)
		return true;

	sResultString._stringArray = new char[sString._stringLength + 1];
	if (!sResultString._stringArray)
		return false;

	for (int i = 0; i <= sString._stringLength; ++i)
		sResultString._stringArray[i] = sString._stringArray[i];
	sResultString._stringLength = sString._stringLength;

	return true;
}

bool BaseString::Copy(BaseString& sResultString, const char* sString)
{
	int stringLength = strlen(sString);

	sResultString.Clear();

	if ((stringLength == 0) || (!sString))
		return true;

	sResultString._stringArray = new char[stringLength + 1];
	if (!sResultString._stringArray)
		return false;

	for (int i = 0; i <= stringLength; ++i)
		sResultString._stringArray[i] = sString[i];
	sResultString._stringLength = stringLength;

	return true;
}

bool BaseString::Copy(BaseString& sResultString, const char* sString, const int& iStartPositionition, const int& iEndPositionition)
{
	sResultString.Clear();

	int stringLength = iEndPositionition - iStartPositionition + 1;
	if (stringLength <= 0)
		return true;

	sResultString._stringArray = new char[stringLength + 1];
	if (!sResultString._stringArray)
		return false;

	int i = 0;
	for (; i < stringLength; ++i)
		sResultString._stringArray[i] = sString[i + iStartPositionition];
	sResultString._stringArray[i] = '\0';
	sResultString._stringLength = stringLength;

	return true;
}

bool BaseString::Concat(BaseString& sResultString, const BaseString& sString1, const BaseString& sString2)
{
	sResultString.Clear();

	int stringLength = sString1._stringLength + sString2._stringLength;
	if (stringLength == 0)
		return true;

	sResultString._stringArray = new char[stringLength + 1];
	if (!sResultString._stringArray)
		return false;
	sResultString._stringLength = stringLength;

	strcpy_s(sResultString._stringArray, sResultString._stringLength + 1, sString1._stringArray);
	strcat_s(sResultString._stringArray, sResultString._stringLength + 1, sString2._stringArray);

	return true;
}
