/******************************************************************************
 * Copyright (C) 2017 Lakoo Games Ltd.                                        *
 *                                                                            *
 * This file is part of Text Purifier.                                        *
 *                                                                            *
 * Text Purifier is free software: you can redistribute it and/or modify it   *
 * under the terms of the GNU Lesser General Public License as published      *
 * by the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                        *
 *                                                                            *
 * Text Purifier is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU Lesser General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with Text Purifier.  If not, see <http://www.gnu.org/licenses/>.     *
 ******************************************************************************/

/**
 * @file   test_util.h
 * @author Aludirk Wong
 * @date   2017-08-03
 */

#ifndef __LAKOO_TEST_UTIL_H__
#define __LAKOO_TEST_UTIL_H__

#include <algorithm>
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <list>
#include <memory>
#include <vector>

#include <cppunit/extensions/HelperMacros.h>

#include "text_purifier_c.h"


const char TRUE = 1;
const char FALSE = 0;


namespace CppUnit
{
    template <>
    struct assertion_traits<char>
    {
        static bool equal(const char& lhs, const char& rhs)
        {
            return lhs == rhs;
        }

        static std::string toString(const char& ch)
        {
            return std::to_string(ch);
        }
    };

    template<>
    struct assertion_traits<const char*>
    {
        static bool equal(const char* const& lhs, const char* const& rhs)
        {
            return strcmp(lhs, rhs) == 0;
        }

        static std::string toString(const char* const& str)
        {
            return std::string(str);
        }
    };

    template<>
    struct assertion_traits<const wchar_t*>
    {
        static bool equal(const wchar_t* const& lhs, const wchar_t* const& rhs)
        {
            return wcscmp(lhs, rhs) == 0;
        }

        static std::string toString(const wchar_t* const& str)
        {
            const char* const locale = setlocale(LC_ALL, "C.UTF-8");
            const std::size_t size = std::wcstombs(nullptr, str, 0) + 1;

            std::vector<char> cStr(size);
            std::memset(cStr.data(), 0, size);
            std::wcstombs(cStr.data(), str, size);

            setlocale(LC_ALL, locale);
            return std::string(cStr.begin(), cStr.end());
        }
    };
}


namespace TestUtil
{
    template <typename _Type>
    struct tp_func
    {
        typedef void (*add_func_T)(void*, const _Type*);
        typedef void (*add_list_func_T)(void*, const _Type* const*, size_t);
        typedef const _Type* (*purify2str_T)(void*, const _Type*, const _Type*);
        typedef const _Type* (*purify2char_T)(void*, const _Type*, _Type, char);
        typedef void (*free_str_T)(void*, const _Type*);
        typedef char (*check_func_T)(void*, const _Type*);

        static add_func_T add_func;
        static add_list_func_T add_list_func;
        static purify2str_T purify2str;
        static purify2char_T purify2char;
        static free_str_T free_str;
        static check_func_T check_func;
    };

    template <>
    struct tp_func<char>
    {
        typedef void (*add_func_T)(void*, const char*);
        typedef void (*add_list_func_T)(void*, const char* const*, size_t);
        typedef const char* (*purify2str_T)(void*, const char*, const char*);
        typedef const char* (*purify2char_T)(void*, const char*, char, char);
        typedef void (*free_str_T)(void*, const char*);
        typedef char (*check_func_T)(void*, const char*);

        static add_func_T add_func;
        static add_list_func_T add_list_func;
        static purify2str_T purify2str;
        static purify2char_T purify2char;
        static free_str_T free_str;
        static check_func_T check_func;
    };

    tp_func<char>::add_func_T tp_func<char>::add_func = text_purifier_add;
    tp_func<char>::add_list_func_T tp_func<char>::add_list_func = text_purifier_add_list;
    tp_func<char>::purify2str_T tp_func<char>::purify2str = text_purifier_purify2str;
    tp_func<char>::purify2char_T tp_func<char>::purify2char = text_purifier_purify2char;
    tp_func<char>::free_str_T tp_func<char>::free_str = text_purifier_free_str;
    tp_func<char>::check_func_T tp_func<char>::check_func = text_purifier_check;

