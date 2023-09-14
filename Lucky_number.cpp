#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
using namespace std;

class Unlucky_Number_Exception : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Сгенерировано 5-ти или 7-ми значное число.";
    }
};

int generate_Random_Number()
{
    int num_Digits = 6; // Генерируем только 6-значные числа
    int number = 0;

    for (int i = 0; i < num_Digits; ++i)
    {
        int digit = rand() % 10;
        number = number * 10 + digit;
    }

    return number;
}

bool Lucky_Number(int number)
{
    int first_Half = number / 1000;
    int second_Half = number % 1000;
    int sum_First_Half = 0;
    int sum_Second_Half = 0;

    while (first_Half > 0)
    {
        sum_First_Half += first_Half % 10;
        first_Half /= 10;
    }

    while (second_Half > 0)
    {
        sum_Second_Half += second_Half % 10;
        second_Half /= 10;
    }

    return sum_First_Half == sum_Second_Half;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    try
    {
        srand(static_cast<unsigned>(time(nullptr)));

        char choice;

        do
        {
            cout << "Нажмите Enter для генерации числа (6 цифр) или 0 для выхода..." << endl;
            choice = cin.get();

            if (choice == '\n')
            {
                int number = generate_Random_Number();
                cout << "Сгенерированное число: " << number << endl;

                if (number < 100000 || number >= 1000000)
                {
                    throw Unlucky_Number_Exception();
                }

                if (Lucky_Number(number))
                {
                    cout << "Число " << number << " является счастливым!" << endl;
                }
                else
                {
                    cout << "Число " << number << " не является счастливым." << endl;
                }
            }
        } while (choice != '0');
    }
    catch (const Unlucky_Number_Exception& e)
    {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
