//                Copyright Jo Bates 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "../mat.hpp"
#include "../math.hpp"
#include "../vec.hpp"

#ifdef _MSC_VER
#define TUE_CONSTEXPR
#else
#define TUE_CONSTEXPR constexpr
#endif

namespace tue {

template<typename T, int R>
class mat<T, 4, R>
{
public:
  using column_type = vec<T, R>;
  using row_type = vec<T, 4>;
  using component_type = T;

  static constexpr int column_count = 4;
  static constexpr int row_count = R;
  static constexpr int component_count = column_count * row_count;

private:
  struct { vec<T, R> columns[4]; } impl_;

public:
  mat() = default;

  explicit constexpr mat(const T& s) noexcept
    : impl_({{
        vec<T, R>(vec<T, 4>(s, T(0), T(0), T(0))),
        vec<T, R>(vec<T, 4>(T(0), s, T(0), T(0))),
        vec<T, R>(vec<T, 4>(T(0), T(0), s, T(0))),
        vec<T, R>(vec<T, 4>(T(0), T(0), T(0), s)),
      }}) {
  }

  constexpr mat(
      const vec<T, R>& column0,
      const vec<T, R>& column1,
      const vec<T, R>& column2,
      const vec<T, R>& column3) noexcept
    : impl_({{
        column0,
        column1,
        column2,
        column3,
      }}) {
  }

  template<int OtherR>
  explicit constexpr mat(const mat<T, 2, OtherR>& other) noexcept
    : impl_({{
        vec<T, R>::extend_(other[0], T(0), T(0)),
        vec<T, R>::extend_(other[1], T(0), T(0)),
        vec<T, R>(vec<T, 4>(T(0), T(0), T(1), T(0))),
        vec<T, R>(vec<T, 4>(T(0), T(0), T(0), T(1))),
      }}) {
  }

  template<int OtherR>
  explicit constexpr mat(const mat<T, 3, OtherR>& other) noexcept
    : impl_({{
        vec<T, R>::extend_(other[0], T(0), T(0)),
        vec<T, R>::extend_(other[1], T(0), T(0)),
        vec<T, R>::extend_(other[2], T(1), T(0)),
        vec<T, R>(vec<T, 4>(T(0), T(0), T(0), T(1))),
      }}) {
  }

  template<int OtherR>
  explicit constexpr mat(const mat<T, 4, OtherR>& other) noexcept
    : impl_({{
        vec<T, R>::extend_(other[0], T(0), T(0)),
        vec<T, R>::extend_(other[1], T(0), T(0)),
        vec<T, R>::extend_(other[2], T(1), T(0)),
        vec<T, R>::extend_(other[3], T(0), T(1)),
      }}) {
  }

  template<typename U>
  explicit constexpr mat(const mat<U, 4, R>& other) noexcept
    : impl_({{
        vec<T, R>(other[0]),
        vec<T, R>(other[1]),
        vec<T, R>(other[2]),
        vec<T, R>(other[3]),
      }}) {
  }

  template<typename U>
  constexpr operator mat<U, 4, R>() const noexcept
  {
    return {
      impl_.columns[0],
      impl_.columns[1],
      impl_.columns[2],
      impl_.columns[3],
    };
  }

  static constexpr mat identity() noexcept {
    return mat(T(1));
  }

  static constexpr mat zero() noexcept {
    return mat(T(0));
  }

  template<typename I>
  constexpr vec<T, R> column(const I& i) const noexcept {
    return impl_.columns[i];
  }

  template<typename I>
  void set_column(const I& i, const vec<T, R>& column) noexcept {
    impl_.columns[i] = column;
  }

  template<typename J>
  constexpr vec<T, 4> row(const J& j) const noexcept {
    return {
      impl_.columns[0][j],
      impl_.columns[1][j],
      impl_.columns[2][j],
      impl_.columns[3][j],
    };
  }

  template<typename J>
  void set_row(const J& j, const vec<T, 4>& row) noexcept {
    impl_.columns[0][j] = row[0];
    impl_.columns[1][j] = row[1];
    impl_.columns[2][j] = row[2];
    impl_.columns[3][j] = row[3];
  }

