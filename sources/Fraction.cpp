#include "Fraction.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

namespace ariel
{

    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
    {
        if (denominator == 0)
        {
            throw std::invalid_argument("Denominator cannot be zero");
        }

        reduce();
    }

    Fraction::Fraction(double flt)
    {
        double rounded_flt = round(flt * 1000) / 1000;
        numerator = static_cast<int>(rounded_flt * FRACTION_SCALE);
        denominator = FRACTION_SCALE;
        reduce();
    }

    void Fraction::reduce()
    {
        // Find the greatest common divisor of the numerator and denominator
        int gcd = std::__gcd(abs(numerator), denominator);

        // Divide both the numerator and denominator by the GCD to reduce the fraction
        numerator /= gcd;
        denominator /= gcd;

        // Make sure the denominator is always positive
        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // Round a float to 3 decimal places
    float roundFloat(float num)
    {
        float rounded_num = round(num * 1000.0f) / 1000.0f;
        return rounded_num;
    }

    int Fraction::getNumerator() const
    {
        return numerator;
    }

    int Fraction::getDenominator() const
    {
        return denominator;
    }

    Fraction operator+(const Fraction &other, const Fraction &frac)
    {
        long long num = (long long)other.numerator * frac.denominator + (long long)frac.numerator * other.denominator;
        long long den = (long long)other.denominator * frac.denominator;
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() || den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Overflow in operator+");
        }
        Fraction result((int)num, (int)den);
        return result;
    }

