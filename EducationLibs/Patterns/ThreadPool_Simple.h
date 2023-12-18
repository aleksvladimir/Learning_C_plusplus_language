#pragma once

#include <condition_variable>
#include <future>
#include <thread>
#include <vector>
#include <queue>

/**
 * \brief Thread pool implementation
 *
 * todo:
 * - Add the ability to pass an argument (or multiple) to each task’s invocation.
 * - Add a “future”-like object which gets returned from add_task and lets you query status, result, etc.
 * - Add a way to ask the thread pool “how busy are you?”.
 * - Scale the thread pool up and down automatically based on demand.
 * - Use a priority queue instead.
 */
class ThreadPool
{
public:
  using Task = std::function<void()>;

  explicit ThreadPool( uint32_t num_threads )
  {
    if ( num_threads > max_threads_count )
      num_threads = max_threads_count;
    thread_list.reserve( num_threads );
    for ( size_t i = 0; i < num_threads; ++i )
      thread_list.emplace_back( &ThreadPool::run, this );
  }

  ~ThreadPool() noexcept
  {
    quit = true;
    task_cv_notify.notify_all();
    for ( auto & thread : thread_list )
      if ( thread.joinable() )
        thread.join();
  }

  /**
   * \brief Adds a task to be executed
   * \param task - task to be executed
   */
  void add_task( Task task )
  {
    std::unique_lock<std::mutex> lock( task_mutex );
    task_list.emplace( std::move( task ) );
    lock.unlock();
    task_cv_notify.notify_one();
  }

private:

  static const size_t max_threads_count = 1024;
  std::vector<std::thread> thread_list;

  std::queue<Task> task_list;                     // task list with callbacks (user use method add_task)
  std::condition_variable task_cv_notify;         // notify about a new task in the task list
  std::mutex task_mutex;                          // mutex for sync task list: when producer and consumer pushing and popping a tasks

  std::atomic<bool> quit = false;                // flag to end executing tasks by thread pool

  void run() noexcept
  {
    while ( !quit )
    {
      try
      {
        std::unique_lock<std::mutex> u_lock( task_mutex );
        task_cv_notify.wait( u_lock, [this]() { return quit || !task_list.empty(); } ); // lock when woken up, unlock when sleep
        if ( !quit && !task_list.empty() )
        {
          Task task = std::move( task_list.front() );
          task_list.pop();
          u_lock.unlock();
          task();
        }
      }
      catch ( ... )
      {
      }
    }
  }
};

// HOW TO USE:
//#include <iostream>
//int main()
//{
//  try
//  {
//    ThreadPool threadPool( 2025 );
//    std::mutex cout_mx;
//    auto i = 1u;
//    while ( i++ < 3004 )
//    {
//      threadPool.add_task( [&cout_mx, i]()->void {
//        std::unique_lock<std::mutex> cout_lock( cout_mx );
//        std::cout << "executing task " << i << " by thread " << std::this_thread::get_id() << "...\n";
//        cout_lock.unlock();
//        std::this_thread::sleep_for( std::chrono::seconds( 10 ) );
//        cout_lock.lock();
//        std::cout << "executed task " << i << " by thread " << std::this_thread::get_id() << "...\n";
//        } );
//      std::unique_lock<std::mutex> cout_lock( cout_mx );
//      std::cout << "main add task " << i << "\n";
//      cout_lock.unlock();
//      std::this_thread::sleep_for( std::chrono::microseconds( 1 ) );
//    }
//
//    std::this_thread::sleep_for( std::chrono::seconds( 10 ) );
//  }
//  catch ( ... )
//  {
//  }
//}
