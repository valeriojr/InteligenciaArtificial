//
// Created by Valerio on 26/10/2019.
//

#ifndef ARTIFICIAL_INTELLIGENCE_UTIL_H
#define ARTIFICIAL_INTELLIGENCE_UTIL_H

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

void prettyPrint(char* str);

#endif //ARTIFICIAL_INTELLIGENCE_UTIL_H
