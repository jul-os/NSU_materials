//what's inside the functions
#include "naming.h"

BitArray::BitArray() {
	len = 0;
	bits = NULL;
}

BitArray::~BitArray(){}


  // If first variable is less than 0, bit array will be made such as BitArray()
  // If second variable is less than zero or more than square of first variable array, value = 0
BitArray::BitArray(int size, unsigned long val) {
	if ((size <= 0)) {
		len = 0;
		bits = NULL;
		return;
	}
	else if ((val < 0) || (val > std::pow(2, size)))
		val = 0;
	len = size;
	bits = new bool[len];

	unsigned long SafeVal = val;
	int degree = 0;
	while ((val > 0) && (degree < len)) {
		val /= 2;
		degree++;
	}

	int i = 0;
	while(i < degree){
		if (SafeVal % 2 == 0)
			bits[degree - i - 1] = false;
		i++;
		SafeVal = SafeVal / 2;
	}
	if (degree != len)
		for (int i = degree; i < len; i++)
			bits[i] = false;
}

BitArray::BitArray(const BitArray& b) {
	len = b.len;
	bits = new bool[len];
	for (int i = 0; i < b.len; i++)
		bits[i] = b.bits[i];
}

BitArray& BitArray::set(int index, bool val) {
	if (index < 1 || index > len)
		return *this;
	bits[index - 1] = val;
	return *this;
}

BitArray& BitArray::set() {
	for (int i = 0; i < len; i++)
		bits[i] = true;
	return *this;
}

BitArray& BitArray::reset(int index) {
	if (index < 1 || index > len - 1)
		return *this;
	bits[index - 1] = false;
	return *this;
}

BitArray& BitArray::reset() {
	for (int i = 0; i < len; i++)
		bits[i] = false;
	return *this;
}

bool BitArray::any() const {
	for (int i = 0; i < len; i++)
		if (bits[i]) 
			return true;
	return false;
}

bool BitArray::none() const {
	return !any();
}

bool BitArray::empty() const {
	return len == 0;
}

int BitArray::size() const {
	return len;
}

int BitArray::count() const {
	int amount = 0;
	for (int i = 0; i < len; i++)
		if (bits[i])
			amount++;
	return amount;
}

void BitArray::resize(int n, bool value) {
	if (n < 0)
		return;

	BitArray old(*this);
	delete[] bits;
	bits = new bool[n];
	len = n;

	if (this->size() > old.size()) {
		for (int i = 0; i < old.size(); i++)
			bits[i] = old.bits[i];
		for (int i = old.size(); i < n; i++)
			bits[i] = value;
	}
	else {
		for (int i = 0; i < n; i++)
			bits[i] = old.bits[i];

	}
}

void BitArray::swap(BitArray& bits1, BitArray& bits2) {
	if (bits1.len < bits2.len)
		bits1.resize(bits2.len, false);
	else
		bits2.resize(bits1.len, false);
	for (int i = 0; i < bits1.len; i++)
		if (bits1.bits[i] && !bits2.bits[i]){
			bits1.bits[i] = false;
			bits2.bits[i] = true;
		}
		else if (!bits1.bits[i] && bits2.bits[i]) {
			bits1.bits[i] = true;
			bits2.bits[i] = false;
		}
}



void BitArray::push_back(bool val) {
	this->resize(this->len + 1, val);
}

std::string BitArray::to_string() const {
	std::string output;
	for (int i = 0; i < len; i++)
		if (bits[i])
			output += "1";
		else
			output += "0";
	return output;
}

BitArray& BitArray::operator=(const BitArray& second) {
	if (second.len != len)
		return*this;
	for (int i = 0; i < len; i++)
		if (bits[i] == second.bits[i])
			bits[i] = true;
		else
			bits[i] = false;
	return *this;
}

BitArray& BitArray::operator&=(const BitArray& second) {
	if (second.len != len)
		return*this;
	for (int i = 0; i < len; i++)
		if (bits[i] && second.bits[i])
			bits[i] = true;
		else
			bits[i] = false;
	return *this;
}

BitArray& BitArray::operator|=(const BitArray& second) {
	if (second.len != len)
		return*this;
	for (int i = 0; i < len; i++)
		if (bits[i] || second.bits[i])
			bits[i] = true;
		else
			bits[i] = false;
	return *this;
}

BitArray& BitArray::operator^=(const BitArray& second) {
	if (second.len != len)
		return*this;
	for (int i = 0; i < len; i++)
		if (bits[i] ^ second.bits[i])
			bits[i] = true;
		else
			bits[i] = false;
	return *this;
}
BitArray BitArray::operator~() const {
	BitArray a(this->size());
	for (int i = 0; i < len; i++)
			a.bits[i] = !bits[i];
	return a;
}

BitArray& BitArray::operator<<=(int val) {
	if (val < 1)
		return *this;
	if (val >= len) {
		for (int i = 0; i < len; i++)
			bits[i] = false;
		return *this;
	}

	for (int i = 0; i < len - val; i++)
		bits[i] = bits[i + val];
	for (int i = len - val; i < len; i++)
		bits[i] = false;
	return *this;
}

BitArray& BitArray::operator>>=(int val) {
	if (val < 1)
		return *this;
	if (val >= len) {
		for (int i = 0; i < len; i++)
			bits[i] = false;
		return *this;
	}

	for (int i = len; i > val; i--)
		bits[i] = bits[i - val];
	for (int i = 0; i < val; i++)
		bits[i] = false;
	return *this;
}

BitArray BitArray::operator<<(int val) const {
	BitArray output(*this);
	return output.operator<<=(val);
}

BitArray BitArray::operator>>(int val) const {
	BitArray output(*this);
	return output.operator>>=(val);
}

bool BitArray::operator[](int val) const {
	if (val < 0 || val > len)
		return false;
	return bits[val - 1];
}

void BitArray::clear() {
	len = 0;
	bits = NULL;
}

bool operator==(const BitArray& a, const BitArray& b) {
	if (a.size() != b.size())
		return false;
	for (int i = 0; i < a.size(); i++)
		if (a.operator[](i) != b.operator[](i))
			return false;
	return true;
}

bool operator!=(const BitArray& a, const BitArray& b) {
	return !(operator==(a, b));
}

BitArray operator&(const BitArray& a, const BitArray& b) {
	BitArray c(a);
	return c.operator&=(b);
}

BitArray operator|(const BitArray& a, const BitArray& b) {
	BitArray c(a);
	return c.operator|=(b);
}

BitArray operator^(const BitArray& a, const BitArray& b) {
	BitArray c(a);
	return c.operator^=(b);
}


