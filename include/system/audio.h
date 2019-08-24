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

#ifndef BPVM_SYSTEM_AUDIO_H_
#define BPVM_SYSTEM_AUDIO_H_

#include "./memory.h"

namespace bpvm {

	namespace system {

		class audio :
				public bpvm::type::singleton<bpvm::system::audio> {

			public:

				~audio(void);

				void render(
					__in const bpvm::system::memory &memory
					);

			protected:

				friend class bpvm::type::singleton<bpvm::system::audio>;

				audio(void);

				audio(
					__in const audio &other
					) = delete;

				audio &operator=(
					__in const audio &other
					) = delete;

				void create_device(void);

				void destroy_device(void);

				void on_initialize(
					__in const void *context
					) override;

				void on_uninitialize(void) override;

				SDL_AudioDeviceID m_device;

				SDL_AudioSpec m_specification;
		};
	}
}

#endif // BPVM_SYSTEM_AUDIO_H_
