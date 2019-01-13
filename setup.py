from distutils.core import setup, Extension
from Cython.Build import cythonize

compile_args = ['-g', '-std=c++11']

ext = Extension(
      name="playlist_wrapper",
      sources=["playlist_wrapper.pyx", "cpp/Playlist.cpp"],
      language="c++",
      include_dirs=["cpp"], extra_compile_args=compile_args
)


setup(ext_modules=cythonize(ext))