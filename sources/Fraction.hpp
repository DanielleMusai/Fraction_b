#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
#include <numeric>
#include <limits>

//using namespace std;


namespace ariel
{

    const int FRACTION_SCALE = 10000; //  takes a double parameter is to convert the double value to an integer representation that can be used to represent a fraction

    class Fraction
    {
    private:
        int numerator, denominator;

    public:
        Fraction(int num = 0, int den = 1);                                                                     // default values and prevent devision by 0
        Fraction(double flt) : numerator(static_cast<int>(flt * FRACTION_SCALE)), denominator(FRACTION_SCALE) {} // casting to a fraction
        void reduce();                                                                                           // which simplifies the fraction by dividing the numerator and denominator by their gcd. if the fraction is 6/8, simplfy would simplify it to 3/4.
        // i used friend functions to allow them to access the private member variables numerator and denominator.
        int getNumerator() const;
        int getDenominator() const;

        friend Fraction operator+(const Fraction &other, const Fraction &frac);
        friend Fraction operator-(const Fraction &other, const Fraction &frac);
        friend Fraction operator*(const Fraction &other, const Fraction &frac);
        friend Fraction operator/(const Fraction &other, const Fraction &frac);

        friend Fraction operator+(const Fraction &other, double frac);
        friend Fraction operator-(const Fraction &other, double frac);
        friend Fraction operator*(const Fraction &other, double frac);
        friend Fraction operator/(const Fraction &other, double frac);

        friend Fraction operator+(double frac, const Fraction &other);
        friend Fraction operator-(double frac, const Fraction &other);
        friend Fraction operator*(double frac, const Fraction &other);
        friend Fraction operator/(double frac, const Fraction &other);

        friend bool operator==(const Fraction &other, const Fraction &frac);
        friend bool operator!=(const Fraction &other, const Fraction &frac);
        friend bool operator>(const Fraction &other, const Fraction &frac);
        friend bool operator<(const Fraction &other, const Fraction &frac);
        friend bool operator>=(const Fraction &other, const Fraction &frac);
        friend bool operator<=(const Fraction &other, const Fraction &frac);
        friend bool operator==(const Fraction &other, double frac);
        friend bool operator==(double frac, const Fraction &other);
        Fraction &operator++();   // pre
        Fraction operator++(int); // post
        Fraction &operator--();
        Fraction operator--(int);
        friend std::ostream& operator<<(std::ostream& ost, const Fraction& frac);
        friend std::istream &operator>>(std::istream &ist, Fraction &frac);
    };


}



#endif // FRACTION_HPP