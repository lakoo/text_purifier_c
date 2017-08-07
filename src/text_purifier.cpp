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
 * @file   text_purifier.cpp
 * @author Aludirk Wong
 * @date   2017-08-01
 */

#include "text_purifier_c.h"

#include "text_purifier.h"


using namespace lakoo;


void* text_purifier_init(void)
{
    return new TextPurifier();
}

void text_purifier_destroy(void* handle)
{
    if(nullptr != handle)
    {
        delete static_cast<TextPurifier*>(handle);
    }
}

void text_purifier_add(void* handle, const char* str)
{
    if(nullptr != handle)
    {
        TextPurifier* tp = static_cast<TextPurifier*>(handle);
        tp->add(str);
    }
}

void text_purifier_wadd(void* handle, const wchar_t* str)
{
    if(nullptr != handle)
    {
        TextPurifier* tp = static_cast<TextPurifier*>(handle);
        tp->add(str);
    }
}

void text_purifier_add_list(void* handle, const char* const* list, size_t count)
{
    if(nullptr != handle)
    {
        TextPurifier* tp = static_cast<TextPurifier*>(handle);
        tp->add(list, static_cast<std::size_t>(count));
    }
}

void text_purifier_add_wlist(void* handle, const wchar_t* const* list, size_t count)
{
    if(nullptr != handle)
    {
        TextPurifier* tp = static_cast<TextPurifier*>(handle);
        tp->add(list, static_cast<std::size_t>(count));
    }
}

const char* text_purifier_purify2str(void* handle, const char* str, const char* mask)
{
    if(nullptr != handle)
    {
        const TextPurifier* tp = static_cast<TextPurifier*>(handle);
        return tp->purify(str, mask);
    }

    return nullptr;
}

const char* text_purifier_purify2char(void* handle, const char* str, char mask, char isMatchSize)
{
    if(nullptr != handle)
    {
        const TextPurifier* tp = static_cast<TextPurifier*>(handle);
        return tp->purify(str, mask, static_cast<bool>(isMatchSize));
    }

    return nullptr;
}

void text_purifier_free_str(void* handle, const char* str)
{
    if(nullptr != handle)
    {
        const TextPurifier* tp = static_cast<TextPurifier*>(handle);
        tp->freePurifiedString(str);
    }
}

const wchar_t* text_purifier_wpurify2str(void* handle, const wchar_t* str, const wchar_t* mask)
{
    if(nullptr != handle)
    {
        const TextPurifier* tp = static_cast<TextPurifier*>(handle);
        return tp->purify(str, mask);
    }

    return nullptr;
}

const wchar_t* text_purifier_wpurify2char(void* handle,
                                          const wchar_t* str,
                                          wchar_t mask,
                                          char isMatchSize)
{
    if(nullptr != handle)
    {
        const TextPurifier* tp = static_cast<TextPurifier*>(handle);
        return tp->purify(str, mask, static_cast<bool>(isMatchSize));
    }

    return nullptr;
}

void text_purifier_free_wstr(void* handle, const wchar_t* str)
{
    if(nullptr != handle)
    {
        const TextPurifier* tp = static_cast<TextPurifier*>(handle);
        tp->freePurifiedString(str);
    }
}

char text_purifier_check(void* handle, const char* str)
{
    if(nullptr != handle)
    {
        const TextPurifier* tp = static_cast<TextPurifier*>(handle);
        return tp->check(str) ? 1 : 0;
    }

    return 0;
}

char text_purifier_wcheck(void* handle, const wchar_t* str)
{
    if(nullptr != handle)
    {
        const TextPurifier* tp = static_cast<TextPurifier*>(handle);
        return tp->check(str) ? 1 : 0;
    }

    return 0;
}
