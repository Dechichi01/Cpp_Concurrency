/*
	. Keyed events are simple and fast
	. Don't offer the hability to secure, inherit or name then
	. New lock object -> SRWLock
		. Mostly implemented in user mode
		. Can fallback to kernel mode in certain situations
		. Can acquire the lock exclusively (no recursion)
		. Or shared, which allows read access
*/

/*
	NOTE: HOw the hell he's returning values with deleted copy/move constructors? 
*/

//#include "precompiled.h"

//template<typename T>
//class auto_lock
//{
//	using UnlockAction = void (T::*)();
//	T& m_lock;
//	UnlockAction m_unlock_action;
//
//public:
//	explicit auto_lock(T& lock, UnlockAction action) noexcept
//		: m_lock(lock), m_unlock_action(action)
//	{
//	}
//
//	~auto_lock() noexcept
//	{
//		(m_lock.*m_unlock_action)();
//	}
//
//	/*auto_lock(const auto_lock&) = delete;
//	auto_lock& operator=(const auto_lock&) = delete;*/
//	/*auto_lock(auto_lock&&) = delete;
//	auto_lock& operator=(auto_lock&&) = delete;*/
//};
//
//class slim_lock
//{
//	SRWLOCK m_lock;
//
//public:
//	slim_lock() noexcept
//		: m_lock{}
//	{}
//
//	/*slim_lock(const slim_lock&) = delete;
//	slim_lock& operator=(const slim_lock&) = delete;*/
//	/*slim_lock(slim_lock&&) = delete;
//	slim_lock& operator=(slim_lock&&) = delete;*/
//
//	SRWLOCK* native_handle() noexcept
//	{
//		return &m_lock;
//	}
//
//	auto_lock<slim_lock> get_exclusive()
//	{
//		enter();
//		return auto_lock<slim_lock>{ *this, &slim_lock::exit };
//	}
//
//	auto_lock<slim_lock> get_shared()
//	{
//		enter_shared();
//		return auto_lock<slim_lock>{ *this, &slim_lock::exit_shared };
//	}
//
//private:
//	void enter() noexcept
//	{
//		AcquireSRWLockExclusive(&m_lock);
//	}
//
//	void exit() noexcept
//	{
//		ReleaseSRWLockExclusive(&m_lock);
//	}
//
//	void enter_shared() noexcept
//	{
//		AcquireSRWLockShared(&m_lock);
//	}
//
//	void exit_shared() noexcept
//	{
//		ReleaseSRWLockShared(&m_lock);
//	}
//};

//int main()
//{
//}