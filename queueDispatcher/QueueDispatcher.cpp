#include "concurrent_queue.hpp"
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include "../reportPrinter/ReportPrinter.hpp"
namespace queueDispatcher
{
class QueueDispatcher
{
public:
        QueueDispatcher(std::string fileName, utils::concurrent_queue<std::pair<size_t, size_t>>& queue,
                        printer::ReportPrinter& reportPrinter):the_fileName(fileName), totalAmount(0), the_queue(queue)
                        , the_reportPrinter(reportPrinter)
	{
	}
	void dispatch()
	{
		while (true)
		{
                    processFile(the_queue.wait_and_pop());
                    createReport();
		}
	}
        void processFile(std::pair<size_t, size_t> filePositions)
        {
            std::ifstream infile(the_fileName);
            std::string line;
            if(infile.is_open() && (filePositions.second > filePositions.first))
            {
                infile.seekg(filePositions.first);

                std::string file_part;
                file_part.resize(filePositions.second - filePositions.first);
                infile.read(&file_part[0], filePositions.second - filePositions.first);
                std::istringstream iss(file_part);
                while (std::getline(iss, line))
                {
                    parseLine(line);
                }
            }
        }

        void createReport()
        {
            the_reportPrinter.print(amountForBank, totalAmount);
            totalAmount = 0;
            amountForBank.clear();
        }

private:
        void parseLine(std::string line)
        {
                std::vector<std::string>   result;
                std::stringstream lineStream(line);
                std::string cell;
                while(std::getline(lineStream,cell, ','))
                {
                        result.push_back(cell);
                }
                double amount = string_to_double(result.back());
                totalAmount += amount;
                auto it  = amountForBank.find(result[targetBankIndex]);
                if (it != amountForBank.end()){
                        it->second += amount;
                }
                else{
                        amountForBank[result[targetBankIndex]] += amount;
                }

        }
        double string_to_double( const std::string& s )
        {
                std::istringstream i(s);
                double x;
                if (!(i >> x))
                        return 0;
                return x;
        }
	const int targetBankIndex = 2;
	double totalAmount;
        utils::concurrent_queue<std::pair<size_t, size_t>>& the_queue;
        printer::ReportPrinter& the_reportPrinter;
	std::map<std::string, double> amountForBank;
        std::string the_fileName;
};
}