  T* data() noexcept {
    return impl_.columns[0].data();
  }

  const T* data() const noexcept {
    return impl_.columns[0].data();
  }

  vec<T, R>* columns() noexcept {
    return impl_.columns;
  }

  const vec<T, R>* columns() const noexcept {
    return impl_.columns;
  }

  template<typename I>
  vec<T, R>& operator[](const I& i) noexcept {
    return impl_.columns[i];
  }

  template<typename I>
  constexpr const vec<T, R>& operator[](const I& i) const noexcept {
    return impl_.columns[i];
  }

  mat& operator++() noexcept {
    ++impl_.columns[0];
    ++impl_.columns[1];
    ++impl_.columns[2];
    ++impl_.columns[3];
    return *this;
  }

  mat& operator--() noexcept {
    --impl_.columns[0];
    --impl_.columns[1];
    --impl_.columns[2];
    --impl_.columns[3];
    return *this;
  }

  mat operator++(int) noexcept {
    const auto orig = *this;
    ++*this;
    return orig;
  }

  mat operator--(int) noexcept {
    const auto orig = *this;
    --*this;
    return orig;
  }

  template<typename U>
  mat& operator+=(const U& other) noexcept {
    impl_.columns[0] += other;
    impl_.columns[1] += other;
    impl_.columns[2] += other;
    impl_.columns[3] += other;
    return *this;
  }

  template<typename U>
  mat& operator+=(const mat<U, 4, R>& other) noexcept {
    impl_.columns[0] += other[0];
    impl_.columns[1] += other[1];
    impl_.columns[2] += other[2];
    impl_.columns[3] += other[3];
    return *this;
  }

  template<typename U>
  mat& operator-=(const U& other) noexcept {
    impl_.columns[0] -= other;
    impl_.columns[1] -= other;
    impl_.columns[2] -= other;
    impl_.columns[3] -= other;
    return *this;
  }

  template<typename U>
  mat& operator-=(const mat<U, 4, R>& other) noexcept {
    impl_.columns[0] -= other[0];
    impl_.columns[1] -= other[1];
    impl_.columns[2] -= other[2];
    impl_.columns[3] -= other[3];
    return *this;
  }

  template<typename U>
  mat& operator*=(const U& other) noexcept {
    impl_.columns[0] *= other;
    impl_.columns[1] *= other;
    impl_.columns[2] *= other;
    impl_.columns[3] *= other;
    return *this;
  }

  template<typename U, int OtherC, int OtherR>
  mat& operator*=(const mat<U, OtherC, OtherR>& other) noexcept {
    return *this = *this * other;
  }

  template<typename U>
  mat& operator/=(const U& other) noexcept {
    impl_.columns[0] /= other;
    impl_.columns[1] /= other;
    impl_.columns[2] /= other;
    impl_.columns[3] /= other;
    return *this;
  }

  template<typename U>
  mat& operator/=(const mat<U, 4, R>& other) noexcept {
    impl_.columns[0] /= other[0];
    impl_.columns[1] /= other[1];
    impl_.columns[2] /= other[2];
    impl_.columns[3] /= other[3];
    return *this;
  }

  template<typename U>
  mat& operator%=(const U& other) noexcept {
    impl_.columns[0] %= other;
    impl_.columns[1] %= other;
    impl_.columns[2] %= other;
    impl_.columns[3] %= other;
    return *this;
  }

  template<typename U>
  mat& operator%=(const mat<U, 4, R>& other) noexcept {
    impl_.columns[0] %= other[0];
    impl_.columns[1] %= other[1];
    impl_.columns[2] %= other[2];
    impl_.columns[3] %= other[3];
    return *this;
  }

  template<typename U>
  mat& operator&=(const U& other) noexcept {
    impl_.columns[0] &= other;
    impl_.columns[1] &= other;
    impl_.columns[2] &= other;
    impl_.columns[3] &= other;
    return *this;
  }

