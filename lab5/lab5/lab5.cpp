#include <iostream>
#include <string>

using namespace std;

const int M = 3;
const double A = 0.6180339887;

int hash_method_division(int key)
{
	return key % M;
}

int hash_method_mutliplication(int key)
{
	return (int)(M * (key * A - floor(key * A)));
}

int hash_method_string_keys(string s)
{
	int a = 31;
	int n = (int)s.length();
	int sum = 0;

	for (int i = 0; i < n; i++)
		sum += s[i] * (int)pow(a, i);

	return sum % M;
}

int interface_func(int& key, string& key_str)
{
	int action, new_key;
	string new_key_str;

	cout << "\nTable size: " << M << endl;
	cout << "Current int key: " << key << ", string key: " << key_str;
	cout << "\nChoose action (from 1 to 4) "
		"\n {1} enter int key"
		"\n {2} enter string key"
		"\n {3} print result of hash functions"
		"\n {4} exit" << endl;
	cin >> action;
	switch (action)
	{
	case 1:
	{
		cout << "new key: ";
		cin >> new_key;
		key = new_key;
	}
	break;
	case 2:
	{
		cout << "new string key: ";
		cin.ignore(1);
		getline(cin, new_key_str);
		key_str = new_key_str;
	}
	break;
	case 3:
		cout << "hash division: " << hash_method_division(key) << endl;
		cout << "hash multiplication: " << hash_method_mutliplication(key) << endl;
		cout << "hash string keys: " << hash_method_string_keys(key_str) << endl;
		break;
	case 4:
		return -1;
	default:
		cout << "Incorrect number" << endl;
	}
	return 0;
}

int main()
{
	int key = 0, res = 0;
	string key_str = "Hello world!";

	do
	{
		res = interface_func(key, key_str);
	} while (res != -1);

	return 0;
}
