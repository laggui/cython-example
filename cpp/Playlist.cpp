#include "Playlist.h"

#include <iostream>
#include <fstream>

const std::string Playlist::sPlaylistExtension = ".ipl";

Playlist::Playlist(const std::string & name)
	: mName{ name }
{
}

std::shared_ptr<Song> Playlist::song(int index) const
{
	if (index < static_cast<int>(mSongList.size()) && index >= 0) {
		return mSongList[index];
	}
	return nullptr;
}

std::string Playlist::name() const
{
	return mName;
}

int Playlist::size() const
{
	return mSongList.size();
}

int Playlist::addSong(std::shared_ptr<Song> song, int index)
{
	if (song) {
		if (index >= 0) {
			// Insert at index
			mSongList.insert(mSongList.begin() + index, song);
		}
		else if (index == -1) {
			// Default case, insert at end for O(1) complexity
			mSongList.push_back(song);
			index = mSongList.size() - 1;
		}
	}
	return index;
}

void Playlist::setName(const std::string & name)
{
	mName = name;
}

std::vector<std::shared_ptr<Song>> Playlist::constructFromFile()
{
	const char delim{ ';' };
	std::vector<std::shared_ptr<Song>> newSongs;
	std::string line;
	std::size_t first;
	std::size_t second;
	std::ifstream playlistFile(mName + sPlaylistExtension);

	if (playlistFile.is_open())
	{
		while (std::getline(playlistFile, line))
		{
			// Playlist song format: ARTIST;SONG;ALBUM
			first = line.find(delim);
			second = line.find(delim, first + 1);

			// newSongs.push_back(std::shared_ptr<Song>(new Song{ line.substr(first + 1, second - first - 1), // song
			// 												   line.substr(0, first), // artist
			// 												   line.substr(second + 1) // album
			// 												 }));
			// Use make_shared to create new shared pointer (only one heap-allocation - faster)
			newSongs.push_back(std::make_shared<Song>(line.substr(first + 1, second - first - 1), // song
													  line.substr(0, first), // artist
													  line.substr(second + 1) // album
													 ));
		}
		playlistFile.close();
		mSongList.insert(mSongList.end(), newSongs.begin(), newSongs.end());
	}
	return newSongs;
}
