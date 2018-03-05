#include <gtest/gtest.h>
#include "QueueDispatcher.cpp"
#include "ReportPrinterMock.hpp"

using namespace queueDispatcher;
class QueueDispatcherTest : public ::testing::Test
{
public:
	const std::string the_line = "2014.01.02T12:00:14, 67 1234 5678 0000 0000 1234 5678, 68 1234 5678 0000 0000 1234 5678, 123.45";
	const std::string the_secondLine = "2014.03.01T10:11:14, 40 1234 5678 0000 0000 1234 5678, 50 1234 5678 0000 0000 1234 5678, 25000.00";
	printer::ReportPrinterMock the_printerMock;
	std::string the_fileName;
	utils::concurrent_queue<std::pair<size_t, size_t>> the_queue;
	QueueDispatcher sut;

	QueueDispatcherTest():the_fileName("./queue_test.txt"), sut(the_fileName, the_queue, the_printerMock){}
	
	void modifyFile(std::ios_base::openmode mode = std::ios_base::trunc)
	{
		
		std::ofstream outfile(the_fileName, mode);
		outfile << the_line <<std::endl;
		outfile << the_secondLine <<std::endl;
		
	}
};
TEST_F(QueueDispatcherTest, create)
{
	modifyFile();
	auto inp = std::make_pair(0, the_line.size() + the_secondLine.size());
	sut.processFile(inp);
	EXPECT_CALL(the_printerMock, print(::testing::_, 25123.45));
	sut.createReport();
}