  template<typename U>
  mat& operator&=(const mat<U, 4, R>& other) noexcept {
    impl_.columns[0] &= other[0];
    impl_.columns[1] &= other[1];
    impl_.columns[2] &= other[2];
    impl_.columns[3] &= other[3];
    return *this;
  }

  template<typename U>
  mat& operator|=(const U& other) noexcept {
    impl_.columns[0] |= other;
    impl_.columns[1] |= other;
    impl_.columns[2] |= other;
    impl_.columns[3] |= other;
    return *this;
  }

  template<typename U>
  mat& operator|=(const mat<U, 4, R>& other) noexcept {
    impl_.columns[0] |= other[0];
    impl_.columns[1] |= other[1];
    impl_.columns[2] |= other[2];
    impl_.columns[3] |= other[3];
    return *this;
  }

  template<typename U>
  mat& operator^=(const U& other) noexcept {
    impl_.columns[0] ^= other;
    impl_.columns[1] ^= other;
    impl_.columns[2] ^= other;
    impl_.columns[3] ^= other;
    return *this;
  }

  template<typename U>
  mat& operator^=(const mat<U, 4, R>& other) noexcept {
    impl_.columns[0] ^= other[0];
    impl_.columns[1] ^= other[1];
    impl_.columns[2] ^= other[2];
    impl_.columns[3] ^= other[3];
    return *this;
  }

  template<typename U>
  mat& operator<<=(const U& other) noexcept {
    impl_.columns[0] <<= other;
    impl_.columns[1] <<= other;
    impl_.columns[2] <<= other;
    impl_.columns[3] <<= other;
    return *this;
  }

  template<typename U>
  mat& operator<<=(const mat<U, 4, R>& other) noexcept {
    impl_.columns[0] <<= other[0];
    impl_.columns[1] <<= other[1];
    impl_.columns[2] <<= other[2];
    impl_.columns[3] <<= other[3];
    return *this;
  }

  template<typename U>
  mat& operator>>=(const U& other) noexcept {
    impl_.columns[0] >>= other;
    impl_.columns[1] >>= other;
    impl_.columns[2] >>= other;
    impl_.columns[3] >>= other;
    return *this;
  }

