/* Механіко-математичний факультет, 2 курс (2023/2024)
   Група "Комп'ютерна механіка", Назаренко Владислав, курсова робота за темою 1

   Даний файл описує методи класів SVector та SMatrix, структура яких представлена у файлі Project1_classes.h */

#include "Project1_classes.h"
#include "Project1_general.h"

using namespace std;

void SVector::Console_input() {
    printf("Enter vector: ");
    DType element; // вектор
    UInt a = 0;    // пробігає по координатам вектора в циклі

    while (true) {
        scanf_s("%lf", &element);
        SVector::value[{0, a}] = element;
        if (element == 0) {
            break; // умова переривання циклу еквівалентна натисканню Enter
        }
        a++;
    }
    SVector::length = a; // довжина рівна кінцевому значенню a
}

void SVector::Console_print() {
    for (UInt b = 0; b < SVector::length; b++) {
        DType element = SVector::value[{0, b}];
        if (element) {
            printf("%.1lf ", element); // виведення елементів з точністю 1 знак після крапки
        }
        else {
            printf("%u ", 0);
        }
    }
    printf("\n");
}

void SVector::Txt_input(const char* file) {
    ifstream f(file); // "input fstream"
    DType element;
    UInt c = 0;

    while (!f.eof()) { // eof = true тоді, коли пустий файл
        f >> element;
        if (element != 0) {
            SVector::value[{0, c}] = element;
        }
        c++;
    }
    SVector::length = c - 1;
    f.close();
}

void SVector::Txt_print(const char* file) {
    ofstream f(file); // "output fstream"
    for (UInt d = 0; d < SVector::length; d++) {
        DType element = SVector::value[{0, d}];
        f << element << " ";
    }
    f.close();
}

UInt SVector::Get_length() {
    return SVector::length;
}
MType SVector::Get_value() {
    return SVector::value;
}

SVector operator+(const SVector& x, const SVector& y) {

    SVector equivalent_vector;
    if (x.length == y.length) { // додавання відбувається лише при однаковій довжині векторів
        equivalent_vector.length = x.length;
        DType X, Y; // вектори x, y, equivalent_vector мають рівну довжину при рівних довжинах x та y

        for (UInt e = 0; e < x.length; e++) {
            X = 0;
            Y = 0; // // нижче - перевірка на існування компоненти з індексом у проміжку {0, e}
            if ((x.value.find({ 0, e }) != x.value.end())) { // дві окремі перевірки для кожного з векторів
                X = x.value.at({ 0, e });
            }
            if ((y.value.find({ 0, e }) != y.value.end())) {
                Y = y.value.at({ 0, e });
            }
            equivalent_vector.value[{0, e}] = X + Y;
        }
    }
    return equivalent_vector;
}

DType operator*(const SVector& x, const SVector& y) {
    DType value = 0;

    if (x.length == y.length) { // множення відбувається лише при однаковій довжині векторів
        for (UInt e = 0; e < x.length; e++) { // нижче - перевірка на існування компоненти з індексом у проміжку {0, e}
            if ((x.value.find({ 0, e }) != x.value.end()) && (y.value.find({ 0, e }) != y.value.end())) {
                value += x.value.at({ 0, e }) * y.value.at({ 0, e }); // скалярний добуток
            }
        }
    }
    return value; // результат множення (скалярний добуток)
}

void SMatrix::Console_input(UInt rows, UInt cols, const char* inputType) {
    SMatrix::rows = rows;
    SMatrix::cols = cols;
    if (inputType == "row") {
        printf("Enter matrix (ROW): ");

        DType element;
        for (UInt i = 0; i < cols; i++) {     // "зовнішнє" пробігання по стовпцях - заповнення рядка
            for (UInt j = 0; j < rows; j++) { // "внутрішнє" пробігання по рядках - заповнення стовпців
                scanf_s("%lf", &element);
                if (element != 0) {
                    SMatrix::value[{i, j}] = element;
                }
            }
        }
    }
    else if (inputType == "table") {
        printf("Enter matrix (TABLE): \n");

        DType element;
        for (UInt i = 0; i < cols; i++) {
            printf("Enter %u row: ", i + 1);  // оскільки численння i починається з 0 то додаємо 1, щоб
            for (UInt j = 0; j < rows; j++) { // вийшов запит на введення 1 рядка
                scanf_s("%lf", &element);
                if (element != 0) {
                    SMatrix::value[{i, j}] = element;
                }
            }
            cin.clear();
        }
    }
}

/* check_const - число, необхідне для перевірки чи змінна кількість елементів у матриці
   (кількість елементів повинна бути константою) */
