//#include "precompiled.h"
//#include <deque>
//#include <vector>
//
///*
//	. Queue that blocks execution during pop
//	. Guarded region: Region of code that prohibites code to continue until a condition is met. It should allow other thread to fullfill the requirement
//	. Ungarded regions are unsafe (see pop method):
//		. It's possible for a thread to exit the lock, but another thread picks up the event signal, and steal the wait (stolen wait)
//		. Since events have no counting (like semaphores), signlaing thje event multiple times does not solve
//		. A solution to this involves making the exit/enter and wait event atomic
//		. Putting sleep in them can force a deadlock 
//*/
//
//template<typename T>
//class block_queue
//{
//	std::deque<T> m_queue;
//	slim_lock m_lock;
//	event m_event;
//
//public:
//
//	using value_type = T;//to work with std algs
//
//	block_queue()
//		: m_queue{}, m_lock{}, m_event{ event_type::auto_reset}
//	{}
//
//	void push_back(const T& element)
//	{
//		auto guard = m_lock.get_exclusive();
//		m_queue.push_back(element);
//		m_event.set();
//	}
//
//	T& pop()
//	{
//		auto guard = m_lock.get_exclusive();
//
//		while (m_queue.empty())
//		{
//			m_lock.exit();
//
//			VERIFY(m_event.wait());
//
//			m_lock.enter();
//		}
//
//		T& value = m_queue.front();
//		m_queue.pop_front();
//
//		return value;
//	}
//
//	bool unsafe_empty()
//	{
//		return m_queue.empty();
//	}
//};
//
//auto queue = block_queue<int>{};
//
//void consume()
//{
//	unsigned count{};
//
//	for (;;)
//	{
//		auto element = queue.pop();
//
//		if (element == -1)
//		{
//			TRACE(L"Consumer %10d %10d\n", GetCurrentThreadId(), count);
//			break;
//		}
//
//		++count;
//	}
//}
//
//template<typename T, typename Count, typename Value>
//T iota_n(T first, Count count, Value value)
//{
//	for (Count i = Count{}; i < count; i++)
//	{
//		*first = value++;
//		first++;
//	}
//
//	return first;
//}
//
//int main()
//{
//	auto cs = std::vector<KennyKerr::null_handle>(8);
//
//	for (auto& c : cs)
//	{
//		c = make_thread(consume);
//	}
//
//	auto producer = make_thread([]()
//	{
//		iota_n(std::back_inserter(queue), 10, 0);
//	});
//
//	wait_all(INFINITE, producer);
//
//	std::fill_n(std::back_inserter(queue), cs.size(), -1);
//
//	ASSERT(cs.size() <= MAXIMUM_WAIT_OBJECTS);
//	WaitForMultipleObjects(static_cast<DWORD>(cs.size()), reinterpret_cast<const HANDLE*>(&cs[0]), true, INFINITE);
//
//	ASSERT(queue.unsafe_empty());
//}