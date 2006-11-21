#include "audio.h"

#include <SDL/SDL_mixer.h>

#include <map>
#include <cctype> // for toupper



namespace System{
namespace Audio {


std::map<std::string, AudioItem*> AudioData;
typedef std::map<std::string, AudioItem*>::iterator AudioDataItem;




AudioItem* get(std::string key) {
	AudioDataItem it = AudioData.find(key);
	if (it == AudioData.end()) return NULL;
	return it->second;
}




bool Initialize(){
	return Mix_OpenAudio(
			MIX_DEFAULT_FREQUENCY, 	// Frequency
			MIX_DEFAULT_FORMAT,				// Format
			2,								// Stereo
			1024							// Chunksize
		) == 0;
}



void Stop(){ 
	for(AudioDataItem pos = AudioData.begin(); pos != AudioData.end(); ++pos){
		if((*pos).second){
			(*pos).second->Stop();
		}
	}
}

void Close(){
	//Stop();
	for(AudioDataItem pos = AudioData.begin(); pos != AudioData.end(); ++pos){
		/*if((*pos).second){
			(*pos).second->Close();
			delete (*pos).second;
		}*/
	}
	AudioData.clear();
	Mix_CloseAudio();
}

bool Play(std::string name, bool looping){
	AudioItem* a = get(name);
	if(a){
		a->Play(looping);
		return true;
	}
}

int Volume(std::string name, int volume){
	AudioItem* a = get(name);
	if(a){
		return a->Volume(volume);
	}
	return -1;
}

int Volume(std::string name){
	AudioItem* a = get(name);
	if(a){
		return a->Volume();
	}
	return -1;
}

int VolumeChange(std::string name, int volumechange){
	AudioItem* a = get(name);
	if(a){
		return a->VolumeChange(volumechange);
	}
	return -1;
}

bool LoadSound(std::string name, std::string filename){
	AudioItem* a = new SoundItem();
	if(a->Load(filename)){
		AudioData[name] = a;
		return true;
	}
	delete a;
	return false;
}

bool LoadMusic(std::string name, std::string filename){
	AudioItem* a = new MusicItem();
	if(a->Load(filename)){
		AudioData[name] = a;
		return true;
	}
	delete a;
	return false;
}


}
}

