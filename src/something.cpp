#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <SDL.h>

#ifdef SOMETHING_RELEASE
#define STB_IMAGE_IMPLEMENTATION
#endif
#define STBI_ONLY_PNG
#include "./stb_image.h"

#include "aids.hpp"

using namespace aids;

#include "something_math.cpp"

#ifndef SOMETHING_RELEASE
#include "config_common.cpp"
#else
#include "./baked_config.hpp"
#endif

// READ THIS FIRST ---> https://en.wikipedia.org/wiki/Single_Compilation_Unit
#ifndef SOMETHING_RELEASE
// TODO(#173): config autoreloading does not work on Windows
// TODO(#174): config autoreloading does not work on MacOS
#  ifdef __linux__
#    include "something_fmw_inotify.cpp"
#  else
#    include "something_fmw_dummy.cpp"
#  endif // __linux__
#endif // SOMETHING_RELEASE
#include "something_error.cpp"
#include "something_render.cpp"
#include "something_font.cpp"
#include "something_camera.cpp"
#include "something_texture.cpp"
#include "something_sprite.cpp"
#include "something_tile_grid.cpp"
#include "something_sound.cpp"
#include "something_entity.cpp"
#include "something_popup.cpp"
#include "something_item.cpp"
#include "something_toolbar.cpp"
#include "something_commands.cpp"
#include "something_select_popup.cpp"
#include "something_console.cpp"
#include "something_game.cpp"
#include "something_main.cpp"
