/*
   Copyright (c) 2014 Narciso Cerezo. All rights reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "Game.h"

#include <sys/time.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "Renderer.h"

using namespace std;

namespace cocosdl {

  Game *Game::_instance = NULL;

  Game::Game( const char *title, const int x, const int y, const int width, const int height ) :
  _window( NULL ),
  _renderer( NULL ),
  _title( title ? title : "Game" ),
  _windowFlags( SDL_WINDOW_SHOWN ),
  _scene( NULL ),
  _running( false ),
  _backgroundMusicPlaying( "" ),
  _soundVolume( DEFAULT_SOUND_VOLUME ),
  _musicVolume( DEFAULT_MUSIC_VOLUME ),
  _windowRect( x, y, width, height )
  {
  }

  Game::Game( const char *title, const int x, const int y, const int width, const int height, const Uint32 windowFlags ) :
  _window( NULL ),
  _renderer( NULL ),
  _title( title ? title : "Game" ),
  _windowFlags( SDL_WINDOW_SHOWN ),
  _scene( NULL ),
  _running( false ),
  _backgroundMusicPlaying( "" ),
  _soundVolume( DEFAULT_SOUND_VOLUME ),
  _musicVolume( DEFAULT_MUSIC_VOLUME ),
  _windowRect( x, y, width, height )
  {
  }

  Game::~Game()
  {
    for( map<string, TTF_Font *>::iterator i = _fonts.begin(); i != _fonts.end(); ++i )
    {
      TTF_CloseFont( ( *i ).second );
    }
    for( map<string, Mix_Music *>::iterator i = _music.begin(); i != _music.end(); ++i )
    {
      Mix_FreeMusic( ( *i ).second );
    }
    for( map<string, Mix_Chunk *>::iterator i = _sounds.begin(); i != _sounds.end(); ++i )
    {
      Mix_FreeChunk( ( *i ).second );
    }
    if( _window )
    {
      SDL_DestroyWindow( _window );
    }
    if( _renderer )
    {
      delete _renderer;
    }
  }


  Game *Game::getInstance()
  {
    return _instance;
  }

  bool Game::init( const char *title, const int x, const int y, const int width, const int height )
  {
    if( !_instance )
    {
      _instance = new Game( title, x, y, width, height );
      return _instance->init();
    }
    return true;
  }

  bool Game::init( const char *title, const int x, const int y, const int width, const int height, const Uint32 windowFlags )
  {
    if( !_instance )
    {
      _instance = new Game( title, x, y, width, height, windowFlags );
      return _instance->init();
    }
    return true;
  }

  bool Game::init()
  {

    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
      SDL_Log( "Can't initialize SDL" );
      return false;
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if( ( IMG_Init( imgFlags ) & imgFlags ) != imgFlags )
    {
      SDL_Log( "Can't initialize SDL image" );
      return false;
    }

    if( TTF_Init() != 0 )
    {
      SDL_Log( "Can't initialize SDL TTF" );
      return false;
    }

    if( Mix_Init( MIX_INIT_MP3 ) != MIX_INIT_MP3 )
    {
      SDL_Log( "Can't initialize SDL Mixer" );
      return false;
    }

    if( Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIXER_CHANNELS, MIXER_CHUNK_SIZE ) == -1 )
    {
      SDL_Log( "Can't open audio" );
      return false;
    }

    _window = SDL_CreateWindow(
        _title.c_str(),
        _windowRect.getX(),
        _windowRect.getY(),
        _windowRect.getWidth(),
        _windowRect.getHeight(),
        _windowFlags
    );
    if( !_window )
    {
      SDL_Log( "Can't create window" );
      return false;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( !renderer )
    {
      SDL_Log( "Can't create renderer" );
      return false;
    }
    _renderer = new Renderer( renderer );
    Rect clipRect( 0, 0, _windowRect.getWidth(), _windowRect.getHeight() );
    _renderer->setClipRect( clipRect );

    Mix_VolumeMusic( (int) ( _musicVolume * MIX_MAX_VOLUME ) );

    return true;
  }

  void Game::setScene( Scene *scene )
  {
    _scene = scene;
  }

  void Game::run()
  {

    Uint32 nextGameTick = SDL_GetTicks();
    int loops;
    SDL_Event event;
    _running = true;
    while( _running )
    {
      if( _scene )
      {

        loops = 0;
        while( SDL_GetTicks() > nextGameTick && loops < MAX_FRAME_SKIP )
        {
          while( SDL_PollEvent( &event ) )
          {
            _scene->handleEvent( event );
          }

          nextGameTick += SKIP_TICKS;
          loops++;
        }

        _renderer->clear();
        _scene->runActions();
        _scene->update( currentTimeMillis() / 10 );
        _scene->draw();
        _renderer->present();
      }
      else
      {
        while( SDL_PollEvent( &event ) )
        { } // consume input while no scene to consume them
      }
    }
  }


  long long Game::currentTimeMillis()
  {
    struct timeval tv;
    gettimeofday( &tv, NULL );
    return (long long) ( tv.tv_sec * 1000 + tv.tv_usec / 1000 );
  }

  void Game::quit()
  {
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    Mix_CloseAudio();
    SDL_Quit();
  }

  bool Game::loadFont( const string &name, const int fontSize )
  {
    TTF_Font *font = getFont( name, fontSize );
    if( !font )
    {
      string path = getResourcePath() + name + ".ttf";
      font = TTF_OpenFont( path.c_str(), fontSize );
      if( font )
      {
        char sizeString[20];
        snprintf( sizeString, 20, "%d", fontSize );
        string key = name + sizeString;
        _fonts.insert( _fonts.end(), make_pair( key, font ) );
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return true;
    }
  }

  TTF_Font *Game::getFont( const string &name, const int fontSize )
  {
    char sizeString[20];
    snprintf( sizeString, 20, "%d", fontSize );
    string key = name + sizeString;
    map<string, TTF_Font *>::iterator position = _fonts.find( key );
    if( position != _fonts.end() )
    {
      return ( *position ).second;
    }
    else
    {
      return NULL;
    }
  }


  bool Game::loadMusic( const string &name )
  {
    Mix_Music *music = getMusic( name );
    if( !music )
    {
      string path = getResourcePath() + name + ".mp3";
      music = Mix_LoadMUS( path.c_str() );
      if( music )
      {
        _music.insert( _music.end(), make_pair( name, music ) );
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return true;
    }
  }

  Mix_Music *Game::getMusic( const string &name )
  {
    map<string, Mix_Music *>::iterator position = _music.find( name );
    if( position != _music.end() )
    {
      return ( *position ).second;
    }
    else
    {
      return NULL;
    }
  }

  bool Game::playBackgroundMusic( const string &name )
  {
    Mix_Music *music = getMusic( name );
    if( music )
    {
      if( Mix_FadeInMusic( music, -1, MUSIC_FADE_IN_MS ) != -1 )
      {
        _backgroundMusicPlaying = name;
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }

  bool Game::stopBackgroundMusic()
  {
    return Mix_FadeOutMusic( MUSIC_FADE_OUT_MS ) == 1;
  }

  void Game::setMusicVolume( const float musicVolume )
  {
    _musicVolume = musicVolume;
    Mix_VolumeMusic( (int) ( MIX_MAX_VOLUME * musicVolume ) );
  }

  bool Game::loadSound( const string &name )
  {
    Mix_Chunk *sound = getSound( name );
    if( !sound )
    {
      string path = getResourcePath() + name + ".ogg";
      sound = Mix_LoadWAV( path.c_str() );
      if( sound )
      {
        Mix_VolumeChunk( sound, (int) ( MIX_MAX_VOLUME * _soundVolume ) );
        _sounds.insert( _sounds.end(), make_pair( name, sound ) );
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return true;
    }
  }

  Mix_Chunk *Game::getSound( const string &name )
  {
    map<string, Mix_Chunk *>::iterator position = _sounds.find( name );
    if( position != _sounds.end() )
    {
      return ( *position ).second;
    }
    else
    {
      return NULL;
    }
  }

  int Game::playSound( const string &name )
  {
    Mix_Chunk *sound = getSound( name );
    if( sound )
    {
      return Mix_PlayChannel( -1, sound, 0 );
    }
    else
    {
      return -1;
    }
  }


  void Game::setSoundVolume( const float soundVolume )
  {
    _soundVolume = soundVolume;
    int volume = (int) ( MIX_MAX_VOLUME * soundVolume );
    for( map<string, Mix_Chunk *>::iterator i = _sounds.begin(); i != _sounds.end(); ++i )
    {
      Mix_VolumeChunk( ( *i ).second, volume );
    }
  }

  /*
   * Get the resource path for res located in res/subDir
   * It's assumed the project directory is structured like:
   * bin/
   *  the executable
   * res/
   */
  std::string Game::getResourcePath( const std::string &subDir )
  {
    //We need to choose the path separator properly based on which
    //platform we're running on, since Windows uses a different
    //separator than most systems
  #ifdef _WIN32
    const char PATH_SEP = '\\';
  #else
    const char PATH_SEP = '/';
  #endif
    //This will hold the base resource path: Lessons/res/
    //We give it static lifetime so that we'll only need to call
    //SDL_GetBasePath once to get the executable path
    static std::string baseRes;

    if( baseRes.empty() )
    {
      //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
      char *basePath = SDL_GetBasePath();
      if( basePath )
      {
        baseRes = basePath;
        SDL_free( basePath );
      }
      else
      {
        return "";
      }

      //We replace the last bin/ with res/ to get the the resource path
      size_t pos = baseRes.rfind( "bin" );
      if( pos < baseRes.length() )
      {
        baseRes = baseRes + "res" + PATH_SEP;
      }
      else
      {
        baseRes = baseRes.substr( 0, pos ) + "res" + PATH_SEP;
      }
      SDL_Log( "Resources dir: %s", baseRes.c_str() );
    }

    //If we want a specific subdirectory path in the resource directory
    //append it to the base path. This would be something like Lessons/res/Lesson0
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
  }

}
