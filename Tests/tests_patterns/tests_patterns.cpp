#include "../../EducationLibs/Patterns/Singleton.h"
#include "../../EducationLibs/Patterns/ThreadPool_Requests.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests_templates
{
	TEST_CLASS( TestsTemplates )
	{
	public:
		
		TEST_METHOD( TestSingleton )
		{
      auto & fm = FileManager::getInstance();
      FileManager ss;
      auto & fm2 = ss.getInstance();
			Assert::IsTrue( &fm.val == &fm2.val );
		}

		TEST_METHOD( TestThreadPool_requests )
		{
      try
      {
        // граница дл€ разделени€ данных в консоли
        const char * border = "----------------------------\n";

        // ‘ормирование очереди задач/запросов
        const int NumberOfTask = 14;  // количество задач/запросов
        std::cout << border;
        std::cout << "Forming queries: \n";
        for ( size_t id = 1; id <= NumberOfTask; ++id )
          requestQueue.push( new Request( id ) );
        requestQueue.push( nullptr );
        std::cout << "Number of tasks: " << NumberOfTask << "\n";

        Assert::IsTrue( 14 == requestQueue.size() - 1 );

        // «апуск несколько рабочих потоков (NumberOfThreads).
        std::cout << border;
        std::cout << "Number of work threads: " << NumberOfThreads << "\n";
        std::cout << border;
        std::thread threadsList[ NumberOfThreads ];
        size_t thread_id = 1;
        for ( auto & thread : threadsList )
          thread = std::thread( workThread, thread_id++ );

        // ”кладка в одну очередь задач до тех пор, пока GetRequest() не вернЄт nullptr. 
        auto request = GetRequest();
        while ( request )
        {
          {
            std::lock_guard<std::mutex> unique_lock( workMutex );
            workRequestQueue.push( request );
          }
          work_req_queue_notifier.notify_one();
          {
            std::lock_guard<std::mutex> cout_lock( cout_mx );
            std::cout << "Main thread put task: " << request->id << "\n";
          }
          request = GetRequest();
        }

        //  орректна€ остановка рабочих потоков. ќни должны доделать текущий ProcessRequest, если он имеетс€, и остановитьс€.
        // ≈сли имеютс€ необработанные задани€, не обращать на них внимани€. 
        needWork = false;
        work_req_queue_notifier.notify_one();
        for ( auto & thread : threadsList )
        {
          if ( thread.joinable() )
            thread.join();
        }
        std::cout << border;
        std::cout << "Number of outstanding tasks: " << workRequestQueue.size() << "\n";

        // очистка пам€ти оставшихс€ запросов производитс€ главным потоком
        while ( !workRequestQueue.empty() )
        {
          delete workRequestQueue.front();
          workRequestQueue.pop();
        }
        Assert::IsTrue( workRequestQueue.empty() );

        // «авершение программы.
        std::cout << border;
        std::cout << "Threads stopped successfully" << "\n";
        std::cout << "The program is completed." << "\n";

        Assert::IsTrue( request == nullptr );
      }
      catch ( ... )
      {
        Assert::IsTrue( false );
      }
		}
	};
}
