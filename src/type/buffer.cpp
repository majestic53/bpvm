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

#include "../../include/type/buffer.h"
#include "../../include/type/trace.h"
#include "./buffer_type.h"

namespace bpvm {

	namespace type {

		buffer::buffer(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		buffer::~buffer(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		void
		buffer::load(
			__in const std::string &path
			)
		{
			int length;
			std::ifstream file;

			TRACE_ENTRY_FORMAT("Path[%u]=%s", path.size(), STRING(path));

			file = std::ifstream(STRING(path), std::ios::binary | std::ios::in);
			if(!file) {
				THROW_BPVM_TYPE_BUFFER_EXCEPTION_FORMAT(BPVM_TYPE_BUFFER_EXCEPTION_FILE_NOT_FOUND, "%s", STRING(path));
			}

			file.seekg(0, std::ios::end);
			length = file.tellg();
			file.seekg(0, std::ios::beg);

			if(length > 0) {
				std::vector<uint8_t>::resize(length);
				file.read((char *)&((*this)[0]), std::vector<uint8_t>::size());
			} else {
				std::vector<uint8_t>::clear();
			}

			file.close();

			if(length < 0) {
				THROW_BPVM_TYPE_BUFFER_EXCEPTION_FORMAT(BPVM_TYPE_BUFFER_EXCEPTION_FILE_INVALID, "%s", STRING(path));
			}

			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "File path", "%s", STRING(path));
			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "File size", "%.01f KB (%u bytes)",
				std::vector<uint8_t>::size() / (float)std::kilo::num, std::vector<uint8_t>::size());

			TRACE_EXIT();
		}
	}
}
