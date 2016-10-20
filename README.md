# converting_iterator
A c++ iterator wrapper to convert the underlying type to another type

# Usage
To create a converting iterator you need 3 things - 

1. a container/existing iterator
2. a desired type T you'd like to mirror the original iterators type as
3. and a conversion policy (i.e - how upon dereferencing the iterator its type will be converted to T)
  * the library currently has 2 conversion types - `static_cast_conversion_policy` which simply `static_casts` `T` to `U`, and `view_cast_conversion_policy` which `static_casts` `T` to `U` removing references from `U` (returning it by value)

Now you can simply call `ci::begin` or `ci::from_iterator` and create your converting iterator.
The iterator is comparable against the iterators of the original container, so you can easily compare your iterator to `container.end()` etc.

The converting iterator's interface is determined by the original iterators iterator category, and it will implement the interface expecated by said category.

# Example
```C++
class A
{
public:
	A(int a)
		: m_a(a)
	{}

	int m_a;
};

class B : public A
{
public:
	using A::A;
};

int main() 
{
  std::vector<B> x = { 1, 2, 3, 4 };

  auto ci = ci::begin<A, ci::static_cast_conversion_policy>(x);
  static_assert(std::is_same<A, decltype(*ci)>::value, "uh oh");
  for (ci; ci != x.end(); ++ci) {
    //do stuff
  }

  std::list<double> y = { 1.5, 2, 3.3, 4 }; 

  //here, we use the view_cast_conversion_policy, because a ref to double is not convertible to a ref to int
  //but we can convert it to a non-ref int (with data loss ofcourse)
  for (auto ci2 = ci::from_iterator<int, ci::view_cast_conversion_policy>(y.begin()); ci2 != y.end(); ++ci2) {
    //do stuff
  }
  
  return 0;
}
```
