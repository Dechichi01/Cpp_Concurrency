/*
	. Used for signing
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