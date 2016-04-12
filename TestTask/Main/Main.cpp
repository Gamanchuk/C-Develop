#include <iostream>
#include <conio.h>

#include "../ClassesHeaders/ChildString.h"

using namespace std;

int main(int argc, char** argv)
{
	int result = 2;
	if (argc<2)
	{
		cout << "Doesn't receive path to file with source code." << endl;
		result = 1;
	}
	else
	{
		// инициализация переменных
		ChildString fileContent;

		// чтение файла
		fileContent.Read(argv[1]);

		fileContent.Remove('\r');                  // избавление от \r
		fileContent.Remove('{');                   // избавление от фигурных скобок
		fileContent.Remove('}');                   // избавление от фигурных скобок
		fileContent.TrimRight('\\');               // избавление от слэшей в конце строк
		fileContent.DeleteComplexComment();        // избавление от многострочных комментариев
		fileContent.DeleteSingleComment();         // избавление от однострочных комментариев
		fileContent.Normalize();                   // нормализация кода
		fileContent.DeleteEmptyStrings();          // удаление пустых строк
		fileContent.SaveHtmlResult("result.html"); // сохранение результата в HTML файле

		cout << "Press any key to destroy this window..." << endl;

		result = 0;
	}
	_getch();
	return result;
}
