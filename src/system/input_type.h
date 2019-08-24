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

#ifndef BPVM_SYSTEM_INPUT_TYPE_H_
#define BPVM_SYSTEM_INPUT_TYPE_H_

#include "../../include/type/exception.h"

namespace bpvm {

	namespace system {

		#define BPVM_SYSTEM_INPUT_HEADER "[BPVM::SYSTEM::INPUT]"
#ifndef NDEBUG
		#define BPVM_SYSTEM_INPUT_EXCEPTION_HEADER BPVM_SYSTEM_INPUT_HEADER " "
#else
		#define BPVM_SYSTEM_INPUT_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			BPVM_SYSTEM_INPUT_EXCEPTION_CONTEXT_INVALID = 0,
		};

		#define BPVM_SYSTEM_INPUT_EXCEPTION_MAX BPVM_SYSTEM_INPUT_EXCEPTION_CONTEXT_INVALID

		static const std::string BPVM_SYSTEM_INPUT_EXCEPTION_STR[] = {
			BPVM_SYSTEM_INPUT_EXCEPTION_HEADER "Invalid context",
			};

		#define BPVM_SYSTEM_INPUT_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > BPVM_SYSTEM_INPUT_EXCEPTION_MAX) ? STRING_UNKNOWN : \
				STRING(BPVM_SYSTEM_INPUT_EXCEPTION_STR[_TYPE_]))

		#define THROW_BPVM_SYSTEM_INPUT_EXCEPTION(_EXCEPT_) \
			THROW_BPVM_SYSTEM_INPUT_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_BPVM_SYSTEM_INPUT_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION(BPVM_SYSTEM_INPUT_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		#define INPUT_ADDRESS 0x00000000

		static const SDL_Scancode INPUT_CODE[] = {
			SDL_SCANCODE_S, // INPUT_8
			SDL_SCANCODE_D, // INPUT_9
			SDL_SCANCODE_Z, // INPUT_A
			SDL_SCANCODE_C, // INPUT_B
			SDL_SCANCODE_4, // INPUT_C
			SDL_SCANCODE_R, // INPUT_D
			SDL_SCANCODE_F, // INPUT_E
			SDL_SCANCODE_V, // INPUT_F
			SDL_SCANCODE_X, // INPUT_0
			SDL_SCANCODE_1, // INPUT_1
			SDL_SCANCODE_2, // INPUT_2
			SDL_SCANCODE_3, // INPUT_3
			SDL_SCANCODE_Q, // INPUT_4
			SDL_SCANCODE_W, // INPUT_5
			SDL_SCANCODE_E, // INPUT_6
			SDL_SCANCODE_A, // INPUT_7
			};

		#define INPUT_SCANCODE(_TYPE_) \
			(((_TYPE_) > INPUT_MAX) ? SDL_SCANCODE_UNKNOWN : \
				INPUT_CODE[_TYPE_])
	}
}

#endif // BPVM_SYSTEM_INPUT_TYPE_H_
