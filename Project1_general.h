/* Механіко-математичний факультет, 2 курс (2023/2024)
   Група "Комп'ютерна механіка", Назаренко Владислав, курсова робота за темою 1

   Даний файл містить всі стандартні бібліотеки, які використовуються у файлах Project1_classes.h,
   Project1.cpp та Project1_test.cpp, а також надає псевдоніми деяким типам даних */

#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <iostream>  // введення-виведення
#include <fstream>   // файли
#include <cmath>     // математичні функції
#include <exception> // виключення (помилки)
#include <iomanip>   // інструменти для форматування виводу
#include <map>       // пари "ключ-значення"
#include <array>

typedef double DType;                  // тип double       отримує псевдонім DType
typedef unsigned int UInt;             // тип unsigned int отримує псевдонім UInt
typedef std::array<UInt, 2> Coords;    // кожен елемент масиву має два беззнакових значення
typedef std::map<Coords, DType> MType; // пара "Ключ - Coords, значення - DType" отримує псевдонім MType
#endif
