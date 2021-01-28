//
//  predicate.h
//  stl_algorithms
//
//  Created by Andreas Schuler on 12.01.20.
//  Copyright © 2020 Andreas Schuler. All rights reserved.
//

#ifndef predicate_h
#define predicate_h

// Functor
template<typename T>
class BiggerThan {
public:
    BiggerThan( T val ) : val(val) {}
    bool operator()( T const & other ) const {
        return other > this->val;
    }
private:
    T val;
};

template<typename T>
class LowerThan {
public:
    LowerThan( T val ) : val(val) {}
    bool operator()( T const & other ) const {
        return other < this->val;
    }
private:
    T val;
};


#endif /* predicate_h */
