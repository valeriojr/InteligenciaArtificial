//
// Created by Valerio on 26/10/2019.
//

#ifndef ARTIFICIALINTELLIGENCE_UTIL_H
#define ARTIFICIALINTELLIGENCE_UTIL_H

#include <string.h>

#define NEW(TYPE) (TYPE*)(malloc(sizeof(TYPE)))
#define NEW_ARRAY(TYPE, COUNT) (TYPE*)(malloc(COUNT * sizeof(TYPE)))

#define SWAP(TYPE, a, b)\
TYPE __aux__ = a;\
a = b;\
b = __aux__;\

/*
 * https://blog.noctua-software.com/c-lambda.html
*/
#define LAMBDA(c_) ({ c_ _;})

#define between(a, x, b) (x >= a && x <= b)

void tocamelcase(char* str){

}

#endif //ARTIFICIALINTELLIGENCE_UTIL_H
