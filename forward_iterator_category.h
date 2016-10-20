#pragma once
#include "base_iterator_category.h"
#include "input_iterator_category.h"
#include "output_iterator_category.h"
#include "iterator_category_utils.h"

namespace ci
{
	template<typename Iterator, typename Derived>
	struct forward_iterator_category : public base_iterator_category<Iterator, Derived>
	{
		using base_iterator_category::base_iterator_category;

		auto operator*() &
		{
			return *input_iterator_category<Iterator, Derived>{ iter };
		}

		auto operator->() &
		{
			return input_iterator_category<Iterator, Derived>{ iter }.operator->();
		}

		auto operator*() const &
		{
			return *input_iterator_category<Iterator, Derived>{ iter };
		}

		auto operator->() const &
		{
			return input_iterator_category<Iterator, Derived>{ iter }.operator->();
		}

		auto operator*() &&
		{
			return *output_iterator_category<Iterator, Derived>{ iter };
		}

		auto operator->() &&
		{
			return output_iterator_category<Iterator, Derived>{ iter }.operator->();
		}

		auto operator*() const &&
		{
			return *output_iterator_category<Iterator, Derived>{ iter };
		}

		auto operator->() const &&
		{
			return output_iterator_category<Iterator, Derived>{ iter }.operator->();
		}
	};

	DECLARE_COMPARISON_OPERATOR_OVERLOAD(== , forward_iterator_category)
	DECLARE_COMPARISON_OPERATOR_OVERLOAD(!= , forward_iterator_category)
}
