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

#ifndef BPVM_TYPE_H_
#define BPVM_TYPE_H_

#include "../include/type/exception.h"

namespace bpvm {

	#define BPVM_HEADER "[BPVM]"
#ifndef NDEBUG
	#define BPVM_EXCEPTION_HEADER BPVM_HEADER " "
#else
	#define BPVM_EXCEPTION_HEADER
#endif // NDEBUG

	enum {
		BPVM_EXCEPTION_CONTEXT_INVALID = 0,
		BPVM_EXCEPTION_EXTERNAL,
	};

	#define BPVM_EXCEPTION_MAX BPVM_EXCEPTION_EXTERNAL

	static const std::string BPVM_EXCEPTION_STR[] = {
		BPVM_EXCEPTION_HEADER "Invalid context",
		BPVM_EXCEPTION_HEADER "External exception",
		};

	#define BPVM_EXCEPTION_STRING(_TYPE_) \
		(((_TYPE_) > BPVM_EXCEPTION_MAX) ? STRING_UNKNOWN : \
			STRING(BPVM_EXCEPTION_STR[_TYPE_]))

	#define THROW_BPVM_EXCEPTION(_EXCEPT_) \
		THROW_BPVM_EXCEPTION_FORMAT(_EXCEPT_, "", "")
	#define THROW_BPVM_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
		THROW_EXCEPTION(BPVM_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

	#define FRAME_RATE (MILLISECONDS_PER_SECOND / FRAMES_PER_SECOND)

	#define FRAMES_PER_SECOND 60.f

	#define MILLISECONDS_PER_SECOND std::milli::den

	#define SDL_FLAGS (SDL_INIT_AUDIO | SDL_INIT_VIDEO)
}

#endif // BPVM_TYPE_H_
