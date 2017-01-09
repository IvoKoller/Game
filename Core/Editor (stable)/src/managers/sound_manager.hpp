#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#define GAU_THREAD_POLICY_MULTI 2
#include "../../ext/gorilla-audio/ga.h"
#include "../../ext/gorilla-audio/gau.h"

#include "../utils/debug.hpp"
#include "../audio/sound.hpp"
#include "dynamicManager.hpp"

namespace evo {
namespace audio {

	class SoundManager : public DynamicManager<Sound> {
		friend class Sound;

		static gau_Manager* m_Manager;
		static ga_Mixer* m_Mixer;
	public:
		static void init();
		static void update();
		static void clear();
		//SoundManager() { }
	};

} }

#endif /* end of include guard: SOUND_MANAGER_HPP */
