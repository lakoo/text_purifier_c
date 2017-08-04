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
 * @file   test.h
 * @author Aludirk Wong
 * @date   2017-08-03
 */

#ifndef __LAKOO_TEST_H__
#define __LAKOO_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

#include "test_util.h"


template <typename _Class, typename _Type>
class TestTextPurifier : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(_Class);
    CPPUNIT_TEST(testNull);
    CPPUNIT_TEST(testEmpty);
    CPPUNIT_TEST(testAddWord);
    CPPUNIT_TEST(testAddList);
    CPPUNIT_TEST(testPurify);
    CPPUNIT_TEST_SUITE_END();

public:
    TestTextPurifier()
    : _handle(NULL)
    {
    }

    virtual ~TestTextPurifier() = default;

public:
    void setUp() override
    {
        CPPUNIT_ASSERT(NULL == _handle);
        _handle = text_purifier_init();
        CPPUNIT_ASSERT(NULL != _handle);
    }

    void tearDown() override
    {
        CPPUNIT_ASSERT(NULL != _handle);
        text_purifier_destroy(_handle);
        _handle = NULL;
    }

protected:
    void testNull()
    {
        TestUtil::testNull<_Type>();
    }

    void testEmpty()
    {
        TestUtil::testEmpty<_Type>(_handle);
    }

    void testAddWord()
    {
        TestUtil::testAddWord<_Type>(_handle);
    }

    void testAddList()
    {
        TestUtil::testAddList<_Type>(_handle);
    }

    void testPurify()
    {
        TestUtil::testPurify<_Type>(_handle);
    }

private:
    void* _handle;
};

class TestWcStr final : public TestTextPurifier<TestWcStr, wchar_t> {};
class TestCStr final : public TestTextPurifier<TestCStr, char> {};

#endif // __LAKOO_TEST_H__
