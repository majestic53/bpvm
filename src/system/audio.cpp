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

#include "../../include/system/audio.h"
#include "../../include/type/trace.h"
#include "./audio_type.h"

namespace bpvm {

	namespace system {

		audio::audio(void) :
			m_device(0),
			m_specification({})
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		audio::~audio(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		void
		audio::create_device(void)
		{
			SDL_AudioSpec specification = {};

			TRACE_ENTRY();

			specification.freq = AUDIO_FREQUENCY;
			specification.format = AUDIO_FORMAT;
			specification.channels = AUDIO_CHANNELS;
			specification.samples = AUDIO_SAMPLES;

			m_device = SDL_OpenAudioDevice(nullptr, AUDIO_DIRECTION, &specification, &m_specification, SDL_AUDIO_FLAGS);
			if(!m_device) {
				THROW_BPVM_SYSTEM_AUDIO_EXCEPTION_FORMAT(BPVM_SYSTEM_AUDIO_EXCEPTION_EXTERNAL,
					"SDL_OpenAudioDevice failed! %s", SDL_GetError());
			}

			SDL_PauseAudioDevice(m_device, AUDIO_PLAY);

			TRACE_EXIT();
		}

		void
		audio::destroy_device(void)
		{
			TRACE_ENTRY();

			if(m_device) {
				SDL_PauseAudioDevice(m_device, AUDIO_PAUSE);
				SDL_CloseAudioDevice(m_device);
				m_device = 0;
			}

			m_specification = {};

			TRACE_EXIT();
		}

		void
		audio::on_initialize(
			__in const void *context
			)
		{
			address_t base = {};
			uint32_t address = AUDIO_ADDRESS;
			const bpvm::system::memory *memory;

			TRACE_ENTRY_FORMAT("Context=%p", context);

			TRACE_MESSAGE(LEVEL_INFORMATION, "Audio initializing");

			memory = (const bpvm::system::memory *)context;
			if(!memory) {
				THROW_BPVM_SYSTEM_AUDIO_EXCEPTION_FORMAT(BPVM_SYSTEM_AUDIO_EXCEPTION_CONTEXT_INVALID, "%p", memory);
			}

			base.part[ADDRESS_PART_16] = memory->at(address++);
			base.part[ADDRESS_PART_8] = memory->at(address);

			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Audio address", "%u(%02x%02xZZ)", base.raw, base.part[ADDRESS_PART_16],
				base.part[ADDRESS_PART_8]);

			create_device();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Audio initialized");

			TRACE_EXIT();
		}

		void
		audio::on_uninitialize(void)
		{
			TRACE_ENTRY();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Audio uninitializing");

			destroy_device();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Audio uninitialized");

			TRACE_EXIT();
		}

		void
		audio::render(
			__in const bpvm::system::memory &memory
			)
		{
			address_t base = {};
			uint32_t address = AUDIO_ADDRESS;

			TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			base.part[ADDRESS_PART_16] = memory.at(address++);
			base.part[ADDRESS_PART_8] = memory.at(address);

			if(SDL_QueueAudio(m_device, &memory[base.raw], AUDIO_SAMPLES)) {
				THROW_BPVM_SYSTEM_AUDIO_EXCEPTION_FORMAT(BPVM_SYSTEM_AUDIO_EXCEPTION_EXTERNAL,
					"SDL_QueueAudio failed! %s", SDL_GetError());
			}

			TRACE_EXIT();
		}
	}
}
