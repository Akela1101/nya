#ifndef SIGNALNYA_HPP
#define SIGNALNYA_HPP

#include <tuple>
#include <utility>


namespace nya
{
template<typename EventLoop, typename Slot, typename ...Args>
void invoke_in(EventLoop &eventLoop, Slot &&slotFunc, Args... args)
{
	using namespace std;
	// move arguments to other thread
	eventLoop.post([slotFunc = forward<Slot>(slotFunc), argsT = make_tuple(move(args)...)]() mutable
				   {
					   // move arguments from lambda to slotFunc
					   apply(move(slotFunc), move(argsT));
				   });
}

template<typename EventLoop,
	template<typename, typename ...> class Signal, typename Slot, typename ...Args, typename ...Ts>
void connect_in(EventLoop &eventLoop, Signal<void(Args...), Ts...> &signalFunc, Slot &&slotFunc)
{
	using namespace std;
	// arguments are copied, because there can be multiple slots
	signalFunc.connect([&eventLoop, slotFunc = forward<Slot>(slotFunc)](Args... args) mutable
					   {
						   // slot is copied, because it can be called multiple times
						   auto slotCopy = slotFunc;
						   invoke_in(eventLoop, move(slotCopy), move(args)...);
					   });
}

template<typename EventLoop>
class event_loop_holder
{
protected:
	static EventLoop eventLoop;

public:
	template<typename Slot, typename ...Args>
	static void invoke(Slot &&slotFunc, Args... args)
	{
		using namespace std;
		if constexpr (sizeof...(Args) == 0)
			eventLoop.post(forward<Slot>(slotFunc));
		else
			invoke_in(eventLoop, forward<Slot>(slotFunc), move(args)...);
	}

	template<template<typename, typename ...> class Signal, typename Slot, typename ...Args, typename ...Ts>
	static void connect(Signal<void(Args...), Ts...> &signalFunc, Slot &&slotFunc)
	{
		using namespace std;
		nya::connect_in(eventLoop, signalFunc, forward<Slot>(slotFunc));
	}
};

template<typename EventLoop> EventLoop nya::event_loop_holder<EventLoop>::eventLoop;

}
#endif //SIGNALNYA_HPP
