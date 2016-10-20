#pragma once
#include "base_iterator_category.h"
#include "iterator_category_utils.h"

namespace ci
{
	template<typename Iterator, typename Derived>
	struct input_iterator_category : public base_iterator_category<Iterator, Derived>
	{
		using base_iterator_category::base_iterator_category;

		auto operator*() & -> decltype(
			typename traits::conversion_policy{}.operator()<typename traits::converting::reference>(std::declval<typename traits::original::reference>())
			)
		{
			return typename traits::conversion_policy{}.operator()<traits::converting::reference>(*iter);
		}

		auto operator->() & -> decltype(
			typename traits::conversion_policy{}.operator()<traits::converting::pointer>(std::declval<typename traits::original::pointer>())
			)
		{
			return typename traits::conversion_policy{}.operator() < traits::converting::pointer > (iter.operator->());
		}

		auto operator*() const & -> decltype(
			typename traits::conversion_policy{}.operator()<typename traits::converting::reference>(std::declval<typename traits::original::reference>())
			)
		{
			return typename traits::conversion_policy{}.operator()<traits::converting::reference>(*iter);
		}

		auto operator->() const & -> decltype(
			typename traits::conversion_policy{}.operator()<traits::converting::pointer>(std::declval<typename traits::original::pointer>())
			)
		{
			return typename traits::conversion_policy{}.operator() < traits::converting::pointer > (iter.operator->());
		}
	};

	DECLARE_COMPARISON_OPERATOR_OVERLOAD(== , input_iterator_category)
	DECLARE_COMPARISON_OPERATOR_OVERLOAD(!= , input_iterator_category)
}
