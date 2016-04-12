#ifndef CHILD_STRING_H
#define CHILD_STRING_H

#include "BaseString.h"
#include "Array.h"

class ChildString : public Array<BaseString>
{
public:
	void Remove(char cSubSymbol);			// �������� �������� � ������

	void Trim(char cSubSymbol = ' ');       // �������� �������� �� ����� ������
	void TrimRight(char cSubSymbol = ' ');  // �������� �������� � ����� ������

	void DeleteComplexComment();			// �������� �������������� �����������
	void DeleteSingleComment();				// �������� ������������� �����������

	void DeleteEmptyStrings();				// �������� ������ �����

	void Read(char* sFilePath);				// ������ �����

	void Normalize();						// ������������ ����
	void NormalizeEmptyBlocks();			// ������������ ����� � ;
	void NormalizeOpeningBrackets();		// ������������ ����� � (
	void NormalizeSemicolonStrings();		// ������������ ����� � ;

	void SaveHtmlResult(char* sFilePath);	// ���������� ���������� � HTML �����
};

#endif // #ifndef CHILD_STRING_H
