#ifndef CHILD_STRING_H
#define CHILD_STRING_H

#include "BaseString.h"
#include "Array.h"

class ChildString : public Array<BaseString>
{
public:
	void Remove(char cSubSymbol);			// удаление символов в строке

	void Trim(char cSubSymbol = ' ');       // удаление символов по краям строки
	void TrimRight(char cSubSymbol = ' ');  // удаление символов с конца строки

	void DeleteComplexComment();			// удаление многострочного комментария
	void DeleteSingleComment();				// удаление однострочного комментария

	void DeleteEmptyStrings();				// удаление пустых строк

	void Read(char* sFilePath);				// чтение файла

	void Normalize();						// нормализация кода
	void NormalizeEmptyBlocks();			// нормализация строк с ;
	void NormalizeOpeningBrackets();		// нормализация строк с (
	void NormalizeSemicolonStrings();		// нормализация строк с ;

	void SaveHtmlResult(char* sFilePath);	// сохранение результата в HTML файле
};

#endif // #ifndef CHILD_STRING_H
