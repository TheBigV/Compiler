#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

#include <Windows.h>
#include <WinBase.h>

#include "Compiler.h"

void main()
{
	auto source = ([]
	{
		auto file = ifstream("Source.e");

		string result;
		getline(file, result, '\0');

		file.close();

		return result;
	})();

	auto code = LangE::Compile(source);

	cout << internal << uppercase << setfill('0'); //showbase

	int j = 0, k = 0;
	for(auto i : code)
	{
		cout << hex << setw(2) << int(i) << ' ';
		++j; if(j > 3) { j = 0; cout << '\t'; ++k; if(k > 3) { k = 0; cout << endl; } }
	}

	auto funcSource = (LangE::uint8*)VirtualAlloc(NULL,code.size(),MEM_COMMIT,PAGE_EXECUTE_READWRITE);

	for(size_t i = 0; i < code.size(); ++i) funcSource[i] = code[i];

	auto func = (void(*)())funcSource;

	func();

	cout << endl;
	system("pause");
}


