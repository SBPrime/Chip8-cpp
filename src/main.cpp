/*
 * Copyright (c) 2018, SBPrime <https://github.com/SBPrime/>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   main.cpp
 * Author: SBPrime
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <signal.h>

#include <SDL.h>

#include "chip8.h"
#include "test.h"
#include "SdlScreen.h"
#include "EmuClock.h"

#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480
#define FPS 30
#define SOUND_LEN   1024

CChip8 chip8;
CEmuClock emuClock(&chip8);

CSdlScreen screen;

uint8_t SOUND_BEEP[SOUND_LEN];
uint8_t SOUND_SILENT[SOUND_LEN];

SDL_Window* window = NULL;
SDL_AudioSpec audio;
SDL_Surface* screenSurface = NULL;
SDL_Surface* backSurface = NULL;
SDL_Rect rectTo;

bool isRunning = true;

static void handleSDLEvent(SDL_Event *e) {
    switch (e->type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYUP:
        case SDL_KEYDOWN:
        {
            int down = e->type == SDL_KEYDOWN;
            switch (e->key.keysym.sym) {
                case SDLK_1:
                    chip8.setKey(C8_KEY1, down);
                    break;
                case SDLK_2:
                    chip8.setKey(C8_KEY2, down);
                    break;
                case SDLK_3:
                    chip8.setKey(C8_KEY3, down);
                    break;
                case SDLK_4:
                    chip8.setKey(C8_KEYC, down);
                    break;
                case SDLK_q:
                    chip8.setKey(C8_KEY4, down);
                    break;
                case SDLK_w:
                    chip8.setKey(C8_KEY5, down);
                    break;
                case SDLK_e:
                    chip8.setKey(C8_KEY6, down);
                    break;
                case SDLK_r:
                    chip8.setKey(C8_KEYD, down);
                    break;
                case SDLK_a:
                    chip8.setKey(C8_KEY7, down);
                    break;
                case SDLK_s:
                    chip8.setKey(C8_KEY8, down);
                    break;
                case SDLK_d:
                    chip8.setKey(C8_KEY9, down);
                    break;
                case SDLK_f:
                    chip8.setKey(C8_KEYE, down);
                    break;
                case SDLK_z:
                    chip8.setKey(C8_KEYA, down);
                    break;
                case SDLK_x:
                    chip8.setKey(C8_KEY0, down);
                    break;
                case SDLK_c:
                    chip8.setKey(C8_KEYB, down);
                    break;
                case SDLK_v:
                    chip8.setKey(C8_KEYF, down);
                    break;
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
            }

            break;
        }
        case SDL_WINDOWEVENT:
        {
            if (e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                rectTo.w = e->window.data1,
                rectTo.h = e->window.data2;
            }
            break;
        }
    }
}

void cpuLoop() {
    SDL_Rect rectFrom;
    rectFrom.x = 0;
    rectFrom.y = 0;
    rectFrom.w = S_SCREEN_W;
    rectFrom.h = S_SCREEN_H;
    
    SDL_Event e;
    uint32_t sleep = 1000 / FPS;

    while (!chip8.hasError() && chip8.isRunning() && isRunning) {
        emuClock.tick();

        uint16_t toRun = emuClock.getExecuteCycles();
        for (int i = 0; i < toRun; i++) {
            chip8.doCycle();
        }

        if (chip8.isScreenDirty()) {
            chip8.draw(&screen);
            
            SDL_BlitScaled(backSurface, &rectFrom, 
                           screenSurface, &rectTo);
            SDL_UpdateWindowSurface( window );
        }

        if (SDL_PollEvent(&e)) {
            handleSDLEvent(&e);
        } else {
            SDL_Delay(sleep);
        }
    }

    isRunning = false;
}

/**
 * This method is called when a exit signal is send
 */
static void onExit() {
    isRunning = false;
}

static void fillAudio(void *udata, Uint8 *stream, int len) {
    if (len == 0) {
        return;
    }
    
    SDL_MixAudio(stream, chip8.isSoundOn() ? SOUND_BEEP : SOUND_SILENT, len, SDL_MIX_MAXVOLUME);
}

static int initAudio() {
    for (int i = 0;i<SOUND_LEN;i++) {
        SOUND_BEEP[i] = (i % 128) * 2;
    }
    
    
    /* Set the audio format */
    audio.freq = 22050;
    audio.format = AUDIO_U8; //AUDIO_S16;
    audio.channels = 1;    /* 1 = mono, 2 = stereo */
    audio.samples = SOUND_LEN;  /* Good low-latency value for callback */
    audio.callback = fillAudio;
    audio.userdata = NULL;

    /* Open the audio device, forcing the desired format */
    if ( SDL_OpenAudio(&audio, NULL) < 0 ) {
        std::cout << "Couldn't open audio: " << SDL_GetError() << std::endl;
        return -1;
    }
}

int main(int argc, char**argv) {
    SDL_Event e;
    SDL_DisplayMode mode;
    int status;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Chip8",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    initAudio();
    SDL_PauseAudio(0);

    rectTo.x = 0;
    rectTo.y = 0;
    SDL_GetWindowSize(window, &rectTo.w, &rectTo.h);
    
    screenSurface = SDL_GetWindowSurface(window);
    backSurface = SDL_CreateRGBSurface(0,
            S_SCREEN_W, S_SCREEN_H, 24,
            0, 0, 0, 0);
    screen.init(backSurface->pixels);

    SDL_UpdateWindowSurface(window);
    atexit(onExit);
    signal(SIGINT, exit);

    std::srand(std::time(NULL));


    chip8.reset();
    chip8.load(__TEST, sizeof (__TEST));

    emuClock.init();
    cpuLoop();

    if (backSurface) {
        SDL_FreeSurface(backSurface);
        backSurface = NULL;
    }

    if (window != NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_CloseAudio();
    SDL_Quit();

    return 0;
}
