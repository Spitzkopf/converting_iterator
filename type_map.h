#pragma once
#include <type_traits>

namespace ci
{
	namespace detail
	{
		template<typename K, typename V>
		struct key_value_pair
		{
			using key = K;
			using value = V;
		};

		template<typename ...Values>
		struct type_map
		{};

		template<typename TypeMap, typename K>
		struct at;

		template<typename K, typename V, typename ...Values>
		struct at<type_map<key_value_pair<K, V>, Values...>, K>
		{
			using type = V;
		};

		template<typename K, typename K1, typename V1, typename ...Values>
		struct at<type_map<key_value_pair<K1, V1>, Values...>, K>
		{
			using type = typename at<type_map<Values...>, K>::type;
		};

	}
}
