#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>

using namespace std;

template <class T, int N=100>
class ArrayList{
private:
    int size = N;
    int length = 0;
    T *array;

    void extend_list(){
        int oldsize = size;
        size = size + N;
        T *temp = new T[size];
        for (int i = 0; i < oldsize; i++) {
            temp[i] = array[i];
        }
        delete array;
        array = temp;
    }

public:
    ArrayList(){
        array = new T[N];
    }

    friend ostream &operator<<(ostream &os, ArrayList<T> &alist){
        for(int i = 0; i < alist.getLength(); i++){
            os << alist.get(i) << " ";
        }
        return os;
    }

    T &operator[](int idx){
        return array[idx];
    }

    void insert(T item){
        if (length + 1 >= size) {
            extend_list();
        }
        array[length++] = item;
    }

    T get(int idx){
        return array[idx];
    }

    int getLength(){return length;}

    int getSize(){return size;}

    void remove(const T& item)
    {
        if(length <= 0)
            return;

        T*cpy = new T[size];
        T*cpyStart = cpy;
        T*arrStart = array;

        for(int i = 0; i<length; i++)
        {
            if(array[i] != item)
            {
                *cpy = *array;
                cpy++;
            }

            array++;
        }

        cpy = cpyStart;
        array = arrStart;

        delete[] array;
        array = cpy;
    }
    
    void remove(int index)
    {
        if(index > length - 1)
            return;

        for(int i = 0; i<length; i++)
        {
            if(i>=index)
                array[i] = array[i+1];
        }
        length--;
    }

};

#endif //ARRAYLIST_H
