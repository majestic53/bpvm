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

#include "../../include/system/video.h"
#include "../../include/type/trace.h"
#include "./video_type.h"

namespace bpvm {

	namespace system {

		video::video(void) :
			m_renderer(nullptr),
			m_texture(nullptr),
			m_window(nullptr)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		video::~video(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

#ifndef NDEBUG
		void
		video::frame_rate(
			__in float frame_rate
			)
		{
			std::stringstream result;

			TRACE_ENTRY_FORMAT("Frame-Rate=%.01f", frame_rate);

			result << m_title << " [" << STRING_FLOAT(frame_rate) << " fps]";
			SDL_SetWindowTitle(m_window, STRING(result.str()));

			TRACE_EXIT();
		}
#endif // NDEBUG

		void
		video::on_initialize(
			__in const void *context
			)
		{
			size_t index = 0;
			std::vector<color_t>::iterator color;

			TRACE_ENTRY_FORMAT("Context=%p", context);

			TRACE_MESSAGE(LEVEL_INFORMATION, "Video initializing");

			m_color.resize(UINT8_MAX + 1, COLOR_BACKGROUND);

			for(color = m_color.begin(); color != m_color.end(); ++color) {

				if(index <= COLOR_MAX) {
					uint8_t type = index++;

					color->blue = (type % COLOR_WIDTH);
					type -= color->blue;
					color->blue *= COLOR_SCALE;

					color->green = ((type / COLOR_WIDTH) % COLOR_WIDTH);
					type -= (color->green * COLOR_WIDTH);
					color->green *= COLOR_SCALE;

					color->red = ((type / (COLOR_WIDTH * COLOR_WIDTH)) % COLOR_WIDTH);
					color->red *= COLOR_SCALE;
				}
			}

			m_pixel.resize(DISPLAY_WIDTH * DISPLAY_WIDTH, COLOR_BACKGROUND);
			m_title = DISPLAY_TITLE;

			m_window = SDL_CreateWindow(STRING(m_title), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					DISPLAY_WIDTH * DISPLAY_SCALE, DISPLAY_WIDTH * DISPLAY_SCALE, SDL_WINDOW_FLAGS);

			if(!m_window) {
				THROW_BPVM_SYSTEM_VIDEO_EXCEPTION_FORMAT(BPVM_SYSTEM_VIDEO_EXCEPTION_EXTERNAL,
					"SDL_CreateWindow failed! %s", SDL_GetError());
			}

			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_FLAGS);
			if(!m_renderer) {
				THROW_BPVM_SYSTEM_VIDEO_EXCEPTION_FORMAT(BPVM_SYSTEM_VIDEO_EXCEPTION_EXTERNAL,
					"SDL_CreateRenderer failed! %s", SDL_GetError());
			}

			if(SDL_RenderSetLogicalSize(m_renderer, DISPLAY_WIDTH, DISPLAY_WIDTH)) {
				THROW_BPVM_SYSTEM_VIDEO_EXCEPTION_FORMAT(BPVM_SYSTEM_VIDEO_EXCEPTION_EXTERNAL,
					"SDL_RenderSetLogicalSize failed! %s", SDL_GetError());
			}

			if(SDL_SetRenderDrawColor(m_renderer, COLOR_BACKGROUND.red, COLOR_BACKGROUND.green, COLOR_BACKGROUND.blue,
					COLOR_BACKGROUND.alpha)) {
				THROW_BPVM_SYSTEM_VIDEO_EXCEPTION_FORMAT(BPVM_SYSTEM_VIDEO_EXCEPTION_EXTERNAL,
					"SDL_SetRenderDrawColor failed! %s", SDL_GetError());
			}

			if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, SDL_RENDERER_QUALITY) == SDL_FALSE) {
				THROW_BPVM_SYSTEM_VIDEO_EXCEPTION_FORMAT(BPVM_SYSTEM_VIDEO_EXCEPTION_EXTERNAL,
					"SDL_SetHint failed! %s", SDL_GetError());
			}

			m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
					DISPLAY_WIDTH, DISPLAY_WIDTH);

			if(!m_texture) {
				THROW_BPVM_SYSTEM_VIDEO_EXCEPTION_FORMAT(BPVM_SYSTEM_VIDEO_EXCEPTION_EXTERNAL,
					"SDL_CreateTexture failed! %s", SDL_GetError());
			}

			if(SDL_RenderClear(m_renderer)) {
				THROW_BPVM_SYSTEM_VIDEO_EXCEPTION_FORMAT(BPVM_SYSTEM_VIDEO_EXCEPTION_EXTERNAL,
					"SDL_RenderClear failed! %s", SDL_GetError());
			}

			SDL_RenderPresent(m_renderer);

			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Video dimensions", "%ux%ux%u", DISPLAY_WIDTH, DISPLAY_WIDTH, DISPLAY_SCALE);
			TRACE_MESSAGE(LEVEL_INFORMATION, "Video initialized");

			TRACE_EXIT();
		}

		void
		video::on_uninitialize(void)
		{
			TRACE_ENTRY();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Video uninitializing");

			if(m_texture) {
				SDL_DestroyTexture(m_texture);
				m_texture = nullptr;
			}

			if(m_renderer) {
				SDL_DestroyRenderer(m_renderer);
				m_renderer = nullptr;
			}

			if(m_window) {
				SDL_DestroyWindow(m_window);
				m_window = nullptr;
			}

			m_title.clear();
			m_pixel.clear();
			m_color.clear();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Video uninitialized");

			TRACE_EXIT();
		}

		void
		video::step(
			__in const bpvm::system::memory &memory
			)
		{
			address_t address = {};
			uint32_t index = 0, x, y = 0;

			TRACE_ENTRY_FORMAT("Memory=%p", &memory);

			address.part[ADDRESS_PART_16] = memory.at(PIXEL_ADDRESS);

			for(; y < DISPLAY_WIDTH; ++y) {
				address.part[ADDRESS_PART_8] = y;

				for(x = 0; x < DISPLAY_WIDTH; ++x) {
					address.part[ADDRESS_PART_0] = x;
					m_pixel.at(index++) = m_color.at(memory.at(address.raw));
				}
			}

			if(SDL_UpdateTexture(m_texture, nullptr, &m_pixel[0], DISPLAY_WIDTH * sizeof(color_t))) {
				THROW_BPVM_SYSTEM_VIDEO_EXCEPTION_FORMAT(BPVM_SYSTEM_VIDEO_EXCEPTION_EXTERNAL,
					"SDL_UpdateTexture failed! %s", SDL_GetError());
			}

			if(SDL_RenderClear(m_renderer)) {
				THROW_BPVM_SYSTEM_VIDEO_EXCEPTION_FORMAT(BPVM_SYSTEM_VIDEO_EXCEPTION_EXTERNAL,
					"SDL_RenderClear failed! %s", SDL_GetError());
			}

			if(SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr)) {
				THROW_BPVM_SYSTEM_VIDEO_EXCEPTION_FORMAT(BPVM_SYSTEM_VIDEO_EXCEPTION_EXTERNAL,
					"SDL_RenderCopy failed! %s", SDL_GetError());
			}

			SDL_RenderPresent(m_renderer);

			TRACE_EXIT();
		}
	}
}
