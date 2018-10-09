#include "precompiled.h"

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

auto lock = slim_lock{};
int shared = 0;

void reader() throw()
{
	for (;;)
	{
		Sleep(10);

		auto guard = lock.get_shared();

		Sleep(500);

		if (shared < 5)
		{
			TRACE(L"shared=%d id=%d\n", shared, GetCurrentThreadId());
		}
		else
		{
			break;
		}
	}
}

int main()
{
	auto r1 = make_thread(reader);
	auto r2 = make_thread(reader);

	auto w = make_thread([]
	{
		for (unsigned i = 0; i != 5; ++i)
		{
			Sleep(1000);

			auto guard = lock.get_exclusive();

			++shared;
		}
	});

	wait_all(INFINITE, r1, r2, w);
}
