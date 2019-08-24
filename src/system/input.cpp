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

#include "../../include/system/input.h"
#include "../../include/type/trace.h"
#include "./input_type.h"

namespace bpvm {

	namespace system {

		input::input(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		};

		input::~input(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		};

		void
		input::change(
			__in bpvm::system::memory &memory,
			__in SDL_Scancode scancode,
			__in bool state
			)
		{
			std::map<SDL_Scancode, int>::iterator entry;

			TRACE_ENTRY_FORMAT("Memory=%p, Scancode=%u(%x), State=%s", &memory, scancode, scancode, state ? "Pressed" : "Released");

			entry = m_input.find(scancode);
			if(entry != m_input.end()) {
				input_t *input = (input_t *)&memory[INPUT_ADDRESS];

				if(state) {
					input->raw |= (1 << entry->second);
				} else {
					input->raw &= ~(1 << entry->second);
				}
			}

			TRACE_EXIT();
		};

		void
		input::on_initialize(
			__in const void *context
			)
		{
			int type = 0;
			input_t input = {};
			size_t address = INPUT_ADDRESS;
			const bpvm::system::memory *memory;

			TRACE_ENTRY();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Input initializing");

			memory = (const bpvm::system::memory *)context;
			if(!memory) {
				THROW_BPVM_SYSTEM_INPUT_EXCEPTION_FORMAT(BPVM_SYSTEM_INPUT_EXCEPTION_CONTEXT_INVALID, "%p", memory);
			}

			input.part[INPUT_PART_LOW] = memory->at(address++);
			input.part[INPUT_PART_HIGH] = memory->at(address);

			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Input state", "%u(%04x)", input.raw, input.raw);

			for(; type <= INPUT_MAX; ++type) {
				m_input.insert(std::make_pair(INPUT_SCANCODE(type), type));
			}

			TRACE_MESSAGE(LEVEL_INFORMATION, "Input initialized");

			TRACE_EXIT();
		};

		void
		input::on_uninitialize(void)
		{
			TRACE_ENTRY();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Input uninitializing");

			m_input.clear();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Input uninitialized");

			TRACE_EXIT();
		};
	}
}
