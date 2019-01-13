#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <memory>
#include <vector>
#include <string>
#include "Song.h"

// Playlist is my example class which contains a number of songs. As expected, a Playlist does not own
// the songs since multiple playlists can have the same song. Thus, this also allowed me to make use of
// shared pointers.
class Playlist
{
public:
	Playlist(const std::string & name);
	~Playlist() = default;

	// Getter
	std::shared_ptr<Song> song(int index) const;
	std::string name() const;
	int size() const;
	// Setter
	int addSong(std::shared_ptr<Song> song, int index = -1);
	void setName(const std::string & name);
	std::vector<std::shared_ptr<Song>> constructFromFile();
private:
	std::string mName;
	std::vector<std::shared_ptr<Song>> mSongList; // playlist does not own the songs --> shared_ptr

	static const std::string sPlaylistExtension;
};

#endif // !PLAYLIST_H