    template <>
    struct tp_func<wchar_t>
    {
        typedef void (*add_func_T)(void*, const wchar_t*);
        typedef void (*add_list_func_T)(void*, const wchar_t* const*, size_t);
        typedef const wchar_t* (*purify2str_T)(void*, const wchar_t*, const wchar_t*);
        typedef const wchar_t* (*purify2char_T)(void*, const wchar_t*, wchar_t, char);
        typedef void (*free_str_T)(void*, const wchar_t*);
        typedef char (*check_func_T)(void*, const wchar_t*);

        static add_func_T add_func;
        static add_list_func_T add_list_func;
        static purify2str_T purify2str;
        static purify2char_T purify2char;
        static free_str_T free_str;
        static check_func_T check_func;
    };

    tp_func<wchar_t>::add_func_T tp_func<wchar_t>::add_func = text_purifier_wadd;
    tp_func<wchar_t>::add_list_func_T tp_func<wchar_t>::add_list_func = text_purifier_add_wlist;
    tp_func<wchar_t>::purify2str_T tp_func<wchar_t>::purify2str = text_purifier_wpurify2str;
    tp_func<wchar_t>::purify2char_T tp_func<wchar_t>::purify2char = text_purifier_wpurify2char;
    tp_func<wchar_t>::free_str_T tp_func<wchar_t>::free_str = text_purifier_free_wstr;
    tp_func<wchar_t>::check_func_T tp_func<wchar_t>::check_func = text_purifier_wcheck;

    //--------------------------------------------------------------------------

    #define STRING(_Type, _Str) getString<_Type>(_Str, L##_Str)

    template <typename _Type>
    const _Type* getString(const char*, const wchar_t*);
    template <> const char* getString<char>(const char* c, const wchar_t*) { return c; }
    template <> const wchar_t* getString<wchar_t>(const char*, const wchar_t* wc) { return wc; }

    //--------------------------------------------------------------------------

    #define CHARACTER(_Type, _Char) getCharacter<_Type>(_Char, L##_Char)

    template <typename _Type>
    _Type getCharacter(char, wchar_t);
    template <> char getCharacter<char>(char c, wchar_t) { return c; }
    template <> wchar_t getCharacter<wchar_t>(char, wchar_t wc) { return wc; }

    //--------------------------------------------------------------------------

    template <typename _Type>
    _Type getMask();
    template <> char getMask<char>() { return '*'; }
    template <> wchar_t getMask<wchar_t>() { return L'禁'; }

    //--------------------------------------------------------------------------

    template <typename _Type>
    const _Type* replaceMask(const _Type* str)
    {
        static std::basic_string<_Type> buffer; // Only work for single thread.
        buffer = str;
        std::replace(buffer.begin(), buffer.end(), CHARACTER(_Type, '#'), getMask<_Type>());
        return buffer.c_str();
    }

    //--------------------------------------------------------------------------

    #define TEST_WORD_LIST(_Type) \
        STRING(_Type, "歧視甲"), \
        STRING(_Type, "歧視乙"), \
        STRING(_Type, "歧視丙"), \
        STRING(_Type, "歧視甲乙丙"), \
        STRING(_Type, "粗口甲"), \
        STRING(_Type, "粗口乙"), \
        STRING(_Type, "粗口丙"), \
        STRING(_Type, "粗口甲乙丙"), \
        STRING(_Type, "色情甲"), \
        STRING(_Type, "色情乙"), \
        STRING(_Type, "色情丙"), \
        STRING(_Type, "色情甲乙丙"), \
        STRING(_Type, " \r\n\t"), \
        STRING(_Type, "")

