#include "ReportPrinter.hpp"
#include <iostream>
#include <algorithm>
namespace
{
template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                   flip_pair<A,B>);
    return dst;
}
}
namespace printer
{
class DefaultPrinter : public ReportPrinter 
{
typedef std::map<std::string, double> ResultMap;
typedef std::map<double, std::string> ReversedResultMap;
public:
	void print(ResultMap amountForBank, double totalAmount) override	
	{
		auto sortedAmountForBank = flip_map<std::string, double>(amountForBank);
		for (ReversedResultMap::reverse_iterator it = sortedAmountForBank.rbegin(); it != sortedAmountForBank.rend(); it++)
		{
			std::cout << "amount for " << (*it).second << " is " << (*it).first << std::endl;
		}	
		std::cout << "total amount is " << totalAmount << std::endl;
	}
};
}
