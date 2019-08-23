/**
 * BPVM
 * Copyright (C) 2019 David Jolly
 *
 * BPVM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BPVM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BPVM_COMMON_TRACE_H_
#define BPVM_COMMON_TRACE_H_

#ifndef NDEBUG
	#define _TRACE(_LEVEL_, _PREFIX_, _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, _FORMAT_, ...) { \
		if((_LEVEL_) <= (TRACE)) { \
			bpvm::type::trace::generate(_LEVEL_, _PREFIX_, _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, _FORMAT_, __VA_ARGS__); \
		} \
		}
#else
	#define _TRACE(_LEVEL_, _PREFIX_, _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, _FORMAT_, ...)
#endif // NDEBUG

#define TRACE_ENTRY() \
	TRACE_ENTRY_FORMAT("", "")
#define TRACE_ENTRY_FORMAT(_FORMAT_, ...) \
	_TRACE(LEVEL_VERBOSE, "+", __FUNCTION__, __FILE__, __FUNCTION__, __LINE__, _FORMAT_, __VA_ARGS__)

#define TRACE_ERROR(_MESSAGE_, _FILE_, _FUNCTION_, _LINE_) \
	_TRACE(LEVEL_ERROR, "", _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, "", "")

#define TRACE_EXIT() \
	TRACE_EXIT_FORMAT("", "")
#define TRACE_EXIT_FORMAT(_FORMAT_, ...) \
	_TRACE(LEVEL_VERBOSE, "-", __FUNCTION__, __FILE__, __FUNCTION__, __LINE__, _FORMAT_, __VA_ARGS__)

#define TRACE_MESSAGE(_LEVEL_, _MESSAGE_) \
	TRACE_MESSAGE_FORMAT(_LEVEL_, _MESSAGE_, "", "")
#define TRACE_MESSAGE_FORMAT(_LEVEL_, _MESSAGE_, _FORMAT_, ...) \
	_TRACE(_LEVEL_, "", _MESSAGE_, __FILE__, __FUNCTION__, __LINE__, _FORMAT_, __VA_ARGS__)

#endif // BPVM_COMMON_TRACE_H_
