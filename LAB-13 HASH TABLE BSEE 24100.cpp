#include <iostream>
using namespace std;

#define TABLE_SIZE 10
#define PRIME 7   // PRIME NUMBER < TABLE_SIZE

int hashTable[TABLE_SIZE];
int status[TABLE_SIZE];
// 0 = EMPTY, 1 = OCCUPIED, 2 = DELETED

// PRIMARY HASH FUNCTION
int hash1(int key)
{
    return key % TABLE_SIZE;
}

// SECONDARY HASH FUNCTION
int hash2(int key)
{
    return PRIME - (key % PRIME);
}

// INSERT USING DOUBLE HASHING
void insertKey(int key)
{
    int index = hash1(key);

    if (status[index] == 0 || status[index] == 2)
    {
        hashTable[index] = key;
        status[index] = 1;
        return;
    }

    int step = hash2(key);

    for (int i = 1; i < TABLE_SIZE; i++)
    {
        int newIndex = (index + i * step) % TABLE_SIZE;

        if (status[newIndex] == 0 || status[newIndex] == 2)
        {
            hashTable[newIndex] = key;
            status[newIndex] = 1;
            return;
        }
    }

    cout << "HASH TABLE IS FULL" << endl;
}

// SEARCH KEY
void searchKey(int key)
{
    int index = hash1(key);
    int step = hash2(key);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int newIndex = (index + i * step) % TABLE_SIZE;

        if (status[newIndex] == 0)
            break;

        if (status[newIndex] == 1 && hashTable[newIndex] == key)
        {
            cout << "KEY FOUND AT INDEX " << newIndex << endl;
            return;
        }
    }

    cout << "KEY NOT FOUND" << endl;
}

// DELETE KEY
void deleteKey(int key)
{
    int index = hash1(key);
    int step = hash2(key);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int newIndex = (index + i * step) % TABLE_SIZE;

        if (status[newIndex] == 0)
            break;

        if (status[newIndex] == 1 && hashTable[newIndex] == key)
        {
            status[newIndex] = 2;
            cout << "KEY DELETED" << endl;
            return;
        }
    }

    cout << "KEY NOT FOUND" << endl;
}

// DISPLAY HASH TABLE
void displayTable()
{
    cout << "\nINDEX\tVALUE\n";
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        cout << i << "\t";
        if (status[i] == 1)
            cout << hashTable[i];
        else
            cout << "-";
        cout << endl;
    }
}

int main()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        status[i] = 0;

    int choice, key;

    do
    {
        cout << "\n1. INSERT\n2. SEARCH\n3. DELETE\n4. DISPLAY\n5. EXIT\n";
        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "ENTER KEY: ";
            cin >> key;
            insertKey(key);
            break;

        case 2:
            cout << "ENTER KEY TO SEARCH: ";
            cin >> key;
            searchKey(key);
            break;

        case 3:
            cout << "ENTER KEY TO DELETE: ";
            cin >> key;
            deleteKey(key);
            break;

        case 4:
            displayTable();
            break;

        case 5:
            cout << "EXITING PROGRAM" << endl;
            break;

        default:
            cout << "INVALID CHOICE" << endl;
        }

    } while (choice != 5);

    return 0;
}
