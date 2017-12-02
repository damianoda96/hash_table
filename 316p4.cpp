#include <iostream>

struct Hash_Entry
{
    int key;
    int value;
    
    Hash_Entry(int key, int value)
    {
        this->key = key;
        this->value = value;
    }
    
    int getKey()
    {
        return key;
    }
    
    int getValue()
    {
        return value;
    }
};

const int TABLE_SIZE = 128;

struct Hash_Map
{
    Hash_Entry ** table;
    
    Hash_Map()
    {
        table = new Hash_Entry* [TABLE_SIZE];
        
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            table[i] = NULL;
        }
    }
    
    int get(int key)
    {
        int hash = (key % TABLE_SIZE);
        
        while(table[hash] != NULL && table[hash]->getKey() != key)
        {
            hash = (hash + 1) % TABLE_SIZE;
        }
        if(table[hash] == NULL)
        {
            return -1;
        }
        else
        {
            return table[hash]->getValue();
        }
    }
    
    void put(int key, int value)
    {
        int hash = (key % TABLE_SIZE);
        
        while(table[hash] != NULL && table[hash]->getKey() != key)
        {
            hash = (hash + 1)  % TABLE_SIZE;
        }
        if(table[hash] != NULL)
        {
            delete table[hash];
        }
        
        table[hash] = new Hash_Entry(key, value);
    }
    
    ~Hash_Map()
    {
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            if(table[i] != NULL)
            {
                delete table[i];
            }
            
            delete table;
        }
    }
};

int main(int argc, char** argv)
{
    return 0;
    
}

