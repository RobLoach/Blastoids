#include "audio.h"

#include <string>
#include <map>
#include <cctype> // for toupper

#include <SDL/SDL.h>
#include <FMOD/fmod.h>
#include <FMOD/fmod_errors.h> // optional



namespace System {

	std::map<std::string, AudioItem*> AudioData;
	typedef std::map<std::string, AudioItem*>::iterator AudioDataItem;

	MusicItem* currentMusic;
	CAudio Audio;

	AudioItem* get(std::string filename) {
		AudioDataItem it = AudioData.find(filename);
		if (it == AudioData.end()) return NULL;
		return it->second;
	}



	CAudio::CAudio(){
		if (FSOUND_GetVersion() < FMOD_VERSION){
	        //SDL_SetError("FMOD.DLL version is old, please update it.");
			return;
		}
	
		if (!FSOUND_Init(32000, 64, 0)){
	        //SDL_SetError(FMOD_ErrorString(FSOUND_GetError()));
			return;
		}
		//return true;
	}
	
	CAudio::~CAudio(){
		Stop();
		for(AudioDataItem pos = AudioData.begin(); pos != AudioData.end(); ++pos){
			if(pos->second){
				pos->second->Close();
				delete pos->second;
			}
		}
		AudioData.clear();
		FSOUND_Close();
	}

	void CAudio::StopMusic(){
		if(currentMusic)
			currentMusic->Stop();
	}

	int CAudio::MusicVolume(int volume) {
		for(AudioDataItem pos = AudioData.begin(); pos != AudioData.end(); ++pos){
			if(pos->second){
				if(pos->second->type == 2){
					pos->second->Volume(volume);
				}
			}
		}
		return volume;
	}

	bool CAudio::IsPlaying(std::string filename){
		AudioItem* a = get(filename);
		if(a){
			return a->IsPlaying();
		} else {
			return false;
		}
	}

	void CAudio::Close(std::string filename){
		AudioItem* a = get(filename);
		if(a){
			a->Close();
			AudioData.erase(filename);
		}
	}



	bool CAudio::Load(std::string name, std::string filename, int type){
		// Check if already exists
		AudioDataItem it = AudioData.find(name);
		if (it != AudioData.end())
			return true; // Already loaded

		// Get the type
		if(type <= 0){
			//TODO - Find what type it is
			std::string fileExtension = "NONE";
			if(filename.length() > 4)
				fileExtension = filename.substr(filename.length() - 3, 3);

			// Convert to uppercase
			for (int i = 0; i < fileExtension.length(); i++ )
				fileExtension[i] = toupper(fileExtension[i]);

			if(fileExtension == "MOD" || fileExtension == "S3M" || 
					fileExtension == ".XM" || fileExtension == ".IT" || 
					fileExtension == "MID" || fileExtension == "IDI" || 
					fileExtension == "RMI" || fileExtension == "SGT" ||
					fileExtension == "FSB"){
				type = 2; // Music
			} else if(fileExtension == "WAV" || fileExtension == "MP2" || 
					fileExtension == "MP3" || fileExtension == "OGG" || 
					fileExtension == "RAW"){
				type = 1; // Sound
			} else {
				type = 1; // Default
			}
		}

		// Create the item that we'll be adding in
		AudioItem* a;
		switch(type){
		case 1: a = new SoundItem(); break;
		case 2: a = new MusicItem(); break;
		case 3: a = new StreamItem(); break;
		default: a = new SoundItem(); break;
		}
		if(a->Load(filename)){
			AudioData[name] = a;
			a->type = type;
			return true;
		} else {
			delete a;
			return false;
		}		
	}


	void CAudio::Play(std::string filename){
		AudioItem* a = get(filename);
		if(a != NULL)
			a->Play();
	}

	bool CAudio::Stop(std::string filename){
		AudioItem* a = get(filename);
		if(a != NULL){
			a->Stop();
			return true;
		}
	}
	void CAudio::Stop(){
		for(AudioDataItem pos = AudioData.begin(); pos != AudioData.end(); pos++){
			if(pos->second){
				pos->second->Stop();
			}
		}
	}


	void CAudio::Pause(std::string filename, bool pause){
		AudioItem* a = get(filename);
		if(a != NULL)
			a->Pause(pause);
	}
	bool CAudio::Pause(std::string filename){
		AudioItem* a = get(filename);
		if(a != NULL)
			return a->Pause();
	}


	void CAudio::Looping(std::string filename, bool looping){
		AudioItem* a = get(filename);
		if(a != NULL)
			a->Looping(looping);
	}
	bool CAudio::Looping(std::string filename){
		AudioItem* a = get(filename);
		if(a != NULL)
			return a->Looping();
	}

	void CAudio::Volume(int volume){
		if(volume<0) volume = 0;
		else if(volume>100) volume = 100;
		FSOUND_SetSFXMasterVolume((int)(volume*2.55));
	}
	int CAudio::Volume(){
		return (int)(FSOUND_GetSFXMasterVolume()/2.55);
	}
	
	void CAudio::Volume(std::string filename, int volume){
		AudioItem* a = get(filename);
		if(a != NULL)
			return a->Volume(volume);
	}

	int CAudio::Volume(std::string filename){
		AudioItem* a = get(filename);
		if(a != NULL)
			return a->Volume();
	}
	

	




}

