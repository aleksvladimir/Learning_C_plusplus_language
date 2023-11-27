#pragma once

#include <iostream> 
#include <atomic> 
#include <mutex> 
#include <queue> 
#include <thread> 

//todo: Сделать класс - CoutLogger

// мьютекс для вывода сообщений в консоль (std::cout не потокобезопасный)
std::mutex cout_mx;

/**
 * \brief Запрос
 */
class Request
{
public:
  Request() = default;
  Request( size_t request_id ) : id( request_id )
  {
    std::cout << " - Called constructor. Request task " << id << ".\n";    
  }
  ~Request()
  {
    std::cout << " - Called destructor. Request task " << id << ".\n";    
  }

  /**
   * \brief Обработка запроса
   */
  void handling()
  {
    // происходит обработка запроса 
    std::this_thread::sleep_for( std::chrono::microseconds( 200 ) );
  }

  // для удобства отладки утечки памяти
  void * operator new( size_t size )
  {
    auto p = malloc( size );
    std::cout << " - Malloc: " << p << "\n";
    return p;
  }
  // для удобства отладки утечки памяти
  void operator delete( void * p )
  {
    {
      std::lock_guard<std::mutex> cout_lock( cout_mx );
      std::cout << " - Free: " << p << "\n";
    }
    return free( p );
  }

  size_t id = 0;  // id запроса
};

//todo: Сделать класс - RequstQueue

// пользовательская очередь заданий
static std::queue<Request *> requestQueue;

/**
 * \brief Получить запрос
 * \return Возвращает nullptr если нужно завершить процесс, либо указатель на память, которую в дальнейшем требуется удалить 
 */
Request * GetRequest() noexcept
{
  // происходит получение запроса 
  std::this_thread::sleep_for( std::chrono::microseconds( 1 ) );
  Request *request = nullptr;
  try
  {
    // в очереди есть запросы и они не пустые
    if ( !requestQueue.empty() )
    {
      request = requestQueue.front();
      requestQueue.pop();
    }
    else
      return nullptr;
  }
  catch ( ... )
  {
  }
  return request;
}

//todo: Сделать класс - ProcessRequest

/**
 * \brief Обрабатывает запрос, но память не удаляет 
 * \param request - запрос
 */
void ProcessRequest( Request * request ) noexcept
{
  try
  {
    request->handling();
  }
  catch ( ... )
  {
  }
}

// todo: Отдельный класс - WorkThreads

// количество рабочих потоков 
const int NumberOfThreads = 2;

// очередь заданий для рабочих потоков 
std::queue<Request *> workRequestQueue;

// мьютекс для выталкивания запросов из очереди заданий для рабочих потоков 
std::mutex workMutex;

// флаг необходимости продолжать работу потока, поток должен завершиться, как только основной поток ему это скомандует 
static std::atomic<bool> needWork = true;

// уведомитель наличия запросов. выполняет блокировку потока и
//  синхронизацию очереди между рабочими потоками и главным потоком
std::condition_variable work_req_queue_notifier;

/**
 * \brief Функция рабочего потока.
 * Вызовы GetRequest() и ProcessRequest() могут работать долго. 
 * \param thread_id - id потока
 */
void workThread( size_t thread_id )
{
  try
  {
    // Завершиться, как только основной поток ему это скомандует. 
    while ( needWork )
    {
      Request * workRequest = nullptr;
      {
        std::unique_lock<std::mutex> unique_lock( workMutex );
        if ( !work_req_queue_notifier.wait_for( unique_lock, std::chrono::milliseconds( 100 ),
          [] { return !workRequestQueue.empty() || needWork == true; } ) )
          continue;
        if ( workRequestQueue.empty() )
          continue;
        workRequest = workRequestQueue.front();
        workRequestQueue.pop();
      }
      {
        std::lock_guard<std::mutex> cout_lock( cout_mx );
        std::cout << " - Work thread #" << thread_id << " took task: " << workRequest->id << "\n";
      }
      // Обрабатывать поступающие через очередь запросы с помощью ProcessRequest. 
      ProcessRequest( workRequest );
      {
        std::lock_guard<std::mutex> cout_lock( cout_mx );
        std::cout << " - Work thread #" << thread_id << " task: " << workRequest->id << " done!\n";
      }

      // очистка памяти обработанных запросов (не обработанные запросы будут очищенны главным потоком!
      delete workRequest;
    }
  }
  catch ( ... )
  {
  }
  std::lock_guard<std::mutex> cout_lock( cout_mx );
  std::cout << " - Work thread #" << thread_id << " finished job\n";
}