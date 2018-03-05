#include <gtest/gtest.h>
#include "fileWatcher.cpp"
#include <fstream>
#include <thread>
#include <iostream>
#include <ios>

using namespace fileWatcher;
class FileWatcherTest : public ::testing::Test
{
public:
	FileWatcherTest():the_fileName("./file.txt"),the_queue(), sut(the_fileName, the_queue){}
	void modifyFile(std::ios_base::openmode mode = std::ios_base::trunc)
	{
		
		std::ofstream outfile(the_fileName, mode);
		outfile << the_line <<std::endl;
		
	}
const std::string the_line = "2014.01.02T12:00:14, 67 1234 5678 0000 0000 1234 5678, 68 1234 5678 0000 0000 1234 5678, 123.45";
const std::string the_shorter_line = "2014.01.02T12:00:14, 67 1234 5678 0000 0000 1234 5678, 68 1234 5678 0000 0000 1234 5678, 3.45";
std::string the_fileName;
concurrent_queue<std::pair<size_t, size_t>> the_queue;
FileWatcher sut;

};

TEST_F(FileWatcherTest, shouldAddCorrectValuesToQueueWhenFileHaveOneLineAndIsUpdatedWithLine)
{
	modifyFile();
	sut.processFile();	
	EXPECT_EQ(the_queue.size(), 1);
	auto res = the_queue.wait_and_pop();
	EXPECT_EQ(res.first, 0);
	EXPECT_EQ(res.second, strlen(the_line.c_str())+1);
	
	modifyFile(std::ios_base::app);
	sut.processFile();	
	EXPECT_EQ(the_queue.size(), 1);
	res = the_queue.wait_and_pop();
	EXPECT_EQ(res.first, strlen(the_line.c_str())+1);
	EXPECT_EQ(res.second, 2*(strlen(the_line.c_str())+1));
}
