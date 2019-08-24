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

#include "../include/system/input.h"
#include "../include/system/processor.h"
#include "../include/system/video.h"
#include "../include/bpvm.h"
#include "./bpvm_type.h"

namespace bpvm {

	class runtime :
			public bpvm::type::singleton<bpvm::runtime> {

		public:

			~runtime(void)
			{
				TRACE_ENTRY();

				TRACE_MESSAGE(LEVEL_INFORMATION, BPVM " unloaded");

				TRACE_EXIT();
			}

			const char *error(void) const
			{
				const char *result;

				TRACE_ENTRY();

				result = STRING(m_error);

				TRACE_EXIT_FORMAT("Result=%p", result);
				return result;
			}

			int run(
				__in const bpvm_t *configuration
				)
			{
				int result = EXIT_SUCCESS;

				TRACE_ENTRY_FORMAT("Configuration=%p", configuration);

				try {
					initialize(configuration);
					run_loop();
				} catch(bpvm::type::exception &exc) {
					m_error = exc.to_string();
					result = EXIT_FAILURE;
				} catch(std::exception &exc) {
					m_error = exc.what();
					result = EXIT_FAILURE;
				}

				uninitialize();

				TRACE_EXIT_FORMAT("Result=%i(%x)", result, result);
				return result;
			}

		protected:

			friend class bpvm::type::singleton<bpvm::runtime>;

			runtime(void) :
				m_input(bpvm::system::input::instance()),
				m_memory(bpvm::system::memory::instance()),
				m_processor(bpvm::system::processor::instance()),
				m_video(bpvm::system::video::instance())
			{
				TRACE_ENTRY();

				TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, BPVM " loaded", "%s", VERSION_STRING());

				TRACE_EXIT();
			}

			runtime(
				__in const runtime &other
				) = delete;

			runtime &operator=(
				__in const runtime &other
				) = delete;

			void on_initialize(
				__in const void *context
				) override
			{
				SDL_version version = {};

				TRACE_ENTRY_FORMAT("Context=%p", context);

				if(SDL_Init(SDL_FLAGS)) {
					THROW_BPVM_EXCEPTION_FORMAT(BPVM_EXCEPTION_EXTERNAL, "SDL_Init failed! %s", SDL_GetError());
				}

				SDL_GetVersion(&version);
				TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "SDL loaded", "%u.%u.%u", version.major, version.minor, version.patch);

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime initializing");

				if(!context) {
					THROW_BPVM_EXCEPTION_FORMAT(BPVM_EXCEPTION_CONTEXT_INVALID, "%p", context);
				}

				TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Runtime context", "%p", context);

				m_memory.initialize(context);
				//m_audio.initialize(&m_memory);
				m_input.initialize(&m_memory);
				m_processor.initialize(&m_memory);
				m_video.initialize(&m_memory);

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime initialized");

				TRACE_EXIT();
			}

			void on_uninitialize(void) override
			{
				TRACE_ENTRY();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime uninitializing");

				m_video.uninitialize();
				m_processor.uninitialize();
				m_input.uninitialize();
				//m_audio.uninitialize();
				m_memory.uninitialize();

				m_error.clear();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime uninitialized");

				SDL_Quit();

				TRACE_MESSAGE(LEVEL_INFORMATION, "SDL unloaded");

				TRACE_EXIT();
			}

			bool poll_events(void)
			{
				bool result = true;
				SDL_Event event = {};

				TRACE_ENTRY();

				while(SDL_PollEvent(&event)) {

					switch(event.type) {
						case SDL_KEYDOWN:
						case SDL_KEYUP:

							if(!event.key.repeat) {
								m_input.change(m_memory, event.key.keysym.scancode,
									event.key.state == SDL_PRESSED);
							}
							break;
						case SDL_QUIT:
							result = false;
						default:
							break;
					}

					if(!result) {
						break;
					}
				}

				TRACE_EXIT_FORMAT("Result=%x", result);
				return result;
			}

			void run_loop(void)
			{
				uint32_t begin = 0, current = 0;

				TRACE_ENTRY();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime loop entry");

				for(;;) {
					float frequency, rate;
					uint32_t end = SDL_GetTicks();

					rate = (end - begin);
					if(rate >= MILLISECONDS_PER_SECOND) {
						rate = (current - ((rate - MILLISECONDS_PER_SECOND) / FRAMES_PER_SECOND));
						rate = ((rate > 0.f) ? rate : 0.f);

						TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Runtime framerate", "%.01f", rate);

#ifndef NDEBUG
						m_video.set_frame_rate(rate);
#endif // NDEBUG
						begin = end;
						current = 0;
					}

					if(!poll_events()) {
						TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime loop interrupted");
						break;
					}

					m_processor.update(m_memory);
					m_video.render(m_memory);
					//m_audio.render(m_memory);

					frequency = (SDL_GetTicks() - end);
					if(frequency < FRAME_RATE) {
						SDL_Delay(FRAME_RATE - frequency);
					}

					++current;
				}

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime loop exit");

				TRACE_EXIT();
			}

			std::string m_error;

			bpvm::system::input &m_input;

			bpvm::system::memory &m_memory;

			bpvm::system::processor &m_processor;

			bpvm::system::video &m_video;
	};
}

const char *
bpvm_err(void)
{
	const char *result;

	TRACE_ENTRY();

	result = bpvm::runtime::instance().error();

	TRACE_EXIT_FORMAT("Result=%p", result);
	return result;
}

int
bpvm_run(
	__in const bpvm_t *config
	)
{
	int result;

	TRACE_ENTRY_FORMAT("Configuration=%p", config);

	result = bpvm::runtime::instance().run(config);

	TRACE_EXIT_FORMAT("Result=%i(%x)", result, result);
	return result;
}

const char *
bpvm_ver(void)
{
	const char *result;

	TRACE_ENTRY();

	result = VERSION_STRING();

	TRACE_EXIT_FORMAT("Result=%p", result);
	return result;
}
