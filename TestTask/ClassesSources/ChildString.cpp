#include "../ClassesHeaders/ChildString.h"

#include <fstream>
#include <iostream>

using namespace std;

// удаление символов в строке
void ChildString::Remove(char cSubSymbol)
{
	for (int i = 0; i < _arrayLength; ++i)
		_arrayData[i].Remove(cSubSymbol);
}

// удаление символов по кра€м строки
void ChildString::Trim(char cSubSymbol /* =' ' */)
{
	for (int i = 0; i < _arrayLength; ++i)
		_arrayData[i].Trim(cSubSymbol);
}

// удаление символов с конца строки
void ChildString::TrimRight(char cSubSymbol /* =' ' */)
{
	for (int i = 0; i < _arrayLength; ++i)
		_arrayData[i].TrimRight(cSubSymbol);
}

// удаление многострочного комментари€
void ChildString::DeleteComplexComment()
{
	bool isCommentStarted = false;
	int PositionCommentStarted = -1;
	for (int i = 0; i < _arrayLength; ++i)
	{
		if (isCommentStarted)
		{
			int endPosition = _arrayData[i].Find("*/");
			if (endPosition > -1)
			{
				++endPosition; // переход на / со *
				_arrayData[i].Remove(0, endPosition);
				isCommentStarted = false;

				// перенос остатка на предыдущую строку с кодом
				BaseString tempString;
				BaseString::Copy(tempString, _arrayData[PositionCommentStarted]);
				BaseString::Concat(_arrayData[PositionCommentStarted], tempString, _arrayData[i]);
				PositionCommentStarted = -1;
				_arrayData[i].Clear();
			}
			else
				_arrayData[i].Clear();
		}
		else
		{
			int startPosition = _arrayData[i].Find("/*");
			if (startPosition > -1)
			{
				isCommentStarted = true;
				PositionCommentStarted = i;

				BaseString tempString;
				BaseString::Copy(tempString, _arrayData[i]);

				int endPosition = _arrayData[i].Find("*/");
				if (endPosition > -1)
				{
					++endPosition; // переход на / со *
					_arrayData[i].Remove(startPosition, endPosition);
					isCommentStarted = false;
					PositionCommentStarted = -1;
				}
				else
					_arrayData[i].Remove(startPosition, _arrayData[i]._stringLength - 1);
			}
		}
	}
}

// удаление однострочного комментари€
void ChildString::DeleteSingleComment()
{
	for (int i = 0; i < _arrayLength; ++i)
		_arrayData[i].DeleteSingleComment();
}

// удаление пустых строк
void ChildString::DeleteEmptyStrings()
{
	int j = 0;
	cout << "\nStart removing empty strings...\n\n";
	for (int i = _arrayLength - 1; i>-1; --i)
	{
		if ((_arrayData[i]._stringLength == 0) || ((_arrayData[i]._stringLength == 1) && (_arrayData[i]._stringArray[0] == ';')))
		{
			Delete(i);
			++j;
		}
	}
	
}

// нормализаци€ кода
void ChildString::Normalize()
{
	cout << "\nStart normalizing...\n";
	NormalizeEmptyBlocks();      // нормализаци€ строк с ;
	NormalizeOpeningBrackets();  // нормализаци€ строк с (
	NormalizeSemicolonStrings(); // нормализаци€ строк с ;
}

// нормализаци€ строк с ;
void ChildString::NormalizeEmptyBlocks()
{
	for (int i = 0; i < _arrayLength; ++i)
	{
		_arrayData[i].Replace(" ;", ";", true);
		_arrayData[i].Replace("\t;", ";", true);
		_arrayData[i].Replace(";;", ";", true);
	}
}

// нормализаци€ строк с (
void ChildString::NormalizeOpeningBrackets()
{
	for (int i = 0; i < _arrayLength; ++i)
		_arrayData[i].Replace(" (", "(", true);
}

// нормализаци€ строк с ;
void ChildString::NormalizeSemicolonStrings()
{
	int j = 0;
	for (int i = 0; i < _arrayLength; ++i)
	{
		int searchPositionition = 0;
		_arrayData[i].Trim(' ');
		_arrayData[i].Trim('\t');
		int forPosition = _arrayData[i].Find("for(");
		if (forPosition == 0)
			searchPositionition = _arrayData[i].FindCloseBracket(forPosition + 3);
		if (searchPositionition > -1)
		{
			int semicolonPosition = _arrayData[i].Find(";", searchPositionition);
			if (semicolonPosition > -1)
			{
				++semicolonPosition;
				Insert(i + 1);
				++j;
				BaseString::Copy(_arrayData[i + 1], _arrayData[i], semicolonPosition, _arrayData[i]._stringLength - 1);
				_arrayData[i].Remove(semicolonPosition, _arrayData[i]._stringLength - 1);
				
			}
		}
	}
	
}

// чтение файла
void ChildString::Read(char* sFilePath)
{
	Clear();

	fstream f;
	f.open(sFilePath, ios_base::in);

	char oneString[1024];
	int i = 0;
	cout << "Start reading...\n";
	for (; !f.eof(); ++i)
	{
		Add();
		f.getline(oneString, 1024, '\n');
		_arrayData[i] = oneString;
	}
	
	f.close();
}

// сохранение результата в HTML файле
void ChildString::SaveHtmlResult(char* sFilePath)
{
	fstream f;
	f.open(sFilePath, ios_base::out);

	f << "<html>\r\n";
	f << "<head>\r\n";
	f << "</head>\r\n";
	f << "<body>\r\n";

	char tempStr[1024];
	sprintf_s(tempStr, 1024, "<h1>Source code file contains %d of LLoC</h1>\r\n", _arrayLength);
	f << tempStr;

	f << "</body>\r\n";
	f << "</html>\r\n";

	f.close();

	//cout << "\nTotal strings count: " << _arrayLength << endl;
	cout << "Lloc was found" << endl;
	cout << "\nReport about LLOC you can see on path: " << sFilePath << endl;
}
