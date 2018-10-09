/*
	. Critical section relies on events from the kernel object to provide synchronization
	. The creation of the event object for the critical section is deffered
	. Works without any exception/error handling
*/

//#include "precompiled.h"

//class critical_section
//{
//private:
//	CRITICAL_SECTION m_lock;
//
//public:
//	critical_section() noexcept
//	{
//		InitializeCriticalSection(&m_lock);
//	}
//
//	~critical_section()
//	{
//		DeleteCriticalSection(&m_lock);
//	}
//
//	void enter()
//	{
//		EnterCriticalSection(&m_lock);
//	}
//
//	void exit()
//	{
//		LeaveCriticalSection(&m_lock);
//	}
//};
//
//template<typename T>
//class auto_lock
//{
//private:
//	T& m_lock;
//
//public:
//	explicit auto_lock(T& lock)
//		: m_lock(lock)
//	{
//		m_lock.enter();
//	}
//
//	~auto_lock()
//	{
//		m_lock.exit();
//	}
//};

//int main()
//{
//	auto lock = critical_section{};
//	{
//		auto guard = auto_lock<critical_section>(lock);
//	}
//}