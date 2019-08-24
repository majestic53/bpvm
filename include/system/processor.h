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

#ifndef BPVM_SYSTEM_PROCESSOR_H_
#define BPVM_SYSTEM_PROCESSOR_H_

#include "./memory.h"

namespace bpvm {

	namespace system {

		class processor :
				public bpvm::type::singleton<bpvm::system::processor> {

			public:

				~processor(void);

				void update(
					__in bpvm::system::memory &memory
					);

			protected:

				friend class bpvm::type::singleton<bpvm::system::processor>;

				processor(void);

				processor(
					__in const processor &other
					) = delete;

				processor &operator=(
					__in const processor &other
					) = delete;

				void on_initialize(
					__in const void *context
					) override;

				void on_uninitialize(void) override;
		};
	}
}

#endif // BPVM_SYSTEM_PROCESSOR_H_
