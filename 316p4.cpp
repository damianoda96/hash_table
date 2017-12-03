#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

const int TABLE_SIZE = 10001;

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

struct Sequence_Array
{
    int** sequence_array;
    int size_of_array;
    
    Sequence_Array()
    {
        sequence_array = NULL;
    }
    
    Sequence_Array(int size)
    {
        this->size_of_array = size;
        sequence_array = new int* [size];
    }
    
    ~Sequence_Array()
    {
        for(int i = 0; i < size_of_array; i++)
        {
            if (this->sequence_array[i] != NULL)
            {
                delete sequence_array[i];
            }
        }
    }
    
    void push_back(int* sequence)
    {
        for(int i = 0; i < size_of_array; i++)
        {
            if(this->sequence_array[i] == NULL)
            {
                sequence_array[i] = sequence;
                break;
            }
        }
    }
    
    int size()
    {
        return size_of_array;
    }
};

int* generatedSequence(int size)
{
    int random_integer;
    
    int* sequence = new int[size];
    
    srand (time(NULL));
    
    for(int i = 0; i < size; i++)
    {
        random_integer = rand() % 9;
            
        sequence[i] = random_integer;
    }
    
    return sequence;
    
}

int main(int argc, char** argv)
{
    
    //This is a structure that holds an array of int*
    Sequence_Array aos(10);
    
    //First, generate each sequence
    for(int i = 1000; i <= 10000; i+=1000)
    {
        aos.push_back(generatedSequence(i));
    }
    
    std::cout << "SEQUENCES CREATED\n";
    
    return 0;
    
}

