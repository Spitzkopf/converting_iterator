#pragma once

namespace ci
{
	//forward declaration
	template<typename CV>
	struct converting_iterator_traits;

	template<typename Iterator, typename Derived>
	struct base_iterator_category
	{
		using iterator_type = Iterator;

		using traits = converting_iterator_traits<Derived>;

		base_iterator_category(iterator_type& iter)
			: iter(iter)
		{}

		Derived& operator++() { ++iter;  return static_cast<Derived&>(*this); }

		Derived operator++(int) { Derived retval = static_cast<Derived&>(*this); ++(*this); return retval; }

		iterator_type& iter;
	};
}
