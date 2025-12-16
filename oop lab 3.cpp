#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Error : public exception{ //exception - базовый класс
public:
    Error(){}
    virtual const char* what(){ 
        return "Ошибка в программе";
    }
    virtual ~Error() {}
};

class PointerError : public Error {
public:
    const char* what() override { 
        return "Ошибочный указатель";
    }
};

class ListError : public Error {
public:
    const char* what() override { 
        return "Ошибка работы со списком";
    }
};

class IndexError : public Error {
public:
    const char* what() override { 
        return "Недопустимый индекс";
    }
};

class OverListError : public Error {
public:
    const char* what() override { 
        return "Список переполнен";
    }
};

template <typename T>
class PointerArr {
private:
    vector <T*> pointers;
public:
    ~PointerArr() {
        for (auto ptr : pointers) {
            delete ptr;
        }
    }

    void add(T* ptr) {
        if (ptr == nullptr) {
            throw PointerError();
        }
        pointers.push_back(ptr);
    }
    T*& operator[](size_t index) {
        if (index >= pointers.size()) {
            throw overflow_error("Выход за границы массива");
        }
        return pointers[index];
    }
    size_t getSize() const {
        return pointers.size();
    }
};

class MyClass {
private:
    int id;
    string name;
public:
    MyClass(int i, const string& n) : id(i), name(n) {}
    void show() const {
        cout << "MyClass: id - " << id << ", name - " << name << endl;
    }
};

int main(){
    setlocale(LC_ALL, "RU");
    try {
        cout << "Масив ошибок" << endl;
            PointerArr<Error> errorArray;
            errorArray.add(new Error());
            errorArray.add(new ListError());
            errorArray.add(new IndexError());
            errorArray.add(new OverListError());

            for (size_t i = 0; i < errorArray.getSize(); ++i) {
                cout << errorArray[i]->what() << endl;
            }

            cout << "Масив для демонстрации" << endl;
            PointerArr<MyClass> arr;
            arr.add(new MyClass(81, "Илья"));
            arr.add(new MyClass(24, "Шейн"));
            for (size_t i = 0; i < arr.getSize(); ++i) {
                arr[i]->show();
            }
            cout << "\\Попытка доступа к несуществующему индексу 15" << endl;
            arr[15] -> show(); 

        } 
    /*catch (const exception& e) {
            cout << "Поймано необработанное исключение: " << e.what() << endl;
            cout << "Программа будет завершена аварийно" << endl;
            return 1;
        }*/

        catch (const overflow_error& e) {
            cout << "Поймано критическое overflow_error: " << e.what() << endl;
            cout << "Программа будет завершена аварийно" << endl;
            return 1;
        }

       


        // Все очищено автоматически, т.к. деструктор класса PointerArray освобождает память
        return 0;
    }