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
 * File:   CEmuClock.cpp
 * Author: SBPrime
 */

#include "EmuClock.h"
#include <iostream>
#include <SDL.h>

CEmuClock::CEmuClock(CChip8* chip) {
    m_chip8 = chip;
}

CEmuClock::~CEmuClock() {
}

void CEmuClock::init() {
    m_cpuCurrentCycles = m_chip8->getCycles();
    m_toRunCycles = (uint16_t) (m_cpuCurrentCycles / (1000.0 / CPU_SLEEP));

    m_currentWait = 0;
    m_timeEnter = SDL_GetTicks();
}

void CEmuClock::tick() {
    uint32_t now = SDL_GetTicks();
    uint32_t deltaMilis = now - m_timeEnter;
    m_timeEnter = now;

    uint32_t currentCycles = m_chip8->getCycles();
    bool updateCpuCucles = currentCycles != m_cpuCurrentCycles;
    if (!updateCpuCucles && m_currentWait <= 0) {
        updateCpuCucles = CPU_SLEEP < deltaMilis;
    }

    if (updateCpuCucles) {
        m_cpuCurrentCycles = currentCycles;
        m_toRunCycles = (uint16_t) (m_cpuCurrentCycles / (1000 / (deltaMilis > CPU_SLEEP ? deltaMilis : CPU_SLEEP)));
    }

    m_currentWait -= deltaMilis;
}

uint16_t CEmuClock::getExecuteCycles() {
    if (m_currentWait > 0) {
        return 0;
    }
    
    m_currentWait += CPU_SLEEP;
    
    return m_toRunCycles;
}
