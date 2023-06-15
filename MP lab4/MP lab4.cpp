// GeneratorRandom.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>


/*!
    \brief Класс, первый генератор
*/
class Random1
{
    size_t now; ///< Текущее число

public:
    /*!
        \brief Конструктор генератора
        \param[in] a начальное зерно генератора
    */
    Random1(size_t a)
    {
        now = a;
    }

    /*!
        Получение следующего псевдослучайного числа
        \param[in] mod Число, меньше которого генерируются числа
        \return Возращает случаное целое число в диапазоне [0, mod)
    */
    unsigned int Next(unsigned int mod)
    {
        now = std::hash<long long>()(now);

        return now % mod;
    }
};


/*!
    \brief Класс, первый генератор
*/
class Random2
{
    size_t now; ///< Текущее число

public:
    /*!
        \brief Конструктор генератора
        \param[in] a начальное зерно генератора
    */
    Random2(size_t a)
    {
        now = a;
    }

    /*!
        Получение следующего псевдослучайного числа
        \param[in] mod Число, меньше которого генерируются числа
        \return Возращает случаное целое число в диапазоне [0, mod)
    */
    unsigned int Next(unsigned int mod)
    {
        now = std::hash<unsigned int>()(Line(now));

        return now % mod;
    }

    /*!
        Линейный конгруэнтный метод
        \param[in] a Число, для которого ищется следующее в последовательности
        \return Возвращает следующее число в последовтельности для линейного конгруэнтного метода
    */
    unsigned int Line(unsigned int a)
    {
        return (22695477 * a + 1) % 4294967295;
    }
};

int main()
{
    int sizes[10] = { 1000, 10000, 50000, 100000, 200000, 300000, 400000, 500000, 750000, 1000000 };

    for (int size : sizes)
    {
        Random1 rnd = Random1(8541282);
        std::ofstream out;
        char filename[80];
        memset(filename, 0, 80);
        sprintf_s(filename, "%s%d%s", "random1\\data_", size, ".csv");

        out.open(filename);

        auto begin = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size; i++)
        {
            out << rnd.Next(50000) << std::endl;
        }

        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Generation of " << size << " elements with 1 generator " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

        out.close();
    }

    for (int size : sizes)
    {
        Random2 rnd = Random2(8541282);
        std::ofstream out;
        char filename[80];
        memset(filename, 0, 80);
        sprintf_s(filename, "%s%d%s", "random2\\data_", size, ".csv");

        out.open(filename);

        auto begin = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size; i++)
        {
            out << rnd.Next(50000) << std::endl;
        }

        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Generation of " << size << " elements with 2 generator " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;


        out.close();
    }

    for (int size : sizes)
    {
        std::ofstream out;
        char filename[80];
        memset(filename, 0, 80);
        sprintf_s(filename, "%s%d%s", "random_auto\\data_", size, ".csv");

        out.open(filename);

        auto begin = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < size; i++)
        {
            out << (int)(rand() / RAND_MAX * 50000) << std::endl;
        }

        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Generation of " << size << " elements with default generator " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;


        out.close();
    }
}
