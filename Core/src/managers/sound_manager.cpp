#include "sound_manager.hpp"

namespace evo {
namespace audio {

	gau_Manager* SoundManager::m_Manager = nullptr;
	ga_Mixer* SoundManager::m_Mixer = nullptr;

	void SoundManager::init() {
		gc_initialize(0);
		m_Manager = gau_manager_create();
		m_Mixer = gau_manager_mixer(m_Manager);
	}

	void SoundManager::clean() {
		Manager::clean();
		gau_manager_destroy(m_Manager);
		gc_shutdown();
	}

	void SoundManager::update() {
		gau_manager_update(m_Manager);
	}

} }
