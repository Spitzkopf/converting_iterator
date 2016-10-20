#pragma once
#include "bidirectional_iterator_category.h"
#include "iterator_category_utils.h"

#include <type_traits>

namespace ci
{
	template<typename Iterator, typename Derived>
	struct random_access_iterator_category : public bidirectional_iterator_category<Iterator, Derived>
	{
		using bidirectional_iterator_category::bidirectional_iterator_category;

		template<typename N>
		Derived& operator+=(N n)
		{
			iter += n;
			return static_cast<Derived&>(*this);
		}

		template<typename N>
		Derived& operator-=(N n)
		{
			iter -= n;
			return static_cast<Derived&>(*this);
		}

		template<typename N>
		auto operator[](N n) const -> decltype(std::declval<const iterator_type>()[n])
		{
			return iter[n];
		}

		template<typename N>
		auto operator[](N n) -> decltype(std::declval<iterator_type>()[n])
		{
			return iter[n];
		}
	};

	template<typename Iterator, typename Derived, typename N>
	Derived operator+(const random_access_iterator_category<Iterator, Derived>& lhs, N rhs)
	{
		return{ lhs.iter + rhs };
	}

	template<typename Iterator, typename Derived, typename N>
	Derived operator+(N lhs, const random_access_iterator_category<Iterator, Derived>& rhs)
	{
		return{ lhs + rhs.iter };
	}

	template<typename Iterator, typename Derived, typename N>
	Derived operator-(const random_access_iterator_category<Iterator, Derived>& lhs, N rhs)
	{
		return{ lhs.iter - rhs };
	}

	template<typename Iterator, typename Derived, typename N>
	Derived operator-(N lhs, const random_access_iterator_category<Iterator, Derived>& rhs)
	{
		return{ lhs - rhs.iter };
	}

	DECLARE_COMPARISON_OPERATOR_OVERLOAD(>, random_access_iterator_category)
	DECLARE_COMPARISON_OPERATOR_OVERLOAD(<, random_access_iterator_category)
	DECLARE_COMPARISON_OPERATOR_OVERLOAD(<= , random_access_iterator_category)
	DECLARE_COMPARISON_OPERATOR_OVERLOAD(>= , random_access_iterator_category)
}
