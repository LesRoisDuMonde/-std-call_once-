#pragma once
#include <atomic>
#include <functional>

class Once {
public:
	//������װ��������ͨ������Lambda���������� ��ľ�̬����
	template<typename F, typename...Args, typename = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type>
	void Do(F&& f, Args&&...args) {
		if (Check())
			return;
		[&] {return f(args...);}();
	}
	//���Ա������װ
	template<typename R, typename C, typename...DArgs, typename P, typename...Args>
	void Do(R(C::*f)(DArgs...), P&& p, Args&&...args) {
		if (Check())
			return;
		[&] {return (*p.*f)(args...);}();
	}

	// ԭ�Ӳ��� 
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