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

#ifndef BPVM_SYSTEM_AUDIO_TYPE_H_
#define BPVM_SYSTEM_AUDIO_TYPE_H_

#include "../../include/type/exception.h"

namespace bpvm {

	namespace system {

		#define BPVM_SYSTEM_AUDIO_HEADER "[BPVM::SYSTEM::AUDIO]"
#ifndef NDEBUG
		#define BPVM_SYSTEM_AUDIO_EXCEPTION_HEADER BPVM_SYSTEM_AUDIO_HEADER " "
#else
		#define BPVM_SYSTEM_AUDIO_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			BPVM_SYSTEM_AUDIO_EXCEPTION_CONTEXT_INVALID = 0,
			BPVM_SYSTEM_AUDIO_EXCEPTION_EXTERNAL,
		};

		#define BPVM_SYSTEM_AUDIO_EXCEPTION_MAX BPVM_SYSTEM_AUDIO_EXCEPTION_EXTERNAL

		static const std::string BPVM_SYSTEM_AUDIO_EXCEPTION_STR[] = {
			BPVM_SYSTEM_AUDIO_EXCEPTION_HEADER "Invalid context",
			BPVM_SYSTEM_AUDIO_EXCEPTION_HEADER "External exception",
			};

		#define BPVM_SYSTEM_AUDIO_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > BPVM_SYSTEM_AUDIO_EXCEPTION_MAX) ? STRING_UNKNOWN : \
				STRING(BPVM_SYSTEM_AUDIO_EXCEPTION_STR[_TYPE_]))

		#define THROW_BPVM_SYSTEM_AUDIO_EXCEPTION(_EXCEPT_) \
			THROW_BPVM_SYSTEM_AUDIO_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_BPVM_SYSTEM_AUDIO_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION(BPVM_SYSTEM_AUDIO_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		#define AUDIO_ADDRESS 0x00000006

		#define AUDIO_CHANNELS 1
		#define AUDIO_DIRECTION 0
		#define AUDIO_FREQUENCY 15360
		#define AUDIO_FORMAT AUDIO_U8
		#define AUDIO_PAUSE 1
		#define AUDIO_PLAY 0
		#define AUDIO_SAMPLES 256

		#define SDL_AUDIO_FLAGS 0
	}
}

#endif // BPVM_SYSTEM_AUDIO_TYPE_H_
