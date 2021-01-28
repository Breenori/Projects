#include "bf_search.h"
#include "bm_search.h"
#include "kmp_search.h"
#include "datacollector.h"
#include<time.h>
#include<string>
#include<fstream>

typedef std::pair<int, size_t> result_type;

enum variant { BF, BM, KMP };

// Returns a generated text of desired length containing only letters of the desired alphabet.
std::string generate_text(size_t const length, std::vector<char> const& alphabet);
// Returns position and amount of comparisons for a specific search algorithm and text/pattern combo while collecting data in the given datacollector.
result_type test_search(std::string const& text, std::string const& pattern, datacollector& dc, variant const searcher, std::vector<char> charset, size_t const start_pos = 0);
// Prints amount of comparisons and position to console.
void print_result(result_type const& result);
// Tests bruteforce, boyer moore and knuth moris pratt algorithm for a single text/pattern/charset combo.
void test_all_functions(std::string const& text, std::string const& pattern, std::vector<char> charset, std::string const& filename);
// Tests all functions and scenarios and creates csv files for each testcase.
void test_and_print();
// Tests all the testcases specified in the documentation
void testcases();

void main()
{
	srand((int)time(0));
	//test_and_print();
	testcases();
}

void test_and_print()
{
	// Create all the necessary charsets
	std::vector<char> binary = { '0', '1' };
	std::vector<char> basepairs = { 'A', 'G', 'C', 'T' };
	std::vector<char> aminoacids = { 'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V', 'B', 'Z', 'J' };
	std::vector<char> ascii;
	for (int c(0); c < 256; c++)
	{
		ascii.push_back((char)c);
	}

	// Worst case
	std::string worst_case_t("");
	std::string worst_case_p("00001");
	for (int i(0); i < 10000; i++)
	{
		worst_case_t += "00000";
	}
	worst_case_t += "1";

	// Best case (BM) (T not present in pattern, full shift)
	std::string best_case_t("ACGAGTACGAGTACGAGTACGAGT");
	std::string best_case_p("ACGAGG");

	// Example for aminoacids
	std::string aa_t("MVLSPADKTN VKAAWGKVGA HAGEYGAEAL ERMFLSFPTT KTYFPHFDLS HGSAQVKGHG KKVADALTNA VAHVDDMPNA LSALSDLHAH KLRVDPVNFK LLSHCLLVTL AAHLPAEFTP AVHASLDKFL ASVSTVLTSK YR");
	std::string aa_p("VAHV");

	// Random "text"
	std::string rand_ascii(generate_text(10000, ascii));

	// Usual text
	std::string usual_text("");
	std::ifstream in("lorem.txt");
	std::string line;
	std::string usual_pattern("ullamcorper");
	if (in)
	{
		while (std::getline(in, line))
		{
			usual_text += line;
		}
	}
	in.close();

	// Test all functions for all scenarios
	test_all_functions(worst_case_t, worst_case_p, binary, "binary_worstcase");
	std::cout << std::endl;
	test_all_functions(best_case_t, best_case_p, basepairs, "basepair_bestcase");
	std::cout << std::endl;
	test_all_functions(aa_t, aa_p, aminoacids, "aminoacids_test");
	std::cout << std::endl;
	test_all_functions(rand_ascii, "r2d2", ascii, "ascii_randomtext");
	std::cout << std::endl;
	test_all_functions(usual_text, usual_pattern, ascii, "ascii_usualtext");
}
void testcases()
{
	// Create two charsets to test
	std::vector<char> binary = { '0', '1' };
	std::vector<char> ascii;
	for (int c(0); c < 256; c++)
	{
		ascii.push_back((char)c);
	}

	datacollector dc(ascii);

	// Test empty text and populated pattern
	size_t bf = bf_search::match("", "looooooooooooooooooooooooooooong", dc);
	size_t bm = bm_search::match("", "looooooooooooooooooooooooooooong", dc);
	size_t kmp = kmp_search::match("", "looooooooooooooooooooooooooooong", dc);

	// Test empty pattern and populated text
	bf = bf_search::match("short", "", dc);
	bm = bm_search::match("short", "", dc);
	kmp = kmp_search::match("short", "", dc);

	// Test pattern longer than text
	bf = bf_search::match("short", "looooooooooooooooooooooooooooong", dc);
	bm = bm_search::match("short", "looooooooooooooooooooooooooooong", dc);
	kmp = kmp_search::match("short", "looooooooooooooooooooooooooooong", dc);

	// Test with uninitialized datacollector
	datacollector uninitialized;
	bf = bf_search::match("short", "looooooooooooooooooooooooooooong", dc);
	bm = bm_search::match("short", "looooooooooooooooooooooooooooong", dc);
	kmp = kmp_search::match("short", "looooooooooooooooooooooooooooong", dc);

	// Test with datacollector having wrong charset
	dc.init(binary);
	bf = bf_search::match("short", "looooooooooooooooooooooooooooong", dc);
	bm = bm_search::match("short", "looooooooooooooooooooooooooooong", dc);
	kmp = kmp_search::match("short", "looooooooooooooooooooooooooooong", dc);
}
result_type test_search(std::string const& text, std::string const& pattern, datacollector& dc, variant const searcher, std::vector<char> charset, size_t const start_pos)
{
	// Create a pair to return both the position AND the amount of comparisons
	std::pair<int, size_t> result;

	dc.init(charset);

	switch (searcher)
	{
	case(variant::BF):
		result.first = bf_search::match(text, pattern, dc, start_pos);
		break;
	case(variant::BM):
		result.first = bm_search::match(text, pattern, dc, start_pos);
		break;
	case(variant::KMP):
		result.first = kmp_search::match(text, pattern, dc, start_pos);
		break;
	}
	result.second = dc.get_comparison_count();

	return result;
}
void print_result(result_type const& result)
{
	if (result.first == -1)
	{
		std::cout << "Pattern not found." << std::endl;
	}
	else
	{
		std::cout << "Pattern found at: " << result.first << std::endl;
	}
	std::cout << "Comparisons made: " << result.second << std::endl;
}
void test_all_functions(std::string const& text, std::string const& pattern, std::vector<char> charset, std::string const& filename)
{
	datacollector dc;

	std::ofstream out("output/" + filename + ".csv");

	// Execute all algorithms and save the important data
	result_type result_bf(test_search(text, pattern, dc, variant::BF, charset));
	std::vector<size_t> bf_s(dc.get_success_statistics());
	std::vector<size_t> bf_f(dc.get_failure_statistics());
	size_t bf_c(dc.get_comparison_count());
	result_type result_bm(test_search(text, pattern, dc, variant::BM, charset));
	std::vector<size_t> bm_s(dc.get_success_statistics());
	std::vector<size_t> bm_f(dc.get_failure_statistics());
	size_t bm_c(dc.get_comparison_count());
	result_type result_kmp(test_search(text, pattern, dc, variant::KMP, charset));
	std::vector<size_t> kmp_s(dc.get_success_statistics());
	std::vector<size_t> kmp_f(dc.get_failure_statistics());
	size_t kmp_c(dc.get_comparison_count());

	// Print the overall info to the console.
	print_result(result_bf);
	print_result(result_bm);
	print_result(result_kmp);

	// Print the datacollector info to csv file
	out << "character;bf_success;bf_failure;bm_success;bm_failure;kmp_success;kmp_failure\n";
	for (size_t i(0); i < charset.size(); i++)
	{
		// Ignore rows containing only zeroes
		if (bf_s[i] > 0 || bf_f[i] > 0 || bm_s[i] > 0 || bm_f[i] > 0 || kmp_s[i] > 0 || kmp_f[i] > 0)
		{
			// The first characters in ASCII charset can't be displayed properly, so we substitute them with something else.
			if (charset.size() == 256 && i <= 31)
			{
				out << "[control char]" << i << ";";
			}
			else
			{
				// semicolon, quotes and double quotes are reserved and need to be handled differently.
				// to keep things consistent, everything other than single quotes are displayed between single quotes. (e.g. 'A' instead of A)
				if (charset[i] == (char)59)
				{
					out << "\" ' \";";
				}
				else
				{
					out << "' " << charset[i] << " '" << ";";
				}
			}

			// OUtput all the successful and failed attempts for each letter
			out << bf_s[i] << ";" << bf_f[i] << ";" << bm_s[i] << ";" << bm_f[i] << ";" << kmp_s[i] << ";" << kmp_f[i] << std::endl;
		}
	}

	out << std::endl;

	// Print total comparisons
	out << "bf_total;" << bf_c << std::endl;
	out << "bm_total;" << bm_c << std::endl;
	out << "kmp_total;" << kmp_c << std::endl;

	out.close();
}
std::string generate_text(size_t const length, std::vector<char> const& alphabet)
{
	std::string text("");
	// Generate a text based on the alphabet size and the desired length
	if (alphabet.size() > 0)
	{
		for (size_t i(0); i < length; i++)
		{
			text += alphabet[rand() % alphabet.size()];
		}
	}
	return text;
}