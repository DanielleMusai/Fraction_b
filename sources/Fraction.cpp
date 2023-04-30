#include "Fraction.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
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
   // result.reduce();
    return result;
}

Fraction operator*(const Fraction &other, const Fraction &frac)
{
    long long num = (long long)other.numerator * frac.numerator;
    long long den = (long long)other.denominator * frac.denominator;
    // check for overflow
if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() || den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Overflow in operator/");
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
    if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() || den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Overflow in operator/");
    }
    Fraction result((int)num, (int)den);
    return result;
}
    // Overloaded operator+ with Fraction and double operand
    Fraction operator+(const Fraction &other, double frac)
    {
        return other + Fraction(frac);
    }

    // Overloaded operator- with Fraction and double operand
    Fraction operator-(const Fraction &other, double frac)
    {
        return other - Fraction(frac);
    }

    // Overloaded operator* with Fraction and double operand
    Fraction operator*(const Fraction &other, double frac)
    {
        return other * Fraction(frac);
    }

    // Overloaded operator/ with Fraction and double operand
    Fraction operator/(const Fraction &other, double frac)
    {
        if (frac == 0)
        {
            throw std::runtime_error("Denominator cannot be zero");
        }
        return other / Fraction(frac);
    }

    // Overloaded operator+ with double and Fraction operand
    Fraction operator+(double frac, const Fraction &other)
    {
        return Fraction(frac) + other;
    }

    // Overloaded operator- with double and Fraction operand
    Fraction operator-(double frac, const Fraction &other)
    {

        return Fraction(frac) - other;
    }

    // Overloaded operator* with double and Fraction operand
    Fraction operator*(double frac, const Fraction &other)
    {
        return Fraction(frac) * other;
    }

    // Overloaded operator/ with double and Fraction operand
    Fraction operator/(double frac, const Fraction &other)
    {
        if (other == Fraction{0})
        {
            throw std::invalid_argument("Denominator cannot be zero");
        }

        return Fraction(frac) / other;
    }

    bool operator==(const Fraction &other, const Fraction &frac)
    {
        return (other.numerator == frac.numerator) && (other.denominator == frac.denominator);
    }

    bool operator==(const Fraction &other, double frac)
    {
        double epsilon = 0.000001; // Define an epsilon value for tolerance
        double fractionValue = static_cast<double>(other.numerator) / other.denominator;
        return std::abs(fractionValue - frac) < epsilon;
    }

    bool operator==(double frac, const Fraction &other)
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
    int n = 0, d = 1;
    char c;

    // Read the numerator
    if (ist >> n)
    {
        // Check for zero numerator
        if (n == 0)
        {
            frac = Fraction(0, 1);
            return ist;
        }

        // Check for the '/' character
        if (ist >> c && c == '/')
        {
            // Read the denominator
            if (ist >> d)
            {
                // Check for a valid denominator
                if (d == 0)
                {
                    throw std::runtime_error("Denominator cannot be zero");
                }
            }
            else
            {
                // Invalid input format
                throw std::runtime_error("Invalid fraction format");
            }
        }
        else
        {
            // Invalid input format
            throw std::runtime_error("Invalid fraction format");
        }
    }
    else
    {
        // Invalid input format
        throw std::runtime_error("Invalid fraction format");
    }

    // Create the fraction
    frac = Fraction(n, d);

    // Clear any flags that may have been set
    ist.clear();

    return ist;
}


}