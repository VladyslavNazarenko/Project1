/* Механіко-математичний факультет, 2 курс (2023/2024)
   Група "Комп'ютерна механіка", Назаренко Владислав, курсова робота за темою 1

   Даний файл представляє структуру класів SVector та SMatrix, методи яких описані у файлі Project1.cpp */

#ifndef __CLASSES_H__
#define __CLASSES_H__
#include "Project1_general.h"

class SVector;
class SMatrix;

class SVector {
    friend SMatrix;   // кожен метод класу SVector має доступ до всіх полів класу SMatrix

private:              // "приховані" від користувача дані
    UInt length;      // довжина вектора
    MType value;      // значення вектора у відповідній координаті

public:               // методи доступні для всіх частин даного класу та інших класів
    void Console_input();
    void Console_print();

    void Txt_input(const char* file);
    void Txt_print(const char* file);

    UInt Get_length(); // отримання довжини вектора
    MType Get_value(); // отримання значення вектора

    friend SVector operator+(const SVector& x, const SVector& y);   // сума
    friend DType operator*(const SVector& x, const SVector& y); // добуток
};

class SMatrix {

private:
    UInt rows; // рядки
    UInt cols; // стовпці
    MType value;
    DType Det(UInt row, UInt col, DType result);

public: // нижче - матриця розміру 2х2, якщо користувач не вказав розмір матриці
    void Console_input(UInt rows = 2, UInt cols = 2, const char* inputType = "row");
    void Console_print(UInt check_const);

    void Txt_input(const char* file);
    void Txt_print(const char* file);

    SVector Matrix_x_Vector(SVector& x);                          // добуток матриці та вектора
    friend SMatrix operator+(const SMatrix& x, const SMatrix& y); // сума
    friend SMatrix operator*(const SMatrix& x, const SMatrix& y); // добуток матриць

    DType Det();   // визначник
    SMatrix Inv(); // обернена матриця
};
#endif
