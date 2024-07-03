/*
 * Name: Lidor Malichi
 * ID: 318515947
 * Email: lidor673@gmail.com
 */

#include "../include/Complex.hpp"

Complex::Complex(const double &re, const double &im) : _re(re), _im(im){}

Complex &Complex::operator-()
{
    _re = -_re;
    _im = -_im;
    return *this;
}

Complex Complex::operator+(const Complex &other) const
{
    return Complex(_re + other._re, _im + other._im);  
}

Complex &Complex::operator+=(const Complex &other)
{
    _re+= other._re;
    _im+= other._im;
    return *this;
}

Complex Complex::operator-(const Complex &other) const
{
    return Complex(_re - other._re, _im - other._im);
}

Complex &Complex::operator-=(const Complex &other)
{
    _re-= other._re;
    _im-= other._im;
    return *this;
}

Complex Complex::operator*(const Complex &other)
{
    return Complex (_re * other._re - _im * other._im,
                    _re * other._im + _im * other._re);
}

Complex &Complex::operator*=(const Complex &other)
{
    double new_re = _re*other._re - _im*other._im;
    double new_im = _re*other._im + _im*other._re; 
    _re = new_re;
     _im = new_im;
	return *this;
}

bool Complex::operator==(const Complex &other) const
{
    return _re == other._re && _im == other._im;
}

bool Complex::operator!=(const Complex &other) const
{
    return !(*this == other);
}

bool Complex::operator<(const Complex &other) const
{
    return std::sqrt(_re*_re + _im*_im) < std::sqrt(other._re*other._re + other._im*other._im);
}

bool Complex::operator>(const Complex &other) const
{
    return other < *this;
}

bool Complex::operator<=(const Complex &other) const
{
    return *this < other || *this == other;
}

bool Complex::operator>=(const Complex &other) const
{
    return other <= *this;
}

std::ostream &operator<<(std::ostream &output, const Complex &c)
{
    output << c._re << " + " << c._im << "i";
    return output;
}


