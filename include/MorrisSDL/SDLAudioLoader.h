#pragma once

#include <SDL_mixer.h>
#include <string>

class SDLAudioLoader
{
public:
	static SDLAudioLoader& GetInstance()
	{
		static SDLAudioLoader instance;
		return instance;
	}

	Mix_Music* LoadMusic(const std::string& fileName)
	{
		static const std::string dataFolderName = "../data/";
		const std::string filePath = dataFolderName + fileName;

		Mix_Music* musicPtr = nullptr;

		musicPtr = Mix_LoadMUS(filePath.c_str());

		if (!musicPtr)
			throw std::string("Unable to load audio file: " + filePath);

		return musicPtr;
	}

	Mix_Chunk* LoadChunk(const std::string& fileName)
	{
		static const std::string dataFolderName = "../data/";
		const std::string filePath = dataFolderName + fileName;

		Mix_Chunk* chunkPtr = nullptr;

		chunkPtr = Mix_LoadWAV(filePath.c_str());

		if (!chunkPtr)
			throw std::string("Unable to load audio file: " + filePath);

		return chunkPtr;
	}


private:
	SDLAudioLoader() {}

	SDLAudioLoader(const SDLAudioLoader& other) = delete;
	void operator=(const SDLAudioLoader& other) = delete;
};