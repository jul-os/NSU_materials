#ifndef BITARRAY_H
#define BITARRAY_H

#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <array>
#include <gtest/gtest.h>
#include "tests.h"

// В этой задаче для простоты не требуется делать контейнер шаблонным,
// но это вполне допускается по желанию студента.
class BitArray
{
  FRIEND_TEST(BitArray, EmptyCreate);
  FRIEND_TEST(BitArray, Create);
  FRIEND_TEST(BitArray, CopyCreate);
  FRIEND_TEST(BitArray, SetOne);
  FRIEND_TEST(BitArray, SetAll);
  FRIEND_TEST(BitArray, ResetOne);
  FRIEND_TEST(BitArray, ResetAll);
  FRIEND_TEST(BitArray, any);
  FRIEND_TEST(BitArray, none);
  FRIEND_TEST(BitArray, empty);
  FRIEND_TEST(BitArray, size);
  FRIEND_TEST(BitArray, count);
  FRIEND_TEST(BitArray, swap);
  FRIEND_TEST(BitArray, resize);
  FRIEND_TEST(BitArray, push_back);
  FRIEND_TEST(BitArray, to_string);
  FRIEND_TEST(BitArray, OperatorElement);
  FRIEND_TEST(BitArray, OperatorEqually);
  FRIEND_TEST(BitArray, OperatorAnd);
  FRIEND_TEST(BitArray, OperatorNotEqually);
  FRIEND_TEST(BitArray, OperatorOr);
  FRIEND_TEST(BitArray, OperatorInversion);
  FRIEND_TEST(BitArray, OperatorLShift);
  FRIEND_TEST(BitArray, OperatorRShift);
  FRIEND_TEST(BitArray, OperatorLShiftConst);
  FRIEND_TEST(BitArray, OperatorRShiftConst);
  FRIEND_TEST(BitArray, clear);

public:
  // Default constructor. Creates an empty class. Fills length value with 0, and bits with value NULL
  BitArray();
  // Copy constructor
  BitArray(const BitArray &);
  // Конструирует массив, хранящий заданное количество бит.
  // If first variable less then 0, bit array will be made such as BitArray()
  // If second varianle less then zero or more then square of first variable array will be made false
  explicit BitArray(int, unsigned long = 0);
  // explicit нужен чтобы убедиться, что нет неявных преобразований типа аргумента в тип класса

  // Destructor
  ~BitArray();

  // Обменивает значения двух битовых массивов.
  void swap(BitArray &, BitArray &);
  // Изменяет размер массива. В случае расширения, новые элементы
  // инициализируются значением value.
  void resize(int num_bits, bool value = false);
  // Очищает массив.
  void clear();
  // Добавляет новый бит в конец массива. В случае необходимости
  // происходит перераспределение памяти.
  void push_back(bool bit);

  // Битовые операции над массивами.
  // Работают только на массивах одинакового размера.
  // Обоснование реакции на параметр неверного размера входит в задачу.

  // next functions writes the value to the variable from which the function was called
  // if the arrays lengths are not equal, next functiona will not work
  BitArray &operator=(const BitArray &b);
  // makes all bits inperforms the && operation with each bit of the array in pairs
  BitArray &operator&=(const BitArray &b);
  // makes all bits inperforms the || operation with each bit of the array in pairs
  BitArray &operator|=(const BitArray &b);
  // makes all bits inperforms the != operation with each bit of the array in pairs
  BitArray &operator^=(const BitArray &b);

  // Битовый сдвиг с заполнением нулями.
  // Performs a bitwise shift to the left in a given variable
  BitArray &operator<<=(int n);
  // Performs a bitwise shift to the right in a given variable
  BitArray &operator>>=(int n);
  // returns a variable with a bitwise shift to the left
  BitArray operator<<(int n) const;
  // returns a variable with a bitwise shift to the right
  BitArray operator>>(int n) const;

  // Устанавливает бит с индексом n в значение val.
  // If  first variable not included in the array value this function will not work
  // if second value is empty functuon will make it true
  BitArray &set(int n, bool val = true);
  // Заполняет массив истиной (1).
  BitArray &set();

  // Устанавливает бит с индексом n в значение false (0).
  BitArray &reset(int n);
  // Заполняет массив ложью.
  // If  first variable not included in the array value this function will not work
  BitArray &reset();

  // true, если массив содержит истинный бит.
  bool any() const;
  // true, если все биты массива ложны.
  bool none() const;
  // Подсчитывает количество единичных бит.
  int count() const;
  // Returns length of the array
  int size() const;
  // Returns true if length of array is 0
  bool empty() const;

  // Битовая инверсия
  BitArray operator~() const;
  // Возвращает значение бита по индексу i.
  // if variable not included in the array function will return false
  bool operator[](int i) const;

  // Возвращает строковое представление массива.
  std::string to_string() const;

private:
  bool *bits;
  int len;
};
// returns true if arrays are equal and false if not
bool operator==(const BitArray &a, const BitArray &b);
// returns false if arrays are equal and true if not
bool operator!=(const BitArray &a, const BitArray &b);

// the following functions return a BitArray with the operation performed on the specified variables
// Performs the operation &&
BitArray operator&(const BitArray &b1, const BitArray &b2);
// Performs the operation ||
BitArray operator|(const BitArray &b1, const BitArray &b2);
// Performs the operation !=
BitArray operator^(const BitArray &b1, const BitArray &b2);

#endif
