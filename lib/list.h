#ifndef LIST_H
#define LIST_H

//mem.h is not yet a file, but it must in the end impliment the malloc(), free(), and realloc() functions
#include "mem.h"

template<typename T>
class list{
    public:
        T *data;
        int itemsize;
        int totalsize;
        
        list(){
            totalsize = 1;
            itemsize = 0;
            data = (T*)malloc(1);
        }
        
        ~list(){
            free(data);
        }
        
        list(int s){
            if(!s){
                s++;
            }
            totalsize = s;
            itemsize = 0;
            data = (T*)malloc(s);
        }
        
        int size(){
            return itemsize;
        }
        
        void append(T info){
            if(itemsize == totalsize){
                data = (T*)realloc(data, totalsize * sizeof(T) * 2);
                totalsize *= 2;
            }
            data[itemsize] = info;
            itemsize++;
        }
        
        void remove(int index){
            if(index > itemsize || index < 0){
                return;
            }
            for(int i = index; i < itemsize - 1; i++){
                data[i] = data[i+1];
            }
            itemsize--;
            if(totalsize / 2 >= itemsize && totalsize / 2 > 0){
                data = (T*)realloc(data, (totalsize / 2) * sizeof(T));
                totalsize = totalsize / 2;
            }
        }
        
        void resize(int newsize){
            data = (T*)realloc(data, newsize);
            totalsize = newsize;
            if(itemsize > totalsize){
                itemsize = totalsize;
            }
        }
};

#endif
