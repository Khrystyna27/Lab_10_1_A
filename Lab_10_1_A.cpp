// Lab_10_1_A.cpp
// < Прізвище Ім’я >
// Лабораторна робота № 10.1.
// Послідовний пошук в масиві структур
// Варіант 30, рівень A
// Сформувати динамічний масив структур, що містять інформацію про студентів:
// прізвище, курс, спеціальність, оцінки з фізики, математики, інформатики.
// Вивести масив у вигляді таблиці та виконати послідовний пошук:
//   1. обчислити кількість оцінок «добре» (4) з кожного предмету;
//   2. обчислити процент студентів, які отримали і з фізики, і з математики оцінку «5».
 
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
 
enum Specialnist { KN, IN, ME, FI, TN };
const string specStr[] = { "Комп’ютерні науки", "Інформатика",
                          "Математика та економіка", "Фізика та інформатика",
                          "Трудове навчання" };
 
struct Student
{
   string       prizv;
   unsigned     kurs;
   Specialnist  spec;
   int          fizyka;
   int          matematyka;
   int          informatyka;
};
 
void Create(Student *p, const int N);
void Print(Student *p, const int N);
void CountGood(Student *p, const int N, int &fiz, int &mat, int &inf);
double PercentFiveFive(Student *p, const int N);
 
#ifndef UNIT_TEST           // під час unit-тестування main не компілюється
int main()
{
   int N;
   cout << "Введіть кількість студентів N: "; cin >> N;
   Student *p = new Student[N];
   int fiz, mat, inf;
   double proc;
 
   Create(p, N);
   Print(p, N);
 
   CountGood(p, N, fiz, mat, inf);
   cout << "Кількість оцінок «добре» (4):" << endl;
   cout << "    з фізики:      " << fiz << endl;
   cout << "    з математики:  " << mat << endl;
   cout << "    з інформатики: " << inf << endl << endl;
   proc = PercentFiveFive(p, N);
   cout << "Процент студентів, які отримали і з фізики, і з математики оцінку «5»:" << endl;
   cout << fixed << setprecision(2) << proc << "%" << endl;
 
   delete[] p;
   return 0;
}
#endif
 
// Повертає рядок s, доповнений пробілами до ширини width (кількість символів UTF-8,
// а не байтів – щоб таблиця з кирилицею була вирівняна на macOS/Linux)
string Cell(const string &s, const int width, const bool leftAlign = true)
{
   int len = 0;
   for (unsigned char c : s)
       if ((c & 0xC0) != 0x80)        // рахуємо лише перші байти символів
           len++;
   string pad(len < width ? width - len : 0, ' ');
   return leftAlign ? s + pad : pad + s;
}
 
void Create(Student *p, const int N)
{
   int spec;
   for (int i = 0; i < N; i++)
   {
       cout << "Студент № " << i + 1 << ":" << endl;
       cin.get();  // очищуємо буфер клавіатури – бо залишаються символи
       cin.sync();  // "кінець рядка", які не дають ввести наступний літерний рядок
       cout << "    прізвище: "; getline(cin, p[i].prizv);
       cout << "    курс: "; cin >> p[i].kurs;
       cout << "    спеціальність (0 - Комп’ютерні науки, 1 - Інформатика," << endl;
       cout << "                   2 - Математика та економіка, 3 - Фізика та інформатика," << endl;
       cout << "                   4 - Трудове навчання): ";
       cin >> spec;
       p[i].spec = (Specialnist)spec;
       cout << "    оцінка з фізики: "; cin >> p[i].fizyka;
       cout << "    оцінка з математики: "; cin >> p[i].matematyka;
       cout << "    оцінка з інформатики: "; cin >> p[i].informatyka;
       cout << endl;
   }
}
 
void Print(Student *p, const int N)
{
   cout << "Таблиця студентів" << endl;
   cout << string(83, '=') << endl;
   cout << "| " << Cell("№", 3) << " | " << Cell("Прізвище", 12) << " | " << Cell("Курс", 4)
        << " | " << Cell("Спеціальність", 23) << " | " << Cell("Фізика", 6)
        << " | " << Cell("Матем.", 6) << " | " << Cell("Інформ.", 7) << " |" << endl;
   cout << string(83, '-') << endl;
   for (int i = 0; i < N; i++)
   {
       cout << "| " << setw(3) << right << i + 1
            << " | " << Cell(p[i].prizv, 12)
            << " | " << setw(4) << right << p[i].kurs
            << " | " << Cell(specStr[p[i].spec], 23)
            << " | " << setw(6) << right << p[i].fizyka
            << " | " << setw(6) << right << p[i].matematyka
            << " | " << setw(7) << right << p[i].informatyka << " |" << endl;
   }
   cout << string(83, '=') << endl;
   cout << endl;
}
 
// Обчислює кількість оцінок «добре» (4) з кожного предмету;
// результати повертає через параметри-посилання
void CountGood(Student *p, const int N, int &fiz, int &mat, int &inf)
{
   fiz = 0; mat = 0; inf = 0;
   for (int i = 0; i < N; i++)
   {
       if (p[i].fizyka == 4)      fiz++;
       if (p[i].matematyka == 4)  mat++;
       if (p[i].informatyka == 4) inf++;
   }
}
 
// Обчислює процент студентів, які отримали і з фізики, і з математики оцінку «5»
double PercentFiveFive(Student *p, const int N)
{
   int k = 0;
   for (int i = 0; i < N; i++)
       if (p[i].fizyka == 5 && p[i].matematyka == 5)
           k++;
   return 100.0 * k / N;
}
