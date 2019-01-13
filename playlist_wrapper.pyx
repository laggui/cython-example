# cython: language_level=3

cimport playlist_decl as pl

from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp.memory cimport unique_ptr, shared_ptr
from cython.operator cimport dereference as deref

cdef class PySong:
    """Python object factory class taking C++ struct ptr"""
    cdef shared_ptr[pl.Song] ptr
    
    def __cinit__(self, _name=b"", _artist=b"", _album=b"", _alloc=True):
        # Note: exposing _alloc could be dangerous. Might need to rethink that even though this isn't the goal of this project.
        if _alloc:
            self.ptr = shared_ptr[pl.Song](new pl.Song()) # TO-DO: check for usage of make_shared in cython vs creating shared_ptr with new
            deref(self.ptr).name = _name
            deref(self.ptr).artist = _artist
            deref(self.ptr).album = _album

    property name:
        def __get__(self):
            return deref(self.ptr).name
        def __set__(self, _name):
            deref(self.ptr).name = _name
    
    property artist:
        def __get__(self):
            return deref(self.ptr).artist
        def __set__(self, _artist):
            deref(self.ptr).artist = _artist
    
    property album:
        def __get__(self):
            return deref(self.ptr).album
        def __set__(self, _album):
            deref(self.ptr).album = _album
    
    @staticmethod
    cdef create(shared_ptr[pl.Song] PySong_ptr):
        # Create new MyStruct object. This does not create
        # new structure but does allocate a null pointer
        cdef PySong _mysong = PySong(_alloc=False)
        # Set pointer of cdef class to existing struct ptr
        _mysong.ptr = PySong_ptr
        # Return the wrapped PySong object with PySong_ptr
        return _mysong

cdef class PyPlaylist:
    cdef unique_ptr[pl.Playlist] thisptr

    def __init__(self, string name):
        self.thisptr.reset(new pl.Playlist(name))
    
    def song(self, int index):
        s = deref(self.thisptr).song(index)
        return PySong.create(s) if s != NULL else -1
    
    def name(self):
        return deref(self.thisptr).name()
    
    def size(self):
        return deref(self.thisptr).size()
    
    def add_song(self, PySong song, int index = -1):
        return deref(self.thisptr).addSong(song.ptr, index)
    
    def set_name(self, string name):
        deref(self.thisptr).setName(name)
    
    def construct_from_file(self):
        v = deref(self.thisptr).constructFromFile()
        return [PySong.create(s) for s in v]