#include "pfc-mini.hpp"
#include<fstream>

// global variables are bad, yes. But due to pfc not allowing functions to be given parameters this is one quick and easy fix.
uint32_t C_SIZE = 10;
const uint32_t bs_N = 1000 * 1000;
const uint32_t m = 5;

// BS iterations from our lessons.
int binary_search_1(int* const& vec, size_t const n, int const x);
int binary_search_2(int* const& vec, size_t const n, int const x);
int binary_search_3(int* const& vec, size_t const n, int const x);

// Returns a carray of size n initialized from 0 to n (carry[i] = i)
int* get_carray(size_t n);
// Function to measure how long it takes everything other than the binary search to complete.
void test_bs_prep();
// Function to measure the runtime of bs1 for a random existing value.
void test_bs1_rand();
// Function to measure the runtime of bs1 for a nonexisting value
void test_bs1_out();
// Function to measure the runtime of bs2 for a random existing value.
void test_bs2_rand();
// Function to measure the runtime of bs2 for a nonexisting value
void test_bs2_out();
// Function to measure the runtime of bs3 for a random existing value.
void test_bs3_rand();
// Function to measure the runtime of bs3 for a nonexisting value
void test_bs3_out();

void main()
{
    std::ofstream bs_out("out.csv");
    // Print the csv header.
    bs_out << "N;BS1 Random;BS1 Notfound;BS2 Random;BS2 Notfound;BS3 Random;BS3 Notfound" << std::endl;
    // Imbue the outputstream to write commas instead of dots to make excel work easier.
    bs_out.imbue(std::locale("de"));

    // measure the binary search results for different carray sizes.
    while (C_SIZE <= 10000000)
    {
        // Measure how long it takes to create, initialize and delete a carray and run the for loop.
        double time_bs_prep(pfc::in_s(pfc::timed_run(test_bs_prep)));

        // Measure the time needed for each variation
        // Since we prepare a carray, assign variables etc. we have to substract the preparation time measured before.
        double time_bs1_random((pfc::in_s(pfc::timed_run(test_bs1_rand)) - time_bs_prep) / bs_N / m * 1000 * 1000 * 1000);
        double time_bs1_notfound((pfc::in_s(pfc::timed_run(test_bs1_out)) - time_bs_prep) / bs_N / m * 1000 * 1000 * 1000);
        double time_bs2_random((pfc::in_s(pfc::timed_run(test_bs2_rand)) - time_bs_prep) / bs_N / m * 1000 * 1000 * 1000);
        double time_bs2_notfound((pfc::in_s(pfc::timed_run(test_bs2_out)) - time_bs_prep) / bs_N / m * 1000 * 1000 * 1000);
        double time_bs3_random((pfc::in_s(pfc::timed_run(test_bs3_rand)) - time_bs_prep) / bs_N / m * 1000 * 1000 * 1000);
        double time_bs3_notfound((pfc::in_s(pfc::timed_run(test_bs3_out)) - time_bs_prep) / bs_N / m * 1000 * 1000 * 1000);

        bs_out << C_SIZE << ";" << time_bs1_random << ";" << time_bs1_notfound
            << ";" << time_bs2_random << ";" << time_bs2_notfound
            << ";" << time_bs3_random << ";" << time_bs3_notfound << std::endl;

        // Increase it by factor of 10 to get a nice approximation without using too much resources.
        C_SIZE *= 10;
    }
    bs_out.close();

}


