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

#include "../../include/system/memory.h"
#include "../../include/type/trace.h"
#include "../../include/bpvm.h"
#include "./memory_type.h"

namespace bpvm {

	namespace system {

		memory::memory(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		memory::~memory(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		void
		memory::on_initialize(
			__in const void *context
			)
		{
			const bpvm_t *configuration;

			TRACE_ENTRY_FORMAT("Context=%p", context);

			TRACE_MESSAGE(LEVEL_INFORMATION, "Memory initializing");

			configuration = (const bpvm_t *)context;
			if(!configuration || !configuration->path) {
				THROW_BPVM_SYSTEM_MEMORY_EXCEPTION_FORMAT(BPVM_SYSTEM_MEMORY_EXCEPTION_CONTEXT_INVALID, "%p", configuration);
			}

			bpvm::type::buffer::load(configuration->path);

			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "File path", "%s", configuration->path);
			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "File size", "%.01f KB (%u bytes)",
				bpvm::type::buffer::size() / (float)std::kilo::num, bpvm::type::buffer::size());

			bpvm::type::buffer::resize(MEMORY_LENGTH, MEMORY_FILL);

			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Memory size", "%.01f KB (%u bytes)",
				bpvm::type::buffer::size() / (float)std::kilo::num, bpvm::type::buffer::size());

			TRACE_MESSAGE(LEVEL_INFORMATION, "Memory initialized");

			TRACE_EXIT();
		}

		void
		memory::on_uninitialize(void)
		{
			TRACE_ENTRY();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Memory uninitializing");

			bpvm::type::buffer::clear();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Memory uninitialized");

			TRACE_EXIT();
		}
	}
}
