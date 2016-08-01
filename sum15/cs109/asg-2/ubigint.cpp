// $Id: ubigint.cpp,v 1.8 2015-07-03 14:46:41-07 - - $

//---------------------------------------------------------------------
// Name:       Cecilia Condes
// ID:         ccondes
// Class:      cmps109    
// Date:       16.7.15
// Filename:   ubigint.cpp
//---------------------------------------------------------------------


#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

#include "ubigint.h"
#include "debug.h"

ubigint::ubigint (unsigned long that): ubig_value() {
   stringstream that_stream;
   that_stream << that; // convert long to stringstream
   const string that_str = that_stream.str(); // stringstream to str

   for(auto rit=that_str.rbegin(); rit != that_str.rend(); rit++)
      ubig_value.push_back(*rit);

   // DEBUGF ('~', this << " -> " << ubig_value);
}

ubigint::ubigint (const string& that): ubig_value() {
   for(auto rit=that.rbegin(); rit != that.rend(); rit++)
      ubig_value.push_back(*rit);
}

// is this even necessary?
ubigint::ubigint (ubigvalue_t ubv): ubig_value(ubv) {
   while (ubig_value.size() > 0 && ubig_value.back() == 0)
      ubig_value.pop_back();
}

// adds two vectors of unsigned chars
ubigint ubigint::operator+ (const ubigint& that) const {
   ubigvalue_t ubig_A = ubig_value;
   ubigvalue_t ubig_B = that.ubig_value;
   ubigvalue_t::iterator it_A = ubig_A.begin();
   ubigvalue_t::iterator it_B = ubig_B.begin();
   int num_A;
   int num_B;

   // should specify size of result
   ubigvalue_t result(max(ubig_A.size(), ubig_B.size()) + 1);

   int carry = 0;
   int sum;
   for(; it_A != ubig_A.end() || it_B != ubig_B.end();){
      num_A = (it_A != ubig_A.end())?*it_A - '0':0;
      num_B = (it_B != ubig_B.end())?*it_B - '0':0;
      sum = carry + (num_A + num_B)%10;
      result.push_back(sum + '0');
      carry = (num_A + num_B > 9)?1:0;
      if(it_A != ubig_A.end()) ++it_A;
      if(it_B != ubig_B.end()) ++it_B;
   }

   unsigned char foo = '1';
   if(carry == 1) result.push_back(foo);

   while (result.size() > 0 && result.back() == 0)
      result.pop_back();

   return ubigint{result};
}

// subtracts two vectors of unsigned chars
ubigint ubigint::operator- (const ubigint& that) const {
   if (*this < that) throw domain_error ("ubigint::operator-(a<b)");

   ubigvalue_t ubig_A = ubig_value;
   ubigvalue_t ubig_B = that.ubig_value;
   ubigvalue_t::iterator it_A = ubig_A.begin();
   ubigvalue_t::iterator it_B = ubig_B.begin();

   // string result_str;
   ubigvalue_t result(max(ubig_A.size(), ubig_B.size()));

   int carry = 0;
   int add;
   int sum;
   int num_A;
   int num_B;
   for(; it_A != ubig_A.end() || it_B != ubig_B.end();){
      num_A = (it_A != ubig_A.end() )?*it_A - '0':0;
      num_B = (it_B != ubig_B.end() )?*it_B - '0':0;
      add = (num_A < num_B)?10:0;
      sum = carry + (num_A - num_B) + add;
      result.push_back(sum + '0');
      carry = (num_A < num_B)?-1:0;
      if(it_A != ubig_A.end()) ++it_A;
      if(it_B != ubig_B.end()) ++it_B;
   }

   while (result.size() > 0 && result.back() == 0)
      result.pop_back();

   // this constructor trims trailing zeroes
   return ubigint{result};
}

// The Egyptian multiplication method was used in this assignment

ubigint ubigint::operator* (const ubigint& that) const {
   int carry;
   int d;
   ubigvalue_t u = ubig_value;
   ubigvalue_t v = that.ubig_value;
   size_t m = u.size();
   size_t n = v.size();
   ubigvalue_t result = ubigvalue_t(m+n, '0');

   for(size_t i = 0; i < m; ++i){
      carry = 0;

      for(size_t j = 0; j < n; ++j){
         d = (result[i+j] - '0') + (u[i]-'0')*(v[j]-'0') + carry;
         result[i+j] = ((d%10) + '0');
         carry = d / 10;
      }

      result[i+n] = (carry + '0');
   }

   while (result.size() > 0 && result.back() == 0)
      result.pop_back();

   return ubigint{result};
}

