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

#ifndef __Game_H_
#define __Game_H_

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <stack>
#include "Scene.h"
#include "Rect.h"
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

namespace cocosdl {

  static const float DEFAULT_SOUND_VOLUME = 0.7f;
  static const float DEFAULT_MUSIC_VOLUME = 0.3f;
  static const int TICKS_PER_SECOND = 25;
  static const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
  static const int MAX_FRAME_SKIP = 5;
  static const int MIXER_CHANNELS = 2;
  static const int MIXER_CHUNK_SIZE = 1024;
  static const int MUSIC_FADE_IN_MS = 1000;
  static const int MUSIC_FADE_OUT_MS = 1000;

  class Scene;
  class Renderer;

  /**
   * This is the Game singleton. It handles the underlying framework initialization and disposal, runs the main game loop,
   * and provides a common repository for shared res such as fonts, music or sounds.
   *
   * @author narciso.cerezo@gmail.com
   * @version 1.0
   */
  class Game
  {

  public:
    virtual ~Game();

    /**
     * Get the Game instance. You must call one of the init methods first to initialize and create the game instance.
     *
     * @return the Game instance, or NULL if no init method has been called first.
     */
    static Game *getInstance();

    /**
     * Initialize the Game instance.
     *
     * @param title window title
     * @param x window x
     * @param y window y
     * @param width window witdth
     * @param height window height
     */
    static bool init( const char *title, const int x, const int y, const int width, const int height );

    /**
     * Initialize the Game instance.
     *
     * @param title window title
     * @param x window x
     * @param y window y
     * @param width window witdth
     * @param height window height
     * @param windowFlags (see SDL_Init)
     */
    static bool init( const char *title, const int x, const int y, const int width, const int height, const Uint32 windowFlags );

    /**
     * Quit the game and exit.
     */
    static void quit();


    SDL_Window *getWindow() const
    {
      return _window;
    }

    Renderer *getRenderer() const
    {
      return _renderer;
    }

    const std::string &getTitle() const
    {
      return _title;
    }

    const Rect &getWindowRect() const
    {
      return _windowRect;
    }

    Uint32 getWindowFlags() const
    {
      return _windowFlags;
    }

    Scene *getScene() const
    {
      return _scene;
    }

    /**
     * Set the current scene. You must set a scene or the game will do nothing...<br/>
     * The previous scene is NOT freed, you must free it yourself.
     *
     * @param scene the scene
     */
    void setScene( Scene *scene );

    /**
     * Run the game. After initializing and preloading res you must call this method to run the game.
     */
    void run();

    /**
     * Load a TTF font.
     *
     * @param name the font name (not including the .ttf extension, which must be lowercase)
     * @param fontSize font size in points.
     * @return true if the font was found and loaded, false otherwise
     */
    bool loadFont( const std::string &name, const int fontSize );

    /**
     * Get a previously loaded font.
     *
     * @param name the font name
     * @param fontSize the font size in points
     * @return the TTF_Font instance, NULL if not loaded
     */
    TTF_Font *getFont( const std::string &name, const int fontSize );

    /**
     * Load a background music MP3 file.
     *
     * @param the file name (not including the .mp3 extension, which must be lowercase)
     * @return bool if the file was found and loaded, false otherwise
     */
    bool loadMusic( const std::string &name );

    /**
     * Get a previously loaded music item.
     *
     * @param name the file name
     * @return the Mix_Music object, NULL if not loaded
     */
    Mix_Music *getMusic( const std::string &name );

    /**
     * Play a background music file. If one was already playing it will be stopped first.<br/>
     * The music fades in and plays in an infinite loop.
     *
     * @param name the music file name
     * @return true if the music starts to play, false otherwise
     */
    bool playBackgroundMusic( const std::string &name );

    /**
     * Stop the currently playing music file (if any). The music fades out.
     *
     * @return true if there was a music file playing and has been stopped, false otherwise
     */
    bool stopBackgroundMusic();

    /**
     * Get the sound volume.
     *
     * @return sound volume, 0.0f meaning muted, 1.0f meaning full volume.
     */
    float getSoundVolume() const
    {
      return _soundVolume;
    }

    /**
     * Set the sound volume.
     *
     * @param soundVolume sound volume, 0.0f meaning muted, 1.0f meaning full volume.
     */
    void setSoundVolume( const float soundVolume );

    /**
     * Get the music volume.
     *
     * @return music volume, 0.0f meaning muted, 1.0f meaning full volume.
     */
    float getMusicVolume() const
    {
      return _musicVolume;
    }

    /**
     * Set the music volume.
     *
     * @return music volume, 0.0f meaning muted, 1.0f meaning full volume.
     */
    void setMusicVolume( const float musicVolume );

    /**
     * Load a sound effect file (OGG format).
     *
     * @param name sound file name, not including extension (.ogg which must be lowercase)
     * @return true if the file was found and loaded, false otherwise
     */
    bool loadSound( const std::string &name );

    /**
     * Get a previously loaded sound effect.
     *
     * @param sound name
     * @return Mix_Chunk object, NULL if not loaded
     */
    Mix_Chunk *getSound( const std::string &name );

    /**
     * Play a sound effect.
     *
     * @param name the sound effect name
     * @return the channel the sound is playing on, -1 if not able to play it
     */
    int playSound( const std::string &name );

    /**
     * Get the system current time in milliseconds.
     *
     * @return current system time in milliseconds.
     */
    long long currentTimeMillis();

    /**
     * Get the full path for resource files (images, sounds, music, etc).
     *
     * @param subDir a given subdirectory of the path, blank by default which means the root resource folder.
     */
    std::string getResourcePath( const std::string &subDir = "" );

    /**
     * Stop the game.
     */
    void stopGame()
    {
      _running = false;
    }

  private:
    static Game *_instance;

    SDL_Window    *_window;
    Renderer      *_renderer;
    std::string   _title;
    Rect          _windowRect;
    Uint32        _windowFlags;
    Scene         *_scene;
    bool          _running;

    std::map<std::string, TTF_Font *> _fonts;
    std::map<std::string, Mix_Music *> _music;
    std::map<std::string, Mix_Chunk *> _sounds;
    std::string _backgroundMusicPlaying;
    float _soundVolume;
    float _musicVolume;

    Game( const char *title, const int x, const int y, const int width, const int height );

    Game( const char *title, const int x, const int y, const int width, const int height, const Uint32 windowFlags );

    bool init();

  };

}

#endif //__Game_H_
