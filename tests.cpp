#include "naming.h"
#include <gtest/gtest.h>


TEST(BitArray, EmptyCreate) {
	BitArray BA;
	EXPECT_EQ(0, BA.len) << "length != 0";
	EXPECT_EQ(NULL, BA.bits) << "length != 0";
};

TEST(BitArray, Create) {
	BitArray BA1(10);
	EXPECT_EQ(10, BA1.len) << "test of len";
	for (int i = 0; i < 10; i++)
		EXPECT_FALSE(BA1.bits[i]) << "Test with no value";

	BitArray BA2(2, 1);
	bool b[2]{ true, false };
	for (int i = 0; i < BA2.len; i++)
		if (b[i])
			EXPECT_TRUE(BA2.bits[i]) << "little test";
		else
			EXPECT_FALSE(BA2.bits[i]) << "little test";


	bool a[15]{ true, true, true, true, true, true, false, false, true, true, true, false, false, false, false };
	BitArray BA3(15, 2023);
	EXPECT_EQ(15, BA3.len);
	for (int i = 0; i < BA3.len; i++)
		for (int i = 0; i < BA3.len; i++)
			if (a[i])
				EXPECT_TRUE(BA3.bits[i]) << "a little bit big test  ";
			else
				EXPECT_FALSE(BA3.bits[i]) << "a little bit big test  ";

	
	BitArray BA4(-1, 2023);
	EXPECT_EQ(NULL, BA4.bits) << "test of negative len";
	EXPECT_EQ(0 , BA4.len) << "test of negative len";

	BitArray BA5(5, -1);
	EXPECT_EQ(5, BA5.len) << "test with negative val";
	for (int i = 0; i < BA5.len; i++)
		EXPECT_FALSE(BA5.bits[i]);

	BitArray BA6(5, 99999);
	EXPECT_EQ(5, BA6.len) << "test with extra val";
	for (int i = 0; i < BA6.len; i++)
		EXPECT_FALSE(BA6.bits[i]);
};

TEST(BitArray, CopyCreate) {
	BitArray BA1(10, 553);
	BitArray BA2(BA1);
	EXPECT_EQ(BA1, BA2) << "copy test";

	BitArray BA3;
	BitArray BA4(BA3);
	EXPECT_EQ(BA3, BA4) << "empty copy test";
};

TEST(BitArray, SetOne) {
	BitArray BA1(15, 2023);
	bool a[15]{ true, true, true, true, true, true, false, false, true, true, true, false, false, false, true };
	BA1.set(15);
	for (int i = 0; i < BA1.len; i++)
		if (a[i])
			EXPECT_TRUE(BA1.bits[i]) << "set true test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "set true test";

	BA1.set(16, true);
	for (int i = 0; i < BA1.len; i++)
		if (a[i])
			EXPECT_TRUE(BA1.bits[i]) << "more than len set test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "more than len set test";

	BA1.set(-1, true);
	for (int i = 0; i < BA1.len; i++)
		if (a[i])
			EXPECT_TRUE(BA1.bits[i]) << "negative adress set test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "negative adress set test";

	a[0] = false;
	BA1.set(1, false);
	for (int i = 0; i < BA1.len; i++)
		if (a[i])
			EXPECT_TRUE(BA1.bits[i]) << "set negative test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "set negative test";

};

TEST(BitArray, SetAll) {
	BitArray BA1(15, 2023);
	BA1.set();
	for (int i = 0; i < BA1.len; i++)
		EXPECT_TRUE(BA1[i]) << "SetAll test";

	BitArray BA2;
	BA2.set();
	EXPECT_EQ(NULL, BA2.bits) << "SetAll empty test";
	EXPECT_EQ(BA2.len, 0) << "SetAll empty test";
};

TEST(BitArray, ResetOne) {
	BitArray BA1(15, 2023);
	bool a[15]{ false, true, true, true, true, true, false, false, true, true, true, false, false, false, false };
	BA1.reset(1);
	for (int i = 0; i < BA1.len; i++)
		if (a[i])
			EXPECT_TRUE(BA1.bits[i]) << "reset true test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "reset true test";

	BA1.reset(16);
	for (int i = 0; i < BA1.len; i++)
		if (a[i])
			EXPECT_TRUE(BA1.bits[i]) << "more than len reset test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "more than len reset test";

	BA1.reset(-1);
	for (int i = 0; i < BA1.len; i++)
		if (a[i])
			EXPECT_TRUE(BA1.bits[i]) << "negative adress reset test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "negative adress reset test";
};

TEST(BitArray, ResetAll) {
	BitArray BA1(99, 34977870470);
	BA1.reset();
	for (int i = 0; i < BA1.len; i++)
		EXPECT_FALSE(BA1.bits[i]);

	BitArray BA2;
	BA2.reset();
	EXPECT_EQ(NULL, BA2.bits) << "ResetAll empty test";
	EXPECT_EQ(BA2.len, 0) << "ResetAll empty test";
};

