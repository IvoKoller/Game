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

	void SoundManager::update() {
		gau_manager_update(m_Manager);
	}

	void SoundManager::clear() {
		for (int i = 0; i < m_Elements.size(); i++) delete m_Elements[i];

		gau_manager_destroy(m_Manager);
		gc_shutdown();
	}

} }
