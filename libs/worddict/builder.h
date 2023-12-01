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

#ifndef _WORDDICT_WORDDICT_BUILDER_H_
#define _WORDDICT_WORDDICT_BUILDER_H_

#include <utility>

#include "worddict/worddict.h"
#include "worddict/details/dawg_builder.h"
#include "worddict/details/dawg_dict.h"
#include "worddict/details/dictraits.h"

namespace wstux {
namespace wd {

template<typename TChar>
class builder final
{
public:
    using base_type  = typename details::traits<TChar>::base_type;
    using char_type  = typename details::traits<TChar>::char_type;
    using size_type  = typename details::traits<TChar>::size_type;
    using uchar_type = typename details::traits<TChar>::uchar_type;
    using value_type = typename details::traits<TChar>::value_type;

    builder() {}

    bool build(word_dict<char_type>& /*dict*/)
    {
        details::dawg_dict<char_type> inter;
        if (! m_builder.finish(inter)) {
            return false;
        }

        m_builder.clear();
        return false;
    }

    template<typename ...TArgs>
    bool insert(TArgs&& ...args) { return m_builder.insert(std::forward<TArgs>(args)...); }

private:
    details::dawg_builder<char_type> m_builder;
};

} // namespace wd
} // namespace wstux

#endif /* _WORDDICT_WORDDICT_BUILDER_H_ */

