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

#ifndef _WORDDICT_WORDDICT_DAWG_DICT_H_
#define _WORDDICT_WORDDICT_DAWG_DICT_H_

#include <deque>

#include "worddict/details/dictraits.h"

namespace wstux {
namespace wd {
namespace details {

template<typename TChar>
class dawg_dict final
{
public:
    using base_type  = typename details::traits<TChar>::base_type;
    using char_type  = typename details::traits<TChar>::char_type;
    using size_type  = typename details::traits<TChar>::size_type;
    using uchar_type = typename details::traits<TChar>::uchar_type;
    using value_type = typename details::traits<TChar>::value_type;

    dawg_dict() {}

    size_type merged_states_count() const { return 0; }

    size_type merged_transitions_count() const { return 0; }

    size_type merging_states_count() const { return 0; }

    size_type size() const { return 0; }

    size_type states_count() const { return 0; }

    size_type transitions_count() const { return 0; }
};

} // namespace details
} // namespace wd
} // namespace wstux

#endif  /* _WORDDICT_WORDDICT_DAWG_DICT_H_ */

