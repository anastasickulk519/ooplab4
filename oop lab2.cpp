#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Shop;

class Product
{
private:
	string name;
	double price;
	string company;
	int kolvo;
	bool nalichie;
public:
	Product(string name, double price , string company, int kolvo, bool nalichie) {
		this->name = name;
		this->price = price;
		this->company = company;
		this->kolvo = kolvo;
		this->nalichie = nalichie;
	};
	void print() {
		cout << "Товар: " << name << " - Производитель: " << company << " - Цена: " << price << "руб. - Количество : " << kolvo << " - Наличие : " << (nalichie ? "есть" : "нет") << endl;
	}
	friend class Shop;
	~Product() {
		cout << "Товары закончились" << endl;
	};
};

class Shop{
private:
	vector<unique_ptr<Product>> product;//unique_ptr выделяет динамическую память для хранения класса product
	//он автоматически освободит память, когда она станет не нужна. Следовательно мы не столкнёмся с утечками памяти
public:
	Shop() {
		cout << "Магазин открыт" << endl;
	};
	Shop(string name, double price, string company, int kolvo, bool nalichie) {
		//уловия задания конечно выполнены, но это не то, что я хочу
		product.push_back(make_unique<Product>(name, price, company, kolvo, nalichie));
	};
	void addProduct() {
		string name;
		double price;
		string company;
		int kolvo;
		bool nalichie;

		cout << "На англиском введите товар, цену, производителя, количество и наличие (0 или 1):" << endl;
		cin >> name >> price >> company >> kolvo >> nalichie;
		product.push_back(make_unique<Product>(name, price, company, kolvo, nalichie));
		cout << "Товар добавлен" << endl;
	}

	void findProduct() {
		string name;
		cout << "Введите название товара на англиском (с большой буквы): ";
		cin >> name;

		bool found = false;
		for (int i = 0; i < product.size(); i++) {
			if (product[i]->name == name) {
				cout << "Товар найден: ";
				product[i]->print();
				found = true;
				break;
			}
		}
		if (found == false) {
			cout << "Данный товар отсутствует в магазине" << endl;
		}
	}

	void deleteProduct() {
		string name;
		cout << "Введите название товара на англиском (с большой буквы): ";
		cin >> name;

		bool found = false;
		for (int i = 0; i < product.size(); i++) {
			if (product[i]->name == name) {
				product.erase(product.begin() + i);//удаляет элемент из вектора
				cout << "Товар " << name << " удалён" << endl;
				found = true;
				break;
			}
		}
		if (found == false) {
			cout << "Такого товара нет в магазине" << endl;
		}
	}
	void print_info() {
		for (int i = 0; i < product.size(); i++) {
			product[i]->print();
		}
	}
	// Метод для добавления начальных товаров
	void initializeProducts() {
		product.push_back(make_unique<Product>("Milk", 89.99, "Company 1", 40, false));
		product.push_back(make_unique<Product>("Bread", 46.99, "Company 2", 35, true));
		product.push_back(make_unique<Product>("Eggs", 120.49, "Company 3", 100, true));
		product.push_back(make_unique<Product>("Chicken", 499.99, "Company 4", 0, false));
		product.push_back(make_unique<Product>("Cookies", 99.99, "Company 5", 24, true));
	}
	~Shop() {
		cout << "Магазин закрыт" << endl;
	};
};

int main()
{
	setlocale(LC_ALL, "RU");
	Shop shop;
	shop.initializeProducts();

	int a;
	do {
		cout << "Выберете: \n1 - посмотреть информацию о товарах\n2 - добавить новый товар\n3 - удалить товар\n4 - найти товар\n0 - выход" << endl;
		cin >> a;
		switch (a)
		{
		case(1):
			shop.print_info();
			break;
		case(2):
			shop.addProduct();
			break;
		case(3):
			shop.deleteProduct();
			break;
		case(4):
			shop.findProduct();
			break;
		default:
			cout << "Ошибка: нет такого действия" << endl;
			break;
		}
	} while (a != 0);
}

