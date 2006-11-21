#include <SDL/SDL_mixer.h>
#include <string>

namespace System{
namespace Audio {




bool Initialize();
void Close();
bool LoadSound(std::string name, std::string filename);
bool LoadMusic(std::string name, std::string filename);
bool Play(std::string name, bool looping = false);
void Stop();
int Volume(std::string name, int volume);
int Volume(std::string name);
int VolumeChange(std::string name, int volume);


class AudioItem {
public:
	AudioItem() : m_type(0) { }
	virtual void Close() = 0;
	virtual ~AudioItem() { }
	virtual void Play(bool looping) = 0;
	virtual void Stop() = 0;
	virtual bool Load(std::string) = 0;
	virtual bool IsPlaying(){ return false; }
	virtual int Volume() = 0;
	virtual int Volume(int volume) = 0;
	virtual int VolumeChange(int volume) = 0;

	int Type(){ return m_type; }
protected:
	int m_type;
};


class MusicItem : public AudioItem {
public:
	MusicItem() : m_fade(0), handle(NULL) { }
	bool Load(std::string filename){
		handle = Mix_LoadMUS(filename.c_str());
		this->m_type = 2;
		return handle != NULL;
	}
	void Close(){
		Stop();
		if(handle){
			Mix_FreeMusic(handle);
			handle = NULL;
		}
	}
	void Play(bool looping){
		Mix_FadeInMusic(handle, looping ? -1 : 1, m_fade);
	}
	void Stop(){
		Mix_HaltMusic();
		//Mix_FadeOutMusic(m_fade);
	}

	bool IsPlaying(){
		return Mix_PlayingMusic() == 1;
	}

	int Volume(int volume){
		if(volume < 0) volume = 0;
		if(volume > 100) volume = MIX_MAX_VOLUME;
		Mix_VolumeMusic((int)(MIX_MAX_VOLUME * ((double)volume / (double)100)));
		return volume;
	}
	int Volume(){
		return (int)((double)((double)Mix_VolumeMusic(-1) / (double)MIX_MAX_VOLUME) * (double)100);
	}
	int VolumeChange(int volume){
		return Volume(Volume() + volume);
	}
	
	~MusicItem() { Close(); }
private:
	Mix_Music* handle;
	int m_fade;
};


class SoundItem : public AudioItem {
public:
	SoundItem() : m_channel(-1), handle(NULL) { }
	bool Load(std::string filename){
		handle = Mix_LoadWAV(filename.c_str());
		this->m_type = 1;
		if(handle != NULL){
			Mix_VolumeChunk(handle, MIX_MAX_VOLUME);
			return true; 
		}
		return false;
	}
	void Close(){
		Stop();
		if(handle){
			Mix_FreeChunk(handle);
			handle = NULL;
		}
	}
	void Play(bool looping){
		if(handle){
			m_channel = Mix_PlayChannel(-1, handle, looping ? -1 : 0);
		}
	}
	void Stop(){
		if(Mix_Playing(m_channel) != 0)
			Mix_HaltChannel(m_channel);
		m_channel = -1;
	}

	int Volume(int volume){
		if(volume < 0) volume = 0;
		if(volume > 100) volume = MIX_MAX_VOLUME;
		Mix_VolumeChunk(handle, (int)((double)MIX_MAX_VOLUME * ((double)volume / (double)100)));
		return volume;
	}
	int Volume(){
		return (int)(((double)Mix_VolumeChunk(handle, -1) / (double)MIX_MAX_VOLUME) * (double)100);
	}

	int VolumeChange(int volume){
		return Volume(Volume() + volume);
	}

	~SoundItem() { Close(); }
	
private:
	Mix_Chunk* handle;
	int m_channel;
};



}
}
