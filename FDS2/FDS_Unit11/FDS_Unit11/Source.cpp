#include "pfc-mini.hpp"

typedef int value_t;
const uint32_t N = 1000 * 1000 * 1000; //unsigned int, 32 bit
const size_t m = 5;    //10 vielleicht besser

void for_ () {
    value_t a(45);
    value_t b(98);
    value_t c(23);
    value_t d(34);
    value_t e(43);

    for (uint32_t i(0); i < N; i++) {
        //nothing
    }

}

void for_assignments() {
    value_t a(100);
    value_t b(98);
    value_t c(66);
    value_t d(34);
    value_t e(12);

    for (uint32_t i(0); i < N; i++) {
        a = a / 3;
        b = b / 4;
        c = c / 5;
        d = d / 6;
        e = e / 7;
    }
}


void main() {
    double time_for(pfc::in_s(pfc::timed_run(for_)));
    std::cout << "for:               " << time_for << " [sec]\n";

    double time_for_assignments(pfc::in_s(pfc::timed_run(for_assignments)));
    std::cout << "for + assignments: " << time_for_assignments << " [sec]\n";

    double time_assignment((time_for_assignments - time_for) / N / m);
    std::cout << "one assignment:    " << time_assignment * 1000 * 1000 * 1000 << " [ns]\n";

}