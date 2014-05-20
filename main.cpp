#include <iostream>
#include <fstream>

using namespace std;

int main(int argv, char** argc)
{
	setlocale(LC_ALL, "rus");
	ifstream inFile;
	ofstream outFile;
	char key[256], menu, bufferChar;
	if(argv > 1)
		inFile.open(argc[1], ios_base::in);
	else
	{
		char nameFile[256];
		cout<<"Введите имя входного файла: ";
		cin>>nameFile;
		inFile.open(nameFile, ios_base::in);
	}
	if(!inFile)
	{
		cout<<"\nНе удалось входной открыть файл.";
		return 1;
	}
	if(argv > 2)
		outFile.open(argc[2], ios_base::out);
	else
	{
		char nameFile[256];
		cout<<"\nВведите имя выходного файла: ";
		cin>>nameFile;
		outFile.open(nameFile, ios_base::out);
	}
	if(!outFile)
	{
		cout<<"\nНе удалось открыть выходной файл.";
		return 2;
	}
	cout<<"\nВыберите соответствующий пункт меню:\n1-шифрование файла\n2-расшифровка файла\n";
	do 
	{
		cin>>menu;
	} while (menu != '1' && menu != '2');
	if(menu == '1')
	{
		if(argv > 3)
			strcpy_s(key, argc[3]);
		else
		{
			cout<<"\nВведите ключевое слово: ";
			cin>>key;
		}
		int i = 0;
		while(key[i] != '\0')
			i++;
		outFile<<char(i);
		for(i = 0; key[i] != '\0'; i++)
			outFile<<char(key[i] + i);
		i = 0;
		inFile.get(bufferChar);
		while (!inFile.eof())
		{
			bufferChar += key[i];
			outFile<<bufferChar;
			inFile.get(bufferChar);
			i++;
			if(key[i] == '\0')
				i = 0;
		}
	}
	else
	{
		inFile.get(bufferChar);
		int key_long = bufferChar;
		int i;
		for(i = 0; i < key_long; i++)
		{
			inFile.get(bufferChar);
			key[i] = bufferChar - i;
		}
		key[i] = '\0';
		i = 0;
		inFile.get(bufferChar);
		while (!inFile.eof())
		{
			bufferChar -= key[i];
			outFile<<bufferChar;
			inFile.get(bufferChar);
			i++;
			if(key[i] == '\0')
				i = 0;
		}

	}
	inFile.close();
	outFile.close();
	return 0;
}
