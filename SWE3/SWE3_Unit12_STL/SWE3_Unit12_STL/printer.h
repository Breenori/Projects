//
//  Printer.h
//  stl_algorithms
//
//  Created by Andreas Schuler on 12.01.20.
//  Copyright © 2020 Andreas Schuler. All rights reserved.
//

#ifndef Printer_h
#define Printer_h

// Functor
template<typename T>
class Printer {
public:
    Printer(){}
    void operator()( std::set<T> const & elements ) const {
        std::for_each( elements.begin(), elements.end(), [](T const value){
            std::cout << value << " ";
        } );        
    }
};

#endif /* Printer_h */
