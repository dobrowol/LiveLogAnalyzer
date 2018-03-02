#include <iostream>
#include "concurrent_queue.cpp"
#include "fileWatcher/fileWatcher.cpp"
#include "queueDispatcher/QueueDispatcher.cpp"
#include <thread>
using namespace std;
using namespace utils;

concurrent_queue<std::pair<size_t, size_t>> q;
std::string exampleLogFile = "./example.txt";
void runFileWatcher()
{
    fileWatcher::FileWatcher fw(exampleLogFile, q);
    fw.proceed();
    /*for (int i =0; i < 10;i++)
    {
        std::cout << "thread 1" << std::endl;
        sleep(2);
    }*/
}
void runQueueDispatcher()
{
    queueDispatcher::QueueDispatcher qd(exampleLogFile,q);
	qd.dispatch();    
}
void sizeQueue()
{
	while (true)
	{
		std::cout << "size of " << q.size() << std::endl;
        sleep(1);
	}
}
int main(int argc, char *argv[])
{
    std::thread t(runFileWatcher);
    std::thread t2(runQueueDispatcher);
    t.join();
    t2.join();
   //
   // t2.join();
    return 0;
}
