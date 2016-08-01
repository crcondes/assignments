// $Id: ubigint.h,v 1.9 2015-07-03 14:46:41-07 - - $

#ifndef __UBIGINT_H__
#define __UBIGINT_H__

#include <exception>
#include <iostream>
#include <limits>
#include <utility>
#include <string>
using namespace std;

#include "debug.h"
#include "relops.h"

class ubigint {
   friend ostream& operator<< (ostream&, const ubigint&);
   private:
      using quot_rem = pair<ubigint,ubigint>;
      // using unumber = unsigned long;
      // unumber uvalue {};
      using udigit_t = unsigned char;
      using ubigvalue_t = vector<udigit_t>;
      ubigvalue_t ubig_value;
      
      quot_rem divide (const ubigint&) const;
      void multiply_by_2();
      void divide_by_2();
   public:

      ubigint() = default; // Need default ctor as well.
      ubigint (unsigned long);
      ubigint (const string&);
      ubigint (ubigvalue_t); // trims trailing 0s for use in arithmetic

      ubigint operator+ (const ubigint&) const;
      ubigint operator- (const ubigint&) const;
      ubigint operator* (const ubigint&) const;
      ubigint operator/ (const ubigint&) const;
      ubigint operator% (const ubigint&) const;

      bool operator== (const ubigint&) const;
      bool operator<  (const ubigint&) const;


   friend ostream& operator<< (ostream&, const ubigvalue_t&);
};

#endif

