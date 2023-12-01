#include <testing/testdefs.h>

#include "worddict/details/dawg_builder.h"
#include "worddict/details/dawg_dict.h"

#define __TO_UTF8_STRING(x) x
#define __TO_WSTRING(x) L ## x
#define __TO_UTF16_STRING(x) u ## x
#define __TO_UTF32_STRING(x) U ## x

#define U(TCHAR, x)                                                     \
    []() -> std::basic_string<TCHAR> {                                  \
        using const_ptr_t = const TCHAR*;                               \
        if constexpr (std::is_same<TCHAR, wchar_t>::value) {            \
            return reinterpret_cast<const_ptr_t>(__TO_WSTRING(x));      \
        } else if constexpr (sizeof(TCHAR) == 1) {                      \
            return reinterpret_cast<const_ptr_t>(__TO_UTF8_STRING(x));  \
        } else if constexpr (sizeof(TCHAR) == 2) {                      \
            return reinterpret_cast<const_ptr_t>(__TO_UTF16_STRING(x)); \
        } else /* if constexpr (sizeof(TCHAR) == 4) */ {                \
            return reinterpret_cast<const_ptr_t>(__TO_UTF32_STRING(x)); \
        }                                                               \
    }()

namespace {

template<typename TType>
class dawg_fixture : public ::testing::Test {};

using dawg_types = testing::Types<char, int8_t, uint8_t, //wchar_t,
                                  //char16_t,
                                  //int16_t,
                                  uint16_t>;
TYPED_TEST_SUITE(dawg_fixture, dawg_types);

} // <anonumous> namespace

TYPED_TEST(dawg_fixture, build)
{
    using char_type = TypeParam;
    using string_type = std::basic_string<char_type>;

    const string_type s1 = U(char_type, "bugaga");
    const string_type s2 = U(char_type, "bugagb");
    const string_type s3 = U(char_type, "bugagc");
    const string_type s4 = U(char_type, "bugora");

    wstux::wd::details::dawg_builder<char_type> builder;
    EXPECT_TRUE(builder.insert(s1, 1));
    EXPECT_TRUE(builder.insert(s2, 2));
    EXPECT_TRUE(builder.insert(s3, 3));
    EXPECT_TRUE(builder.insert(s4, 4));

    wstux::wd::details::dawg_dict<char_type> dict;
    EXPECT_TRUE(builder.finish(dict));

    EXPECT_TRUE(dict.merged_states_count() == 3) << dict.merged_states_count() << " != 3";
    EXPECT_TRUE(dict.merged_transitions_count() == 0) << dict.merged_transitions_count() << " != 0";
    EXPECT_TRUE(dict.merging_states_count() == 0) << dict.merging_states_count() << " != 0";
    EXPECT_TRUE(dict.size()== 16) << dict.size() << " != 16";
    EXPECT_TRUE(dict.states_count() == 13) << dict.states_count() << " != 13";
    EXPECT_TRUE(dict.transitions_count() == 15) << dict.transitions_count() << " != 15";
}

TYPED_TEST(dawg_fixture, build_many_words)
{
    using char_type = TypeParam;
    using string_type = std::basic_string<char_type>;

    string_type str = U(char_type, "bugaga");

    wstux::wd::details::dawg_builder<char_type> builder;
    for (size_t i = 0, j = 0; i < std::numeric_limits<uint16_t>::max(); ++i) {
        ASSERT_TRUE(builder.insert(str, i));
        if (j == str.size()) {
            str += 'a';
        } else if (str[j] == 'z') {
            ++j;
        } else {
            ++str[j];
        }
    }

    wstux::wd::details::dawg_dict<char_type> dict;
    EXPECT_TRUE(builder.finish(dict));

    EXPECT_TRUE(dict.merged_states_count() == 63106) << dict.merged_states_count() << " != 63106";
    EXPECT_TRUE(dict.merged_transitions_count() == 0) << dict.merged_transitions_count() << " != 0";
    EXPECT_TRUE(dict.merging_states_count() == 0) << dict.merging_states_count() << " != 0";
    EXPECT_TRUE(dict.size()== 126486) << dict.size() << " != 126486";
    EXPECT_TRUE(dict.states_count() == 63380) << dict.states_count() << " != 63380";
    EXPECT_TRUE(dict.transitions_count() == 126485) << dict.transitions_count() << " != 126485";
}

int main(int /*argc*/, char** /*argv*/)
{
    return RUN_ALL_TESTS();
}