    Fraction operator-(const Fraction &other, const Fraction &frac)
    {
        long long num = (long long)other.numerator * frac.denominator - (long long)frac.numerator * other.denominator;
        long long den = (long long)other.denominator * frac.denominator;
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() || den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Overflow in operator-");
        }
        Fraction result((int)num, (int)den);
        return result;
    }

    Fraction operator*(const Fraction &other, const Fraction &frac)
    {
        long long num = (long long)other.numerator * frac.numerator;
        long long den = (long long)other.denominator * frac.denominator;
        // check for overflow
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() || den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Overflow in operator*");
        }
        Fraction result((int)num, (int)den);
        return result;
    }

    Fraction operator/(const Fraction &other, const Fraction &frac)
    {
        if (frac == 0)
        {
            throw std::runtime_error("Denominator cannot be zero");
        }
        long long num = (long long)other.numerator * frac.denominator;
        long long den = (long long)other.denominator * frac.numerator;
        // all of this is to solve the problem of a max largest possible numerator and/or denominator - overflow
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() || den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Overflow in operator/");
        }
        Fraction result((int)num, (int)den);
        return result;
    }

    // Overloaded operator+ with Fraction and float operand
    Fraction operator+(const Fraction &other, float frac)
    {
        frac = roundFloat(frac);
        int scaled_num = static_cast<int>(frac * FRACTION_SCALE);
        int new_num = other.numerator * FRACTION_SCALE + other.denominator * scaled_num;
        int new_den = other.denominator * FRACTION_SCALE;

        float result = static_cast<float>(new_num) / new_den;
       // result = roundFloat(result); // round to 3 decimal places
        int rounded_num = static_cast<int>(result * new_den);
        return Fraction(rounded_num, new_den);
    }

    // Overloaded operator- with Fraction and float operand
    Fraction operator-(const Fraction &other, float frac)
    {
        // frac = roundFloat(frac);
        int scaled_num = static_cast<int>(frac * FRACTION_SCALE);
        int new_num = other.numerator * FRACTION_SCALE - other.denominator * scaled_num;
        int new_den = other.denominator * FRACTION_SCALE;

        Fraction result_fraction(new_num, new_den);
        // result_fraction.reduce();

        float result = static_cast<float>(result_fraction.getNumerator()) / result_fraction.getDenominator();
        result = roundFloat(result);

        return Fraction(static_cast<int>(result * result_fraction.getDenominator()), result_fraction.getDenominator());
    }

    // Overloaded operator* with Fraction and float operand
    Fraction operator*(const Fraction &other, float frac)
    {
        frac = roundFloat(frac);
        return Fraction(other.numerator * static_cast<int>(frac * FRACTION_SCALE), other.denominator * FRACTION_SCALE);
    }

    // Overloaded operator/ with Fraction and float operand
    Fraction operator/(const Fraction &other, float frac)
    {
        if (frac == 0)
        {
            throw std::runtime_error("Denominator cannot be zero");
        }
        frac = roundFloat(frac);
        return Fraction(FRACTION_SCALE * other.numerator, static_cast<int>(frac * FRACTION_SCALE) * other.denominator);
    }

    // Overloaded operator+ with float and Fraction operand
    Fraction operator+(float frac, const Fraction &other)
    {
        frac = roundFloat(frac);
        int scaled_num = static_cast<int>(frac * FRACTION_SCALE);
        int new_num = other.numerator * FRACTION_SCALE + other.denominator * scaled_num;
        int new_den = other.denominator * FRACTION_SCALE;
        float result = static_cast<float>(new_num) / new_den;
       //result = roundFloat(result);
        int rounded_num = static_cast<int>(result * new_den);
        return Fraction(rounded_num, new_den);
    }


    // Overloaded operator- with float and Fraction operand
    Fraction operator-(float frac, const Fraction &other)
    {
        frac = roundFloat(frac);
        int scaled_num = static_cast<int>(frac * FRACTION_SCALE);
        int new_num = scaled_num * other.denominator - other.numerator * FRACTION_SCALE;
        int new_den = other.denominator * FRACTION_SCALE;
        float result = static_cast<float>(new_num) / new_den;
        //result = roundFloat(result);
        int rounded_num = static_cast<int>(result * new_den);
        return Fraction(rounded_num, new_den);
    }

    // Overloaded operator* with float and Fraction operand
    Fraction operator*(float frac, const Fraction &other)
    {
        return Fraction(other.numerator * static_cast<int>(frac * FRACTION_SCALE), other.denominator * FRACTION_SCALE);
    }

    // Overloaded operator/ with float and Fraction operand
    Fraction operator/(float frac, const Fraction &other)
    {

     
        if (other == Fraction{0})
        {
            throw std::invalid_argument("Denominator cannot be zero");
        }
   //frac = roundFloat(frac);
        float result = static_cast<int>(frac * other.denominator * FRACTION_SCALE);
        result = roundFloat(result);
        return Fraction(result, FRACTION_SCALE * other.numerator);
    }

    bool operator==(const Fraction &other, const Fraction &frac)
    {
        return (other.numerator == frac.numerator) && (other.denominator == frac.denominator);
    }

    bool operator==(const Fraction &other, float frac)
    {
        float epsilon = 0.000001; // Define an epsilon value for tolerance
        float fractionValue = static_cast<float>(other.numerator) / other.denominator;
        return std::abs(fractionValue - frac) < epsilon;
    }

    bool operator==(float frac, const Fraction &other)
    {
        return other == frac; // Reuse the implementation for Fraction == double
    }

    bool operator!=(const Fraction &other, const Fraction &frac)
    {
        return !(other == frac);
    }

    bool operator>(const Fraction &other, const Fraction &frac)
    {
        return (other.numerator * frac.denominator) > (frac.numerator * other.denominator);
    }

    bool operator<(const Fraction &other, const Fraction &frac)
    {
        return (other.numerator * frac.denominator) < (frac.numerator * other.denominator);
    }

    bool operator>=(const Fraction &other, const Fraction &frac)
    {
        return !(other < frac);
    }

    bool operator<=(const Fraction &other, const Fraction &frac)
    {
        return !(other > frac);
    }

    Fraction &Fraction::operator++()
    {
        numerator += denominator;
        return *this;
    }

    Fraction Fraction::operator++(int)
    {
        Fraction t(*this);
        numerator += denominator;
        return t;
    }

    Fraction &Fraction::operator--()
    {
        numerator -= denominator;
        return *this;
    }

    Fraction Fraction::operator--(int)
    {
        Fraction t(*this);
        numerator -= denominator;
        return t;
    }

    std::ostream &operator<<(std::ostream &ost, const Fraction &frac)
    {
        ost << frac.getNumerator() << '/' << frac.getDenominator();
        return ost;
    }
std::istream &operator>>(std::istream &ist, Fraction &frac)
{
    int numerator, denominator;
    ist >> numerator >> denominator;

    if (ist.fail()) {
        throw std::runtime_error("Invalid input format");
    }

    if (denominator == 0)
    {
        throw std::runtime_error("Invalid fraction format");
    }

    if (numerator == 0)
    {
        frac.numerator = 0;
        frac.denominator = 1;
        return ist;
    }

    int sign = (numerator < 0) != (denominator < 0) ? -1 : 1;
    numerator = std::abs(numerator);
    denominator = std::abs(denominator);

    frac.numerator = sign * numerator;
    frac.denominator = denominator;

    frac.reduce();
    // Check for any remaining characters in the input stream
    // if (ist.rdbuf()->in_avail() > 0)
    // {
    //     throw std::runtime_error("Invalid input format: expected only two fractions");
    // }
    return ist;
}


}