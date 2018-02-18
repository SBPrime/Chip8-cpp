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
 * File:   chip8.h
 * Author: SBPrime
 */

#ifndef _CHIP8_H
#define _CHIP8_H

#include <stdint.h>
#include "SdlScreen.h"

#define MEM_SIZE 0x1000
#define REGISTERS 0x10
#define STACK_SIZE 0x20         /* 24 */
#define KEYS 0x10

#define CLOCK_FRQ   60
#define CPU_FRQ     500
#define FONT        0x00

#define S_RPL       REGISTERS   /* 8 */

#define S_SCREEN_W  128
#define S_SCREEN_H  64
#define S_CPU_FRQ   1000
#define S_FONT      0x50

#define ENTRY_POINT 0x200

#define SCREEN_SIZE S_SCREEN_W * S_SCREEN_H

#define C8_KEY0     0x0
#define C8_KEY1     0x1
#define C8_KEY2     0x2
#define C8_KEY3     0x3
#define C8_KEY4     0x4
#define C8_KEY5     0x5
#define C8_KEY6     0x6
#define C8_KEY7     0x7
#define C8_KEY8     0x8
#define C8_KEY9     0x9
#define C8_KEYA     0xA
#define C8_KEYB     0xB
#define C8_KEYC     0xC
#define C8_KEYD     0xD
#define C8_KEYE     0xE
#define C8_KEYF     0xF

enum ErrorCodes {
    EC_Ok,
    EC_IllegalOpcode,
    EC_IllegalAddress,
    EC_StackOverflow,
    EC_StackUnderflow
};

enum BgColors : uint8_t {
    BGBlue = 0,
    BGBlack = 1,
    BGGreen = 2,
    BGRed = 3,
    BGMax = 4
};

class CChip8 {
public:    
    inline bool isSoundOn() { return m_isSoundOn; }
    inline bool hasError() { return m_errorCode != EC_Ok; }
    inline bool isScreenDirty() { return m_isScreenDirty; }
    inline bool isRunning() { return m_isRunning; }
    inline uint16_t getCycles() { return m_cpuCycles; }
    inline BgColors getBackground() { return m_bgcolor; }
    
    CChip8();   
    virtual ~CChip8();
    
    void reset();
    void load(const uint8_t* const data, const uint16_t dataSize);
    void doCycle();

    void setKey(uint8_t keyId, uint8_t keyStatus);
    void draw(CSdlScreen* const screen);
private:
    uint8_t ram[MEM_SIZE];
    uint8_t v[REGISTERS];
    uint8_t rpl[S_RPL];
    
    uint16_t i;
    uint16_t pc;
    
    uint16_t stack[STACK_SIZE];
    uint16_t sp;
    
    uint32_t m_timerBegin;
    float m_timerDelay;
    float m_timerSound;
    
    uint8_t m_keyStatus[KEYS];
    
    uint8_t m_screen[SCREEN_SIZE];
    
    ErrorCodes m_errorCode;   
    BgColors m_bgcolor;
    bool m_hiResMode;
    bool m_isScreenDirty;
    bool m_isRunning;
    bool m_isSoundOn;
    
    uint16_t m_cpuCycles;
    
    void error(ErrorCodes ec);
    bool draw(uint8_t x, uint8_t y, uint8_t h);
    bool drawe(uint8_t x, uint8_t y);
    
    void moveDown(uint8_t lines);
    void moveUp(uint8_t lines);
    void moveLeft();
    void moveRight();
    
    void doTimers();
    void doOp();
    
    void super();
    
    void op0xxx(uint16_t op);
    void op5xxx(uint16_t op);
    void op8xxx(uint16_t op);
    void opDxxx(uint16_t op);
    void opExxx(uint16_t op);
    void opFxxx(uint16_t op);
};

#endif /* _CHIP8_H */