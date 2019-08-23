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

#ifndef BPVM_TYPE_BUFFER_H_
#define BPVM_TYPE_BUFFER_H_

#include "../common.h"

namespace bpvm {

	namespace type {

		class buffer :
				public std::vector<uint8_t> {

			public:

				buffer(void);

				virtual ~buffer(void);

				void load(
					__in const std::string &path
					);

			protected:

				buffer(
					__in const buffer &other
					) = delete;

				buffer &operator=(
					__in const buffer &other
					) = delete;
		};
	}
}

#endif // BPVM_TYPE_BUFFER_H_
