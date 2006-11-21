#if !defined(_AUDIOSYSTEM_H_INCLUDED_)
#define _AUDIOSYSTEM_H_INCLUDED_

#include <string>
#include <map>

#include <FMOD/fmod.h>
#include <FMOD/fmod_errors.h> // optional




namespace System {
namespace Audio {
	
class AudioItem;
class MusicItem;
class SoundItem;


bool Initialize();
void Close();
void Close(std::string filename);

void Stop();
bool Stop(std::string filename);

bool Load(std::string filename, int type = 0);
void Play(std::string filename);
void Pause(std::string filename, bool pause);
bool Pause(std::string filename);
void Looping(std::string filename, bool looping);
bool Looping(std::string filename);

void Volume(int volume);
int Volume();
void Volume(std::string filename, int volume);
int Volume(std::string filename);

extern MusicItem* currentMusic;


/*****************************************************************/
	class AudioItem
	{
	public:
		virtual ~AudioItem() { }
		virtual void Play() = 0;
		virtual void Stop() = 0;
		virtual void Close() = 0;
		virtual bool Load(std::string) = 0;

		// These functions only exist in Music
		virtual void Pause(bool pause){ }
		virtual bool Pause(){ return false; }
		virtual bool Looping(){ return false; }
		virtual void Looping(bool looping){ }

		virtual void Volume(int volume) { }
		virtual int Volume() { return 100; }

		int type;
	};


/*****************************************************************/
	class SoundItem : public AudioItem
	{
	public:
		SoundItem() : channel(-1), handle(NULL) { }
		bool Load(std::string filename){
			handle = FSOUND_Sample_Load(
					FSOUND_FREE|FSOUND_UNMANAGED,
					filename.c_str(), 0, 0, 0);
			return handle != NULL;
		}
  		void Stop() { FSOUND_StopSound(channel); }
		void Play() {
			if(handle)
				channel = FSOUND_PlaySound(FSOUND_FREE, handle);
		}
		void Close() {
			if(handle){
				Stop();
				FSOUND_Sample_Free(handle);
			}
		}
		~SoundItem() { Close(); }

		FSOUND_SAMPLE* Handle(){ return handle; }
	private:
		FSOUND_SAMPLE* handle;
		int channel;
	};


/*****************************************************************/


	class MusicItem : public AudioItem
	{
	public:
		MusicItem() : looping(true), handle(NULL) { }
		bool Load(std::string filename){
			handle = FMUSIC_LoadSong(filename.c_str());
			return handle != NULL;
		}
		void Close(){
			Stop();
			if(handle){
				FMUSIC_FreeSong(handle);
			}
		}
		~MusicItem(){ Close(); }
		void Play() {
			if(handle){
				if(currentMusic){
					FMUSIC_StopSong(currentMusic->Handle());
				}
				currentMusic = this;
				FMUSIC_PlaySong(handle);
			}
		}
		void Stop() {
			if(handle){
				FMUSIC_StopSong(handle);
				currentMusic = NULL;
			}
		}
		void Pause(bool pause) {
			if(handle)
				FMUSIC_SetPaused(handle, pause);
		}
		bool Pause() {
			if(handle)
				return FMUSIC_GetPaused(handle);
			else
				return false;
		}
		bool Looping(){ return looping; }
		void Looping(bool looping){
			if(handle){
				FMUSIC_SetLooping(handle, looping);
			    this->looping = looping;
			}
		}

		void Volume(int volume) {
			if(handle)
				FMUSIC_SetMasterVolume(handle, (int)(volume*2.55));
		}
		int Volume() {
			if(handle)
				return (int)(FMUSIC_GetMasterVolume(handle)/2.55);
			else
				return -1;
		}

		FMUSIC_MODULE* Handle(){ return handle; }
	private:
		FMUSIC_MODULE* handle;
		bool looping;
	};

/*****************************************************************/
	
	class StreamItem : public AudioItem {
	public:
		StreamItem( ) : channel(-1), handle(NULL) { }
		bool Load(std::string filename){
			handle = FSOUND_Stream_Open(filename.c_str(),0, 0, 0);
			return handle != NULL;
		}
		void Close(){
			if(handle){
				Stop();
				FSOUND_Stream_Close(handle);
			}
		}
		~StreamItem() { Close(); }
		void Play() {
			if(handle)
				channel = FSOUND_Stream_Play(FSOUND_FREE, handle);
		}
		void Stop() {
			if(handle)
				FSOUND_Stream_Stop(handle);
		}
		FSOUND_STREAM* Handle(){ return handle; }
	private:
		FSOUND_STREAM* handle;
		int channel;
	};
/*****************************************************************/
}
}


#endif // _AUDIOSYSTEM_H_INCLUDED_












