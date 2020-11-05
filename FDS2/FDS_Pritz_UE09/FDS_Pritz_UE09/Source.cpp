#include "measurement.h"
#include<time.h>
#include<fstream>
using namespace measurement;


void main() {
    srand((int)time(0));
    
    // Measuring the runtime in seconds of all loops with their designated actions
    double time_for                     (pfc::in_s(pfc::timed_run(for_)));
    double time_for_assignments         (pfc::in_s(pfc::timed_run(for_assignments)));
    double time_for_assignments_vector  (pfc::in_s(pfc::timed_run(for_assignments_carray)));
    double time_for_compare             (pfc::in_s(pfc::timed_run(for_compare)));
    double time_for_add                 (pfc::in_s(pfc::timed_run(for_add)));
    double time_for_division            (pfc::in_s(pfc::timed_run(for_division)));
    double time_for_multiply            (pfc::in_s(pfc::timed_run(for_multiply)));
    double time_for_index               (pfc::in_s(pfc::timed_run(for_index)));
    
    std::ofstream actions_out("actions_measurement.csv");
    actions_out.imbue(std::locale("de"));

    // Calculate the runtime in seconds for ONE execution of each command by dividing through the amount of executions
    // Since time assignment consists of a for loop and assignments we have to substract the for loop.
    double time_assignment  ((time_for_assignments  - time_for)                     / N / m);
    // Since we are assigning the results of compare/add/division/multiply we have to subtract the time needed for the assignments in a loop which we calculated above.
    double time_compare     ((time_for_compare      - time_for_assignments)         / N / m);
    double time_add         ((time_for_add          - time_for_assignments)         / N / m);
    double time_division    ((time_for_division     - time_for_assignments)         / N / m);
    double time_multiply    ((time_for_multiply     - time_for_assignments)         / N / m);
    // To measure the index action we have to subtract BOTH the time needed for assignments AND the time needed for creating and deleting the carray
    double time_index       ((time_for_index        - time_for_assignments_vector)  / N / m);

    // Then print the values to a file as nanoseconds
    actions_out << ";one assignment;one compare;one add;one division;one multiply;one index;unit\n"
                << "result;"
                << time_assignment  * 1000 * 1000 * 1000 << ";"
                << time_compare     * 1000 * 1000 * 1000 << ";"
                << time_add         * 1000 * 1000 * 1000 << ";"
                << time_division    * 1000 * 1000 * 1000 << ";"
                << time_multiply    * 1000 * 1000 * 1000 << ";"
                << time_index       * 1000 * 1000 * 1000 << ";"
                << "[ns]\n"
                << "expectation;0,52;4,44;0,81;1,67;0,50;0,59;[ns]";

    actions_out.close();
}
