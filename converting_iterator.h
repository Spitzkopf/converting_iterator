#pragma once
#include "iterator_categories.h"
#include "type_map.h"

namespace ci
{
	struct static_cast_conversion_policy
	{
		template<typename U, typename T>
		U operator()(T&& t)
		{
			return static_cast<U>(std::forward<T>(t));
		}
	};

	struct view_cast_conversion_policy
	{
		template<typename U, typename T>
		typename std::remove_reference<U>::type operator()(T&& t)
		{
			return static_cast<typename std::remove_reference<U>::type>(std::forward<T>(t));
		}
	};

	namespace detail 
	{
		template<typename I, typename D>
		using tag_to_category_map = detail::type_map<
			detail::key_value_pair<std::input_iterator_tag, input_iterator_category<I, D>>,
			detail::key_value_pair<std::output_iterator_tag, output_iterator_category<I, D>>,
			detail::key_value_pair<std::forward_iterator_tag, forward_iterator_category<I, D>>,
			detail::key_value_pair<std::bidirectional_iterator_tag, bidirectional_iterator_category<I, D>>,
			detail::key_value_pair<std::random_access_iterator_tag, random_access_iterator_category<I, D>>
		>;
	}

	template<typename T,
		typename Original,
		typename ConversionPolicy,
		typename Category = typename Original::iterator_category>
		struct converting_iterator
		: public std::iterator<Category, T>
		, public detail::at<detail::tag_to_category_map<Original, converting_iterator<T, Original, ConversionPolicy, Category>>, Category>::type
	{
	public:
		using base = typename detail::at<detail::tag_to_category_map<Original, converting_iterator<T, Original, ConversionPolicy, Category>>, Category>::type;

		converting_iterator(Original original)
			: m_original(std::move(original))
			, base(m_original)
		{}

	private:
		Original m_original;
	};

	template<typename T, typename Original, typename ConversionPolicy, typename Category>
	struct converting_iterator_traits<converting_iterator<T, Original, ConversionPolicy, Category>>
	{
		using type = T;
		using converting = std::iterator<Category, T>;
		using original = Original;
		using conversion_policy = ConversionPolicy;
	};

	template<typename T, typename ConversionPolicy, typename C>
	auto ci_begin(C&& container) -> converting_iterator<T, decltype(std::forward<C>(container).begin()), ConversionPolicy>
	{
		return{ std::forward<C>(container).begin() };
	}

	template<typename T, typename ConversionPolicy, typename C>
	auto ci_end(C&& container) -> converting_iterator<T, decltype(std::forward<C>(container).end()), ConversionPolicy>
	{
		return{ std::forward<C>(container).end() };
	}
}
