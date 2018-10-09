/*
	. Always consume kernel resources
	. 100% kernel sync object
	. Upside: kernel is aware and can provide cross process sync
	. Downsice: heavy weight lock
*/

//#include "precompiled.h"

//extern bool wait_one(const HANDLE h, const DWORD milliseconds = INFINITE);

//int main()
//{
//	auto lock = KennyKerr::null_handle
//	{
//		CreateMutex(nullptr, false, nullptr)
//	};
//
//	if (!lock)
//	{
//		throw windows_exception();
//	}
//
//	VERIFY(wait_one(lock.get()));
//	VERIFY(ReleaseMutex(lock.get()));
//}