void SMatrix::Console_print(UInt check_const) {
    if ((float)SMatrix::cols * SMatrix::rows / check_const != SMatrix::cols * SMatrix::rows / check_const) {
        throw logic_error("The matrix does not exist."); // throw - ініціація помилки (в нашому випадку тип помилки слід обрати logic_error)
    }

    UInt cols_i = 0; // для відстеження кількості виведених стовпців
    for (UInt i = 0; i < SMatrix::rows; i++) { // повторне пробігання по рядкам і стовпцям матриці
        for (UInt j = 0; j < SMatrix::cols; j++) {
            if (SMatrix::value.find({ i, j }) != SMatrix::value.end()) {
                printf("%.1lf ", SMatrix::value.at({ i, j }));
            }
            else {
                printf("%u ", 0); // виведення нуля при відсутності елемента в даній позиції
            }
            cols_i++;

            if ((float)cols_i / check_const == cols_i / check_const) {
                printf("\n"); // виведення матриці, якщо кількість стовпців ( -> елементів) не змінилася 
            }
        }
    }
}

void SMatrix::Txt_input(const char* file) {
    std::ifstream f(file); // "input fstream"
    DType element;
    UInt rows = 0, cols = 0;

    while (!f.eof()) {
        f >> element;
        if (element != 0) {
            SMatrix::value[{rows, cols}] = element;
        }
        cols++;

        char nextChar = f.peek();
        if (nextChar == '\n' || nextChar == EOF) { // Перехід на новий рядок у файлі
            rows++;
            cols = 0;
        }
    }
    SMatrix::rows = rows;
    SMatrix::cols = cols - 1;
    f.close();
}

void SMatrix::Txt_print(const char* file) {
    std::ofstream f(file); // "output fstream"
    for (UInt i = 0; i < SMatrix::rows; i++) {
        for (UInt j = 0; j < SMatrix::cols; j++) {
            DType element = SMatrix::value.at({ i, j });
            f << element << " ";
        }
        f << "\n"; // Перехід на новий рядок у файлі
    }
    f.close();
}

SVector SMatrix::Matrix_x_Vector(SVector& x) {
    if (SMatrix::cols != x.Get_length()) { // помилка при різній кількості стовпців у матриці та кількості елементів у векторі
        throw logic_error("The number of cols don't match the length of the vector.");
    }
    SVector result_product; // новий вектор, що містить операції множення

    for (UInt i = 0; i < SMatrix::rows; i++) { // цикл по рядках матриці
        DType prod = 0; // пробігання по добуткам елемента вектора на стовпець матриці
        for (UInt j = 0; i < SMatrix::cols; j++) { // цикл по стовпцях
            DType product1 = 0; // множники
            DType product2 = 0;

            if (SMatrix::value.find({ i, j }) != SMatrix::value.end()) { // вже стандартна перевірка на існування елементів,
                product1 = SMatrix::value.at({ i, j });                       // котрі виступають множниками el1, el2
            }
            if (x.Get_value().find({ 0, j }) != x.Get_value().end()) {
                product2 = x.Get_value().at({ 0, j });
            }
            prod += product1 * product2;
        }
        result_product.value.insert(MType::value_type({ 0, i }, prod));
    }
    return result_product;
}

SMatrix operator+(const SMatrix& x, const SMatrix& y) {
    if (x.cols != y.cols || x.rows != y.rows) { // задаємо додавання матриць виключно однакового розміру
        throw logic_error("Only matrices of the same size can be added.");
    }

    SMatrix Sum_result;
    Sum_result.rows = x.rows;
    Sum_result.cols = x.cols;
    for (UInt i = 0; i < x.rows; i++) {
        for (UInt j = 0; j < x.cols; j++) {
            DType element1 = 0;
            DType element2 = 0;
            if (x.value.find({ i, j }) != x.value.end()) {
                element1 = x.value.at({ i, j });
            }
            if (y.value.find({ i, j }) != y.value.end()) {
                element2 = y.value.at({ i, j });
            }
            Sum_result.value[{i, j}] = element1 + element2;
        }
    }
    return Sum_result;
}

SMatrix operator*(const SMatrix& x, const SMatrix& y) {
    if (x.cols != y.rows || x.rows != y.cols) {
        throw logic_error("Only matrices of the same size can be multiplied.");
    }

    SMatrix result_product;
    result_product.rows = x.rows;
    result_product.cols = y.cols;
    for (UInt k = 0; k < x.rows; k++) {
        for (UInt i = 0; i < x.rows; i++) {
            DType prod = 0;
            for (UInt j = 0; j < x.cols; j++) {
                DType element1 = 0;
                DType element2 = 0;
                if (x.value.find({ k, j }) != x.value.end()) {
                    element1 = x.value.at({ k, j });
                }
                if (y.value.find({ j, i }) != y.value.end()) {
                    element2 = y.value.at({ j, i });
                }
                prod += element1 * element2;
            }
            result_product.value[{k, i}] = prod;
        }
    }
    return result_product;
}
