#pragma once
#include<vector>

class BigInteger
{
public:


	BigInteger(int number=0, unsigned char m_base=10);
	BigInteger(long long int, unsigned char);
	BigInteger(const std::string &number, unsigned char);

	void setSign(int);
	int getSign();
	void setBase(unsigned char);
	int getBase();

	BigInteger removeZeros();

	BigInteger multiply(int digit);

	friend bool operator== (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight);
	friend bool operator!= (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight);
	friend bool operator> (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight);
	friend bool operator< (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight);
	friend bool operator>= (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight);
	friend bool operator<= (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight);

	friend BigInteger operator+ (BigInteger bigInteger);
	friend BigInteger operator- (BigInteger bigInteger);

	BigInteger operator+= (BigInteger adder);
	BigInteger operator+= (int adder);

	BigInteger operator-= (BigInteger substractInt);
	BigInteger operator-= (int substractInt);

	BigInteger operator*= (BigInteger multiplier);
	BigInteger operator*= (int multiplierInt);

	BigInteger operator/= (BigInteger bigInt);
	BigInteger operator/= (int integer);

	BigInteger operator%= (BigInteger bigInt);
	BigInteger operator%= (int integer);

	friend BigInteger operator+ (BigInteger firstBigInt, BigInteger secondBigInt);
	friend BigInteger operator+ (BigInteger firstBigInt, int secondInt);
	friend BigInteger operator+ (int firstInt, BigInteger secondBigInt);

	friend BigInteger operator- (BigInteger bigInteger, BigInteger substractBigInt);
	friend BigInteger operator- (BigInteger bigInteger, int substractInt);
	friend BigInteger operator- (int integer, BigInteger substractBigInt);

	friend BigInteger operator* (BigInteger firstBigInt, BigInteger secondBigInt);
	friend BigInteger operator* (BigInteger firstBigInt, int secondInt);
	friend BigInteger operator* (int firstInt, BigInteger secondBigInt);

	friend BigInteger operator/ (BigInteger first, BigInteger second);
	friend BigInteger operator/ (BigInteger first, int second);
	friend BigInteger operator/ (int first, BigInteger second);

	friend BigInteger operator^ (BigInteger bigInt, int exp);

	friend BigInteger operator% (BigInteger leftBigInt, BigInteger rightBigInt);
	friend BigInteger operator% (BigInteger leftBigInt, int rightInt);
	friend BigInteger operator% (int leftInt, BigInteger rightBigInt);

	friend std::ostream& operator<< (std::ostream& os, const BigInteger& bigInteger);
	friend std::istream& operator>> (std::istream& is, BigInteger& bigInteger);


private :
	std::vector < unsigned char > digits;
	int sign;
	unsigned char base;


};