  template<typename U>
  mat& operator>>=(const mat<U, 4, R>& other) noexcept {
    impl_.columns[0] >>= other[0];
    impl_.columns[1] >>= other[1];
    impl_.columns[2] >>= other[2];
    impl_.columns[3] >>= other[3];
    return *this;
  }
};

template<typename T, int R>
inline TUE_CONSTEXPR auto operator+(const mat<T, 4, R>& m) noexcept {
  return mat<decltype(+m[0][0]), 4, R>(+m[0], +m[1], +m[2], +m[3]);
}

template<typename T, int R>
inline TUE_CONSTEXPR auto operator-(const mat<T, 4, R>& m) noexcept {
  return mat<decltype(-m[0][0]), 4, R>(-m[0], -m[1], -m[2], -m[3]);
}

template<typename T, int R>
inline TUE_CONSTEXPR auto operator~(const mat<T, 4, R>& m) noexcept {
  return mat<decltype(~m[0][0]), 4, R>(~m[0], ~m[1], ~m[2], ~m[3]);
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator+(
    const T& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs + rhs[0][0]), 4, R>{
    lhs + rhs[0],
    lhs + rhs[1],
    lhs + rhs[2],
    lhs + rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator+(
    const mat<T, 4, R>& lhs,
    const U& rhs) noexcept {
  return mat<decltype(lhs[0][0] + rhs), 4, R>{
    lhs[0] + rhs,
    lhs[1] + rhs,
    lhs[2] + rhs,
    lhs[3] + rhs,
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator+(
    const mat<T, 4, R>& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs[0][0] + rhs[0][0]), 4, R>{
    lhs[0] + rhs[0],
    lhs[1] + rhs[1],
    lhs[2] + rhs[2],
    lhs[3] + rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator-(
    const T& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs - rhs[0][0]), 4, R>{
    lhs - rhs[0],
    lhs - rhs[1],
    lhs - rhs[2],
    lhs - rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator-(
    const mat<T, 4, R>& lhs,
    const U& rhs) noexcept {
  return mat<decltype(lhs[0][0] - rhs), 4, R>{
    lhs[0] - rhs,
    lhs[1] - rhs,
    lhs[2] - rhs,
    lhs[3] - rhs,
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator-(
    const mat<T, 4, R>& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs[0][0] - rhs[0][0]), 4, R>{
    lhs[0] - rhs[0],
    lhs[1] - rhs[1],
    lhs[2] - rhs[2],
    lhs[3] - rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator*(
    const T& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs * rhs[0][0]), 4, R>{
    lhs * rhs[0],
    lhs * rhs[1],
    lhs * rhs[2],
    lhs * rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator*(
    const mat<T, 4, R>& lhs,
    const U& rhs) noexcept {
  return mat<decltype(lhs[0][0] * rhs), 4, R>{
    lhs[0] * rhs,
    lhs[1] * rhs,
    lhs[2] * rhs,
    lhs[3] * rhs,
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator/(
    const T& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs / rhs[0][0]), 4, R>{
    lhs / rhs[0],
    lhs / rhs[1],
    lhs / rhs[2],
    lhs / rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator/(
    const mat<T, 4, R>& lhs,
    const U& rhs) noexcept {
  return mat<decltype(lhs[0][0] / rhs), 4, R>{
    lhs[0] / rhs,
    lhs[1] / rhs,
    lhs[2] / rhs,
    lhs[3] / rhs,
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator/(
    const mat<T, 4, R>& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs[0][0] / rhs[0][0]), 4, R>{
    lhs[0] / rhs[0],
    lhs[1] / rhs[1],
    lhs[2] / rhs[2],
    lhs[3] / rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator%(
    const T& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs % rhs[0][0]), 4, R>{
    lhs % rhs[0],
    lhs % rhs[1],
    lhs % rhs[2],
    lhs % rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator%(
    const mat<T, 4, R>& lhs,
    const U& rhs) noexcept {
  return mat<decltype(lhs[0][0] % rhs), 4, R>{
    lhs[0] % rhs,
    lhs[1] % rhs,
    lhs[2] % rhs,
    lhs[3] % rhs,
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator%(
    const mat<T, 4, R>& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs[0][0] % rhs[0][0]), 4, R>{
    lhs[0] % rhs[0],
    lhs[1] % rhs[1],
    lhs[2] % rhs[2],
    lhs[3] % rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator&(
    const T& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs & rhs[0][0]), 4, R>{
    lhs & rhs[0],
    lhs & rhs[1],
    lhs & rhs[2],
    lhs & rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator&(
    const mat<T, 4, R>& lhs,
    const U& rhs) noexcept {
  return mat<decltype(lhs[0][0] & rhs), 4, R>{
    lhs[0] & rhs,
    lhs[1] & rhs,
    lhs[2] & rhs,
    lhs[3] & rhs,
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator&(
    const mat<T, 4, R>& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs[0][0] & rhs[0][0]), 4, R>{
    lhs[0] & rhs[0],
    lhs[1] & rhs[1],
    lhs[2] & rhs[2],
    lhs[3] & rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator|(
    const T& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs | rhs[0][0]), 4, R>{
    lhs | rhs[0],
    lhs | rhs[1],
    lhs | rhs[2],
    lhs | rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator|(
    const mat<T, 4, R>& lhs,
    const U& rhs) noexcept {
  return mat<decltype(lhs[0][0] | rhs), 4, R>{
    lhs[0] | rhs,
    lhs[1] | rhs,
    lhs[2] | rhs,
    lhs[3] | rhs,
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator|(
    const mat<T, 4, R>& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs[0][0] | rhs[0][0]), 4, R>{
    lhs[0] | rhs[0],
    lhs[1] | rhs[1],
    lhs[2] | rhs[2],
    lhs[3] | rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator^(
    const T& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs ^ rhs[0][0]), 4, R>{
    lhs ^ rhs[0],
    lhs ^ rhs[1],
    lhs ^ rhs[2],
    lhs ^ rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator^(
    const mat<T, 4, R>& lhs,
    const U& rhs) noexcept {
  return mat<decltype(lhs[0][0] ^ rhs), 4, R>{
    lhs[0] ^ rhs,
    lhs[1] ^ rhs,
    lhs[2] ^ rhs,
    lhs[3] ^ rhs,
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator^(
    const mat<T, 4, R>& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs[0][0] ^ rhs[0][0]), 4, R>{
    lhs[0] ^ rhs[0],
    lhs[1] ^ rhs[1],
    lhs[2] ^ rhs[2],
    lhs[3] ^ rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator<<(
    const T& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs << rhs[0][0]), 4, R>{
    lhs << rhs[0],
    lhs << rhs[1],
    lhs << rhs[2],
    lhs << rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator<<(
    const mat<T, 4, R>& lhs,
    const U& rhs) noexcept {
  return mat<decltype(lhs[0][0] << rhs), 4, R>{
    lhs[0] << rhs,
    lhs[1] << rhs,
    lhs[2] << rhs,
    lhs[3] << rhs,
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator<<(
    const mat<T, 4, R>& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs[0][0] << rhs[0][0]), 4, R>{
    lhs[0] << rhs[0],
    lhs[1] << rhs[1],
    lhs[2] << rhs[2],
    lhs[3] << rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator>>(
    const T& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs >> rhs[0][0]), 4, R>{
    lhs >> rhs[0],
    lhs >> rhs[1],
    lhs >> rhs[2],
    lhs >> rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator>>(
    const mat<T, 4, R>& lhs,
    const U& rhs) noexcept {
  return mat<decltype(lhs[0][0] >> rhs), 4, R>{
    lhs[0] >> rhs,
    lhs[1] >> rhs,
    lhs[2] >> rhs,
    lhs[3] >> rhs,
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR auto operator>>(
    const mat<T, 4, R>& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return mat<decltype(lhs[0][0] >> rhs[0][0]), 4, R>{
    lhs[0] >> rhs[0],
    lhs[1] >> rhs[1],
    lhs[2] >> rhs[2],
    lhs[3] >> rhs[3],
  };
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR bool operator==(
        const mat<T, 4, R>& lhs,
        const mat<U, 4, R>& rhs) noexcept {
  return lhs[0] == rhs[0]
      && lhs[1] == rhs[1]
      && lhs[2] == rhs[2]
      && lhs[3] == rhs[3];
}

template<typename T, typename U, int R>
inline TUE_CONSTEXPR bool operator!=(
    const mat<T, 4, R>& lhs,
    const mat<U, 4, R>& rhs) noexcept {
  return !(lhs == rhs);
}

namespace math
{
  template<typename T, int R>
  inline auto sin(const mat<T, 4, R>& m) noexcept {
    return mat<decltype(math::sin(m[0][0])), 4, R>{
      math::sin(m[0]),
      math::sin(m[1]),
      math::sin(m[2]),
      math::sin(m[3]),
    };
  }

  template<typename T, int R>
  inline auto cos(const mat<T, 4, R>& m) noexcept {
    return mat<decltype(math::cos(m[0][0])), 4, R>{
      math::cos(m[0]),
      math::cos(m[1]),
      math::cos(m[2]),
      math::cos(m[3]),
    };
  }

  template<typename T, int R>
  inline void sincos(
      const mat<T, 4, R>& m,
      decltype(math::sin(m))& sin_result,
      decltype(math::cos(m))& cos_result) noexcept {
    math::sincos(m[0], sin_result[0], cos_result[0]);
    math::sincos(m[1], sin_result[1], cos_result[1]);
    math::sincos(m[2], sin_result[2], cos_result[2]);
    math::sincos(m[3], sin_result[3], cos_result[3]);
  }

  template<typename T, int R>
  inline auto exp(const mat<T, 4, R>& m) noexcept {
    return mat<decltype(math::exp(m[0][0])), 4, R>{
      math::exp(m[0]),
      math::exp(m[1]),
      math::exp(m[2]),
      math::exp(m[3]),
    };
  }

  template<typename T, int R>
  inline auto log(const mat<T, 4, R>& m) noexcept {
    return mat<decltype(math::log(m[0][0])), 4, R>{
      math::log(m[0]),
      math::log(m[1]),
      math::log(m[2]),
      math::log(m[3]),
    };
  }

  template<typename T, typename U, int R>
  inline auto pow(
      const mat<T, 4, R>& base,
      const U& exponent) noexcept {
    return mat<decltype(math::pow(base[0][0], exponent)), 4, R>{
      math::pow(base[0], exponent),
      math::pow(base[1], exponent),
      math::pow(base[2], exponent),
      math::pow(base[3], exponent),
    };
  }

  template<typename T, typename U, int R>
  inline auto pow(
      const mat<T, 4, R>& base,
      const mat<U, 4, R>& exponent) noexcept {
    return mat<decltype(math::pow(base[0][0], exponent[0][0])), 4, R>{
      math::pow(base[0], exponent[0]),
      math::pow(base[1], exponent[1]),
      math::pow(base[2], exponent[2]),
      math::pow(base[3], exponent[3]),
    };
  }

  template<typename T, int R>
  inline auto recip(const mat<T, 4, R>& m) noexcept {
    return mat<decltype(math::recip(m[0][0])), 4, R>{
      math::recip(m[0]),
      math::recip(m[1]),
      math::recip(m[2]),
      math::recip(m[3]),
    };
  }

  template<typename T, int R>
  inline auto sqrt(const mat<T, 4, R>& m) noexcept {
    return mat<decltype(math::sqrt(m[0][0])), 4, R>{
      math::sqrt(m[0]),
      math::sqrt(m[1]),
      math::sqrt(m[2]),
      math::sqrt(m[3]),
    };
  }

  template<typename T, int R>
  inline auto rsqrt(const mat<T, 4, R>& m) noexcept {
    return mat<decltype(math::rsqrt(m[0][0])), 4, R>{
      math::rsqrt(m[0]),
      math::rsqrt(m[1]),
      math::rsqrt(m[2]),
      math::rsqrt(m[3]),
    };
  }

  template<typename T, int R>
  inline auto min(
      const mat<T, 4, R>& m1,
      const mat<T, 4, R>& m2) noexcept {
    return mat<decltype(math::min(m1[0][0], m2[0][0])), 4, R>{
      math::min(m1[0], m2[0]),
      math::min(m1[1], m2[1]),
      math::min(m1[2], m2[2]),
      math::min(m1[3], m2[3]),
    };
  }

  template<typename T, int R>
  inline auto max(
      const mat<T, 4, R>& m1,
      const mat<T, 4, R>& m2) noexcept {
    return mat<decltype(math::max(m1[0][0], m2[0][0])), 4, R>{
      math::max(m1[0], m2[0]),
      math::max(m1[1], m2[1]),
      math::max(m1[2], m2[2]),
      math::max(m1[3], m2[3]),
    };
  }

  template<typename T, int R>
  inline auto abs(const mat<T, 4, R>& m) noexcept {
    return mat<decltype(math::abs(m[0][0])), 4, R>{
      math::abs(m[0]),
      math::abs(m[1]),
      math::abs(m[2]),
      math::abs(m[3]),
    };
  }

  template<typename T, typename U, int R>
  inline TUE_CONSTEXPR auto compmult(
      const mat<T, 4, R>& lhs,
      const mat<U, 4, R>& rhs) noexcept {
    return mat<decltype(lhs[0][0] * rhs[0][0]), 4, R>{
      lhs[0] * rhs[0],
      lhs[1] * rhs[1],
      lhs[2] * rhs[2],
      lhs[3] * rhs[3],
    };
  }

  template<typename T, int R>
  inline TUE_CONSTEXPR mat<T, 4, R> transpose(
      const mat<T, R, 4>& m) noexcept {
    return {
      m.row(0),
      m.row(1),
      m.row(2),
      m.row(3),
    };
  }
}

}

#undef TUE_CONSTEXPR
#include "matmult.hpp"
