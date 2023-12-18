#include "BitArray.h"
#include <algorithm>

// it's better to compile using g++

BitArray::BitArray()
{
    len = 0;
    bits = nullptr;
}

BitArray::~BitArray() {}
// If first variable is less than 0, bit array will be made such as BitArray()
// If second variable is less than zero or more than square of first variable array, value = 0
BitArray::BitArray(int size, unsigned long val)
{
    if ((size <= 0))
    {
        std::cout << "size is less than or equal to 0" << std::endl;
        len = 0;
        bits = nullptr;
        return;
    }
    //we need to ensure that the value is not negative. unsigned type, if given a negative value, overflows
    //and produces the value too big. By this condition we ensure that the given valuable is not negative
    //here we also ensure that the value can be represented as a bitarray of the desired size
    else if ((val > std::numeric_limits<unsigned long>::max() - std::pow(2, size)) || (val >= std::pow(2, size)))
    {
        std::cout << "value is either less than 0 or too big for the size of the array" << std::endl;
        len = 0;
        bits = nullptr;
        return;
    }

    len = size;
    bits = new bool[len];

    unsigned long SafeVal = val;
    int degree = 0;

    // Calculate the number of bits needed to represent 'val' in binary
    while ((val > 0) && (degree < len))
    {
        val /= 2;
        degree++;
    }

    int i = 0;
    // Fill the 'bits' array with the binary representation of 'SafeVal'
    if (degree != len)
        // if the size of bitarray is bigger than the needed length of the number
    {
        while (i < degree)
        {
            bits[(len - degree) + degree - i - 1] = (SafeVal % 2 != 0);
            i++;
            SafeVal = SafeVal / 2;
        }
        for (int i =0; i < len - degree; i++){
            bits[i]=0;
        }

    }
    else
    {
        // if just right
        while (i < degree)
        {
            bits[degree - i - 1] = (SafeVal % 2 != 0);
            i++;
            SafeVal = SafeVal / 2;
        }
    }

    for (int i = 0; i < len; i++)
    {
        std::cout << bits[i] << " ";
    }
    std::cout << std::endl;
}

BitArray::BitArray(const BitArray &b)
{
    len = b.len;
    bits = new bool[len];
    for (int i = 0; i < b.len; i++)
    {
        bits[i] = b.bits[i];
    }
}

//Sets bit index n to value val.
BitArray &BitArray::set(int index, bool val)
{
    if (index < 1 || index > len)
    {
        return *this;
    }
    bits[index - 1] = val;
    return *this;
}

// Fills array with true (1).
BitArray &BitArray::set()
{
    for (int i = 0; i < len; i++)
    {
        bits[i] = true;
    }
    return *this;
}

// Sets bit index n to value false (0).
BitArray &BitArray::reset(int index)
{
    if (index < 1 || index > len - 1)
    {
        return *this;
    }
    bits[index - 1] = false;
    return *this;
}

// Fills array with false(0).
BitArray &BitArray::reset()
{
    for (int i = 0; i < len; i++)
    {
        bits[i] = false;
    }
    return *this;
}

// true if the array contains a true bit.
bool BitArray::any() const
{
    for (int i = 0; i < len; i++)
    {
        if (bits[i])
        {
            return true;
        }
    }
    return false;
}

// true if every bit in array is false.
bool BitArray::none() const
{
    return !any();
}

// Returns true if length of array is 0
bool BitArray::empty() const
{
    return len == 0;
}

// Returns length of the array
int BitArray::size() const
{
    return len;
}

//counts number of true bits
int BitArray::count() const
{
    int amount = 0;
    for (int i = 0; i < len; i++)
    {
        if (bits[i])
        {
            amount++;
        }
    }
    return amount;
}

// Changes the size of the array. In case of expansion, new elements
// initialized with value.
void BitArray::resize(int n, bool value)
{
    if (n < 0)
    {
        return;
    }
    BitArray old(*this);
    delete[] bits;
    bits = new bool[n];
    len = n;

    if (this->size() > old.size())
    {
        for (int i = 0; i < old.size(); i++)
        {
            bits[n - old.size() + i] = old.bits[i];
        }
        for (int i = 0; i < n - old.size(); i++)
        {
            bits[i] = value;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            bits[i] = old.bits[old.size() - n + i];
        }
    }
}

// Exchanges the values of two bitarrays.
void BitArray::swap(BitArray &bits1, BitArray &bits2)
{
    if (bits1.len < bits2.len)
    {
        bits1.resize(bits2.len, false);
    }
    else
    {
        bits2.resize(bits1.len, false);
    }
    for (int i = 0; i < bits1.len; i++)
        if (bits1.bits[i] && !bits2.bits[i])
        {
            bits1.bits[i] = false;
            bits2.bits[i] = true;
        }
        else if (!bits1.bits[i] && bits2.bits[i])
        {
            bits1.bits[i] = true;
            bits2.bits[i] = false;
        }
}

