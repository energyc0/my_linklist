#include <iostream>
#include <fstream>

using namespace std;

const int MAX = 100;

struct link
{
	int data;
	link* next;
};

class linklist
{
	link* first;
public:
	linklist() { first = NULL; }  // конструктор
	~linklist() // деструктор
	{
		link* current = first;
		while (current)
		{
			link* temp = current;
			if (!current)
				break;
			current = current->next;
			cout << "\nУдаляется элемент cписка " << temp->data << "!!!";
			delete temp;
		}
	}
	void additem( int d) // добавление одного значения в список
	{
		link* newlink = new link;
		newlink->data = d;
		newlink->next = first;
		first = newlink;
	}

	void getitem() //цикл добавления новых значений в список
	{
		int a;
		char ch;
		do
		{
			cout << "\nВведите значение: "; cin >> a;
			additem(a);
			cout << "\nПродолжить?(y/n): "; cin >> ch;
		} while (ch == 'y');
	}

	void fileputitem() // удаление старых значений и запись новых на файл
	{
		ofstream outlink("linkfile.txt", ios::trunc);
		cout << "\nПерезапись на файл...";
		if (!outlink.is_open())
		{
			cout << "\nОшибка открытия файла!";
			exit(-1);
		}
		link* current = first;
		while (current)
		{
			outlink << current->data << " ";
			current = current->next;
		}
		cout << "\nУспешная перезапись";
		outlink.close();
	}

	void filegetitem()  // загрузка значений из файла
	{
		ifstream inlink("linkfile.txt");
		cout << "\nЗагрузка из файла...";
		if (!inlink.is_open())
		{
			cout << "\nОшибка открытия файла!";
			exit(-1);
		}
		inlink.seekg(0, ios::beg);
			link* newfirst = new link;
			inlink >> newfirst->data;
			if (!inlink)
			{
				cout << "\nФайл пуст!";
				return;
			}
			first = newfirst;
			first->next = nullptr;
			while (true)
			{
				link* newlink = new link;
				inlink >> newlink->data;
				if (!inlink)
					break;
				newlink->next = first;
				first = newlink;
			}
		cout << "\nЗагрузка завершена";
		inlink.close();
	}

	void display() const // вывод всех значений
	{
		if (first == NULL)
			cout << "\nСписок пуст!";
		else
		{
			link* current = first;
			while (current)
			{
				cout << current->data << " ";
				current = current->next;
			}
		}
	}

	void removeData()	// удаление значений из списка
	{
		int val;
		cout << "Введите значение для удаления из списка: "; cin >> val;
		if (!first)
			return;
		while(first->data == val)
		{
			link* temp = first;
			first = first->next;
			delete temp;
			if (!first)
				return;
		}
		link* curr = first;
		while (curr)
		{
			if (!curr->next)
				break;
			if (curr->next->data == val)
			{
				link* temp = curr->next;
				curr->next = curr->next->next;
				delete temp;
			}
			else
				curr = curr->next;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	linklist a;
	char ch;
		do
		{
			cin.clear();
			cout << "\nВведите\n'd' для добавления данных в список, \n's' для вывода всех значений из списка, \n'r' для записи новых значений в файл списка, \n'b' для загрузки данных списка из файла,\n'k' для удаления определенного числа из списка,\n'e' для выхода: ";
			cin >> ch;

			cout << "\n--------------------------------------------\n";

			switch (ch)
			{
			case 'd':a.getitem(); break;
			case 's':a.display(); break;
			case 'r':a.fileputitem(); break;
			case 'b':a.filegetitem(); break;
			case'k':a.removeData(); break;
			case 'e': a.~linklist(); exit(0);
			default: cout << "\nОшибка ввода"; break;
			}
		} while (true);
}
