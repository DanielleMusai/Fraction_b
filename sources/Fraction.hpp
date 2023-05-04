#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <numeric>
#include <limits>
#include <cmath>

using namespace std;

namespace ariel
{
    const int FRACTION_SCALE = 10000;

    class Fraction
    {
    private:
        int numerator, denominator;

    public:
        Fraction(int num = 0, int den = 1);
        // Fraction(double flt) : numerator(static_cast<int>(flt * FRACTION_SCALE)), denominator(FRACTION_SCALE) {} // casting to a fraction
        Fraction(double flt);
        float roundFloat(float num);
        // : numerator(static_cast<int>(std::round(flt * FRACTION_SCALE))), denominator(FRACTION_SCALE) {}
       // float roundFloat(float num);
        void reduce();

        int getNumerator() const;
        int getDenominator() const;

        friend Fraction operator+(const Fraction &other, const Fraction &frac);
        friend Fraction operator-(const Fraction &other, const Fraction &frac);
        friend Fraction operator*(const Fraction &other, const Fraction &frac);
        friend Fraction operator/(const Fraction &other, const Fraction &frac);

        friend Fraction operator+(const Fraction &other, float frac);
        friend Fraction operator-(const Fraction &other, float frac);
        friend Fraction operator*(const Fraction &other, float frac);
        friend Fraction operator/(const Fraction &other, float frac);

        friend Fraction operator+(float frac, const Fraction &other);
        friend Fraction operator-(float frac, const Fraction &other);
        friend Fraction operator*(float frac, const Fraction &other);
        friend Fraction operator/(float frac, const Fraction &other);

        friend bool operator==(const Fraction &other, const Fraction &frac);
        friend bool operator!=(const Fraction &other, const Fraction &frac);
        friend bool operator>(const Fraction &other, const Fraction &frac);
        friend bool operator<(const Fraction &other, const Fraction &frac);
        friend bool operator>=(const Fraction &other, const Fraction &frac);
        friend bool operator<=(const Fraction &other, const Fraction &frac);
        friend bool operator==(const Fraction &other, float frac);
        friend bool operator==(float frac, const Fraction &other);

        Fraction &operator++();
        Fraction operator++(int);
        Fraction &operator--();
        Fraction operator--(int);
        friend std::ostream &operator<<(std::ostream &ost, const Fraction &frac);
        friend std::istream &operator>>(std::istream &ist, Fraction &frac);
        // friend std::istream& operator>>(std::istream& ist, std::pair<Fraction&, Fraction&> frac_pair);
    };
}

#endif // FRACTION_HPP
