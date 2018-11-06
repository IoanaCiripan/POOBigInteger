#include "pch.h"
#include "BigInteger.h"
#include "iostream"
#include "sstream"


//BigInteger :: BigInteger()

BigInteger :: ~BigInteger()
{
}


BigInteger :: BigInteger(int number = 0, unsigned char m_base = 10)
{
	this->base = m_base;
	if (number >= 0)
		this->sign = 1;
	else
	{
		this->sign = -1;
		number = (-1) * number;
	}

	while (number)
	{
		this->digits.push_back((number % 10) + '0');
		number /= 10;
	}
	std::reverse(this->digits.begin(), this->digits.end());

}

BigInteger :: BigInteger(long long int number, unsigned char m_base = 10)
{
	this->base = m_base;
	if (number > 0)
		this->sign = 1;
	else
		this->sign = -1;

	while (number)
	{
		this->digits.push_back((number % 10) + '0');
		number /= 10;
	}
	std::reverse(this->digits.begin(), this->digits.end());

}

BigInteger :: BigInteger(const std::string &number, unsigned char m_base = 10)
{
	try
	{
		this->base = m_base;
		int startIndex = 0;


		if (number[0] == '-')
		{
			this->sign = -1;
			startIndex = 1;
		}
		else
			this->sign = 1;

		if (number.size() == 0 || (this->sign == -1 && number.size() == 1))
			throw 20;



		while (number[startIndex] == '0')
		{
			startIndex++;
			if (startIndex == number.size())
			{
				(this->digits).push_back('0');
				this->sign = 1;
				break;
			}
		}


		for (int i = startIndex;i < number.size();i++)
		{
			this->digits.push_back(number[i]);
			if (!(number[i] >= '0'&&number[i] <= '9'))
			{
				(this->digits).clear();
				throw 20;
			}
		}
	}
	catch (int e)
	{
		std::cout << "Number parameter received as String it's not a number " << '\n';
	}
}



void BigInteger :: setSign(int m_sign)
{
	this->sign = m_sign;
}

void BigInteger :: setBase(unsigned char m_base)
{
	this->base = m_base;
}

int BigInteger :: getSign()
{
	return this->sign;
}

int BigInteger :: getBase()
{
	return this->base;
}


BigInteger BigInteger :: removeZeros()
{
	while (this->digits.size() > 0 && this->digits[0] == '0')
	{
		this->digits.erase(this->digits.begin(), this->digits.begin() + 1);
	}
	if (this->digits.size() == 0)
		this->digits.push_back('0');
	return *this;
}

BigInteger BigInteger :: multiply(int digit)
{
	int carry = 0;
	int num;
	(this->digits).insert((this->digits).begin(), '0');
	int i = 1;
	for (int i = (this->digits).size() - 1;i >= 0;i--)
	{

		num = this->digits[i] - '0';
		(this->digits)[i] = ((digit * num + carry) % 10) + '0';
		carry = (digit*num + carry) / 10;

		//(this->digits)[i - 1] = (this->digits)[i - 1] - '0' + carry + '0';

	}
	return *this;
}



bool operator== (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight)
{
	if (bigIntegerLeft.sign != bigIntegerRight.sign)
		return false;
	if (bigIntegerLeft.digits.size() != bigIntegerRight.digits.size())
		return false;

	for (int i = 0;i < bigIntegerLeft.digits.size();i++)
	{
		if (bigIntegerLeft.digits[i] != bigIntegerRight.digits[i])
			return false;
	}

	return true;
}

bool operator!= (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight)
{
	if (bigIntegerLeft == bigIntegerRight)
		return false;
	return true;
}

bool operator< (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight)
{
	if (bigIntegerLeft == bigIntegerRight)
		return false;
	if (bigIntegerLeft > bigIntegerRight)
		return false;

	return true;
}

bool operator> (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight)
{
	bool isPositive = true;

	if (bigIntegerLeft.sign != bigIntegerRight.sign)
		if (bigIntegerLeft.sign == 1)
			return true;
		else
			return false;

	if (bigIntegerLeft.sign == -1)
		isPositive = false;



	if (bigIntegerLeft.digits.size() > bigIntegerRight.digits.size())
		return isPositive;

	if (bigIntegerLeft.digits.size() < bigIntegerRight.digits.size())
		return !isPositive;

	for (int i = 0;i < bigIntegerLeft.digits.size();i++)
	{
		if (bigIntegerLeft.digits[i] > bigIntegerRight.digits[i])
			return isPositive;
		if (bigIntegerLeft.digits[i] < bigIntegerRight.digits[i])
			return !isPositive;
	}

	return false;

}

bool operator>= (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight)
{
	return !(bigIntegerLeft < bigIntegerRight);
}

