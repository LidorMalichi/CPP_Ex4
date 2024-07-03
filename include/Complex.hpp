/*
 * Name: Lidor Malichi
 * ID: 318515947
 * Email: lidor673@gmail.com
 */

#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>


class Complex
{
    private:

        double _re;
        double _im;

    public:

            // Constructor. Also works as a conversion from double and
            // also as a default ctor.
        Complex (const double& re = 0.0,
                const double& im = 0.0);

        // Getters
	    double re() const {return _re;}

	    double im() const {return _im;}
	
        // OPERATORS

        // Unary operators
        bool operator!() const {return _re==0 && _im==0;}

        Complex& operator-(); 


        // Binary operators
    
        Complex operator+(const Complex& other) const;

        Complex& operator+=(const Complex& other);

        Complex operator-(const Complex& other) const;

        Complex& operator-=(const Complex& other);


        Complex operator*(const Complex& other);

        Complex& operator*=(const Complex& other);
    

        // Prefix increment:
        Complex& operator++() 
        {
            _re++;
            return *this;
        }

        // Postfix increment:
        Complex operator++(int dummy_flag_for_postfix_increment) 
        {
            Complex copy = *this;
            _re++;
            return copy;
        }
    

        // Comparison operators

        bool operator==(const Complex& other) const;
        bool operator!=(const Complex& other) const;
        bool operator<(const Complex& other) const;
        bool operator>(const Complex& other) const;
        bool operator<=(const Complex& other) const;
        bool operator>=(const Complex& other) const;

   
    // Print operator
    friend std::ostream& operator<< (std::ostream& output, const Complex& c);

};

#endif