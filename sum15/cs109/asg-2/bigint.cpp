// $Id: bigint.cpp,v 1.73 2015-07-03 14:46:41-07 - - $

// The functions in this file do two things with bigints: call the 
// appropriate mathematical operation on the ubigints contained within
// the bigints, and determine the sign of the result.

//---------------------------------------------------------------------
// Name:       Cecilia Condes
// ID:         ccondes
// Class:      cmps109    
// Date:       16.7.15
// Filename:   bigint.cpp
//---------------------------------------------------------------------

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
   DEBUGF ('~', this << " -> " << uvalue)
}

// create a bigint from a ubigint and a boolean 
bigint::bigint (const ubigint& uvalue, bool is_negative):
                uvalue(uvalue), is_negative(is_negative) {
}

// create a bigint from a string
bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+() const {
   return *this;
}

// unary - operator
bigint bigint::operator-() const {
   return {uvalue, not is_negative};
}

// addition
bigint bigint::operator+ (const bigint& that) const {
   bigint result{};
   // same sign
   if(is_negative == that.is_negative)
      result = {uvalue + that.uvalue, is_negative};

   else{
      // |this| >= |that|
      if(uvalue >= that.uvalue)
         result = {uvalue - that.uvalue, is_negative};
      // |this| <  |that|
      else
         result = {that.uvalue - uvalue, that.is_negative};
   }

   return result;
}

// binary - operator
bigint bigint::operator- (const bigint& that) const {
   bigint result{};
   if(is_negative == that.is_negative){
      if(uvalue >= that.uvalue)
         result = {uvalue - that.uvalue, is_negative};
      else
         result = {that.uvalue - uvalue, !that.is_negative};
   }
   else{ // sign(this) != sign(that); one is -, one is +
      if(is_negative) // -this, +that
         result = {uvalue + that.uvalue, true};
      else // +this, -that
         result = {uvalue + that.uvalue, false};
   }
   return result;
}

// multiplication
bigint bigint::operator* (const bigint& that) const {
   bigint result = uvalue * that.uvalue;
   // result.is_negative = (is_negative == that.is_negative)?  is_negative
   //                                                       :  true;
   // result.is_negative = is_negative?is_negative:that.is_negative;
   if(!is_negative == !that.is_negative) result.is_negative = is_negative;
   else result.is_negative = false;
   return result;
   }

// division
bigint bigint::operator/ (const bigint& that) const {
   bigint result = uvalue / that.uvalue;
   result.is_negative = is_negative == that.is_negative ? is_negative
                                                        : true;
   return result;
}

// modulo
bigint bigint::operator% (const bigint& that) const {
   bigint result = uvalue % that.uvalue;
   return result;
}

// test equality
bool bigint::operator== (const bigint& that) const {
   return is_negative == that.is_negative and uvalue == that.uvalue;
}

// comparison
bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that) {
   return out << "bigint(" << (that.is_negative ? "'-'" : "'+'")
              << that.uvalue << ")";
}