int binary_search_1(int* const& vec, size_t const n, int const x)
{
    int l(0), r(n - 1);

    while (l <= r)
    {
        int m = (l + r) / 2;

        if (vec[m] == x)
        {
            return m;
        }
        else if (vec[m] > x)
        {
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }

    return -1;
}
int binary_search_2(int* const& vec, size_t const n, int const x)
{
    int l(0), r(n - 1);

    while (true)
    {
        if (l > r)
        {
            return -1;
        }

        int m = (l + r) / 2;

        if (vec[m] > x)
        {
            r = m - 1;
        }
        else if (vec[m] < x)
        {
            l = m + 1;
        }
        else
        {
            return m;
        }
    }
}
int binary_search_3(int* const& vec, size_t const n, int const x)
{
    int l(0), r(n - 1);

    while (l < r)
    {
        int m = (l + r) / 2;

        if (vec[m] < x)
        {
            l = m + 1;
        }
        else
        {
            r = m;
        }
    }

    if (vec[r] == x)
    {
        return r;
    }
    else
    {
        return -1;
    }
}

int* get_carray(size_t n)
{
    // Allocate new memory and set each index to a value.
    int* carray = new int[n];
    for (int i(0); i < n; i++)
    {
        carray[i] = i;
    }
    return carray;
}
void test_bs_prep()
{
    // Execute everything except the binary search to subtract its runtime later.
    int a(122), b(48), c(33), d(22), e(55), z(0);
    int* testcarray = get_carray(C_SIZE);
    for (int i(1); i < bs_N; i++)
    {
        // nothing
    }
    delete[] testcarray;
}
void test_bs1_rand()
{
    int a(122), b(48), c(33), d(22), e(55), z(0);

    int* testcarray = get_carray(C_SIZE);
    for (int i(1); i < bs_N; i++)
    {
        a = binary_search_1(testcarray, C_SIZE, rand() % C_SIZE);
        b = binary_search_1(testcarray, C_SIZE, rand() % C_SIZE);
        c = binary_search_1(testcarray, C_SIZE, rand() % C_SIZE);
        d = binary_search_1(testcarray, C_SIZE, rand() % C_SIZE);
        e = binary_search_1(testcarray, C_SIZE, rand() % C_SIZE);
    }
    delete[] testcarray;
}
void test_bs1_out()
{
    int a(122), b(48), c(33), d(22), e(55), z(0);

    int* testcarray = get_carray(C_SIZE);
    for (int i(1); i < bs_N; i++)
    {
        a = binary_search_1(testcarray, C_SIZE, -1);
        b = binary_search_1(testcarray, C_SIZE, -1);
        c = binary_search_1(testcarray, C_SIZE, -1);
        d = binary_search_1(testcarray, C_SIZE, -1);
        e = binary_search_1(testcarray, C_SIZE, -1);
    }
    delete[] testcarray;
}
void test_bs2_rand()
{
    int a(122), b(48), c(33), d(22), e(55), z(0);

    int* testcarray = get_carray(C_SIZE);
    for (int i(1); i < bs_N; i++)
    {
        a = binary_search_2(testcarray, C_SIZE, rand() % C_SIZE);
        b = binary_search_2(testcarray, C_SIZE, rand() % C_SIZE);
        c = binary_search_2(testcarray, C_SIZE, rand() % C_SIZE);
        d = binary_search_2(testcarray, C_SIZE, rand() % C_SIZE);
        e = binary_search_2(testcarray, C_SIZE, rand() % C_SIZE);
    }
    delete[] testcarray;
}
void test_bs2_out()
{
    int a(122), b(48), c(33), d(22), e(55), z(0);

    int* testcarray = get_carray(C_SIZE);
    for (int i(1); i < bs_N; i++)
    {
        a = binary_search_2(testcarray, C_SIZE, -1);
        b = binary_search_2(testcarray, C_SIZE, -1);
        c = binary_search_2(testcarray, C_SIZE, -1);
        d = binary_search_2(testcarray, C_SIZE, -1);
        e = binary_search_2(testcarray, C_SIZE, -1);
    }
    delete[] testcarray;
}
void test_bs3_rand()
{
    int a(122), b(48), c(33), d(22), e(55), z(0);

    int* testcarray = get_carray(C_SIZE);
    for (int i(1); i < bs_N; i++)
    {
        a = binary_search_3(testcarray, C_SIZE, rand() % C_SIZE);
        b = binary_search_3(testcarray, C_SIZE, rand() % C_SIZE);
        c = binary_search_3(testcarray, C_SIZE, rand() % C_SIZE);
        d = binary_search_3(testcarray, C_SIZE, rand() % C_SIZE);
        e = binary_search_3(testcarray, C_SIZE, rand() % C_SIZE);
    }
    delete[] testcarray;
}
void test_bs3_out()
{
    int a(122), b(48), c(33), d(22), e(55), z(0);

    int* testcarray = get_carray(C_SIZE);
    for (int i(1); i < bs_N; i++)
    {
        a = binary_search_3(testcarray, C_SIZE, -1);
        b = binary_search_3(testcarray, C_SIZE, -1);
        c = binary_search_3(testcarray, C_SIZE, -1);
        d = binary_search_3(testcarray, C_SIZE, -1);
        e = binary_search_3(testcarray, C_SIZE, -1);
    }
    delete[] testcarray;
}
