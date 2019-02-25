#include <type_traits>
 
// 1. Implementing a variadic logical AND
template <bool...> struct bool_sequence {};
 
template <bool... Bs>
using bool_and
 = std::is_same<bool_sequence<Bs...>,
                bool_sequence<(Bs || true)...>>;
 
// 2. Helper function to test implicit conversion 
template <typename T>
  std::true_type create(T v);
 
// 3a. Test for conversion and non-narrowing
template <typename T, typename U>
  decltype(create<U>({std::declval<T>()})) // <- braces
  test_nonnarow_conv(int);
 
// 3b. Fallback function if sfinae fails on 3a
template <typename T, typename U>
  std::false_type test_nonnarow_conv(long);
 
// 3c. Single-argument conversion trait
template <typename T, typename U>
  using is_nonarrow_convertible
  = decltype(test_nonnarow_conv<T, U>(0));
 
// 4. Our multi-argument trait
template <typename T, typename... Ts>
  using nonarrow_convertible
  = bool_and<is_nonarrow_convertible<Ts, T>::value...>;
