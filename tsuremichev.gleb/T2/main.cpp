#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <cmath>
#include "dataStruct.hpp"

// Вспомогательная функция для сравнения структур (компаратор)
bool compareDataStruct(
    const DataStruct &a,
    const DataStruct &b)
{
  const double EPS = 1e-9;

  double absA1 = std::abs(a.key1);
  double absB1 = std::abs(b.key1);

  // 1. Сравнение по абсолютному значению key1
  if (std::abs(absA1 - absB1) > EPS)
  {
    return absA1 < absB1;
  }

  // 2. Сравнение по key2
  if (std::abs(a.key2 - b.key2) > EPS)
  {
    return a.key2 < b.key2;
  }

  // 3. Сравнение по длине строки key3
  return a.key3.length() < b.key3.length();
}

int main()
{
  std::vector<DataStruct> data;

  // Настраиваем итераторы для чтения из консоли (std::cin)
  std::istream_iterator<DataStruct> input_begin(std::cin);
  std::istream_iterator<DataStruct> input_end;

  // Читаем данные до конца ввода
  std::copy(
      input_begin,
      input_end,
      std::back_inserter(data));

  // Проверяем на критические ошибки парсинга
  if (!std::cin.eof() && std::cin.fail())
  {
    std::cerr << "Parsing error occurred!\n";
    return 1;
  }

  // Сортируем данные с использованием нашего компаратора
  std::sort(
      data.begin(),
      data.end(),
      compareDataStruct);

  // Выводим результат в консоль
  std::ostream_iterator<DataStruct> output_iterator(
      std::cout,
      "\n");
  std::copy(
      data.begin(),
      data.end(),
      output_iterator);

  return 0;
}
