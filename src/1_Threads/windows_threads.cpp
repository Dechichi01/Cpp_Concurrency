//#include "precompiled.h"

/*
	stdcall is a windows calling convention: https://docs.microsoft.com/en-us/cpp/cpp/calling-conventions?view=vs-2017
	. Thread is a kernel object, the security descriptor would prevents non-authorized users to use this thread (quite rare)
	. HANDLE is a managed resource that interacts with the thread kernel object
	. CloseHandle doesn't kill the thread, it simply tells the OS you no longer need to hold a reference to that thread
	 
*/
//static DWORD __stdcall work(void *)
//{
//	TRACE(L"Work thread done\n");
//	return 123;
//}

//bool wait_one(const HANDLE h, const DWORD milliseconds = INFINITE)
//{
//	const DWORD result = WaitForSingleObject(h, milliseconds);
//	if (result == WAIT_OBJECT_0)
//	{
//		return true;
//	}
//	else if (result == WAIT_TIMEOUT)
//	{
//		return false;
//	}
//
//	throw windows_exception();
//}

//int main()
//{
//	auto t = KennyKerr::null_handle
//	{
//		CreateThread(nullptr, 0, work, nullptr, 0, nullptr)
//	};
//
//	if (t)
//	{
//		ASSERT(wait_one(t.get()));
//
//		auto exit = DWORD{};
//		VERIFY(GetExitCodeThread(t.get(), &exit));
//		ASSERT(exit == 123);//STILL_ACTIVE 259
//	}
//}