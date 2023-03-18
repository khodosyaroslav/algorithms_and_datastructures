#include <iostream>
#include <string>

using namespace std;

struct Employee
{
	string name;
	string surname;
	string middle_name;
	char gender = 'N';
	string phone_number;

	void setEmployee(string in_name, string in_surname, string in_middle_name,
		char in_gender, string in_phone_number)
	{
		name = in_name;
		surname = in_surname;
		middle_name = in_middle_name;
		gender = in_gender;
		phone_number = in_phone_number;
	}

	void printEmployee()
	{
		cout << name << " " << surname << " " << middle_name << ", gender = "
			<< gender << ", phone number = " << phone_number << endl;
	}
};

class EmployeesList
{
private:
	int _length;
	Employee** _list;

public:
	EmployeesList(int length)
	{
		_length = length;
		_list = new Employee*[_length];
	}

	void addByUser()
	{
		string u_name;
		string u_surname;
		string u_middle_name;
		char u_gender = 'N';
		string u_phone_number;

		cin.ignore(1);
		cout << "Enter name: " << endl;
		getline(cin, u_name);
		
		cout << "Enter surname: " << endl;
		getline(cin, u_surname);

		cout << "Enter middle name: " << endl;
		getline(cin, u_middle_name);

		cout << "Enter gender: " << endl;
		cin >> u_gender;

		cin.ignore(1);
		cout << "Enter phone number: " << endl;
		getline(cin, u_phone_number);

		addEmployee(u_name, u_surname, u_middle_name, u_gender, u_phone_number);
	}

	void addEmployee(string name, string surname, string middle_name,
		char gender, string phone_number)
	{
		Employee** list_updated = new Employee*[_length + 1];
		for (int i = 0; i < _length; i++)
		{
			list_updated[i] = _list[i];
		}
		delete[] _list;

		Employee* employee_added = new Employee;
		employee_added->setEmployee(name, surname, middle_name, gender, phone_number);

		list_updated[_length] = employee_added;
		_list = list_updated;
		_length++;
	}

	void deleteEmployee(int index)
	{
		if (_length != 0)
		{
			for (int i = index; i < _length - 1; i++)
			{
				_list[i] = _list[i + 1];
			}
			_length--;
		}
	}

	void printEmployees()
	{
		if (_length != 0)
			for (int i = 0; i < _length; i++)
				_list[i]->printEmployee();
		else
			cout << "List is empty" << endl;
	}

	void printEmployeesWithTheSameSurname()
	{
		bool flag = false;
		for (int i = 0; i < _length; i++)
		{
			for (int j = i + 1; j < _length; j++)
			{
				if (_list[i]->surname == _list[j]->surname)
				{
					_list[j]->printEmployee();
					cout << " -- WITH -- " << endl;
					_list[i]->printEmployee();
					flag = true;
				}
			}
		}
		if (!flag)
			cout << "NONE";
	}

	void setLength(int length)
	{
		_length = length;
	}
	int getLength()
	{
		return _length;
	}

	int interfaceFunc()
	{
		int action, index;
		cout << "\nChoose action (from 1 to 5) "
			"\n {1} is add employee"
			"\n {2} is remove emplyoee by index"
			"\n {3} is print employess"
			"\n {4} is print employess with the same surname"
			"\n {5} exit" << endl;
		cin >> action;
		switch (action)
		{
		case 1:
			addByUser();
			break;
		case 2:
			cout << "Enter index: ";
			cin >> index;
			deleteEmployee(index);
			break;
		case 3:
			printEmployees();
			break;
		case 4:
			printEmployeesWithTheSameSurname();
			break;
		case 5:
			return -1;
		default:
			cout << "Incorrect number" << endl;
		}
		return 0;
	}
};

EmployeesList initByDefault()
{
	EmployeesList employeeList(0);
	employeeList.addEmployee("Vasya", "Pupkin", "Vadimovich", 'M', "+38-056-666-56-56");
	employeeList.addEmployee("Vadim", "Drozdov", "Vasilievich", 'M', "+38-044-777-88-88");
	employeeList.addEmployee("Anfisa", "Maksimova", "Makarovna", 'W', "+38-086-333-17-17");
	employeeList.addEmployee("Maria", "Ivanova", "Volodymirivna", 'W', "+38-068-388-99-99");
	employeeList.addEmployee("Andrey", "Drozdov", "Maksimovich", 'M', "+38-044-666-33-33");
	return employeeList;
}

int main()
{
	int res = 0;
	EmployeesList employeeList = initByDefault();
	
	do
	{
		res = employeeList.interfaceFunc();
	} while (res != -1);
	
	return 0;
}