    template <typename _Type>
    size_t makeList(const _Type* const*& result)
    {
        static const _Type* const list[] = { TEST_WORD_LIST(_Type) };
        // Only work for single thread.

        result = list;
        return sizeof(list) / sizeof(_Type*);
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testEmpty(void* handle)
    {
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "歧視甲")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "歧視乙")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "歧視丙")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle,
                                                               STRING(_Type, "歧視甲乙丙")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "粗口甲")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "粗口乙")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "粗口丙")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle,
                                                               STRING(_Type, "粗口甲乙丙")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "色情甲")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "色情乙")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "色情丙")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle,
                                                               STRING(_Type, "色情甲乙丙")));
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testWordList(void* handle)
    {
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "歧視")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "粗口")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "色情")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "甲")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "乙")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "丙")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle,
                                                               STRING(_Type, "歧視粗口色情")));
        CPPUNIT_ASSERT_EQUAL(FALSE, tp_func<_Type>::check_func(handle, STRING(_Type, "甲乙丙")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "歧視甲")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "歧視乙")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "歧視丙")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "歧視甲乙丙")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "粗口甲")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "粗口乙")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "粗口丙")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "粗口甲乙丙")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "色情甲")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "色情乙")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "色情丙")));
        CPPUNIT_ASSERT_EQUAL(TRUE, tp_func<_Type>::check_func(handle, STRING(_Type, "色情甲乙丙")));
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testPurifyWithString(void* handle)
    {
    #define TEST(test, mask, expected) \
        { \
            const _Type* result = NULL; \
            result = tp_func<_Type>::purify2str(handle, STRING(_Type, test), STRING(_Type, mask)); \
            CPPUNIT_ASSERT_EQUAL(STRING(_Type, expected), result); \
            tp_func<_Type>::free_str(handle, result); \
        } \

        TEST("", "*禁言*", "");
        TEST("歧視粗口色情", "*禁言*", "歧視粗口色情");
        TEST("甲乙丙", "*禁言*", "甲乙丙");
        TEST("ABC DEF GHI ＜歧視一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321",
             "*禁言*",
             "ABC DEF GHI ＜歧視一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321",
             "*禁言*",
             "ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜歧視甲＞ ＜歧視乙＞ ＜歧視丙＞ 歧視甲乙丙 987 654 321",
             "禁言",
             "ABC DEF GHI ＜禁言＞ ＜禁言＞ ＜禁言＞ 禁言 987 654 321");
        TEST("ABC DEF GHI ＜歧視甲＞ ＜歧視乙＞ ＜歧視丙＞ 歧視甲乙丙 987 654 321",
             "*禁言*",
             "ABC DEF GHI ＜*禁言*＞ ＜*禁言*＞ ＜*禁言*＞ *禁言* 987 654 321");
        TEST("ABC DEF GHI ＜粗口甲＞ ＜粗口乙＞ ＜粗口丙＞ 粗口甲乙丙 987 654 321",
             "禁言",
             "ABC DEF GHI ＜禁言＞ ＜禁言＞ ＜禁言＞ 禁言 987 654 321");
        TEST("ABC DEF GHI ＜粗口甲＞ ＜粗口乙＞ ＜粗口丙＞ 粗口甲乙丙 987 654 321",
             "*禁言*",
             "ABC DEF GHI ＜*禁言*＞ ＜*禁言*＞ ＜*禁言*＞ *禁言* 987 654 321");
        TEST("ABC DEF GHI ＜色情甲＞ ＜色情乙＞ ＜色情丙＞ 色情甲乙丙 987 654 321",
             "禁言",
             "ABC DEF GHI ＜禁言＞ ＜禁言＞ ＜禁言＞ 禁言 987 654 321");
        TEST("ABC DEF GHI ＜色情甲＞ ＜色情乙＞ ＜色情丙＞ 色情甲乙丙 987 654 321",
             "*禁言*",
             "ABC DEF GHI ＜*禁言*＞ ＜*禁言*＞ ＜*禁言*＞ *禁言* 987 654 321");
        TEST("歧視甲乙", "禁言", "禁言乙");
        TEST("歧視甲乙", "*禁言*", "*禁言*乙");
        TEST("粗口甲乙", "禁言", "禁言乙");
        TEST("粗口甲乙", "*禁言*", "*禁言*乙");
        TEST("色情甲乙", "禁言", "禁言乙");
        TEST("色情甲乙", "*禁言*", "*禁言*乙");

    #undef TEST
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testPurifyWithCharacter(void* handle)
    {
    #define TEST(test, isMatchSize, expectedFormat) \
        { \
            const _Type* const expected = replaceMask(STRING(_Type, expectedFormat)); \
            const _Type* result = NULL; \
            result = tp_func<_Type>::purify2char(handle, \
                                                 STRING(_Type, test), \
                                                 getMask<_Type>(), \
                                                 isMatchSize); \
            CPPUNIT_ASSERT_EQUAL(expected, result); \
            tp_func<_Type>::free_str(handle, result); \
        }

        TEST("", TRUE, "");
        TEST("", FALSE, "");
        TEST("歧視粗口色情", TRUE, "歧視粗口色情");
        TEST("歧視粗口色情", FALSE, "歧視粗口色情");
        TEST("甲乙丙", TRUE, "甲乙丙");
        TEST("甲乙丙", FALSE, "甲乙丙");
        TEST("ABC DEF GHI ＜歧視一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321",
             TRUE,
             "ABC DEF GHI ＜歧視一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜歧視一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321",
             FALSE,
             "ABC DEF GHI ＜歧視一二三＞ ＜粗口一二三＞ ＜色情一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321",
             TRUE,
             "ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321",
             FALSE,
             "ABC DEF GHI ＜甲乙丙一二三＞ 987 654 321");
        TEST("ABC DEF GHI ＜歧視甲＞ ＜歧視乙＞ ＜歧視丙＞ 歧視甲乙丙 987 654 321",
             TRUE,
             "ABC DEF GHI ＜###＞ ＜###＞ ＜###＞ ##### 987 654 321");
        TEST("ABC DEF GHI ＜歧視甲＞ ＜歧視乙＞ ＜歧視丙＞ 歧視甲乙丙 987 654 321",
             FALSE,
             "ABC DEF GHI ＜#＞ ＜#＞ ＜#＞ # 987 654 321");
        TEST("ABC DEF GHI ＜粗口甲＞ ＜粗口乙＞ ＜粗口丙＞ 粗口甲乙丙 987 654 321",
             TRUE,
             "ABC DEF GHI ＜###＞ ＜###＞ ＜###＞ ##### 987 654 321");
        TEST("ABC DEF GHI ＜粗口甲＞ ＜粗口乙＞ ＜粗口丙＞ 粗口甲乙丙 987 654 321",
             FALSE,
             "ABC DEF GHI ＜#＞ ＜#＞ ＜#＞ # 987 654 321");
        TEST("ABC DEF GHI ＜色情甲＞ ＜色情乙＞ ＜色情丙＞ 色情甲乙丙 987 654 321",
             TRUE,
             "ABC DEF GHI ＜###＞ ＜###＞ ＜###＞ ##### 987 654 321");
        TEST("ABC DEF GHI ＜色情甲＞ ＜色情乙＞ ＜色情丙＞ 色情甲乙丙 987 654 321",
             FALSE,
             "ABC DEF GHI ＜#＞ ＜#＞ ＜#＞ # 987 654 321");
        TEST("歧視甲乙", TRUE, "###乙");
        TEST("歧視甲乙", FALSE, "#乙");
        TEST("粗口甲乙", TRUE, "###乙");
        TEST("粗口甲乙", FALSE, "#乙");
        TEST("色情甲乙", TRUE, "###乙");
        TEST("色情甲乙", FALSE, "#乙");

    #undef TEST
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testAddWord(void* handle)
    {
        testEmpty<_Type>(handle);

        const _Type* const* list = NULL;
        const size_t size = makeList<_Type>(list);
        for(size_t index = 0; index < size; ++index)
        {
            tp_func<_Type>::add_func(handle, list[index]);
        }

        testWordList<_Type>(handle);
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testAddList(void* handle)
    {
        testEmpty<_Type>(handle);

        const _Type* const* list = NULL;
        const size_t size = makeList<_Type>(list);
        tp_func<_Type>::add_list_func(handle, list, size);
        testWordList<_Type>(handle);
    }

    //--------------------------------------------------------------------------

    template <typename _Type>
    void testPurify(void* handle)
    {
        const _Type* const* list = NULL;
        const size_t size = makeList<_Type>(list);
        tp_func<_Type>::add_list_func(handle, list, size);

        testPurifyWithString<_Type>(handle);
        testPurifyWithCharacter<_Type>(handle);
    }
}

#endif // __LAKOO_TEST_UTIL_H__
