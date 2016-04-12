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
		// ������������� ����������
		ChildString fileContent;

		// ������ �����
		fileContent.Read(argv[1]);

		fileContent.Remove('\r');                  // ���������� �� \r
		fileContent.Remove('{');                   // ���������� �� �������� ������
		fileContent.Remove('}');                   // ���������� �� �������� ������
		fileContent.TrimRight('\\');               // ���������� �� ������ � ����� �����
		fileContent.DeleteComplexComment();        // ���������� �� ������������� ������������
		fileContent.DeleteSingleComment();         // ���������� �� ������������ ������������
		fileContent.Normalize();                   // ������������ ����
		fileContent.DeleteEmptyStrings();          // �������� ������ �����
		fileContent.SaveHtmlResult("result.html"); // ���������� ���������� � HTML �����

		cout << "Press any key to destroy this window..." << endl;

		result = 0;
	}
	_getch();
	return result;
}
