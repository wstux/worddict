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

#ifndef _WORDDICT_WORDDICT_WORDDICT_H_
#define _WORDDICT_WORDDICT_WORDDICT_H_

#include <string_view>

#include "worddict/details/dictraits.h"

namespace wstux {
namespace wd {

template<typename TChar>
class word_dict final
{
public:
    using base_type  = typename details::traits<TChar>::base_type;
    using char_type  = typename details::traits<TChar>::char_type;
    using size_type  = typename details::traits<TChar>::size_type;
    using uchar_type = typename details::traits<TChar>::uchar_type;
    using value_type = typename details::traits<TChar>::value_type;

    value_type find(const std::basic_string_view<char_type>& /*key*/) const { return -1; }

    bool follow(const std::basic_string_view<char_type>& key, base_type& idx) const
    {
        for (size_type i = 0; i < key.length(); ++i) {
            if (! follow(key[i], idx)) {
                return false;
            }
        }
        return true;
    }

    bool follow(const char_type /*label*/, base_type& /*idx*/) const { return false; }

    bool has_value(const base_type& /*idx*/) const { return false; }

    base_type root() const { return 0; }
};

} // namespace wd
} // namespace wstux

#endif /* _WORDDICT_WORDDICT_WORDDICT_H_ */

