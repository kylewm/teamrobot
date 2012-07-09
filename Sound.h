// Sound.h: interface for the Sound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUND_H__D6ABA68D_903A_4EB0_9036_7029088192B7__INCLUDED_)
#define AFX_SOUND_H__D6ABA68D_903A_4EB0_9036_7029088192B7__INCLUDED_

#include <ClanLib/sound.h>
#include <ClanLib/vorbis.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NSOUNDS 2
#define NMUSIC 2

enum sound_t {
	EXPLOSION,
	SPLASH
};
enum music_t {
	REVERSE_SONG,
	THIS_IS_THE_RAINBOW
};

class Sound  
{
public:
	Sound();
	virtual ~Sound();
	
	void loadSounds();
	void playSound(sound_t snd);
	void stopSound(sound_t snd);
	void stopAllSounds();

	void loadMusic();
	void playMusic(music_t song);
	void stopMusic(music_t song);
	void stopAllMusic();
	bool isPlaying(music_t song);

	void mute();
	bool isMuted();

private:
	CL_SoundBuffer sndbuffer[NSOUNDS];
	CL_SoundBuffer musicbuffer[NMUSIC];
	CL_SoundBuffer_Session session[NMUSIC];
	bool muted;
};

#endif // !defined(AFX_SOUND_H__D6ABA68D_903A_4EB0_9036_7029088192B7__INCLUDED_)