bool operator<= (const BigInteger& bigIntegerLeft, const BigInteger& bigIntegerRight)
{
	return !(bigIntegerLeft > bigIntegerRight);
}


BigInteger operator+ (BigInteger bigInteger)
{
	return bigInteger;
}

BigInteger operator- (BigInteger bigInteger)
{
	BigInteger oppositeBigInteger(0, '10');

	if (!(bigInteger.digits.size() == 1 && bigInteger.digits[0] == '0'))
		oppositeBigInteger.sign = -bigInteger.sign;

	for (int i = 0;i < bigInteger.digits.size(); i++)
	{
		oppositeBigInteger.digits.push_back(bigInteger.digits[i]);

	}

	return oppositeBigInteger;

}


BigInteger BigInteger :: operator+= (BigInteger adder)
{
	if ((this->digits).size() > adder.digits.size())
		adder.digits.insert(adder.digits.begin(), (this->digits).size() - adder.digits.size(), '0');
	if ((this->digits).size() < adder.digits.size())
		(this->digits).insert((this->digits).begin(), adder.digits.size() - (this->digits).size(), '0');

	if (this->sign == adder.sign)
	{
		int carry = 0;
		int num = 0;
		for (int i = (this->digits).size() - 1; i >= 0; i--)
		{
			num = (this->digits[i]) - '0' + adder.digits[i] - '0' + carry;
			if (num >= 10)
			{
				num -= 10;
				carry = 1;
			}
			else
				carry = 0;

			(this->digits)[i] = num + '0';
		}
		if (carry == 1)
		{
			this->digits.insert(this->digits.begin(), 1, '1');
		}
		this->removeZeros();
		return *this;
	}

	else 
	{
		int auxSign = this->sign;

		this->sign = 1;
		adder.sign = 1;

		if (*this == adder)
		{
			this->digits.resize(1);
			this->digits[0] = '0';
			this->removeZeros();
			return *this;
		}

		if (*this < adder)
		{
			int num;
			for (int i = (this->digits).size() - 1;i >= 0;i--)
			{
				num = (adder.digits)[i] - '0' - (this->digits[i] - '0');
				if (num < 0)
				{
					num += 10;
					(adder.digits)[i - 1] = (adder.digits)[i - 1] - 1;
				}
				(adder.digits)[i] = num + '0';
			}

			adder.sign = (-1)*auxSign;
			this->sign = adder.sign;
			this->digits = adder.digits;
			this->base = adder.base;

			this->removeZeros();

			return *this;
		}

		if (*this > adder)
		{
			int num;
			for (int i = this->digits.size() - 1;i >= 0;i--)
			{
				num = this->digits[i] - '0' - (adder.digits[i] - '0');
				if (num < 0)
				{
					num += 10;
					this->digits[i - 1] = this->digits[i - 1] - 1;
				}
				this->digits[i] = num + '0';
			}

			this->sign = auxSign;
			this->removeZeros();

			return *this;

		}
	}
}
BigInteger BigInteger :: operator+= (int adder)
{
	BigInteger bigIntAdder = BigInteger(adder, 10);
	return *this += bigIntAdder;
}

BigInteger BigInteger :: operator-= (BigInteger substract)
{
	return *this += (-substract);
}
BigInteger BigInteger :: operator-= (int substract)
{
	BigInteger bigIntSubstract = BigInteger(substract, 10);
	return *this -= bigIntSubstract;
}

BigInteger BigInteger :: operator*=(BigInteger multiplier)
{
	BigInteger rez = BigInteger("0", 10);
	BigInteger thisCopy = BigInteger("0", 10);

	thisCopy.sign = this->sign;
	thisCopy.base = this->base;
	thisCopy.digits = this->digits;

	for (int i = multiplier.digits.size() - 1;i >= 0;i--)
	{
		this->sign = thisCopy.sign;
		this->base = thisCopy.base;
		this->digits = thisCopy.digits;
		for (int j = 1;j <= (multiplier.digits.size() - 1) - i;j++)
		{
			(*this).digits.push_back('0');
		}

		rez += (*this).multiply(multiplier.digits[i] - '0');
	}

	this->sign = rez.sign;
	this->base = rez.base;
	this->digits = rez.digits;

	return *this;
}
BigInteger BigInteger :: operator*=(int multiplierInt)
{
	BigInteger multiplierBigInt = BigInteger(multiplierInt, 10);
	return *this *= multiplierBigInt;

}

BigInteger BigInteger :: operator/= (BigInteger substract)
{
	*this = *this / substract;
	return *this;

}
BigInteger BigInteger :: operator/= (int substract)
{
	BigInteger substractBigInt = BigInteger(substract, 10);
	return *this /= substractBigInt;

}