TEST(BitArray, any) {
	BitArray BA1(15, 2023);
	EXPECT_TRUE(BA1.any()) << "true any test";

	BitArray BA2(15);
	EXPECT_FALSE(BA2.any()) << "false any test";

	BitArray BA3;
	EXPECT_FALSE(BA3.any()) << "empty any test";
};

TEST(BitArray, none) {

	BitArray BA1(15, 2023);
	EXPECT_FALSE(BA1.none()) << "false none test";

	BitArray BA2(15);
	EXPECT_TRUE(BA2.none()) << "true none test";

	BitArray BA3;
	EXPECT_TRUE(BA3.none()) << "empty none test";
};

TEST(BitArray, empty) {
	BitArray BA1;
	EXPECT_TRUE(BA1.empty()) << "true empty test";

	BitArray BA2(15, 2023);
	EXPECT_FALSE(BA2.empty()) << "false empty test";
};

TEST(BitArray, size) {
	BitArray BA1(15, 2023);
	EXPECT_EQ(BA1.len, BA1.size()) << "size test";

	BitArray BA2;
	EXPECT_EQ(BA2.len, BA2.size()) << "empty size test";
};

TEST(BitArray, count) {
	BitArray BA1(15, 2023);
	EXPECT_EQ(9, BA1.count()) << "count test";

	BitArray BA2;
	EXPECT_EQ(0, BA2.count()) << "empty count test";
};

TEST(BitArray, clear) {
	BitArray BA(10, 2023);
	BA.clear();
	EXPECT_EQ(0, BA.len) << "len clear test";
	EXPECT_EQ(NULL, BA.bits) << "bits clear test";
};

TEST(BitArray, resize) {
	BitArray BA1(15, 2023), BA2(20, 2023), BA3 (8, 252);
	BA1.resize(20, false);
	EXPECT_EQ(BA1.len, BA2.len) << "increase resize len test";
	for (int i = 0; i < BA2.len; i++)
		if (BA2.bits[i])
			EXPECT_TRUE(BA1.bits[i]) << "increase resize bit test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "increase resize bit test";

	BA1.resize(8, false);
	EXPECT_EQ(BA1.len, BA3.len) << "decrease resize len test";
	for (int i = 0; i < BA3.len; i++)
		if (BA3.bits[i])
			EXPECT_TRUE(BA1.bits[i]) << "decrease resize bit test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "decrease resize bit test";

};

TEST(BitArray, swap) {
	BitArray BA1(15, 2023), BA2(BA1), BA3(20, 2004), BA4(BA3);
	BA1.swap(BA1, BA3);
	for (int i = 0; i < BA2.len; i++)
		if (BA2.bits[i])
			EXPECT_TRUE(BA3.bits[i]) << "swap test";
		else
			EXPECT_FALSE(BA3.bits[i]) << "swap test";

	for (int i = 0; i < BA4.len; i++)
		if (BA4.bits[i])
			EXPECT_TRUE(BA1.bits[i]) << "swap test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "swap test";
};

TEST(BitArray, push_back) {
	BitArray BA1(15, 2023), BA2(16, 34791);
	BA1.push_back(true);
	EXPECT_EQ(BA1.len, BA2.len) << "push_back len test";
	for (int i = 0; i < BA2.len; i++)
		if (BA2.bits[i])
			EXPECT_TRUE(BA2.bits[i]) << "push_back bits test";
		else
			EXPECT_FALSE(BA2.bits[i]) << "push_back bits test";
};

TEST(BitArray, to_string) {
	BitArray BA1(15, 2023), BA2;
	EXPECT_EQ("111111001110000", BA1.to_string()) << "to_string test";
	EXPECT_EQ("", BA2.to_string()) << "empty to_string test";
};

TEST(BitArray, OperatorElement) {
	BitArray BA(15, 2023);
	EXPECT_TRUE(BA.operator[](1)) << "true operator[] test";
	EXPECT_FALSE(BA.operator[](7)) << "false operator[] test";
	EXPECT_FALSE(BA.operator[](-1)) << "negative val operator[] test";
	EXPECT_FALSE(BA.operator[](16)) << "extra val operator[] test";
};

TEST(BitArray, OperatorEqually) {
	BitArray BA1(15, 2023), BA2(15, 20319), BA3(15,1261);
	BA1.operator=(BA2);
	for (int i = 0; i < BA3.len; i++)
		if (BA3.bits[i])
			EXPECT_TRUE(BA1.bits[i]) << "operator= test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "operator= test";
};

TEST(BitArray, OperatorAnd) {
	BitArray BA1(15, 2023), BA2(15, 20319), BA3(15, 1253);
	BA1.operator&=(BA2);
	for (int i = 0; i < BA3.len; i++)
		if (BA3.bits[i])
			EXPECT_TRUE(BA1.bits[i]) << "operator&= test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "operator&= test";
};

