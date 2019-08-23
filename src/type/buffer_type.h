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

#ifndef BPVM_TYPE_BUFFER_TYPE_H_
#define BPVM_TYPE_BUFFER_TYPE_H_

#include "../../include/type/exception.h"

namespace bpvm {

	namespace type {

		#define BPVM_TYPE_BUFFER_HEADER "[BPVM::TYPE::BUFFER]"
#ifndef NDEBUG
		#define BPVM_TYPE_BUFFER_EXCEPTION_HEADER BPVM_TYPE_BUFFER_HEADER " "
#else
		#define BPVM_TYPE_BUFFER_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			BPVM_TYPE_BUFFER_EXCEPTION_FILE_INVALID = 0,
			BPVM_TYPE_BUFFER_EXCEPTION_FILE_NOT_FOUND,
		};

		#define BPVM_TYPE_BUFFER_EXCEPTION_MAX BPVM_TYPE_BUFFER_EXCEPTION_FILE_NOT_FOUND

		static const std::string BPVM_TYPE_BUFFER_EXCEPTION_STR[] = {
			BPVM_TYPE_BUFFER_EXCEPTION_HEADER "Invalid file",
			BPVM_TYPE_BUFFER_EXCEPTION_HEADER "File not found",
			};

		#define BPVM_TYPE_BUFFER_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > BPVM_TYPE_BUFFER_EXCEPTION_MAX) ? STRING_UNKNOWN : \
				STRING(BPVM_TYPE_BUFFER_EXCEPTION_STR[_TYPE_]))

		#define THROW_BPVM_TYPE_BUFFER_EXCEPTION(_EXCEPT_) \
			THROW_BPVM_TYPE_BUFFER_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_BPVM_TYPE_BUFFER_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION(BPVM_TYPE_BUFFER_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)
	}
}

#endif // BPVM_TYPE_BUFFER_TYPE_H_
