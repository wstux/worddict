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

#ifndef _WORDDICT_WORDDICT_DAWG_BUILDER_H_
#define _WORDDICT_WORDDICT_DAWG_BUILDER_H_

#include <cstring>
#include <map>
#include <type_traits>

#include "worddict/details/dawg_dict.h"
#include "worddict/details/dictraits.h"

namespace wstux {
namespace wd {
namespace details {

template<typename TChar>
class dawg_builder final
{
public:
    using base_type  = typename details::traits<TChar>::base_type;
    using char_type  = typename details::traits<TChar>::char_type;
    using uchar_type = typename details::traits<TChar>::uchar_type;
    using size_type  = typename details::traits<TChar>::size_type;
    using value_type = typename details::traits<TChar>::value_type;

    dawg_builder() {}

    void clear() {}

    bool finish(dawg_dict<TChar>& /*dict*/) { return false; }

    template<typename TValue, typename = typename std::enable_if<std::is_convertible<TValue, value_type>::value>::type>
    bool insert(const char_type* p_key, const TValue value)
    {
        if ((p_key == nullptr) || (*p_key == '\0') || value < 0) {
          return false;
        }
        return insert_impl(p_key, std::strlen(p_key), value);
      }

    template<typename TValue, typename = typename std::enable_if<std::is_convertible<TValue, value_type>::value>::type>
    bool insert(const char_type* p_key, const size_type len, const TValue value)
    {
        if (p_key == NULL || len == 0 || value < 0) {
            return false;
        }
        if (std::find(p_key, p_key + len, '\0') != (p_key + len)) {
            return false;
        }
        return insert_impl(p_key, len, value);
    }

    template<typename TValue, typename = typename std::enable_if<std::is_convertible<TValue, value_type>::value>::type>
    bool insert(const std::basic_string<char_type>& word, const TValue value)
    {
        if (word.empty() || value < 0) {
            return false;
        }
        return insert_impl(word.data(), word.size(), value);
    }

    template<typename TValue, typename = typename std::enable_if<std::is_convertible<TValue, value_type>::value>::type>
    bool insert(const std::basic_string_view<char_type>& word, const TValue value)
    {
        if (word.empty() || value < 0) {
            return false;
        }
        return insert_impl(word.data(), word.size(), value);
    }

    template<typename TValue, typename = typename std::enable_if<std::is_convertible<TValue, value_type>::value>::type>
    bool insert(const std::map<std::basic_string<char_type>, TValue>& words)
    {
        for (const std::pair<const std::basic_string<char_type>, TValue>& w : words) {
            if (! insert(w.first, w.second)) {
                return false;
            }
        }
        return true;
    }

    template<typename TValue, typename = typename std::enable_if<std::is_convertible<TValue, value_type>::value>::type>
    bool insert(const std::map<std::basic_string_view<char_type>, TValue>& words)
    {
        for (const std::pair<const std::basic_string_view<char_type>, TValue>& w : words) {
            if (! insert(w.first, w.second)) {
                return false;
            }
        }
        return true;
    }

private:
    bool insert_impl(const char_type* /*p_key*/, const size_type /*len*/, const value_type /*value*/)
    {
        return false;
    }
};

} // namespace details
} // namespace wd
} // namespace wstux

#endif /* _WORDDICT_WORDDICT_DAWG_BUILDER_H_ */

