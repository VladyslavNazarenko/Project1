/* Механіко-математичний факультет, 2 курс (2023/2024)
   Група "Комп'ютерна механіка", Назаренко Владислав, курсова робота за темою 1

   Даний файл є головною програмою, яка тестує усі написані методи класів SVector та SMatrix */

#include "Project1_classes.h"
#include "Project1_general.h"
#include "Project1.cpp"

int main() {
    SVector Vector1, Vector2;

    Vector1.Console_input();
    Vector1.Console_print();
    cout << Vector1.Get_length();

    Vector2.Txt_input("test.txt");
    Vector2.Txt_print("test.txt");

    SVector Vector3 = Vector1 + Vector2;
    DType x = Vector1 * Vector2;
    cout << x;


    SMatrix Matrix1, Matrix2;

    Matrix1.Console_input();
    Matrix1.Console_print(2);
    Matrix2.Txt_input("test.txt");
    Matrix2.Txt_print("test.txt");

    Matrix1.Matrix_x_Vector(Vector1);
    SMatrix Matrix3 = Matrix1 + Matrix2;
    SMatrix Matrix4 = Matrix1 * Matrix2;
}
