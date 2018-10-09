#pragma once

#include "debug.h"
#include "handle.h"
#include <memory>

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
