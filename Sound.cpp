// Sound.cpp: implementation of the Sound class.
//
//////////////////////////////////////////////////////////////////////

#include "Sound.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Sound::Sound()
{
	muted = false;
}

Sound::~Sound()
{

}

void Sound::loadSounds() {
	sndbuffer[EXPLOSION] = CL_SoundBuffer("./sounds/explosion.ogg");
	sndbuffer[SPLASH] = CL_SoundBuffer("./sounds/splash3.ogg");
}
void Sound::loadMusic() {
	musicbuffer[REVERSE_SONG] = CL_SoundBuffer("./sounds/reversesong.ogg");
	musicbuffer[THIS_IS_THE_RAINBOW] = CL_SoundBuffer("./sounds/thisistherainbow.ogg");
	session[REVERSE_SONG] = musicbuffer[REVERSE_SONG].prepare();
	session[REVERSE_SONG].set_looping(true);
	session[REVERSE_SONG].set_volume(0.5f);
	session[THIS_IS_THE_RAINBOW] = musicbuffer[THIS_IS_THE_RAINBOW].prepare();
	session[THIS_IS_THE_RAINBOW].set_looping(false);
}

void Sound::playSound(sound_t snd) {
	if (!muted) sndbuffer[snd].play();
}

void Sound::playMusic(music_t song) {
	if (!muted) {
		session[song].play();
	}
}

void Sound::stopSound(sound_t snd) {
	sndbuffer[snd].stop();
}

void Sound::stopMusic(music_t song) {
	session[song].stop();
	if (song == THIS_IS_THE_RAINBOW) session[song].set_position_relative(0);
}

void Sound::stopAllSounds() {
	for (int i = 0; i < NSOUNDS; i++) {
		sndbuffer[i].stop();
	}
}

void Sound::stopAllMusic() {
	for (int i = 0; i < NMUSIC; i++) {
		session[i].stop();
	}
}

bool Sound::isPlaying(music_t song) {
	return session[song].is_playing();	

}

void Sound::mute() {
	muted = !muted;
}

bool Sound::isMuted() {
	return muted;
}