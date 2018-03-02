#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
namespace utils
{
template<class Data>
class concurrent_queue
{
private:
    std::queue<Data> the_queue;
    std::condition_variable the_condition_variable;
    std::mutex the_mutex;
public:
    void push(Data const& data)
    {
	    std::unique_lock<std::mutex> lock(the_mutex);
	    bool const was_empty=the_queue.empty();
	    the_queue.push(data);

	    if(was_empty)
	    {
		    the_condition_variable.notify_one();
	    }
    }
    Data wait_and_pop()
    {
	    std::unique_lock<std::mutex> lock(the_mutex);
	    while(the_queue.empty())
	    {
		    the_condition_variable.wait(lock);
	    }

	    Data return_value=the_queue.front();
	    the_queue.pop();
	    return return_value;
    }
    int size(){return the_queue.size();}
};
}
