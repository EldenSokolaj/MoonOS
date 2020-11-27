#ifndef MATH_H
#define MATH_H

template <typename T>
T abs(T in){
    if(in < 0){
        return in * -1;
    }
    return in;
}

#endif