BigInteger BigInteger :: operator%= (BigInteger substract)
{
	*this = *this % substract;
	return *this;
}
BigInteger BigInteger :: operator%= (int integer)
{
	BigInteger bigInt = BigInteger(integer, 10);
	return *this %= bigInt;

}


BigInteger operator+ (BigInteger firstBigInt, BigInteger secondBigInt)
{
	return firstBigInt += secondBigInt;
}
BigInteger operator+ (BigInteger firstBigInt, int secondInt)
{
	BigInteger secondBigInt = BigInteger(secondInt, 10);
	return firstBigInt + secondBigInt;
}
BigInteger operator+ (int firstInt, BigInteger secondBigInt)
{
	BigInteger firstBigInt = BigInteger(firstInt, 10);
	return firstBigInt + secondBigInt;
}

BigInteger operator- (BigInteger bigInteger, BigInteger substractBigInt)
{
	return bigInteger += -substractBigInt;
}
BigInteger operator- (BigInteger bigInteger, int substractInt)
{
	BigInteger substractBigInt = BigInteger(substractInt, 10);
	return bigInteger - substractBigInt;

}
BigInteger operator- (int integer, BigInteger substractBigInt)
{
	BigInteger bigInteger = BigInteger(integer, 10);
	return bigInteger - substractBigInt;
}

BigInteger operator* (BigInteger firstBigInt, BigInteger secondBigInt)
{
	return firstBigInt *= secondBigInt;
}
BigInteger operator* (BigInteger firstBigInt, int secondInt)
{
	BigInteger secondBigInt = BigInteger(secondInt, 10);
	return firstBigInt * secondBigInt;
}
BigInteger operator* (int firstInt, BigInteger secondBigInt)
{
	BigInteger firstBigInt = BigInteger(firstInt, 10);
	return firstBigInt * secondBigInt;
}

BigInteger operator/ (BigInteger leftBigInt, BigInteger rightBigInt)
{
	try {

		if (rightBigInt.digits.size() == 1 && rightBigInt.digits[0] == '0')
			throw 30;

		BigInteger aux = BigInteger(leftBigInt.digits[0] - '0', 10);
		BigInteger rez = BigInteger("0", 10);
		if (leftBigInt < rightBigInt)
			return rez;

		for (int i = 1;i <= rightBigInt.digits.size() - 1;i++)
		{
			char digit = leftBigInt.digits[i];
			aux.digits.push_back(digit);
		}

		int index = rightBigInt.digits.size();
		while (true)
		{
			rez *= 10;
			while (aux >= rightBigInt)
			{
				aux -= rightBigInt;
				rez = rez + 1;
			}
			if (index == leftBigInt.digits.size())
				break;
			char digit = leftBigInt.digits[index];
			aux.digits.push_back(digit);
			aux.removeZeros();
			index++;
		}
		return rez;

	}
	catch (int e)
	{
		std::cout << "You cannot divide by 0 " << '\n';
		return BigInteger(0, 10);
	}



}
BigInteger operator/ (BigInteger leftBigInt, int rightInt)
{
	BigInteger rightBigInt = BigInteger(rightInt, 10);
	return leftBigInt / rightBigInt;
}
BigInteger operator/ (int leftInt, BigInteger rightBigInt)
{
	BigInteger leftBigInt = BigInteger(leftInt, 10);
	return leftBigInt / rightBigInt;
}

BigInteger operator% (BigInteger leftBigInt, BigInteger rightBigInt)
{
	return leftBigInt - (leftBigInt / rightBigInt)*rightBigInt;
}
BigInteger operator% (BigInteger leftBigInt, int rightInt)
{
	BigInteger rightBigInt = BigInteger(rightInt, 10);
	return leftBigInt % rightBigInt;

}
BigInteger operator% (int leftInt, BigInteger rightBigInt)
{
	BigInteger leftBigInt = BigInteger(leftInt, 10);
	return leftBigInt % rightBigInt;

}


BigInteger operator^ (BigInteger bigInt, int exp)
{
	BigInteger rez = BigInteger(1, 10);

	while (exp)
	{
		rez *= bigInt;
		exp--;
	}
	return rez;

}


std::ostream& operator<< (std::ostream& os, const BigInteger& bigInteger)
{

	if (bigInteger.sign == -1)
		os << "-";
	for (int i = 0;i < bigInteger.digits.size();i++)
	{
		os << bigInteger.digits[i];
	}
	return os;
}
std::istream& operator>>  (std::istream& is, BigInteger& bigInteger)
{
	std::string inputString;
	char inputChar;
	getline(is, inputString);
	bigInteger = BigInteger(inputString);
	return is;

}






