#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "manager.hpp"

#define GAU_THREAD_POLICY_MULTI 2
#include "../../ext/gorilla-audio/ga.h"
#include "../../ext/gorilla-audio/gau.h"

namespace evo {
namespace audio {

	class SoundManager : public Manager<Sound> {
		friend class Sound;

		static gau_Manager* m_Manager;
		static ga_Mixer* m_Mixer;

	public:
		static void init();
		static void update();
		static void clean();
	private:
		SoundManager() { }
	};

} }

#endif /* end of include guard: SOUND_MANAGER_H */
