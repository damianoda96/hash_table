#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

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

struct Hash_Table
{
    Hash_Entry ** table;
    
    int collision_counter;
    
    Hash_Table()
    {
        collision_counter = 0;
        
        table = new Hash_Entry* [TABLE_SIZE];
        
        this->clear();
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
    
    void insert_linear(int key, int value)
    {
        int hash = (key % TABLE_SIZE);
        
        while(table[hash] != NULL && table[hash]->getKey() != key)
        {
           collision_counter++;
           hash = (hash + 1) % TABLE_SIZE;
        }

        if(table[hash] != NULL)
        {
            delete table[hash];
        }
        
        table[hash] = new Hash_Entry(key, value);
        
    }
    
    void insert_quadratic(int key, int value)
    {
        int hash = (key % TABLE_SIZE);
        
        int i = 0;
        
        while(table[hash] != NULL && table[hash]->getKey() != key)
        {
            collision_counter++;
            i++;
            //only difference// instead of + 1, i*i
            hash = (hash + (i*i)) % TABLE_SIZE;
        }
        
        if(table[hash] != NULL)
        {
            delete table[hash];
        }
        
        table[hash] = new Hash_Entry(key, value);
        
        
    }
    
    void insert_double(int key, int value)
    {
        
        
    }
    
    void clear_count()
    {
        this->collision_counter = 0;
    }
    
    ~Hash_Table()
    {
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            if(table[i] != NULL)
            {
                delete table[i];
            }
        }
        
        delete table;
    }
    
    void clear()
    {
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            if(table[i] != NULL)
            {
                table[i] = NULL;
            }
        }
    }
    
    int size()
    {
        int count = 0;
        
        for(int i = 0; i < TABLE_SIZE; i++)
        {
            if(table[i] != NULL)
            {
                count++;
            }
        }
        
        return count;
    }
};

struct Sequence_Array
{
    int** sequence_array;
    int size_of_array;
    
    Sequence_Array()
    {
        size_of_array = 0;
        sequence_array = NULL;
    }
    
    Sequence_Array(int size)
    {
        this->size_of_array = size;
        sequence_array = new int* [size];
        this->clear();
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
        
        delete sequence_array;
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
    
    void clear()
    {
        for (int i = 0; i < size_of_array; i++)
        {
            if(sequence_array[i] != NULL)
            {
                sequence_array[i] = NULL;
            }
            
        }
    }
    
    int size()
    {
        return size_of_array;
    }
    
    int* return_sequence(int index)
    {
        return sequence_array[index];
    }

};

int* generatedSequence(int size)
{
    int random_integer;
    
    int* sequence = new int[size];
    
    srand (time(NULL));
    
    for(int i = 0; i < size; i++)
    {
        random_integer = rand() % 32767;
            
        sequence[i] = random_integer;
    }
    
    return sequence;
    
}

int main(int argc, char** argv)
{
    Hash_Table test_table;
    
    //This is a structure that holds an array of int*
    Sequence_Array aos(10);
    
    //First, generate each sequence
    for(int i = 1000; i <= 10000; i+=1000)
    {
        aos.push_back(generatedSequence(i));
    }
    
    std::cout << "SEQUENCES CREATED\n";
    
    //output size///////////////////////////
    std::cout << "Size:\t";
    
    for(int i = 1000; i <= 10000; i+=1000)
    {
        std::cout << i << "\t";
    }
    
    //output linear/////////////////////////////
    
    std::cout << std::endl << "Linear:\t";
    
    int array_index = 0;
    
    for(int i = 1000; i <= 10000; i+=1000)
    {
        int* array = aos.return_sequence(array_index);
        
        for(int j = 0; j < i; j++)
        {
            //insert random key and integer value
            test_table.insert_linear((rand() % 32767), array[j]);
        }
        
        std::cout << test_table.collision_counter << "\t";
        test_table.clear_count();
        test_table.clear();
        
        array_index++;
    
    }
    
    std::cout << std::endl;
    
    test_table.clear_count();
    test_table.clear();
    
    //output quadratic///////////////////////////////////////////
    
    std::cout << std::endl << "Quadratic:  ";
    
    array_index = 0;
    
    for(int i = 1000; i <= 10000; i+=1000)
    {
        int* array = aos.return_sequence(array_index);
        
        for(int j = 0; j < i; j++)
        {
            //insert random key and integer value
            test_table.insert_quadratic((rand() % 32767), array[j]);
        }
        
        std::cout << test_table.collision_counter << "\t";
        test_table.clear_count();
        test_table.clear();
        
        array_index++;
        
    }
    
    std::cout << std::endl;
    
    //output double/////////////////////////
    
    
    
    ///////////////////////////////////////////
    
    return 0;
    
}

