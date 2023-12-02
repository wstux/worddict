#include <testing/testdefs.h>

#include "worddict/builder.h"

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
class wd_fixture : public ::testing::Test {};

using wd_types = testing::Types<char, int8_t, uint8_t, //wchar_t,
                                //char16_t,
                                //int16_t,
                                uint16_t>;
TYPED_TEST_SUITE(wd_fixture, wd_types);

} // <anonumous> namespace

TYPED_TEST(wd_fixture, build)
{
    using char_type = TypeParam;
    using string_type = std::basic_string<char_type>;

    const string_type s1 = U(char_type, "bugaga");
    const string_type s2 = U(char_type, "bugagb");
    const string_type s3 = U(char_type, "bugagc");
    const string_type s4 = U(char_type, "bugora");

    wstux::wd::builder<char_type> builder;
    EXPECT_TRUE(builder.insert(s1, 1));
    EXPECT_TRUE(builder.insert(s2, 2));
    EXPECT_TRUE(builder.insert(s3, 3));
    EXPECT_TRUE(builder.insert(s4, 4));

    wstux::wd::word_dict<char_type> dict;
    EXPECT_TRUE(builder.build(dict));
}

TYPED_TEST(wd_fixture, insert)
{
    using char_type = TypeParam;
    using string_type = std::basic_string<char_type>;

    const string_type s1 = U(char_type, "bugaga");
    const string_type s2 = U(char_type, "bugagb");
    const string_type s3 = U(char_type, "bugagc");
    const string_type s4 = U(char_type, "bugora");

    wstux::wd::builder<char_type> builder;
    EXPECT_TRUE(builder.insert(s1, 1));
    EXPECT_TRUE(builder.insert(s2, 2));
    EXPECT_TRUE(builder.insert(s3, 3));
    EXPECT_TRUE(builder.insert(s4, 4));

    wstux::wd::word_dict<char_type> dict;
    EXPECT_TRUE(builder.build(dict));
}

TYPED_TEST(wd_fixture, insert_map)
{
    using char_type = TypeParam;
    using string_type = std::basic_string<char_type>;

    const std::map<string_type, int> dict_src = {
        {U(char_type, "bugaga"), 1},
        {U(char_type, "bugagb"), 2},
        {U(char_type, "bugagc"), 3},
        {U(char_type, "bugora"), 4},
    };

    wstux::wd::builder<char_type> builder;
    EXPECT_TRUE(builder.insert(dict_src));

    wstux::wd::word_dict<char_type> dict;
    EXPECT_TRUE(builder.build(dict));
}

TYPED_TEST(wd_fixture, find)
{
    using char_type = TypeParam;
    using string_type = std::basic_string<char_type>;

    const string_type s1 = U(char_type, "bugaga");
    const string_type s2 = U(char_type, "bugagb");
    const string_type s3 = U(char_type, "bugagc");
    const string_type s4 = U(char_type, "bugora");

    wstux::wd::builder<char_type> builder;
    EXPECT_TRUE(builder.insert(s1, 1));
    EXPECT_TRUE(builder.insert(s2, 2));
    EXPECT_TRUE(builder.insert(s3, 3));
    EXPECT_TRUE(builder.insert(s4, 4));

    wstux::wd::word_dict<char_type> dict;
    EXPECT_TRUE(builder.build(dict));

    EXPECT_TRUE(dict.find(s1) == 1) << dict.find(s1);
    EXPECT_TRUE(dict.find(s2) == 2) << dict.find(s2);
    EXPECT_TRUE(dict.find(s3) == 3) << dict.find(s3);
    EXPECT_TRUE(dict.find(s4) == 4) << dict.find(s4);
}

TYPED_TEST(wd_fixture, build_many_words)
{
    using char_type = TypeParam;
    using string_type = std::basic_string<char_type>;

    string_type str = U(char_type, "bugaga");

    wstux::wd::builder<char_type> builder;
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

    wstux::wd::word_dict<char_type> dict;
    EXPECT_TRUE(builder.build(dict));

    str = U(char_type, "bugaga");
    for (size_t i = 0, j = 0; i < std::numeric_limits<uint16_t>::max(); ++i) {
        ASSERT_TRUE((size_t)dict.find(str) == i) << i;
        if (j == str.size()) {
            str += 'a';
        } else if (str[j] == 'z') {
            ++j;
        } else {
            ++str[j];
        }
    }
}

int main(int /*argc*/, char** /*argv*/)
{
    return RUN_ALL_TESTS();
}
