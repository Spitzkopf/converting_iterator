#pragma once
#include "base_iterator_category.h"

namespace ci
{
	template<typename Iterator, typename Derived>
	struct output_iterator_category : public base_iterator_category<Iterator, Derived>
	{
		using base_iterator_category::base_iterator_category;

		auto operator*() && -> decltype(
			typename traits::conversion_policy{}.operator()<typename traits::converting::reference>(
				std::move(std::declval<typename traits::original::reference>())
				)
			)
		{
			return typename traits::conversion_policy{}.operator()<traits::converting::reference>(*std::move(iter));
		}

		auto operator->() && -> decltype(
			typename traits::conversion_policy{}.operator()<typename traits::converting::pointer>(
				std::move(std::declval<typename traits::original::pointer>())
				)
			)
		{
			return typename traits::conversion_policy{}.operator() < traits::converting::pointer > (std::move(iter).operator->());
		}

		auto operator*() const && -> decltype(
			typename traits::conversion_policy{}.operator()<typename traits::converting::reference>(
				std::move(std::declval<typename traits::original::reference>())
				)
			)
		{
			return typename traits::conversion_policy{}.operator()<traits::converting::reference>(*std::move(iter));
		}

		auto operator->() const && -> decltype(
			typename traits::conversion_policy{}.operator()<traits::converting::pointer>(
				std::move(std::declval<typename traits::original::pointer>())
				)
			)
		{
			return typename traits::conversion_policy{}.operator()<traits::converting::pointer> (std::move(iter).operator->());
		}
	};
}