// Adds a new bit to the end of the array. If necessary
// memory redistribution occurs.
void BitArray::push_back(bool val)
{
    this->resize(this->len + 1, val);
}

//Returns string representation of array.
std::string BitArray::to_string() const
{
    std::string output;
    for (int i = 0; i < len; i++)
    {
        if (bits[i])
        {
            output += "1";
        }
        else
        {
            output += "0";
        }
    }
    return output;
}

BitArray &BitArray::operator=(const BitArray &second)
{
    if (second.len != len)
    {
        return *this;
    }
    for (int i = 0; i < len; i++)
    {
        bits[i] = (bits[i] == second.bits[i]);
    }
    return *this;
}

// makes all bits perform the && operation with each bit of the array in pairs
BitArray &BitArray::operator&=(const BitArray &second)
{
    if (second.len != len)
    {
        return *this;
    }
    for (int i = 0; i < len; i++)
    {
            bits[i] = (bits[i] && second.bits[i]);
    }
    return *this;
}

// makes all bits perform the || operation with each bit of the array in pairs
BitArray &BitArray::operator|=(const BitArray &second)
{
    if (second.len != len)
    {
        return *this;
    }
    for (int i = 0; i < len; i++)
    {
        bits[i] = (bits[i] || second.bits[i]);
    }
    return *this;
}

// makes all bits perform the != operation with each bit of the array in pairs
BitArray &BitArray::operator^=(const BitArray &second)
{
    if (second.len != len)
    {
        return *this;
    }
    for (int i = 0; i < len; i++)
    {
        bits[i] = (bits[i] ^ second.bits[i]);
    }
    return *this;
}

// Bit inversion
BitArray BitArray::operator~() const
{
    BitArray a(this->size());
    for (int i = 0; i < len; i++)
    {
        a.bits[i] = !bits[i];
    }
    return a;
}

// Performs a bitwise shift to the left in a given variable
BitArray &BitArray::operator<<=(int val)
{
    if (val < 1)
    {
        return *this;
    }
    if (val >= len)
    {
        for (int i = 0; i < len; i++)
        {
            bits[i] = false;
        }
        return *this;
    }

    BitArray old(*this);
    delete[] bits;
    bits = new bool[len];

    for (int i = 0; i < len - val; i++)
    {
        bits[i] = old.bits[i + val];
    }
    for (int i = 0; i < val; i++)
    {
        bits[len - val + i] = old.bits[i];
    }
    return *this;
}

// Performs a bitwise shift to the right in a given variable
BitArray &BitArray::operator>>=(int val)
{
    if (val < 1)
    {
        return *this;
    }
    if (val >= len)
    {
        for (int i = 0; i < len; i++)
        {
            bits[i] = false;
        }
        return *this;
    }

    BitArray old(*this);
    delete[] bits;
    bits = new bool[len];

    for (int i = len; i > val; i--)
    {
        bits[i] = old.bits[i - val];
    }
    for (int i = 0; i < val; i++)
    {
        bits[i] = old.bits[len - val + i];
    }
    return *this;
}

// returns a variable with a bitwise shift to the left
BitArray BitArray::operator<<(int val) const
{
    BitArray output(*this);
    return output.operator<<=(val);
}

// returns a variable with a bitwise shift to the right
BitArray BitArray::operator>>(int val) const
{
    BitArray output(*this);
    return output.operator>>=(val);
}

// Returns the value of the bit at index i
bool BitArray::operator[](int val) const
{
    if (val < 1 || val > len)
    {
        return false;
    }
    return bits[val - 1];
}

// Clears bitarray
void BitArray::clear()
{
    len = 0;
    delete[] bits;
    bits = nullptr;
}

// returns true if arrays are equal and false if not
bool operator==(const BitArray &a, const BitArray &b)
{
    if (a.size() != b.size())
    {
        return false;
    }
    for (int i = 0; i < a.size(); i++)
    {
        if (a.operator[](i) != b.operator[](i))
        {
            return false;
        }
    }
    return true;
}

// returns false if arrays are equal and true if not
bool operator!=(const BitArray &a, const BitArray &b)
{
    return !(operator==(a, b));
}

// Performs the operation &&
BitArray operator&(const BitArray &a, const BitArray &b)
{
    BitArray c(a);
    return c.operator&=(b);
}

// Performs the operation ||
BitArray operator|(const BitArray &a, const BitArray &b)
{
    BitArray c(a);
    return c.operator|=(b);
}

// Performs the operation !=
BitArray operator^(const BitArray &a, const BitArray &b)
{
    BitArray c(a);
    return c.operator^=(b);
}
