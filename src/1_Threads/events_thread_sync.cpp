//#include "precompiled.h"
//
//static auto e = event{ event_type::manual_reset };
//
//static DWORD __stdcall work(void*)
//{
//	TRACE(L"Thread working!!\n\n");
//
//	e.wait();
//
//	TRACE(L"Finished waiting for event!!\n\n");
//	return 0;
//}

//void pick_and_add(HANDLE*) {}
//
//template<typename T, typename... Args>
//void pick_and_add(HANDLE* left, const T& right, const Args&... args)
//{
//	*left = right;
//	pick_and_add(++left, args...);
//}
//
//template<typename... Args>
//void wait_all(const DWORD milliseconds, const Args&... args)
//{
//	//sizeof is staticly evaluated
//	HANDLE handles[sizeof...(args)];
//	pick_and_add(handles, args...);
//
//	WaitForMultipleObjects(sizeof...(args), handles, true, milliseconds);
//}

//int main()
//{
//	auto t1 = KennyKerr::null_handle
//	{
//		CreateThread(nullptr, 0, work, nullptr, CREATE_SUSPENDED, nullptr)
//	};
//
//	auto t2 = KennyKerr::null_handle
//	{
//		CreateThread(nullptr, 0, work, nullptr, CREATE_SUSPENDED, nullptr)
//	};
//
//	ResumeThread(t1.get());
//	ResumeThread(t2.get());
//
//	e.set();
//
//	wait_all(INFINITE, t1.get(), t2.get());
//}