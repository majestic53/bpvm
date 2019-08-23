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

#ifndef BPVM_TYPE_EXCEPTION_TYPE_H_
#define BPVM_TYPE_EXCEPTION_TYPE_H_

#include "../../include/common.h"

namespace bpvm {

	namespace type {

		#define BPVM_TYPE_EXCEPTION_HEADER "[BPVM::TYPE::EXCEPTION]"
#ifndef NDEBUG
		#define BPVM_TYPE_EXCEPTION_EXCEPTION_HEADER BPVM_TYPE_EXCEPTION_HEADER " "
#else
		#define BPVM_TYPE_EXCEPTION_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			BPVM_TYPE_EXCEPTION_EXCEPTION_FORMAT_INVALID = 0,
		};

		#define BPVM_TYPE_EXCEPTION_EXCEPTION_MAX BPVM_TYPE_EXCEPTION_EXCEPTION_FORMAT_INVALID

		static const std::string BPVM_TYPE_EXCEPTION_EXCEPTION_STR[] = {
			BPVM_TYPE_EXCEPTION_EXCEPTION_HEADER "Invalid format",
			};

		#define BPVM_TYPE_EXCEPTION_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > BPVM_TYPE_EXCEPTION_EXCEPTION_MAX) ? STRING_UNKNOWN : \
				STRING(BPVM_TYPE_EXCEPTION_EXCEPTION_STR[_TYPE_]))
	}
}

#endif // BPVM_TYPE_EXCEPTION_TYPE_H_