TEST(BitArray, OperatorNotEqually) {
	BitArray BA1(15, 2023), BA2(15, 20319), BA3(15, 28975);
	BA3.reset(1);
	BA1.operator^=(BA2);
	for (int i = 0; i < BA3.len; i++)
		if (BA3.bits[i])
			EXPECT_TRUE(BA1.bits[i]) << "operator^= test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "operator^= test";
};

TEST(BitArray, OperatorOr) {
	BitArray BA1(15, 2023), BA2(15, 20319), BA3(15, 32639);
	BA1.operator|=(BA2);
	for (int i = 0; i < BA3.len; i++)
		if (BA3.bits[i])
			EXPECT_TRUE(BA1.bits[i]) << "operator|= test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "operator|= test"; 
};

TEST(BitArray, OperatorInversion) {
	BitArray BA1(15, 2023), BA2 = BA1.operator~();

	for (int i = 0; i < BA1.len; i++)
		if (!BA1.bits[i])
			EXPECT_TRUE(BA2.bits[i]) << "operator~ test";
		else
			EXPECT_FALSE(BA2.bits[i]) << "operator~ test";
};

TEST(BitArray, OperatorLShift) {
	BitArray BA1(15, 2023), BA2(15, 39);
	BA1.operator<<=(5);
	for (int i = 0; i < BA1.len; i++)
		if (BA2.bits[i])
			EXPECT_TRUE(BA1.bits[i]) << "operator<<= test";
		else
			EXPECT_FALSE(BA1.bits[i]) << "operator<<= test";
};

TEST(BitArray, OperatorRShift) {
	BitArray BA1(15, 2023), BA2(15, 31756), BA3 = BA2.operator~();
	BA1.operator>>=(5);
	for (int i = 0; i < BA1.len; i++)
		if (BA3.bits[i])
			EXPECT_TRUE(BA1.bits[i]) << "operator>>= test" << i;
		else
			EXPECT_FALSE(BA1.bits[i]) << "operator>>= test" << i;
};

TEST(BitArray, OperatorLShiftConst) {
	BitArray BA1(15, 2023), BA2(15,39), BA3 = BA1.operator<<(5);
	for (int i = 0; i < BA2.len; i++)
		if (BA2.bits[i])
			EXPECT_TRUE(BA3.bits[i]) << "operator<< test";
		else
			EXPECT_FALSE(BA3.bits[i]) << "operator<< test";
};

TEST(BitArray, OperatorRShiftConst) {
	BitArray BA1(15, 2023), BA2(15, 31756), BA3 = BA1.operator>>(5), BA4 = BA2.operator~();
	for (int i = 0; i < BA4.len; i++)
		if (BA4.bits[i])
			EXPECT_TRUE(BA3.bits[i]) << "operator>> test";
		else
			EXPECT_FALSE(BA3.bits[i]) << "operator>> test";
};

TEST(comparison, equality) {
	BitArray BA1(15, 2023), BA2(15, 2023);
	EXPECT_TRUE(operator==(BA1, BA2)) << "true operator== test";
	BA1.reset(1);
	EXPECT_FALSE(operator==(BA1, BA2)) << "false operator== test";
};

TEST(comparison, unequality) {
	BitArray BA1(15, 2023), BA2(15, 2023);
	EXPECT_FALSE(operator!=(BA1, BA2)) << "false operator!= test";
	BA1.reset(1);
	EXPECT_TRUE(operator!=(BA1, BA2)) << "true operator== test";
};

TEST(ClasslessOperators, OperatorAnd) {
	BitArray BA1(15, 2023), BA2(15, 20319), BA3(15, 1253), BA4 = operator&(BA1, BA2);
	for (int i = 0; i < BA3.size(); i++)
		if (BA3.operator[](i))
			EXPECT_TRUE(BA4.operator[](i)) << "operator&= test";
		else
			EXPECT_FALSE(BA4.operator[](i)) << "operator&= test";
};

TEST(ClasslessOperators, OperatorOr) {
	BitArray BA1(15, 2023), BA2(15, 20319), BA3(15, 32639), BA4 = operator|(BA1, BA2);
	for (int i = 0; i < BA3.size(); i++)
		if (BA3.operator[](i))
			EXPECT_TRUE(BA4.operator[](i)) << "operator&= test";
		else
			EXPECT_FALSE(BA4.operator[](i)) << "operator&= test";
};

TEST(ClasslessOperators, OperatorNotEqually) {
	BitArray BA1(15, 2023), BA2(15, 20319), BA3(15, 28975), BA4 = operator^(BA1, BA2);
	BA3.reset(1);
	for (int i = 0; i < BA3.size(); i++)
		if (BA3.operator[](i))
			EXPECT_TRUE(BA4.operator[](i)) << "operator&= test";
		else
			EXPECT_FALSE(BA4.operator[](i)) << "operator&= test";
};

