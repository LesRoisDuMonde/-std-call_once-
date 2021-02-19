#pragma once
#include <atomic>
#include <functional>

class Once {
public:
	//函数封装，包括普通函数，Lambda，函数对象， 类的静态函数
	template<typename F, typename...Args, typename = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type>
	void Do(F&& f, Args&&...args) {
		if (Check())
			return;
		[&] {return f(args...);}();
	}
	//类成员函数封装
	template<typename R, typename C, typename...DArgs, typename P, typename...Args>
	void Do(R(C::*f)(DArgs...), P&& p, Args&&...args) {
		if (Check())
			return;
		[&] {return (*p.*f)(args...);}();
	}

	// 原子操作 
	bool Check(){
		bool ret = m_flag.test_and_set(std::memory_order_acquire);
		return ret;
	}
	void Reset() {
		m_flag.clear(std::memory_order_release);
	}
private:
	std::atomic_flag m_flag = ATOMIC_FLAG_INIT;

};