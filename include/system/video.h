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

#ifndef BPVM_SYSTEM_VIDEO_H_
#define BPVM_SYSTEM_VIDEO_H_

#include "./memory.h"

namespace bpvm {

	namespace system {

		class video :
				public bpvm::type::singleton<bpvm::system::video> {

			public:

				~video(void);

#ifndef NDEBUG
				void frame_rate(
					__in float frame_rate
					);
#endif // NDEBUG

				void step(
					__in const bpvm::system::memory &memory
					);

			protected:

				friend class bpvm::type::singleton<bpvm::system::video>;

				video(void);

				video(
					__in const video &other
					) = delete;

				video &operator=(
					__in const video &other
					) = delete;

				void on_initialize(
					__in const void *context
					) override;

				void on_uninitialize(void) override;

				std::vector<color_t> m_color;

				std::vector<color_t> m_pixel;

				SDL_Renderer *m_renderer;

				SDL_Texture *m_texture;

				std::string m_title;

				SDL_Window *m_window;
		};
	}
}

#endif // BPVM_SYSTEM_VIDEO_H_
