#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <list>

using namespace std;


class LibraryRecord
{

public:

    int ReaderId;

    string Name;

    string Address;


    LibraryRecord( int id, string name, string address ) : ReaderId( id ), Name( name ), Address( address )
    {
    }

    bool operator == ( LibraryRecord other )
    {
        return this->ReaderId == other.ReaderId;
    }

};


class HashTable
{

private:

    vector<list<LibraryRecord>> _table;

    const double _loadFactor = 0.7;

    int _tableSize;

    int _numElements;


    int HashFunction( int key )
    {
        return key % this->_tableSize;
    }

    void Rehash()
    {
        cout << "Рехеширование... Текущий размер таблицы: " << this->_tableSize << "\n";

        this->_tableSize *= 2;
        vector<list<LibraryRecord>> newTable( this->_tableSize );

        for ( int i = 0; i < this->_tableSize; ++i )
            for ( auto record : this->_table[i] )
                newTable[HashFunction( record.ReaderId )].push_back( record );

        this->_table = move( newTable );
        cout << "Рехеширование завершено. Новый размер таблицы: " << this->_tableSize << "\n";
    }


public:

    HashTable( int size = 10 ) : _tableSize( size ), _numElements( 0 )
    {
        this->_table.resize( this->_tableSize );
    }

    void Insert( LibraryRecord record )
    {
        int hash = HashFunction( record.ReaderId );

        for ( auto rec : this->_table[hash] )
        {
            if ( rec == record )
            {
                cout << "Запись с таким номером читательского абонемента уже существует.\n";
                return;
            }
        }

        this->_table[hash].push_back( record );

        if ( (double)( ++this->_numElements ) / this->_tableSize > this->_loadFactor )
            this->Rehash();
    }

    bool Remove( int key )
    {
        int hash = this->HashFunction( key );

        for ( auto it = this->_table[hash].begin(); it != this->_table[hash].end(); it++ )
        {
            if ( it->ReaderId == key )
            {
                this->_table[hash].erase( it );
                --this->_numElements;

                cout << "Запись с номером " << key << " удалена.\n";

                return true;
            }
        }

        cout << "Запись с номером " << key << " не найдена.\n";

        return false;
    }

    LibraryRecord* Search( int key )
    {
        for ( auto record : this->_table[this->HashFunction( key )] )
            if ( record.ReaderId == key )
                return &record;

        return nullptr;
    }

    void Display()
    {
        for ( int i = 0; i < _tableSize; ++i )
        {
            if ( !this->_table[i].empty() )
            {
                cout << "Корзина " << i << ":\n";

                for ( auto record : this->_table[i] )
                {
                    cout << "  Номер читательского: " << record.ReaderId
                        << ", ФИО: " << record.Name
                        << ", Адрес: " << record.Address << "\n";
                }
            }
        }
    }

};


void Init( HashTable& ht )
{
    ht.Insert( LibraryRecord( 12345, "Иванов Иван Иванович", "г. Москва, ул. Пушкина, д. 1" ) );
    ht.Insert( LibraryRecord( 23456, "Петров Петр Петрович", "г. Санкт-Петербург, Невский пр., д. 10" ) );
    ht.Insert( LibraryRecord( 34567, "Сидоров Сидор Сидорович", "г. Казань, ул. Баумана, д. 5" ) );
    ht.Insert( LibraryRecord( 45678, "Кузнецов Алексей Андреевич", "г. Новосибирск, ул. Ленина, д. 20" ) );
    ht.Insert( LibraryRecord( 56789, "Николаев Николай Николаевич", "г. Екатеринбург, ул. Радищева, д. 15" ) );
}

int main()
{
    SetConsoleCP( 1251 );
    SetConsoleOutputCP( 1251 );


    HashTable ht;
    string command;

    Init( ht );


    while ( true )
    {
        cout << "\nВведите команду (insert, remove, search, display, exit): ";
        cin >> command;

        if ( command == "insert" )
        {
            int id;
            string Name, Address;

            cout << "Введите номер читательского абонемента: ";
            cin >> id;
            cin.ignore();
            cout << "Введите ФИО: ";
            getline( cin, Name );
            cout << "Введите адрес: ";
            getline( cin, Address );

            ht.Insert( LibraryRecord( id, Name, Address ) );
        }
        else if ( command == "remove" )
        {
            int id;

            cout << "Введите номер читательского абонемента для удаления: ";
            cin >> id;

            ht.Remove( id );
        }
        else if ( command == "search" )
        {
            int id;

            cout << "Введите номер читательского абонемента для поиска: ";
            cin >> id;

            LibraryRecord* record = ht.Search( id );

            record
                ? cout << "Найдена запись: Номер читательского: " << record->ReaderId << ", ФИО: " << record->Name << ", Адрес: " << record->Address << "\n"
                : cout << "Запись не найдена.\n";
        }
        else if ( command == "display" )
        {
            ht.Display();
        }
        else if ( command == "exit" )
        {
            break;
        }
        else
        {
            cout << "Неизвестная команда.\n";
        }
    }


    return 0;
}
