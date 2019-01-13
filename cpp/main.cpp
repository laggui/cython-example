#include <string>
#include <vector>
#include "Song.h"
#include "Playlist.h"

int main(int argc, const char* argv[]) {
	std::string playlistName{ "../my_playlist" };
	Playlist myPlaylist{ playlistName };

	std::vector<std::shared_ptr<Song>> songsAdded = myPlaylist.constructFromFile();
	std::shared_ptr<Song> newSong(new Song{"How Could You Leave Us", "NF", "Therapy Session"});

	myPlaylist.addSong(newSong);
	std::shared_ptr<Song> tmpSong = myPlaylist.song(9); // nullptr
	tmpSong = myPlaylist.song(7);

	return 0;
}