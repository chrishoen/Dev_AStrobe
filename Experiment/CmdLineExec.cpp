#include "stdafx.h"


#include <boost/lambda/lambda.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/atomic.hpp>
#include <atomic>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sqlite3.h>
#include <filesystem>

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if (aCmd->isCmd("GO1"))  executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))  executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))  executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))  executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))  executeGo5(aCmd);
   if (aCmd->isCmd("GO6"))  executeGo6(aCmd);
   if (aCmd->isCmd("GO7"))  executeGo7(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   using namespace boost::lambda;
   typedef std::istream_iterator<int> in;

   std::for_each(
      in(std::cin), in(), std::cout << (_1 * 3) << " ");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
std::atomic<int> mAtomicInt;
std::atomic< int > m_CommandTries{ 0 };
std::atomic< unsigned long long > m_CommandNumber{ 0 };
std::atomic< unsigned long long > m_FailCommandNumber{ 0 };
std::atomic< unsigned long long > m_RetryCommandNumber{ 0 };

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   mAtomicInt++;

   Ris::CmdLineCmd* tCmd = new Ris::CmdLineCmd("test1, 101, 102.9, data1", true);

   Prn::print(0, "numArg %10d", tCmd->numArg());
   Prn::print(0, "cmd    %10s", my_string_from_bool(tCmd->isCmd("test1")));
   Prn::print(0, "arg1   %10d", tCmd->argInt(1));
   Prn::print(0, "arg2   %10.4f", tCmd->argDouble(2));
   Prn::print(0, "arg3   %10s", tCmd->argString(3));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   std::filesystem::path tPath = "/usr/lib/sendmail.cf";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   using namespace std;
   sqlite3* db;
   char* szErrMsg = 0;

   // open database
   int rc = sqlite3_open("Sqlite_Test.db", &db);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   char tString[200];

   while (true)
   {
      fgets(tString, 200, stdin);
      printf("CMD %d %s", (int)strlen(tString), tString);
      if (strcmp(tString, "e\n") == 0) break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

class X {
public:
   typedef boost::intrusive_ptr<X> pointer;
   X() : refcount_(0) {}

private:
   mutable boost::atomic<int> refcount_;
   friend void intrusive_ptr_add_ref(const X* x)
   {
      x->refcount_.fetch_add(1, boost::memory_order_relaxed);
   }
   friend void intrusive_ptr_release(const X* x)
   {
      if (x->refcount_.fetch_sub(1, boost::memory_order_release) == 1) {
         boost::atomic_thread_fence(boost::memory_order_acquire);
         delete x;
      }
   }
};

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   X::pointer x = new X;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
}

