#ifndef UNTITLED1_BITARRAY_H
#define UNTITLED1_BITARRAY_H

#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <array>
#include <gtest/gtest.h>
#include "tests.h"

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
    // Constructs an array that stores the specified number of bits
    // If first variable is less than 0, bit array will be made such as BitArray()
    // If second variable is less than zero or more than square of first variable array, value = 0
    explicit BitArray(int, unsigned long = 0);

    // Destructor
    ~BitArray();

    // Exchanges the values of two bitarrays.
    void swap(BitArray &, BitArray &);
    // Changes the size of the array. In case of expansion, new elements
    // initialized with value.
    void resize(int num_bits, bool value = false);
    // Clears bitarray
    void clear();
    // Adds a new bit to the end of the array. If necessary
    // memory redistribution occurs.
    void push_back(bool bit);

    // Bitwise operations on arrays.
    // Work only on arrays of the same size.
    // Justification of the reaction to an incorrectly sized parameter is part of the task.

    // next function writes the value to the variable from which the function was called
    // if the arrays lengths are not equal, next functiona will not work
    BitArray &operator=(const BitArray &b);
    // makes all bits perform the && operation with each bit of the array in pairs
    BitArray &operator&=(const BitArray &b);
    // makes all bits perform the || operation with each bit of the array in pairs
    BitArray &operator|=(const BitArray &b);
    // makes all bits perform the != operation with each bit of the array in pairs
    BitArray &operator^=(const BitArray &b);

    // Performs a bitwise shift to the left in a given variable
    BitArray &operator<<=(int n);
    // Performs a bitwise shift to the right in a given variable
    BitArray &operator>>=(int n);
    // returns a variable with a bitwise shift to the left
    BitArray operator<<(int n) const;
    // returns a variable with a bitwise shift to the right
    BitArray operator>>(int n) const;

    // Sets bit index n to value val.
    // If  first variable not included in the array value this function will not work
    // if second value is empty functuon will make it true
    BitArray &set(int n, bool val = true);
    // Fills array with true (1).
    BitArray &set();

    // Sets bit index n to value false (0).
    BitArray &reset(int n);
    // Fills array with false(0).
    // If  first variable not included in the array value this function will not work
    BitArray &reset();

    // true if the array contains a true bit.
    bool any() const;
    // true if every bit in array is false.
    bool none() const;
    //counts number of true bits
    int count() const;
    // Returns length of the array
    int size() const;
    // Returns true if length of array is 0
    bool empty() const;

    // Bit inversion
    BitArray operator~() const;
    // Returns the value of the bit at index i.
    // if variable not included in the array function will return false
    bool operator[](int i) const;

    //Returns string representation of array.
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


#endif //UNTITLED1_BITARRAY_H
