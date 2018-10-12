#include <Windows.h>

class conditional_variable
{
	CONDITION_VARIABLE m_conditional;

public:
	conditional_variable(const conditional_variable& other) = delete;
	conditional_variable& operator=(const conditional_variable&) = delete;
	conditional_variable(conditional_variable&&) = delete;
	conditional_variable& operator=(conditional_variable&&) = delete;

	conditional_variable() noexcept
		: m_conditional{}
	{}

	~conditional_variable() = default;
};

int main()
{
	conditional_variable c1{};// Compiles

	auto c2 = conditional_variable{};// Doesn't compile

	auto* c3 = new conditional_variable();//Compiles
	delete c3;
}