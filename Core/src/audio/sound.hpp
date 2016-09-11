#ifndef SOUND_HPP
#define SOUND_HPP

#include <iostream>
#include <string>

#include "../utils/filepath.hpp"
#include "../../ext/gorilla-audio/ga.h"
#include "../../ext/gorilla-audio/gau.h"

#include "../managers/element.hpp"

namespace evo {
namespace audio {

	class Sound : public Element {
	private:
		std::string m_Filename;

		ga_Sound* m_Sound;
		ga_Handle* m_Handle;
		gc_int32 m_Position;

		bool m_Playing;
		float m_Gain;
	public:
		Sound(const std::string& name, const std::string& filename);
		~Sound();

		void play();
		void loop();
		void pause();
		void resume();
		void stop();

		void setGain(float gain);

		inline const bool isPlaying() const { return m_Playing; }
		inline const float getGain() const { return m_Gain; }
		inline const std::string& getFileName() const { return m_Filename; }

		friend void destroy_on_finish(ga_Handle* in_handle, void* in_context);
		friend void loop_on_finish(ga_Handle* in_handle, void* in_context);

	};

} }

#endif /* end of include guard: SOUND_HPP */
