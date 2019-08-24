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
					loop();
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
				m_memory(bpvm::system::memory::instance()),
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

			void loop(void)
			{
				float frame_frequency, frame_rate;
				uint32_t begin = 0, current = 0, duration = std::milli::den;

				TRACE_ENTRY();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime loop entry");

				frame_frequency = FRAMES_PER_SECOND;
				frame_rate = (std::milli::den / frame_frequency);

				for(;;) {
					float frequency, rate;
					uint32_t end = SDL_GetTicks();

					rate = (end - begin);
					if(rate >= duration) {
						rate = (current - ((rate - duration) / frame_frequency));
						rate = ((rate > 0.f) ? rate : 0.f);

						TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Runtime framerate", "%.01f", rate);

#ifndef NDEBUG
						m_video.frame_rate(rate);
#endif // NDEBUG
						begin = end;
						current = 0;
					}

					if(!poll()) {
						TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime loop interrupted");
						break;
					}

					//m_processor.step(m_memory);
					m_video.step(m_memory);
					//m_audio.step(m_memory);

					frequency = (SDL_GetTicks() - end);
					if(frequency < frame_rate) {
						SDL_Delay(frame_rate - frequency);
					}

					++current;
				}

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime loop exit");

				TRACE_EXIT();
			}

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
				//m_audio.initialize();
				//m_input.initialize();
				//m_processor.initialize();
				m_video.initialize();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime initialized");

				TRACE_EXIT();
			}

			void on_uninitialize(void) override
			{
				TRACE_ENTRY();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime uninitializing");

				m_video.uninitialize();
				//m_processor.uninitialize();
				//m_input.uninitialize();
				//m_audio.uninitialize();
				m_memory.uninitialize();

				m_error.clear();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime uninitialized");

				SDL_Quit();

				TRACE_MESSAGE(LEVEL_INFORMATION, "SDL unloaded");

				TRACE_EXIT();
			}

			bool poll(void)
			{
				bool result = true;
				SDL_Event event = {};

				TRACE_ENTRY();

				while(SDL_PollEvent(&event)) {

					switch(event.type) {
						case SDL_KEYDOWN:
						case SDL_KEYUP:

							if(!event.key.repeat) {
								//m_input.change(event.key.keysym.scancode, event.key.state == SDL_PRESSED);
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

			std::string m_error;

			bpvm::system::memory &m_memory;

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
