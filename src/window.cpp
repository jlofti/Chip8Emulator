#include "../include/window.h"

Window_t::Window_t()
{
}

Window_t::~Window_t()
{
}

void Window_t::start()
{
    // Init SDL Window
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL Video failed to initialise: %s\n", SDL_GetError());
        printf("SDL Video failed init");
    }

    if (SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr, "SDL Audio failed to initialise: %s\n", SDL_GetError());
        printf("SDL Audio failed init");
    }

    // Create the window
    SDL_CreateWindowAndRenderer(WIDTH * SCALE, HEIGHT * SCALE, 0, &window, &renderer);

    if (window == NULL)
    {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        printf("Window failed init");
    }

    SDL_SetWindowTitle(window, "Chip 8 Emulator");

    SDL_AudioSpec audioSpec;
    SDL_zero(audioSpec);
    audioSpec.freq = AUDIO_FREQ;
    audioSpec.format = AUDIO_S16SYS;
    audioSpec.channels = AUDIO_CHANNELS;
    audioSpec.samples = AUDIO_SAMPLES;
    audioSpec.callback = NULL;

    audio = SDL_OpenAudioDevice(NULL, 0, &audioSpec, NULL, 0);
}

void Window_t::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    update();
}

void Window_t::destroy()
{
    SDL_DestroyWindow(window);
    SDL_CloseAudioDevice(audio);
    SDL_Quit();
}

bool Window_t::poll(SDL_Event &e_)
{
    SDL_PollEvent(&e_);
    if (e_.type == SDL_QUIT)
    {
        return 0;
    }

    return 1;
}

void Window_t::setPixel()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Window_t::clearPixel()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Window_t::fill(const int &x_, const int &y_)
{
    SDL_Rect rect;
    rect.x = x_ * SCALE;
    rect.y = y_ * SCALE;
    rect.w = 1 * SCALE;
    rect.h = 1 * SCALE;

    SDL_RenderFillRect(renderer, &rect);
};

void Window_t::update()
{
    SDL_RenderPresent(renderer);
}

void Window_t::playSound()
{
    audioPlaying = true;
    queueAudio();
    SDL_PauseAudioDevice(audio, 0);
}

void Window_t::pauseSound()
{
    if (audioPlaying)
    {
        SDL_PauseAudioDevice(audio, 1);
        audioPlaying = false;
    }
}

void Window_t::queueAudio()
{
    float x = 0;
    for (int i = 0; i < AUDIO_FREQ * AUDIO_DUR_SEC; i++)
    {
        x += .010f;
        int16_t samp = sin(x) * AUDIO_GAIN;
        SDL_QueueAudio(audio, &samp, sizeof(samp));
    }
}
