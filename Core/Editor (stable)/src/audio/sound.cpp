#include "sound.hpp"
#include "../managers/sound_manager.hpp"

namespace evo {
namespace audio {

    void loop_on_finish(ga_Handle* in_handle, void* in_context);
    void destroy_on_finish(ga_Handle* in_handle, void* in_context);

	Sound::Sound(const char* name, const std::string& relativeFilepath)
		: StaticManager(name), m_Filename(relativeFilepath), m_Playing(false) {
		std::vector<std::string> split = split_string(m_Filename, '.');

        if (split.size() < 2) {
			std::cerr << "[Sound] Invalid file name '" << m_Filename << "'!" << std::endl;
			return;
		}

        std::string filename = filepath::makeAbsolute(relativeFilepath);
		m_Sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

		if (m_Sound == nullptr)
			std::cerr << "[Sound] Could not load file '" << m_Filename << "'!" << std::endl;
	}

	Sound::~Sound() {
		ga_sound_release(m_Sound);
	}

	void Sound::play() {
        if(m_Playing)
            return;

		gc_int32 quit = 0;
		m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &destroy_on_finish, &quit, NULL);
		m_Handle->sound = this;
		ga_handle_play(m_Handle);
		m_Playing = true;
	}

	void Sound::loop() { //TODO: fix this
		gc_int32 quit = 0;
		m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &loop_on_finish, &quit, NULL);
		m_Handle->sound = this;
		ga_handle_play(m_Handle);
		m_Playing = true;
	}

	void Sound::resume() {
		gc_int32 quit = 0;
		ga_handle_play(m_Handle);
	}

	void Sound::pause() {
		m_Playing = false;
		ga_handle_stop(m_Handle);
	}

	void Sound::stop() {
		if (!m_Playing)
			return;

		ga_handle_stop(m_Handle);
		m_Playing = false;
	}

	void Sound::setGain(float gain) {
		if (!m_Playing)
		{
			std::cerr << "[Sound] Cannot set gain! Sound is not currently playing!" << std::endl;
			return;
		}
		m_Gain = gain;
		ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, gain);
	}

	void destroy_on_finish(ga_Handle* in_handle, void* in_context) {
		Sound* sound = (Sound*)in_handle->sound;
		sound->stop();
	}

	void loop_on_finish(ga_Handle* in_handle, void* in_context) {
		Sound* sound = (Sound*) in_handle->sound;
		sound->loop();
		ga_handle_destroy(in_handle);
	}
} }
