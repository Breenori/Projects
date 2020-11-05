#include "measurement.h"
using namespace measurement;

void measurement::for_()
{
    value_t a(122), b(48), c(33), d(22), e(55), z(0);

    for (uint32_t i(0); i < N; i++) {
        // nothing
    }

}

void measurement::for_assignments()
{
    value_t a(122), b(48), c(33), d(22), e(55), z(0);

    for (uint32_t i(0); i < N; i++) {
        a = b;
        b = c;
        c = d;
        d = e;
        e = a;
    }

}

void measurement::for_assignments_carray()
{
    value_t a(122), b(48), c(33), d(22), e(55), z(0);
    value_t* carray = new value_t[std::max({ a,b,c,d,e }) + 1];

    for (uint32_t i(0); i < N; i++) {
        a = b;
        b = c;
        c = d;
        d = e;
        e = a;
    }

    delete[] carray;
}

void measurement::for_compare()
{
    value_t a(122), b(48), c(33), d(22), e(55), z(0);

    for (uint32_t i(0); i < N; i++) {
        a = a == b;
        b = b == a;
        c = c == a;
        d = d == a;
        e = e == a;
    }

}

void measurement::for_add()
{
    value_t a(122), b(48), c(33), d(22), e(55), z(0);

    for (uint32_t i(0); i < N; i++) {
        a = a + b;
        b = b + a;
        c = c + a;
        d = d + a;
        e = e + a;
    }
}

void measurement::for_division()
{
    value_t a(122), b(48), c(33), d(22), e(55), z(0);

    for (uint32_t i(0); i < N; i++) {
        z = a / b;
        z = b / z;
        z = c / z;
        z = d / z;
        z = e / z;
    }
}

void measurement::for_multiply()
{
    value_t a(122), b(48), c(33), d(123), e(55), z(0);

    for (uint32_t i(0); i < N; i++) {
        z = a * b;
        b = b * z;
        c = c * z;
        d = d * z;
        e = e * z;
    }
}

void measurement::for_index()
{
    value_t a(122), b(48), c(33), d(22), e(55);
    value_t* carray = new value_t[std::max({ a,b,c,d,e }) + 1];
    for (int i(0); i < std::max({ a,b,c,d,e }) + 1; i++)
    {
        carray[i] = i;
    }

    for (uint32_t i(0); i < N; i++) {
        a = carray[(int)b];
        b = carray[(int)c];
        c = carray[(int)d];
        d = carray[(int)e];
        e = carray[(int)a];
    }

    delete[] carray;
}

