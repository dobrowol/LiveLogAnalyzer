#include "gtest/gtest.h"
#include "concurrent_queue.cpp"
#include <string>
#include <iostream>
#include <thread>
// The fixture for testing class Foo.
using namespace utils;

class QueueTest : public ::testing::Test {

public:
    concurrent_queue sut;
    std::string popped_value;
    void pop()
    {
        popped_value = sut.wait_and_pop();
    }

protected:
	QueueTest():sut(){}

};

void pushToQueue(QueueTest* t)
{
    std::cout << "push To queue"<<std::endl;

    t->sut.push("wiersz");
}
void popFromQueue(QueueTest* t )
{
    std::cout << "pop from queue"<<std::endl;

    t->pop();

}

TEST_F(QueueTest, pushAndPop)
{
    std::string wiersz = "wiersz";
    void * inpParam = static_cast<void*>(&wiersz);
    std::thread t1(pushToQueue, this);
    std::thread t2(popFromQueue, this);
    t1.join();
    t2.join();

    EXPECT_EQ(popped_value, wiersz);
}
TEST_F(QueueTest, popAndPush)
{
    std::string wiersz = "wiersz";
    void * inpParam = static_cast<void*>(&wiersz);
    std::thread t1(pushToQueue, this);
    std::thread t2(popFromQueue, this);
    t2.join();
    t1.join();

    EXPECT_EQ(popped_value, wiersz);
}
	