void ubigint::multiply_by_2() {
   // ubig_value *= 2;

   int carry = 0;
   int product;
   int product_sum;
   ubigvalue_t result(ubig_value.size() + 1);

   // change to const auto& ??
   for(  ubigvalue_t::iterator it = ubig_value.begin(); 
         it != ubig_value.end(); 
         ++it){
      product = ((*it - '0')*2) + carry;
      product_sum = (product % 10);
      // result+= (product_sum + '0');
      result.push_back(product_sum + '0');
      carry = (product > 9)?(product - product_sum) / 10:0;
   }

   // ubigvalue_t result = ubig_value*2;
   ubig_value = result;
}

void ubigint::divide_by_2() {
   // ubig_value /= 2;

   int carry = 0;
   int quotient;

   ubigvalue_t result(ubig_value.size());

   // WHAT THE HELL
   cout << "dividing " << this << " by 2" << endl;
   for(auto it = ubig_value.end(); ; --it){
      if(it == ubig_value.end()){ 
         cout << "skipping end()" << endl;
         continue; // skip end()
      }

      quotient = ((*it - '0') / 2) + carry;
      result.push_back(quotient + '0');
      carry = ((*(it) - '0') % 2 == 0)?0:5;

      cout << "it: " << *it << " q: " <<   quotient << " c: " << carry << endl;

      if(it == ubig_value.begin()) break; // stop AFTER dividing begin
   }

   // STILL DOESN'T WORK
   // cout << "dividing " << this << " by 2" << endl;
   // for(int i = ubig_value.size() - 1; i > 0; --i){
   //    quotient = ((ubig_value[i] - '0') / 2) + carry;
   //    result.push_back(quotient + '0');
   //    carry = ((ubig_value[i] - '0') % 2 == 0) ? 0 : 5;

   //    cout << "it: " << ubig_value[i] << " q: " << quotient << " c: " << carry << endl;
   // }

   ubig_value = result;
}

// vector<char> foo(size);
// for(auto it = foo.end(); ; --it){
//    if(it == foo.end()) continue;

//    cout << *it;

//    if(it == foo.begin()) break;
// }

// NOT DONE

ubigint::quot_rem ubigint::divide (const ubigint& that) const {
   static const ubigint zero {0};
   if (that == zero) throw domain_error ("ubigint::divide: by 0");
   ubigint power_of_2 ("1");

   ubigint divisor = that; // right operand, divisor
   ubigint quotient {0};
   ubigint rem = *this; // left operand, dividend
   cout << "div: " << divisor << " rem: " << rem << " pow: " << power_of_2 << " quot: " << quotient << endl;
   while (divisor < rem) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
      cout << "div: " << divisor << " rem: " << rem << " pow: " << power_of_2 << endl;
   }

   // cout << "div: " << divisor << " rem: " << rem << endl;
   cout << power_of_2 << " > " << zero << endl;
   power_of_2.divide_by_2();
   cout << "now " << power_of_2 << " > " << zero << endl;

   // while (power_of_2 > zero) {
   //    cout << power_of_2 << " > " << zero << endl;
   //    if (divisor <= rem) {
   //       rem = rem - divisor;
   //       quotient = quotient + power_of_2;
   //    }
   //    divisor.divide_by_2();
   //    power_of_2.divide_by_2();
   // }
   // return {quotient, rem};

   ubigint that_copy = that;
   that_copy.divide_by_2();
   if (that_copy > zero) cout << that_copy << " >< " << zero << endl;
   return {that_copy, that_copy};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return divide (that).first;
}

ubigint ubigint::operator% (const ubigint& that) const {
   // ubigint a = ubig_value;
   // ubigint b = that.ubig_value;

   return divide (that).second;
}

bool ubigint::operator== (const ubigint& that) const {
   bool is_equal = (ubig_value.size() == that.ubig_value.size());
   
   if(is_equal){  // if the lengths are the same, must check digits
      auto it_A = ubig_value.begin();
      auto it_B = that.ubig_value.begin();

      // while they are equal and not at the end
      for(; is_equal && (it_A  !=  ubig_value.end());){
         is_equal = *it_A == *it_B;
         ++it_A;
         ++it_B;
      }
   }

   return is_equal;
}

bool ubigint::operator< (const ubigint& that) const {
   // if this.size() < that.size(), this < that
   bool less = ubig_value.size() < that.ubig_value.size();

   // if this.size() > that.size(), this !<that so no need to keep
   //    checking; only check if sizes are the same
   if(ubig_value.size() == that.ubig_value.size()){
      auto it_A = ubig_value.end()-1;
      auto it_B = that.ubig_value.end()-1;

      for(  size_t i = 0; 
            !less && i < max(ubig_value.size(),that.ubig_value.size()); 
            ++i){
            less = (*it_A - '0') < (*it_B - '0');
            ++it_A;
            ++it_B;
      }
   }

   return less;
}

ostream& operator<< (ostream& out, const ubigint& that) { 
   // using ubigvalue_t = vector<unsigned char>;

   string that_str;
   for(  auto it = that.ubig_value.end() -1;
         it  !=  that.ubig_value.begin() -1;
         --it){
      that_str += *it;
   }
   return out << "ubigint(" << that_str << ")";
}
