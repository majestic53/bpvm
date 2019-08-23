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

#ifndef BPVM_TYPE_TRACE_TYPE_H_
#define BPVM_TYPE_TRACE_TYPE_H_

#include "../../include/common.h"

namespace bpvm {

	namespace type {

		#define BPVM_TYPE_TRACE_HEADER "[BPVM::TYPE::TRACE]"
#ifndef NDEBUG
		#define BPVM_TYPE_TRACE_EXCEPTION_HEADER BPVM_TYPE_TRACE_HEADER " "
#else
		#define BPVM_TYPE_TRACE_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			BPVM_TYPE_TRACE_EXCEPTION_FORMAT_INVALID = 0,
			BPVM_TYPE_TRACE_EXCEPTION_TIMESTAMP_INVALID,
		};

		#define BPVM_TYPE_TRACE_EXCEPTION_MAX BPVM_TYPE_TRACE_EXCEPTION_TIMESTAMP_INVALID

		static const std::string BPVM_TYPE_TRACE_EXCEPTION_STR[] = {
			BPVM_TYPE_TRACE_EXCEPTION_HEADER "Invalid format",
			BPVM_TYPE_TRACE_EXCEPTION_HEADER "Invalid timestamp",
			};

		#define BPVM_TYPE_TRACE_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > BPVM_TYPE_TRACE_EXCEPTION_MAX) ? STRING_UNKNOWN : \
				STRING(BPVM_TYPE_TRACE_EXCEPTION_STR[_TYPE_]))

		static const std::string LEVEL_COLOR_STR[] = {
			"\x1b[0m", // LEVEL_NONE
			"\x1b[91m", // LEVEL_ERROR
			"\x1b[93m", // LEVEL_WARNING
			"\x1b[94m", // LEVEL_INFORMATION
			"\x1b[90m", // LEVEL_VERBOSE
			};

		#define LEVEL_COLOR_STRING(_TYPE_) \
			(((_TYPE_) > LEVEL_MAX) ? LEVEL_COLOR_STR[LEVEL_NONE] : \
				STRING(LEVEL_COLOR_STR[_TYPE_]))

#ifdef TRACE_COLOR
		#define LEVEL_COLOR(_LEVEL_) \
			LEVEL_COLOR_STRING(_LEVEL_)
#else
		#define LEVEL_COLOR(_LEVEL_) \
			""
#endif // TRACE_COLOR

		static const std::string LEVEL_STR[] = {
			"", // LEVEL_NONE
			"Error", // LEVEL_ERROR
			"Warning", // LEVEL_WARNING
			"Information", // LEVEL_INFORMATION
			"Verbose", // LEVEL_VERBOSE
			};

		#define LEVEL_STRING(_TYPE_) \
			(((_TYPE_) > LEVEL_MAX) ? STRING_UNKNOWN : \
				STRING(LEVEL_STR[_TYPE_]))

		#define TIMESTAMP_FORMAT "%Y-%m-%d %H:%M:%S"
		#define TIMESTAMP_LENGTH 32
	}
}

#endif // BPVM_TYPE_TRACE_TYPE_H_
