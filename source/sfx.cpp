#include "sfx.h"
#include <iostream>
#include <string>
using namespace std;

#ifdef _WIN32
	#ifndef _XBOX
		#pragma comment(lib, "SDL_mixer.lib")
	#endif
#endif

extern bool fResumeMusic;
extern void DECLSPEC soundfinished(int channel);
extern void DECLSPEC musicfinished();

extern sfxSound * g_PlayingSoundChannels[NUM_SOUND_CHANNELS];

bool sfx_init()
{
	Mix_OpenAudio(22050, AUDIO_S16MSB, 2, 2048);
	Mix_AllocateChannels(NUM_SOUND_CHANNELS+1);

	for(short iChannel = 0; iChannel < NUM_SOUND_CHANNELS; iChannel++)
		g_PlayingSoundChannels[iChannel] = NULL;

    return true;
}

void sfx_close()
{
	Mix_CloseAudio();
}

void sfx_stopallsounds()
{
	for(short iChannel = 0; iChannel < NUM_SOUND_CHANNELS; iChannel++)
	{
		Mix_HaltChannel(iChannel);
		g_PlayingSoundChannels[iChannel] = NULL;
	}
}

void sfx_setmusicvolume(int volume)
{
	Mix_Volume(NUM_SOUND_CHANNELS, volume);
}

void sfx_setsoundvolume(int volume)
{
	for(short iChannel = 0; iChannel < NUM_SOUND_CHANNELS; iChannel++)
	Mix_Volume(iChannel, volume);
}

sfxSound::sfxSound()
{
	paused = false;
	ready = false;
	sfx = NULL;
}

sfxSound::~sfxSound()
{}

bool sfxSound::init(const string& filename)
{
	if(sfx)
		reset();

	cout << "load " << filename << "..." << endl;
	sfx = Mix_LoadWAV(filename.c_str());
	
	if(sfx == NULL)
	{
		printf(" failed!\n");
		return false;
	}

	channel = -1;
	starttime = 0;
	ready = true;
	instances = 0;

	Mix_ChannelFinished(&soundfinished);
	
	return true;
}

int sfxSound::play()
{
	int ticks = SDL_GetTicks();

	//Don't play sounds right over the top (doubles volume)
	if(channel < 0 || ticks - starttime > 40)
	{
		instances++;
		channel = Mix_PlayChannel(-1, sfx, 0);

		if(channel < 0)
			return channel;

		starttime = ticks;
		
		if(g_PlayingSoundChannels[channel])
			printf("Error: Sound was played on channel that was not cleared!\n");

		g_PlayingSoundChannels[channel] = this;
	}
	return channel;
}

int sfxSound::playloop(int iLoop)
{
	instances++;
	channel = Mix_PlayChannel(-1, sfx, iLoop);

	if(channel < 0)
		return channel;

	g_PlayingSoundChannels[channel] = this;

	return channel;
}

void sfxSound::stop()
{
	if(channel != -1)
	{
		instances = 0;
		Mix_HaltChannel(channel);
		channel = -1;
	}
}

void sfxSound::sfx_pause()
{
	paused = !paused;

	if(paused)
		Mix_Pause(channel);
	else
		Mix_Resume(channel);
}

void sfxSound::clearchannel()
{
	if(--instances <= 0)
	{
		instances = 0;
		channel = -1;
	}
}

void sfxSound::reset()
{
	Mix_FreeChunk(sfx);
	sfx = NULL;
	ready = false;

	if(channel > -1)
		g_PlayingSoundChannels[channel] = NULL;

	channel = -1;
}

int sfxSound::isplaying()
{
	if(channel == -1)
		return false;

	return Mix_Playing(channel);
}


sfxMusic::sfxMusic()
{
	paused = false;
	ready = false;
	music = NULL;
	music_chunk = NULL;
	channel = NUM_SOUND_CHANNELS;
}

sfxMusic::~sfxMusic()
{}

bool sfxMusic::load(const string& filename)
{
// 	if(music)
// 		reset();
//
//     cout << "load " << filename << "..." << endl;
// 	music = Mix_LoadMUS(filename.c_str());
//
// 	if(!music)
// 	{
// 	    printf("Error Loading Music: %s\n", Mix_GetError());
// 		return false;
// 	}
//
// 	Mix_HookMusicFinished(&musicfinished);
//
// 	ready = true;
//
// 	return true;

	if(music_chunk)
		reset();

	cout << "load " << filename << "..." << endl;
	music_chunk = Mix_LoadWAV(filename.c_str());

	if(music_chunk == NULL)
	{
		printf(" failed!\n");
		return false;
	}

	Mix_ChannelFinished(&soundfinished);

	ready = true;

	return true;
}

void sfxMusic::play(bool fPlayonce, bool fResume)
{
	// Mix_PlayMusic(music, fPlayonce ? 0 : -1);
	// fResumeMusic = fResume;

	Mix_PlayChannel(channel, music_chunk, fPlayonce ? 0 : -1);
	fResumeMusic = fResume;

}

void sfxMusic::stop()
{
	// Mix_HaltMusic();

	Mix_HaltChannel(channel);

}

void sfxMusic::sfx_pause()
{
	// paused = !paused;
 //
	// if(paused)
	// 	Mix_PauseMusic();
	// else
	// 	Mix_ResumeMusic();

	paused = !paused;

	if(paused)
		Mix_Pause(channel);
	else
		Mix_Resume(channel);

}

void sfxMusic::reset()
{
	// Mix_FreeMusic(music);
	// music = NULL;
	// ready = false;

	Mix_FreeChunk(music_chunk);
	music_chunk = NULL;
	ready = false;

}

int sfxMusic::isplaying()
{
	// return Mix_PlayingMusic();

	return Mix_Playing(channel);

}


