//       $Id: main.cpp 41750 2020-11-22 09:32:40Z p20068 $
//      $URL: https://svn01.fh-hagenberg.at/bin/cepheiden/pfc/trunk/scanner/arithmetic-parser/src/main.cpp $
// $Revision: 41750 $
//     $Date: 2020-11-22 10:32:40 +0100 (So., 22 Nov 2020) $
//   $Author: p20068 $
//   Creator: Peter Kulczycki
//  Creation: November 6, 2020
// Copyright: (c) 2020 Peter Kulczycki (peter.kulczycki<AT>fh-hagenberg.at)
//   License: This document contains proprietary information belonging to
//            University of Applied Sciences Upper Austria, Campus Hagenberg.
//            It is distributed under the Boost Software License (see
//            https://www.boost.org/users/license.html).

#include "./arithmetic_parser.h"

#include <iomanip>

// -------------------------------------------------------------------------------------------------

int main () {
   std::vector const expressions {
      "11 / (-17.3 * 22 + 3)"s,    // gives  -0.0291314
      "62 / (-17 * 2 + 3)"s,       // gives  -2
      "((17 * -4) + 8) / -6"s,     // gives  10
      "1 + 2.0 + 3 * (-5 + -4)"s   // gives -24
   };

   std::cout << std::fixed
             << std::setprecision (3);

   for (auto const & xpr : expressions) {
      try {
         std::cout << "\nevaluating expression '" << xpr << "' ...\n";

         auto const value {
            arithmetic_parser ().parse (xpr)
         };

         std::cout << "result: " << value << '\n';

      } catch (std::exception const & x) {
         std::cerr << "Error: " << x.what () << '\n';
      }
   }
}

/*
evaluating expression '11 / (-17.3 * 22 + 3)' ...
result: -0.029

evaluating expression '62 / (-17 * 2 + 3)' ...
result: -2.000

evaluating expression '((17 * -4) + 8) / -6' ...
result: 10.000

evaluating expression '1 + 2.0 + 3 * (-5 + -4)' ...
result: -24.000
*/

/*
evaluating expression '11 / (-17.3 * 22 + 3)' ...
 0  Expression; {{integer,tc,2},'11'}
 1   Term; {{integer,tc,2},'11'}
 2     Factor; {{integer,tc,2},'11'}
 3       Number; {{integer,tc,2},'11'}
 2     MultOp; {{division,ts,5}}
 2     Factor; {{left parenthesis,ts,9}}
 3       PExpression; {{left parenthesis,ts,9}}
 4         Expression; {{minus,ts,10}}
 5           Term; {{minus,ts,10}}
 6             Factor; {{minus,ts,10}}
 7               AddOp; {{minus,ts,10}}
 7               Number; {{real,tc,3},'17.300'}
 6             MultOp; {{multiply,ts,11}}
 6             Factor; {{integer,tc,2},'22'}
 7               Number; {{integer,tc,2},'22'}
 5           AddOp; {{plus,ts,13}}
 5           Term; {{integer,tc,2},'3'}
 6             Factor; {{integer,tc,2},'3'}
 7               Number; {{integer,tc,2},'3'}
result: -0.029

evaluating expression '62 / (-17 * 2 + 3)' ...
 0  Expression; {{integer,tc,2},'62'}
 1   Term; {{integer,tc,2},'62'}
 2     Factor; {{integer,tc,2},'62'}
 3       Number; {{integer,tc,2},'62'}
 2     MultOp; {{division,ts,5}}
 2     Factor; {{left parenthesis,ts,9}}
 3       PExpression; {{left parenthesis,ts,9}}
 4         Expression; {{minus,ts,10}}
 5           Term; {{minus,ts,10}}
 6             Factor; {{minus,ts,10}}
 7               AddOp; {{minus,ts,10}}
 7               Number; {{integer,tc,2},'17'}
 6             MultOp; {{multiply,ts,11}}
 6             Factor; {{integer,tc,2},'2'}
 7               Number; {{integer,tc,2},'2'}
 5           AddOp; {{plus,ts,13}}
 5           Term; {{integer,tc,2},'3'}
 6             Factor; {{integer,tc,2},'3'}
 7               Number; {{integer,tc,2},'3'}
result: -2.000

evaluating expression '((17 * -4) + 8) / -6' ...
 0  Expression; {{left parenthesis,ts,9}}
 1   Term; {{left parenthesis,ts,9}}
 2     Factor; {{left parenthesis,ts,9}}
 3       PExpression; {{left parenthesis,ts,9}}
 4         Expression; {{left parenthesis,ts,9}}
 5           Term; {{left parenthesis,ts,9}}
 6             Factor; {{left parenthesis,ts,9}}
 7               PExpression; {{left parenthesis,ts,9}}
 8                 Expression; {{integer,tc,2},'17'}
 9                   Term; {{integer,tc,2},'17'}
10                     Factor; {{integer,tc,2},'17'}
11                       Number; {{integer,tc,2},'17'}
10                     MultOp; {{multiply,ts,11}}
10                     Factor; {{minus,ts,10}}
11                       AddOp; {{minus,ts,10}}
11                       Number; {{integer,tc,2},'4'}
 5           AddOp; {{plus,ts,13}}
 5           Term; {{integer,tc,2},'8'}
 6             Factor; {{integer,tc,2},'8'}
 7               Number; {{integer,tc,2},'8'}
 2     MultOp; {{division,ts,5}}
 2     Factor; {{minus,ts,10}}
 3       AddOp; {{minus,ts,10}}
 3       Number; {{integer,tc,2},'6'}
result: 10.000

evaluating expression '1 + 2.0 + 3 * (-5 + -4)' ...
 0  Expression; {{integer,tc,2},'1'}
 1   Term; {{integer,tc,2},'1'}
 2     Factor; {{integer,tc,2},'1'}
 3       Number; {{integer,tc,2},'1'}
 1   AddOp; {{plus,ts,13}}
 1   Term; {{real,tc,3},'2.000'}
 2     Factor; {{real,tc,3},'2.000'}
 3       Number; {{real,tc,3},'2.000'}
 1   AddOp; {{plus,ts,13}}
 1   Term; {{integer,tc,2},'3'}
 2     Factor; {{integer,tc,2},'3'}
 3       Number; {{integer,tc,2},'3'}
 2     MultOp; {{multiply,ts,11}}
 2     Factor; {{left parenthesis,ts,9}}
 3       PExpression; {{left parenthesis,ts,9}}
 4         Expression; {{minus,ts,10}}
 5           Term; {{minus,ts,10}}
 6             Factor; {{minus,ts,10}}
 7               AddOp; {{minus,ts,10}}
 7               Number; {{integer,tc,2},'5'}
 5           AddOp; {{plus,ts,13}}
 5           Term; {{minus,ts,10}}
 6             Factor; {{minus,ts,10}}
 7               AddOp; {{minus,ts,10}}
 7               Number; {{integer,tc,2},'4'}
result: -24.000
*/

/*
evaluating expression '11 / (-17.3 * 22 + 3)' ...
result: 0.000

evaluating expression '62 / (-17 * 2 + 3)' ...
result: 0.000

evaluating expression '((17 * -4) + 8) / -6' ...
result: 0.000

evaluating expression '1 + 2.0 + 3 * (-5 + -4)' ...
result: 0.000
*/
