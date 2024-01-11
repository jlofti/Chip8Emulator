#pragma once
#include <functional>

#ifdef _WIN32
#include <SDL/SDL.h> /* Windows-specific SDL2 library */
#else
#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#endif

#define WIDTH 64
#define HEIGHT 32
#define SCALE 20

#define AUDIO_FREQ (44100 * 2)
#define AUDIO_SAMPLES 1024
#define AUDIO_CHANNELS 1
#define AUDIO_DUR_SEC 1
#define AUDIO_GAIN 10000

class Window_t
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_AudioDeviceID audio;
    bool audioPlaying = false;

public:
    Window_t();
    ~Window_t();
    void setPixel();
    void clearPixel();
    void fill(const int &x_, const int &y_);
    void update();
    void start();
    void clear();
    void destroy();
    bool poll(SDL_Event &e_);
    void playSound();
    void pauseSound();
    void queueAudio();
};