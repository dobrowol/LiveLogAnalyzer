#pragma once
#include <map>
#include<string>
namespace printer
{
class ReportPrinter
{
public:
	virtual void print(std::map<std::string, double> amountForBank, double totalAmount) = 0;	
};
}
