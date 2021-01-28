#ifndef ANALYSIS_TRAITS_H
#define ANALYSIS_TRAITS_H

#include<string>
#include<limits>

using std::string;

namespace analysis {
	template<typename T>
	class analysis_trait {
	public:
		static string max() {
			return "Not available";
		}
		static string min() {
			return "Not available";
		}
		static string neg(T const& value) {
			return "Not available";
		}
		static string zero()
		{
			return "Not available";
		}
		static string one() {
			return "Not available";
		}

		static string as_string(T const& value)
		{
			return "unknown type\n";
		}
	};

	template<>
	class analysis_trait<int> {
	public:
		typedef int value_t;

		static value_t max() {
			return INT_MAX;
		}
		static value_t min() {
			return INT_MIN;
		}
		static value_t neg(const value_t& v) {
			return v * -1;
		}
		static value_t zero()
		{
			return 0;
		}
		static value_t one() {
			return 1;
		}

		static string as_string(value_t const& v)
		{
			return "int: " + std::to_string(v) + "\n";
		}
	};

	template<>
	class analysis_trait<double> {
	public:
		typedef double value_t;

		static value_t max() {
			return DBL_MAX;
		}
		static value_t min() {
			return DBL_MIN;
		}
		static value_t neg(const value_t& v) {
			return v * -1.0;
		}
		static value_t zero()
		{
			return 0.0;
		}
		static value_t one() {
			return 1.0;
		}

		static string as_string(value_t const& v)
		{
			return "double: " + std::to_string(v) + "\n";
		}
	};
}

#endif