#include<iostream>
#include<string>
#include"List.h"
#include <cstdlib>
#include <ctime>
#include<vector>
#include<fstream>
#include<cctype>


using namespace std;
//Написать односвязный список (ключ,значение, указатель)
//Написать хэш-функцию
// 
// генерация данных
// удаление, добавление
// 
//Впихнуть в эксель


//----------------------------------------------------------------
//Выдает хеш по ключу, который является строкой
int hash_in(string key, const int size) {
	int num = 0;
	for (int i = 0; i < key.length(); i++) {
		num = (num * 51 + static_cast<int>(key[i])) % size;
	}
	return num;
}
//----------------------------------------------------------------


//----------------------------------------------------------------
// Генерирует ключ-строку
string generateKey() {
	string key = "";
	string digits = "0123456789";
	string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";



	for (int i = 0; i < 2; i++) {
		key += digits[rand() % 10]; 
	}

	for (int i = 0; i < 2; i++) {
		key += letters[rand() % 26];
	}

	for (int i = 0; i < 2; i++) {
		key += digits[rand() % 10]; 
	}

	return key;
}
//----------------------------------------------------------------


//----------------------------------------------------------------
//Генерирует рандомное число, аля data
int generateNum() {
	return rand() % 100;
}
//----------------------------------------------------------------


//----------------------------------------------------------------
// выполняет полный поиск по ключу
int search_hash(vector<List<int, string>> &arr, int size, string key) {
	int num = hash_in(key, size);
	if (arr[num].getSize() == 0) {
		return 0;
	}
	else {
		return arr[num].search(key);
	}
}
//----------------------------------------------------------------


//----------------------------------------------------------------
//заполняет массив
void push_hash(vector<List<int, string>>& arr, const int size, string key) {
	int num = hash_in(key,size);
	arr[num].push_back(generateNum(), key);
}
//----------------------------------------------------------------

void push_hash_user(vector<List<int, string>>& arr, const int size, string key, const int data) {
	int num = hash_in(key, size);
	arr[num].push_back(data, key);
}


//---------------------------------------------------------------


//----------------------------------------------------------------
//проверка ключа на формат
bool checkKey_format(const string& key) {
	if (key.length() != 6) {
		return false;
	}

	if (!isdigit(key[0]) || !isdigit(key[1])) {
		return false;
	}

	if (!isupper(key[2]) || !isupper(key[3])) {
		return false;
	}

	if (!isdigit(key[4]) || !isdigit(key[5])) {
		return false;
	}

	return true;
}
//----------------------------------------------------------------


int main() {
	setlocale(LC_ALL, "RUS");


	int p = 0;
	cout << "Выберите режим" << endl;
	cout << "1 - автоматическая генерация" << endl;
	cout << "2 - ручная генерация" << endl;
	cout << ">>>>";
	cin >> p;
	if (p == 2) {
		int size;
		while (true)
		{
			cout << "введите размер хеш-таблицы" << endl;
			cin >> size;
			if (size <= 0) {
				cout << "размер таблицы не может быть больше или равен 0" << endl;
				continue;
			}
			else {
				vector<List<int, string>> arr(size);
				vector<string> arr_key(size);
				for (int i = 0; i < size; i++) {
					string key;
					int data;
					cout << "Введите ключ формат:ццББцц >>";
					cin >> key;
					if (!checkKey_format(key)) {
						i--;
						cout << "Неверный формат ключа" << endl;
						continue;
					}
					cout << "Введите данный формат:int >>";
					cin >> data;
					arr_key[i] = key;
					push_hash_user(arr, size, key, data);
				}
				while (true)
				{
					cout << "Таблица заполнена! Выберите действие" << endl;
					cout << "1 - вывести таблицу " << endl << "2 - Выгрузить в exel" << endl;
					cout << "3 - удалить элемент из таблицы" << endl << "4 - найти элемент по ключу" << endl;
					cout << "5 - вернуться назад" << endl;
					cout << ">>>>";
					int p2;
					cin >> p2;
					if (p2 == 1) {
						for (int i = 0; i < arr.size(); i++) {
							cout << i;
							arr[i].print();
							cout << endl;
						}
					}
					else if (p2 == 2) {
						ofstream outFile("data.csv");

						for (int i = 0; i < arr.size(); i++) {
							int num = 0;
							num = arr[i].getSize();

							outFile << num << endl;
						}

						outFile.close();
						cout << "Данные успешно записаны в data.csv!" << endl;
					}
					else if (p2 == 3) {
						//удаление
						cout << "Введите ключ>>";
						string key;
						cin >> key;
						int num = hash_in(key, size);
						arr[num].remove(key);
					}
					else if (p2 == 4) {
						//поиск по ключу
						cout << "Введите ключ>>";
						string key;
						cin >> key;
						int num = hash_in(key, size);
						cout << arr[num].search(key) << endl;
					}
					else if (p2 == 5) {
						break;
					}
				}//end while
				break;
			}
		}

	}
	else {
		int size = 1500;

		vector<List<int, string>> arr(size);
		vector<string> arr_key(size);

		for (int j = 0; j < size; j++) {
			string key = generateKey();
			arr_key[j] = key;
			push_hash(arr, size, key);
		}

		for (int i = 0; i < arr.size(); i++) {
			cout << i;
			arr[i].print();
			cout << endl;
		}
		ofstream outFile("data.csv");

		for (int i = 0; i < arr.size(); i++) {
			int num = 0;
			num = arr[i].getSize();

			outFile << num << endl;
		}

		outFile.close();
		cout << "Данные успешно записаны в data.csv!" << endl;
	}






	return 0;
}


/*
91  11FI76
16  42XG21
48  28YS24


90  31VY65

27  82YL51
69  85NQ18
59  87GG77


78  17QG94

11  27NF43


53  23TK11
*/