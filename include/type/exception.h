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

#ifndef BPVM_TYPE_EXCEPTION_H_
#define BPVM_TYPE_EXCEPTION_H_

#include "../common.h"

namespace bpvm {

	namespace type {

		class exception :
				public std::runtime_error {

			public:

				exception(
					__in const std::string &message,
					__in const std::string &file,
					__in const std::string &function,
					__in size_t line
					);

				virtual ~exception(void);

				static void generate(
					__in const std::string &message,
					__in const std::string &file,
					__in const std::string &function,
					__in size_t line,
					__in const char *format,
					...
					);

				virtual std::string to_string(void) const;

			protected:

				exception(
					__in const exception &other
					) = delete;

				exception &operator=(
					__in const exception &other
					) = delete;

				std::string m_file;

				std::string m_function;

				size_t m_line;
		};
	}
}

#endif // BPVM_TYPE_EXCEPTION_H_
