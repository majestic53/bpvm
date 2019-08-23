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

#ifndef BPVM_SYSTEM_MEMORY_H_
#define BPVM_SYSTEM_MEMORY_H_

#include "../type/buffer.h"
#include "../type/singleton.h"

namespace bpvm {

	namespace system {

		class memory :
				public bpvm::type::singleton<bpvm::system::memory>,
				public bpvm::type::buffer {

			public:

				~memory(void);

			protected:

				friend class bpvm::type::singleton<bpvm::system::memory>;

				memory(void);

				memory(
					__in const memory &other
					) = delete;

				memory &operator=(
					__in const memory &other
					) = delete;

				void on_initialize(
					__in const void *context
					) override;

				void on_uninitialize(void) override;
		};
	}
}

#endif // BPVM_SYSTEM_MEMORY_H_
