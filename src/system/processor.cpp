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

#include "../../include/system/processor.h"
#include "../../include/type/trace.h"
#include "./processor_type.h"

namespace bpvm {

	namespace system {

		processor::processor(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		processor::~processor(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		void
		processor::on_initialize(
			__in const void *context
			)
		{
			address_t jump = {};
			size_t address = COUNTER_ADDRESS;
			const bpvm::system::memory *memory;

			TRACE_ENTRY_FORMAT("Context=%p", context);

			TRACE_MESSAGE(LEVEL_INFORMATION, "Processor initializing");

			memory = (const bpvm::system::memory *)context;
			if(!memory) {
				THROW_BPVM_SYSTEM_PROCESSOR_EXCEPTION_FORMAT(BPVM_SYSTEM_PROCESSOR_EXCEPTION_CONTEXT_INVALID, "%p", memory);
			}

			jump.part[ADDRESS_PART_16] = memory->at(address++);
			jump.part[ADDRESS_PART_8] = memory->at(address++);
			jump.part[ADDRESS_PART_0] = memory->at(address);

			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Processor address", "%u(%08x)", jump.raw, jump.raw);
			TRACE_MESSAGE(LEVEL_INFORMATION, "Processor initialized");

			TRACE_EXIT();
		}

		void
		processor::on_uninitialize(void)
		{
			TRACE_ENTRY();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Processor uninitializing");
			TRACE_MESSAGE(LEVEL_INFORMATION, "Processor uninitialized");

			TRACE_EXIT();
		}

		void
		processor::update(
			__in bpvm::system::memory &memory
			)
		{
			uint8_t *position;
			size_t address = COUNTER_ADDRESS, cycle = 0;
			address_t destination = {}, jump = {}, source = {};

			TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			jump.part[ADDRESS_PART_16] = memory.at(address++);
			jump.part[ADDRESS_PART_8] = memory.at(address++);
			jump.part[ADDRESS_PART_0] = memory.at(address);

			position = (uint8_t *)&memory[jump.raw];

			for(; cycle < CYCLES_PER_FRAME; ++cycle) {
				source.part[ADDRESS_PART_16] = position[ADDRESS_SOURCE_16];
				source.part[ADDRESS_PART_8] = position[ADDRESS_SOURCE_8];
				source.part[ADDRESS_PART_0] = position[ADDRESS_SOURCE_0];

				destination.part[ADDRESS_PART_16] = position[ADDRESS_DESTINATION_16];
				destination.part[ADDRESS_PART_8] = position[ADDRESS_DESTINATION_8];
				destination.part[ADDRESS_PART_0] = position[ADDRESS_DESTINATION_0];

				memory.at(destination.raw) = memory.at(source.raw);

				jump.part[ADDRESS_PART_16] = position[ADDRESS_JUMP_16];
				jump.part[ADDRESS_PART_8] = position[ADDRESS_JUMP_8];
				jump.part[ADDRESS_PART_0] = position[ADDRESS_JUMP_0];

				position = (uint8_t *)&memory[jump.raw];
			}

			TRACE_EXIT();
		}
	}
}
