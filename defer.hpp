#ifndef _PHONZIA_DEFER_H_
#define _PHONZIA_DEFER_H_
#include <functional>

namespace phonzia
{
#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)

#define defer auto MACRO_CONCAT(__defer_obj_, __COUNTER__) = ::phonzia::__defer() -

class __defer
{
	public:
	template <typename Callable>
	__defer &&operator-(Callable &&callable)
	{
		defer_ = std::forward<Callable>(callable);
		return std::move(*this);
	}

	~__defer()
	{
		if (defer_)
			defer_();
	}

	__defer() = default;

	__defer(const __defer &) = delete;
	__defer(__defer &&rhs)
	{
		this->defer_ = std::move(rhs.defer_);
		rhs.defer_ = nullptr;
	}

	__defer &operator=(const __defer &) = delete;
	__defer &operator=(__defer &&rhs)
	{
		if (this != &rhs)
		{
			this->defer_ = std::move(rhs.defer_);
			rhs.defer_ = nullptr;
		}
		return *this;
	}

	private:
	std::function<void()> defer_;
};
}

#endif
