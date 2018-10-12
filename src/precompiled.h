#pragma once

#include "debug.h"
#include "handle.h"
#include <memory>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

struct windows_exception
{
	DWORD error;
	explicit windows_exception(const DWORD value = GetLastError())
		: error(value)
	{}
};

enum class event_type
{
	auto_reset,
	manual_reset
};

class event
{
private:
	KennyKerr::null_handle h;

public:
	explicit event(const event_type type)
		: h(CreateEvent(nullptr, static_cast<bool>(type), false, nullptr))
	{
		if (!h)
		{
			throw windows_exception();
		}
	}

	~event() = default;
	event(const event& other) = delete;
	event& operator=(const event& other) = delete;

	event(event&& other)
		: h(other.h.release())
	{}

	event& operator=(event&& other)
	{
		if (&other != this)
		{
			h = std::move(other.h);
		}

		return *this;
	}

	void set() noexcept
	{
		VERIFY(SetEvent(h.get()));
	}

	void reset() noexcept
	{
		VERIFY(ResetEvent(h.get()));
	}

	bool wait(const DWORD milliseconds = INFINITE) noexcept
	{
		const DWORD result = WaitForSingleObject(h.get(), milliseconds);

		ASSERT(result == WAIT_OBJECT_0 || result == WAIT_TIMEOUT);

		return result == WAIT_OBJECT_0;
	}
};

template<typename T>
class auto_lock
{
	using UnlockAction = void (T::*)();
	T& m_lock;
	UnlockAction m_unlock_action;

public:
	explicit auto_lock(T& lock, UnlockAction action) noexcept
		: m_lock(lock), m_unlock_action(action)
	{
	}

	~auto_lock() noexcept
	{
		(m_lock.*m_unlock_action)();
	}

	/*auto_lock(const auto_lock&) = delete;
	auto_lock& operator=(const auto_lock&) = delete;*/
	/*auto_lock(auto_lock&&) = delete;
	auto_lock& operator=(auto_lock&&) = delete;*/
};

class slim_lock
{
	SRWLOCK m_lock;

public:
	slim_lock() noexcept
		: m_lock{}
	{}

	/*slim_lock(const slim_lock&) = delete;
	slim_lock& operator=(const slim_lock&) = delete;*/
	/*slim_lock(slim_lock&&) = delete;
	slim_lock& operator=(slim_lock&&) = delete;*/

	void enter() noexcept
	{
		AcquireSRWLockExclusive(&m_lock);
	}

	void exit() noexcept
	{
		ReleaseSRWLockExclusive(&m_lock);
	}

	void enter_shared() noexcept
	{
		AcquireSRWLockShared(&m_lock);
	}

	void exit_shared() noexcept
	{
		ReleaseSRWLockShared(&m_lock);
	}

	SRWLOCK* native_handle() noexcept
	{
		return &m_lock;
	}

	auto_lock<slim_lock> get_exclusive()
	{
		enter();
		return auto_lock<slim_lock>{ *this, &slim_lock::exit };
	}

	auto_lock<slim_lock> get_shared()
	{
		enter_shared();
		return auto_lock<slim_lock>{ *this, &slim_lock::exit_shared };
	}

};


////

void pick_and_add(HANDLE*) {}

template<typename T, typename... Args>
void pick_and_add(HANDLE* left, const T& right, const Args&... args)
{
	*left = right.get();
	pick_and_add(++left, args...);
}

template<typename... Args>
void wait_all(const DWORD milliseconds, const Args&... args)
{
	//sizeof is staticly evaluated
	HANDLE handles[sizeof...(args)];
	pick_and_add(handles, args...);

	WaitForMultipleObjects(sizeof...(args), handles, true, milliseconds);
}

bool wait_one(const HANDLE h, const DWORD milliseconds = INFINITE)
{
	const DWORD result = WaitForSingleObject(h, milliseconds);
	if (result == WAIT_OBJECT_0)
	{
		return true;
	}
	else if (result == WAIT_TIMEOUT)
	{
		return false;
	}

	throw windows_exception();
}


using thread_callback = void(*)();

DWORD __stdcall thread_wrapper(void * args)
{
	auto callback = static_cast<thread_callback>(args);

	callback();

	return 0;
}

template <typename F>
KennyKerr::null_handle make_thread(F callback) throw()
{
	return KennyKerr::null_handle
	{
		CreateThread(nullptr,
					 0,
					 thread_wrapper,
					 static_cast<thread_callback>(callback),
					 0,
					 nullptr)
	};
}
