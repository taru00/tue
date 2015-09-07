//                Copyright Jo Bates 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//     Please report any bugs, typos, or suggestions to
//         https://github.com/Cincinesh/tue/issues

#pragma once

#include <utility>

#include "math.hpp"
#include "quat.hpp"
#include "vec.hpp"

namespace tue
{
    /*!
     * \brief  Functions for generating and converting between different types
     *         of transformations.
     */
    namespace transform
    {
        /*!
         * \brief     Converts a rotation vector to an axis-angle vector.
         * \details   If the rotation vector's length is `0`, returns
         *            `(0, 0, 1, 0)`.
         *
         * \tparam T  The rotation vector's component type.
         * \param v   The rotation vector.
         * \return    The axis-angle vector.
         */
        template<typename T>
        inline vec4<decltype(tue::math::sqrt(std::declval<T>()))>
        axis_angle(const vec3<T>& v) noexcept
        {
            using U = decltype(tue::math::length(v));
            const auto angle = tue::math::length(v);
            const auto axis = tue::math::select(
                tue::math::not_equal(angle, U(0)),
                vec3<U>(v) / angle,
                vec3<U>::z_axis());

            return { axis, angle };
        }

        /*!
         * \brief     Converts a rotation vector to an axis-angle vector.
         * \details   If the rotation vector's length is `0`, returns
         *            `(0, 0, 1, 0)`.
         *
         * \tparam T  The rotation vector's component type.
         *
         * \param x   The rotation vector's first component.
         * \param y   The rotation vector's second component.
         * \param z   The rotation vector's third component.
         *
         * \return    The axis-angle vector.
         */
        template<typename T>
        inline vec4<decltype(tue::math::sqrt(std::declval<T>()))>
        axis_angle(const T& x, const T& y, const T& z) noexcept
        {
            return tue::transform::axis_angle(vec3<T>(x, y, z));
        }

        /*!
         * \brief        Converts an axis-angle pair to a rotation vector.
         *
         * \tparam T     The axis-angle component type.
         *
         * \param axis   The axis.
         * \param angle  The angle.
         *
         * \return       The rotation vector.
         */
        template<typename T>
        inline constexpr vec3<T>
        rotation_vec(const vec3<T>& axis, const T& angle) noexcept
        {
            return axis * angle;
        }

        /*!
         * \brief        Converts an axis-angle pair to a rotation vector.
         *
         * \tparam T     The axis-angle component type.
         *
         * \param x      The axis' first component.
         * \param y      The axis' second component.
         * \param z      The axis' third component.
         * \param angle  The angle.
         *
         * \return       The rotation vector.
         */
        template<typename T>
        inline constexpr vec3<T>
        rotation_vec(
            const T& x, const T& y, const T& z,
            const T& angle) noexcept
        {
            return {
                x * angle,
                y * angle,
                z * angle,
            };
        }

        /*!
         * \brief     Converts an axis-angle vector to a rotation vector.
         * \tparam T  The axis-angle component type.
         * \param v   The axis-angle vector.
         * \return    The rotation vector.
         */
        template<typename T>
        inline constexpr vec3<T>
        rotation_vec(const vec4<T>& v) noexcept
        {
            return {
                v[0] * v[3],
                v[1] * v[3],
                v[2] * v[3],
            };
        }

        /*!
         * \brief        Converts an axis-angle pair to a rotation quaternion.
         *
         * \tparam T     The axis-angle component type.
         *
         * \param axis   The axis.
         * \param angle  The angle.
         *
         * \return       The rotation quaternion.
         */
        template<typename T>
        inline quat<decltype(tue::math::sin(std::declval<T>()))>
        rotation_quat(const vec3<T>& axis, const T& angle) noexcept
        {
            using U = decltype(tue::math::sin(angle));
            U s, c;
            tue::math::sincos(U(angle) / U(2), s, c);
            return { vec3<U>(axis) * s, c };
        }

        /*!
         * \brief        Converts an axis-angle pair to a rotation quaternion.
         *
         * \tparam T     The axis-angle component type.
         *
         * \param x      The axis' first component.
         * \param y      The axis' second component.
         * \param z      The axis' third component.
         * \param angle  The angle.
         *
         * \return       The rotation quaternion.
         */
        template<typename T>
        inline quat<decltype(tue::math::sin(std::declval<T>()))>
        rotation_quat(
            const T& x, const T& y, const T& z, const T& angle) noexcept
        {
            using U = decltype(tue::math::sin(angle));
            U s, c;
            tue::math::sincos(U(angle) / U(2), s, c);
            return { x*s, y*s, z*s, c };
        }

        /*!
         * \brief     Converts an axis-angle vector to a rotation quaternion.
         * \tparam T  The axis-angle component type.
         * \param v   The axis-angle vector.
         * \return    The rotation quaternion.
         */
        template<typename T>
        inline quat<decltype(tue::math::sin(std::declval<T>()))>
        rotation_quat(const vec4<T>& v) noexcept
        {
            using U = decltype(tue::math::sin(angle));
            U s, c;
            tue::math::sincos(U(angle) / U(2), s, c);
            return { v[0]*s, v[1]*s, v[2]*s, c };
        }

        /*!
         * \brief     Converts a rotation vector to a rotation quaternion.
         * \details   If the rotation vector's length is `0`, returns
         *            `(0, 0, 0, 1)`.
         *
         * \tparam T  The rotation vector's component type.
         * \param v   The rotation vector.
         * \return    The rotation quaternion.
         */
        template<typename T>
        inline quat<decltype(tue::math::sqrt(std::declval<T>()))>
        rotation_quat(const vec3<T>& v) noexcept
        {
            return tue::transform::rotation_quat(
                tue::transform::axis_angle(v));
        }

        /*!
         * \brief     Converts a rotation vector to a rotation quaternion.
         * \details   If the rotation vector's length is `0`, returns
         *            `(0, 0, 0, 1)`.
         *
         * \tparam T  The rotation vector's component type.
         *
         * \param x   The rotation vector's first component.
         * \param y   The rotation vector's second component.
         * \param z   The rotation vector's third component.
         *
         * \return    The rotation quaternion.
         */
        template<typename T>
        inline quat<decltype(tue::math::sqrt(std::declval<T>()))>
        rotation_quat(const T& x, const T& y, const T& z) noexcept
        {
            return tue::transform::rotation_quat(
                tue::transform::axis_angle(v));
        }
    }
}