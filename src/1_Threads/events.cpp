/*
	. Used for signing
	. Manual and auto events are set manually, 
	. Manual events need to be reset manually
	. While auto reset events are reset by the kernel when one thread resumes (that waits for that event), resumes
*/

//#include "precompiled.h"
//#include <memory>
//
//int main()
//{
//	auto e = event(event_type::manual_reset);
//
//	ASSERT(!e.wait(0));
//
//	e.set();
//
//	ASSERT(e.wait());
//
//	auto e2 = std::move(e);
//
//	e2.set();
//	//e.set();//assert failed
//}