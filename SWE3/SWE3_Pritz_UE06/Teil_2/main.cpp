//
//  main.cpp
//  arithmetic_parser
//
//  Created by Andreas Schuler on 07.12.19.
//  Copyright © 2019 Andreas Schuler. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include "arithmetic_parser.h"


int main(int argc, const char* argv[]) {
    std::vector <std::string> const expressions{
		"+ / 20 - 16 11 6",    // gives 10
    	"* + 1 2 + 3 4" // gives 21
    	""
    };

    // sets the number of values displayed after comma
    std::cout << std::fixed << std::setprecision(3);

    for (std::string const& xpr : expressions) {
        try {
            double const value{ ArithmeticParser().parse(xpr) };
            std::cout << xpr << " = " << value << '\n';
        }
        catch (std::exception const& x) {
            std::cerr << "Error: " << x.what() << '\n';
        }
    }
}