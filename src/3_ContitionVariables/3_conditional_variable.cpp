//#include "precompiled.h"
//#include <deque>
//#include <vector>
//
//class conditional_variable
//{
//	CONDITION_VARIABLE m_conditional;
//
//public:
//	conditional_variable(const conditional_variable& other) = delete;
//	conditional_variable& operator=(const conditional_variable&) = delete;
//	conditional_variable(conditional_variable&&) = delete;
//	conditional_variable& operator=(conditional_variable&&) = delete;
//
//	conditional_variable() noexcept
//		: m_conditional{}
//	{
//		LOG("Calling constructor");
//	}
//
//	template<typename T>
//	void wait_while(slim_lock& lock, const T predicate)
//	{
//		while (predicate())
//		{
//			VERIFY(SleepConditionVariableSRW(&m_conditional, lock.native_handle(), INFINITE, 0));
//		}
//	}
//
//	void wake_one()
//	{
//		WakeConditionVariable(&m_conditional);
//	}
//
//	void wake_all()
//	{
//		WakeAllConditionVariable(&m_conditional);
//	}
//};
//template<typename T>
//class block_queue
//{
//	std::deque<T> m_queue;
//	slim_lock m_lock;
//	conditional_variable m_conditional;
//
//public:
//
//	using value_type = T;//to work with std algs
//
//	block_queue()
//		: m_queue{}, m_lock{}, m_conditional{}
//	{}
//
//	void push_back(const T& element)
//	{
//		auto guard = m_lock.get_exclusive();
//		m_queue.push_back(element);
//		m_conditional.wake_one();
//	}
//
//	T& pop()
//	{
//		auto guard = m_lock.get_exclusive();
//
//		m_conditional.wait_while(m_lock, [&]
//		{
//			return m_queue.empty();
//		});
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
//		iota_n(std::back_inserter(queue), 10000, 0);
//	});
//
//	auto producer2 = make_thread([]()
//	{
//		iota_n(std::back_inserter(queue), 10000, 0);
//	});
//
//	wait_all(INFINITE, producer, producer2);
//
//	std::fill_n(std::back_inserter(queue), cs.size(), -1);
//
//	ASSERT(cs.size() <= MAXIMUM_WAIT_OBJECTS);
//	WaitForMultipleObjects(static_cast<DWORD>(cs.size()), reinterpret_cast<const HANDLE*>(&cs[0]), true, INFINITE);
//
//	ASSERT(queue.unsafe_empty());
//}