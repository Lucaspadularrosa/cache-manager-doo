#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

template <class T>
class CacheManager
{
    // Members (private)
    int capacity;
    map<string, pair<T, int>> cache_data;      // <Clave,<Obj,Indice>>
    map<string, pair<T, int>> cache_data_file; // <Clave,<Obj,Indice>>
    bool write_file(string, T);
    int mru = 0;

public:
    CacheManager(int);
    ~CacheManager();

    void insert(string key, T obj);
    T get(string key);
    void showCache();
    void showFile(string key);
    void writeFile();
};

template <class T>
CacheManager<T>::CacheManager(int cap)
{
    capacity = cap;
}

template <class T>
CacheManager<T>::~CacheManager()
{
    // Destructor
}

template <class T>
bool CacheManager<T>::write_file(string key, T obj)
{
    return true;
}

template <class T>
void CacheManager<T>::writeFile()
{
    ofstream archivo;
    archivo.open("prueba.dat", ios::out | ios::binary);
    if (archivo.fail())
    {
        cout << "No se puede abrir el archivo";
        exit(1);
    }

    for (auto x : cache_data_file)
    {
        archivo << x.first << " "
                << " " << x.second.first.getId() << " " << x.second.first.getData() << " " << x.second.first.getValue() << endl;
    }

    archivo.close();
}

template <class T>
void CacheManager<T>::insert(string key, T obj)
{

    if (cache_data.empty())
    {
        mru++;
        cache_data.insert(make_pair(key, make_pair(obj, mru)));
        cache_data_file.insert(make_pair(key, make_pair(obj, mru)));
        writeFile();
        return;
    }
    else
    {
        if (cache_data.size() < capacity)
        {
            for (auto x = cache_data.begin(); x != cache_data.end(); x++)
            {
                if (x->first == key)
                {
                    auto f = cache_data.find(x->first);
                    cache_data.erase(f);
                    mru++;
                    cache_data.insert(make_pair(key, make_pair(obj, mru)));
                    auto j = cache_data_file.find(x->first);
                    cache_data_file.erase(j);
                    cache_data_file.insert(make_pair(key, make_pair(obj, mru)));

                    return;
                }
            }
            mru++;
            cache_data.insert(make_pair(key, make_pair(obj, mru)));
            cache_data_file.insert(make_pair(key, make_pair(obj, mru)));

            writeFile();
        }
        else
        {
            auto x = cache_data.begin()->second.second;

            int f = 0;

            for (auto cd = cache_data.begin(); cd != cache_data.end(); cd++)
            {
                if (cd->second.second < x)
                {
                    f = cd->second.second;
                }
                else
                {
                    f = x;
                }
            }

            for (auto l = cache_data.begin(); l != cache_data.end(); l++)
            {
                if (l->second.second == f)
                {
                    auto y = cache_data.find(l->first);
                    cache_data.erase(y);
                    mru++;
                    cache_data.insert(make_pair(key, make_pair(obj, mru)));
                    cache_data_file.insert(make_pair(key, make_pair(obj, mru)));

                    writeFile();
                }
            }
        }
    }
}

template <class T>
T CacheManager<T>::get(string key)
{
    string texto;
    ifstream archivo;
    archivo.open("prueba.dat", ios::in | ios::binary);

    if (archivo.fail())
    {
        cout << "No se puede abrir el archivo";
    }

    while (!archivo.eof())
    {
        getline(archivo, texto);
        try
        {

            if (texto.rfind(key) < 4294967295)
            {

                auto obj_file = cache_data_file.find(key);
                auto x = cache_data.begin()->second.second;

                int f = 0;

                for (auto cd = cache_data.begin(); cd != cache_data.end(); cd++)
                {
                    if (cd->second.second < x)
                    {
                        f = cd->second.second;
                    }
                    else
                    {
                        f = x;
                    }
                }

                for (auto l = cache_data.begin(); l != cache_data.end(); l++)
                {
                    if (l->second.second == f)
                    {
                        auto y = cache_data.find(l->first);
                        cache_data.erase(y);
                        mru++;
                        cache_data.insert(make_pair(obj_file->first, make_pair(obj_file->second.first, mru)));
                    }
                }
                return obj_file->second.first;
            }

            auto item = cache_data.find(key);
            if (item != cache_data.end())
            {
                item->second.second++;
                return item->second.first;
            }
        }
        catch (...)
        {
            cout << "No se encontro la clave " << endl;
        }
    }

    archivo.close();
}

template <class T>
void CacheManager<T>::showCache()
{

    for (auto x : cache_data)
    {
        cout << x.first << " "
             << "mru: " << x.second.second << " " << x.second.first.getId() << " " << x.second.first.getData() << " " << x.second.first.getValue() << endl;
    }
}

template <class T>
void CacheManager<T>::showFile(string key)
{

    string texto;
    ifstream archivo;
    archivo.open("prueba.dat", ios::in | ios::binary);

    if (archivo.fail())
    {
        cout << "No se puede abrir el archivo";
    }

    cout << "Archivo" << endl;
    while (!archivo.eof())
    {
        getline(archivo, texto);
        cout << texto << endl;
    }
}