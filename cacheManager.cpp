#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>
#include <vector>

using namespace std;
#include "cache.h"

class Student
{

    int id;
    int value;
    const char *data;

public:
    static const string class_name; // Cada clase tiene un static llamado: class_name
    Student(int _key, int _value, const char *_data) : id(_key), value(_value), data(_data)
    {
        // print();
    }

    void print()
    {
        cout << "Student Object: " << id << ", " << value << ", " << data << ", " << endl;
    };

    ~Student()
    {
    }

    int getId()
    {
        return id;
    }

    int getValue()
    {
        return value;
    }

    string getData()
    {
        std::__cxx11::string s0 = &data[0];
        return s0;
    }
};

const string Student::class_name = "StudentClass";

int main(int argc, char const *argv[])
{
    CacheManager<Student> my_cache(3);

    my_cache.insert("0", Student(0, 22, "student1"));
    my_cache.insert("2", Student(1, 23, "student2"));
    // cout << "---------------- Update ---------------" << endl;
    my_cache.insert("2", Student(2, 24, "student4"));
    my_cache.insert("2", Student(2, 25, "student6"));
    my_cache.insert("3", Student(3, 29, "student4"));
    my_cache.insert("5", Student(6, 31, "student4"));
    my_cache.insert("7", Student(6, 41, "student4"));

    my_cache.showCache();

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    Student return_obj = my_cache.get("2"); // Not in cache but in fileSystem
    cout << return_obj.getId() << " " << return_obj.getData() << " " << return_obj.getValue() << " " << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    my_cache.showCache();

    // string str = my_cache.showFile("2");
    // cout << str << endl;
    // my_cache.insert("2", Student(22, 222, "Eze"));
    // // my_cache.show_cache();

    // cout << "<<<<<<<<<<" << endl;
    // my_cache.showFile("2");

    // my_cache.insert(" 2 ", Student(2, 25, " EZE "));
    // // my_cache.show_cache();

    // my_cache.insert("9", Student(1, 5, "Nine"));
    // my_cache.insert("7", Student(4, 30, "student6"));
    // my_cache.insert("7", Student(4, 39, "student8"));
    // my_cache.insert(" 9 ", Student(1, 5, " Nine "));
    // my_cache.insert(" 9 ", Student(1, 5, " Nine "));
    // // my_cache.show_cache();
    // my_cache.showCache();

    return 0;
}
