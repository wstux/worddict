/*
 * worddict
 * Copyright (C) 2023  Chistyakov Alexander
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _WORDDICT_WORDDICT_DICTRAITS_H_
#define _WORDDICT_WORDDICT_DICTRAITS_H_

#include <type_traits>

namespace wstux {
namespace wd {
namespace details {

template<typename TChar>
struct traits final {};

template<>
struct traits<char> final
{
    using char_type = char;
    using uchar_type = uint8_t;
    using value_type = int32_t;
    using base_type = uint32_t;

    using size_type = size_t;
};

template<>
struct traits<int8_t> final
{
    using char_type  = int8_t;
    using uchar_type = uint8_t;
    using base_type  = uint32_t;
    using value_type = int32_t;

    using size_type  = size_t;
};

template<>
struct traits<uint8_t> final
{
    using char_type  = uint8_t;
    using uchar_type = uint8_t;
    using base_type  = uint32_t;
    using value_type = int32_t;

    using size_type  = size_t;
};

template<>
struct traits<char16_t> final
{
    using char_type  = char16_t;
    using uchar_type = uint16_t;
    using base_type  = uint64_t;
    using value_type = int64_t;

    using size_type  = size_t;
};

template<>
struct traits<int16_t> final
{
    using char_type  = int16_t;
    using uchar_type = uint16_t;
    using base_type  = uint64_t;
    using value_type = int64_t;

    using size_type  = size_t;
};

template<>
struct traits<uint16_t> final
{
    using char_type  = uint16_t;
    using uchar_type = uint16_t;
    using base_type  = uint64_t;
    using value_type = int64_t;

    using size_type  = size_t;
};

} // namespace details
} // namespace wd
} // namespace wstux

#endif /* _WORDDICT_WORDDICT_DICTRAITS_H_ */

