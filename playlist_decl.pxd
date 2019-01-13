# cython: language_level=3

from libcpp.memory cimport shared_ptr
from libcpp.string cimport string
from libcpp.vector cimport vector

cdef extern from "Song.h":
    cdef cppclass Song:
        string name
        string artist
        string album

cdef extern from "Playlist.h":
    cdef cppclass Playlist:
        Playlist(string)
        shared_ptr[Song] song(int)
        string name()
        int size()
        int addSong(shared_ptr[Song], int)
        void setName(string)
        vector[shared_ptr[Song]] constructFromFile()