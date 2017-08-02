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
 * @file   text_purifier_c.h
 * @author Aludirk Wong
 * @date   2017-08-01
 */

#ifndef __LAKOO_TEXT_PURIFIER_C_H__
#define __LAKOO_TEXT_PURIFIER_C_H__

#include <stdlib.h>


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//! Create a text purifier handle.
/**
 * @return The handle for text purifier, and must free with text_purifier_destroy(void*).
 */
void* text_purifier_init(void);

//! Destroy the text purifier handle.
/**
 * @param [in] handle The handle created from text_purifier_init(void) to destroy.
 */
void text_purifier_destroy(void* handle);

//! To add a word to the list to purify.
/**
 * @param [in] handle The text purifier handle.
 * @param [in] str    The char string to add.
 */
void text_purifier_add(void* handle, const char* str);

//! To add a word to the list to purify.
/**
 * @param [in] handle The text purifier handle.
 * @param [in] str    The wchar_t string to add.
 */
void text_purifier_wadd(void* handle, const wchar_t* str);

//! To add a list of words to the list to purify.
/**
 * @param [in] handle The text purifier handle.
 * @param [in] list   The list of char string to add.
 * @param [in] count  The number of words in the list.
 */
void text_purifier_add_list(void* handle, const char* const* list, size_t count);

//! To add a list of words to the list to purify.
/**
 * @param [in] handle The text purifier handle.
 * @param [in] list   The list of wchar_t string to add.
 * @param [in] count  The number of words in the list.
 */
void text_purifier_add_wlist(void* handle, const wchar_t* const* list, size_t count);

//! To purify the string with given mask.
/**
 * @param [in] handle The text purifier handle.
 * @param [in] str    The char string to purify.
 * @param [in] mask   The char string mask.
 * @return            The purified string, must be free with
 *                    text_purifier_free_str(void*, const char*).
 */
const char* text_purifier_purify2str(void* handle, const char* str, const char* mask);

//! To purify the string with given mask.
/**
 * @param [in] handle      The text purifier handle.
 * @param [in] str         The char string to purify.
 * @param [in] mask        The char mask.
 * @param [in] isMatchSize If isMatchSize is not 0, the mask will be repeated until the same size
 *                         with the purified word.
 * @return                 The purified string, must be free with
 *                         text_purifier_free_str(void*, const char*).
 */
const char* text_purifier_purify2char(void* handle, const char* str, char mask, char isMatchSize);

//! To free the purified string.
/**
 * @param [in] handle The text purifier handle.
 * @param [in] str    The string to free.
 * @see text_purifier_purify2str(void*, const char*, const char*) and
 *      text_purifier_purify2char(void*, const char*, char, char).
 */
void text_purifier_free_str(void* handle, const char* str);

//! To purify the string with given mask.
/**
 * @param [in] handle The text purifier handle.
 * @param [in] str    The wchar_t string to purify.
 * @param [in] mask   The wchar_t string mask.
 * @return            The purified string, must be free with
 *                    text_purifier_free_wstr(void*, const wchar_t*).
 */
const wchar_t* text_purifier_wpurify2str(void* handle, const wchar_t* str, const wchar_t* mask);

//! To purify the string with given mask.
/**
 * @param [in] handle      The text purifier handle.
 * @param [in] str         The wchar_t string to purify.
 * @param [in] mask        The wchar_t mask.
 * @param [in] isMatchSize If isMatchSize is not 0, the mask will be repeated until the same size
 *                         with the purified word.
 * @return                 The purified string, must be free with
 *                         text_purifier_free_wstr(void*, const wchar_t*).
 */
const wchar_t* text_purifier_wpurify2char(void* handle,
                                          const wchar_t* str,
                                          wchar_t mask,
                                          char isMatchSize);

//! To free the purified string.
/**
 * @param [in] handle The text purifier handle.
 * @param [in] str    The string to free.
 * @see text_purifier_wpurify2str(void*, const wchar_t*, const wchar_t*) and
 *      text_purifier_wpurify2char(void*, const wchar_t*, wchar_t, char).
 */
void text_purifier_free_wstr(void* handle, const wchar_t* str);

//! Check whether the given string need to be purified.
/**
 * @param [in] handle The text purifier handle.
 * @param [in] str    The char string to check.
 * @return            1 if the given string need to be purified or else 0.
 */
char text_purifier_check(void* handle, const char* str);

//! Check whether the given string need to be purified.
/**
 * @param [in] handle The text purifier handle.
 * @param [in] str    The wchar_t string to check.
 * @return            1 if the given string need to be purified or else 0.
 */
char text_purifier_wcheck(void* handle, const wchar_t* str);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __LAKOO_TEXT_PURIFIER_C_H__
