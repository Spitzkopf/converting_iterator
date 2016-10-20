#pragma once
#include "forward_iterator_category.h"


namespace ci
{
	template<typename Iterator, typename Derived>
	struct bidirectional_iterator_category
		: public forward_iterator_category<Iterator, Derived>
	{
		using forward_iterator_category::forward_iterator_category;

		Derived& operator--() { --iter;  return static_cast<Derived&>(*this); }

		Derived operator--(int) { Derived retval = static_cast<Derived&>(*this); --(*this); return retval; }
	};
}
