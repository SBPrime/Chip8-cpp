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
 * File:   SdlScreen.cpp
 * Author: SBPrime
 */

#include "SdlScreen.h"
#include <stdint.h>
#include <iostream>

CSdlScreen::CSdlScreen() {
}

CSdlScreen::~CSdlScreen() {
}

void CSdlScreen::draw(uint8_t w, uint8_t h, uint8_t stride, const uint8_t * const buff) {
    const uint8_t* ptr = buff;
    uint8_t* pixels = m_sdlBuffer;

    for (int i = 0; i < h; i++) {
        const uint8_t* lptr = ptr;
        ptr += stride;

        for (int j = 0; j < w; j++) {
            uint8_t v = *lptr != 0 ? 0xff : 0x00;
            *pixels = v;    pixels++;
            *pixels = v;    pixels++;
            *pixels = v;    pixels++;

            lptr++;
        }
    }
}

void CSdlScreen::init(void* pixels) {
    m_sdlBuffer = (uint8_t*)pixels;
}
