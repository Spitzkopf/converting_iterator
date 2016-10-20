#pragma once


#define DECLARE_COMPARISON_OPERATOR_OVERLOAD(op, iter_cat) \
template<typename Iterator, typename Derived, typename Other, typename = std::enable_if<!std::is_base_of<iter_cat<Iterator, Derived>, typename std::decay<Other>::type>::value, void>::type> \
bool operator##op(Other&& lhs, const iter_cat<Iterator, Derived>& rhs) { \
	return std::forward<Other>(lhs) op rhs.iter; \
} \
template<typename Iterator, typename Derived, typename Other, typename = std::enable_if<!std::is_base_of<iter_cat<Iterator, Derived>, typename std::decay<Other>::type>::value, void>::type> \
bool operator##op(const iter_cat<Iterator, Derived>& lhs, Other&& rhs) { \
	return lhs.iter op std::forward<Other>(rhs); \
} \
template<typename Iterator, typename Derived> \
bool operator##op(const iter_cat<Iterator, Derived>& lhs, const iter_cat<Iterator, Derived>& rhs) { \
	return lhs.iter op rhs.iter; \
}
