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
 * File:   chip8.cpp
 * Author: SBPrime
 */

#include <string.h>
#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <SDL.h>

#include "chip8.h"
#include "chars.h"

#define OPCODE(n)      ((ram[(n)] << 8) | (ram[(n) + 1]))

CChip8::CChip8() {
    reset();
}

CChip8::~CChip8() {
}

void CChip8::reset() {
    m_errorCode = EC_Ok;
    m_bgcolor = BGBlack;
    m_isRunning = true;
    m_hiResMode = false;
    m_isScreenDirty = false;
    m_cpuCycles = CPU_FRQ;

    i = 0;
    pc = ENTRY_POINT;
    sp = 0;

    m_timerDelay = 0.0f;
    m_timerSound = 0.0f;
    m_timerBegin = SDL_GetTicks();

    memset(ram, 0, MEM_SIZE * sizeof (uint8_t));
    memset(v, 0, REGISTERS * sizeof (uint8_t));
    memset(stack, 0, STACK_SIZE * sizeof (uint16_t));

    memset(m_keyStatus, 0, KEYS * sizeof (uint8_t));
    memset(m_screen, 0, SCREEN_SIZE * sizeof (uint8_t));

    memcpy(&ram[FONT], charset, sizeof (charset));
    memcpy(&ram[S_FONT], s_charset, sizeof (s_charset));
}

void CChip8::load(const uint8_t* data, const uint16_t dataSize) {
    uint16_t toCopy = dataSize;
    if (toCopy + ENTRY_POINT >= MEM_SIZE) {
        toCopy = MEM_SIZE - ENTRY_POINT - 1;
    }
    memcpy(&ram[ENTRY_POINT], data, toCopy);
}

void CChip8::setKey(uint8_t keyId, uint8_t keyStatus) {
    m_keyStatus[keyId] = keyStatus;
}

void CChip8::error(ErrorCodes ec) {
    if (ec == EC_Ok) {
        return;
    }

    m_errorCode = ec;

    std::cout << "Error: ";
    switch (ec) {
        case EC_IllegalOpcode:
            std::cout << "Unknown opcode: 0x"
                    << std::hex << OPCODE(pc);
            break;
        case EC_IllegalAddress:
            std::cout << "Illegal address 0x"
                    << std::hex << pc;
            break;
        case EC_StackOverflow:
            std::cout << "Stack overflow: 0x"
                    << std::hex << sp;
            break;
        case EC_StackUnderflow:
            std::cout << "Stack underflow";
            break;
    }

    std::cout << std::endl;
    std::cout << "PC:\t0x" << std::hex << pc
            << "\tI:\t0x" << std::hex << i
            << "\tSP:\t0x" << std::hex << sp
            << std::endl
            ;
    std::cout << "Registers:" << std::endl;
    for (int i = 0; i < REGISTERS; i++) {
        std::cout << "\t0x" << std::hex << i << ":\t" << std::hex << +v[i];
        if (i % 4 == 3) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "Stack:" << std::endl;
    for (int i = 0; i < STACK_SIZE; i++) {
        std::cout << "\t0x" << std::hex << i << ":\t" << std::hex << stack[i];
        if (i % 4 == 3) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

bool CChip8::draw(uint8_t x, uint8_t y, uint8_t h) {
    bool result = false;
    uint8_t w;
    uint8_t pixel = 0;
    uint16_t ptr = i;

    if (!m_hiResMode) {
        h = h << 1;
        w = 16;
        x = x << 1;
        y = y << 1;
    } else {
        w = 8;
    }

    for (int yline = 0;
            yline < h && ptr < MEM_SIZE && yline + y < S_SCREEN_H;
            yline++) {

        pixel = ram[ptr];
        if (m_hiResMode || (yline % 2 == 1)) {
            ptr++;
        }

        uint8_t bit = 0;
        for (int xline = 0; xline < w && xline + x < S_SCREEN_W; xline++) {
            if ((pixel & (0x80 >> bit)) != 0) {
                uint16_t offset = x + xline + ((y + yline) * S_SCREEN_W);


                result |= m_screen[offset] == 1;
                m_screen[offset] ^= 1;
            }

            if (m_hiResMode || (xline % 2 == 1)) {
                bit++;
            }
        }
    }

    m_isScreenDirty = true;

    return result;
}

bool CChip8::drawe(uint8_t x, uint8_t y) {
    bool result = false;
    uint16_t pixel = 0;
    uint16_t ptr = i;

    for (int yline = 0;
            yline < 16 && ptr + 1 < MEM_SIZE && yline + y < S_SCREEN_H;
            yline++) {

        pixel = (ram[ptr] << 8) | ram[ptr + 1];
        ptr += 2;

        for (int xline = 0; xline < 16 && xline + x < S_SCREEN_W; xline++) {
            if ((pixel & (0x8000 >> xline)) != 0) {
                uint16_t offset = x + xline + ((y + yline) * S_SCREEN_W);


                result |= m_screen[offset] == 1;
                m_screen[offset] ^= 1;
            }
        }
    }

    m_isScreenDirty = true;

    return result;
}

void CChip8::draw(CSdlScreen * const s) {
    if (s == NULL) {
        return;
    }

    s->draw(S_SCREEN_W, S_SCREEN_H, S_SCREEN_W, m_screen);

    m_isScreenDirty = false;
}

void CChip8::super() {
    m_cpuCycles = S_CPU_FRQ;
}

void CChip8::doCycle() {
    if (m_errorCode != EC_Ok) {
        return;
    }

    doOp();
    doTimers();
}

void CChip8::doOp() {

    uint16_t op = OPCODE(pc);

    switch (op & 0xf000) {
        default:
            error(EC_IllegalOpcode);
            return;
        case 0x0000:
            op0xxx(op);
            break;
        case 0x1000: //JP addr
            pc = op & 0x0fff;
            break;
        case 0x2000: //CALL addr
        {
            if (sp == STACK_SIZE) {
                error(EC_StackOverflow);
                return;
            }
            stack[sp++] = pc;
            pc = op & 0x0fff;
            break;
        }
        case 0x3000: //SE Vx, byte
            pc += (v[(op & 0x0f00) >> 8] == (op & 0x00ff)) ? 4 : 2;
            break;
        case 0x4000: //SNE Vx, byte
            pc += (v[(op & 0x0f00) >> 8] != (op & 0x00ff)) ? 4 : 2;
            break;
        case 0x5000:
            op5xxx(op);
            break;
        case 0x6000: //LD Vx, byte
            v[(op & 0x0f00) >> 8] = op & 0x00ff;
            pc += 2;
            break;
        case 0x7000: //ADD Vx, byte
            v[(op & 0x0f00) >> 8] += op & 0x00ff;
            pc += 2;
            break;
        case 0x8000:
            op8xxx(op);
            break;
        case 0x9000: //SNE Vx, Vy
            pc += (v[(op & 0x0f00) >> 8] != v[(op & 0x00f0) >> 4]) ? 4 : 2;
            break;
        case 0xa000: //LD I, addr
            i = op & 0x0fff;
            pc += 2;
            break;
        case 0xb000: //JP V0, addr
            pc = v[0] + (op & 0x0fff);
            break;
        case 0xc000: //RND Vx, byte
            v[(op & 0x0f00) >> 8] = (std::rand() % 0xff) & (op & 0x00ff);
            pc += 2;
            break;
        case 0xd000:
            opDxxx(op);
            break;
        case 0xe000:
            opExxx(op);
            break;
        case 0xf000:
            opFxxx(op);
            break;
    }
}

void CChip8::doTimers() {
    uint32_t now = SDL_GetTicks();
    float delta = CLOCK_FRQ * (now - m_timerBegin) / 1000.0;
    m_timerBegin = now;

    if (m_timerDelay > 0) {
        m_timerDelay -= delta;

        if (m_timerDelay < 0) {
            m_timerDelay = 0.0f;
        }
    }

    if (m_timerSound > 0) {
        m_timerSound -= delta;

        if (m_timerSound < 0) {
            m_timerSound = 0.0f;
        }
    }
    
    m_isSoundOn = m_timerSound >= 1.0;
}

void CChip8::moveDown(uint8_t lines) {
    memmove(&m_screen[lines * S_SCREEN_W], m_screen, (S_SCREEN_H - lines) * S_SCREEN_W);
    memset(m_screen, 0, lines * S_SCREEN_W);
    m_isScreenDirty = true;
}

void CChip8::moveUp(uint8_t lines) {
    memmove(m_screen, &m_screen[lines * S_SCREEN_W], (S_SCREEN_H - lines) * S_SCREEN_W);
    memset(&m_screen[(S_SCREEN_H - lines) * S_SCREEN_W], 0, lines * S_SCREEN_W);
    m_isScreenDirty = true;
}

void CChip8::moveLeft() {
    uint8_t* ptr1 = &m_screen[4];
    uint8_t* ptr2 = m_screen;
    uint8_t* ptr3 = &m_screen[S_SCREEN_W - 5];

    for (int y = 0; y < S_SCREEN_H; y++) {
        memmove(ptr2, ptr1, S_SCREEN_W - 4);
        memset(ptr3, 0, 4);

        ptr1 += S_SCREEN_W;
        ptr2 += S_SCREEN_W;
        ptr3 += S_SCREEN_W;
    }
    m_isScreenDirty = true;
}

void CChip8::moveRight() {
    uint8_t* ptr1 = m_screen;
    uint8_t* ptr2 = &m_screen[4];
    for (int y = 0; y < S_SCREEN_H; y++) {
        memmove(ptr2, ptr1, S_SCREEN_W - 4);
        memset(ptr1, 0, 4);
        ptr1 += S_SCREEN_W;
        ptr2 += S_SCREEN_W;
    }

    m_isScreenDirty = true;
}

void CChip8::op0xxx(uint16_t op) {
    switch (op & 0x00f0) {
        case 0x00c0: //SCD nibble
            super();
            moveDown(op & 0x000f);
            pc += 2;
            return;
        case 0x00b0: //SCU nibble
            super();
            moveUp(op & 0x000f);
            pc += 2;
            return;
    }

    switch (op & 0x0fff) {
        case 0x02a0: //STEPCOL
            m_bgcolor = (BgColors)((m_bgcolor + 1) % BGMax);
            pc += 2;
            return;
    }

    switch (op & 0x00ff) {
        case 0xe0: //CLS
            memset(m_screen, 0, SCREEN_SIZE * sizeof (uint8_t));
            pc += 2;
            return;
        case 0xee: //RET
        {
            if (sp == 0) {
                pc += 2;
                return;
            }
            pc = stack[--sp] + 2;
            return;
        }
        case 0xfb: // SCR
        {
            super();
            moveRight();
            pc += 2;
            return;
        }
        case 0xfc: // SCL
        {
            super();
            moveLeft();
            pc += 2;
            return;
        }
        case 0xfd: // EXIT
            super();
            m_isRunning = false;
            pc += 2;
            return;
        case 0xfe: // LOW
            super();
            m_hiResMode = false;
            pc += 2;
            return;
        case 0xff: // HIGH
            super();
            m_hiResMode = true;
            pc += 2;
            return;
    }

    error(EC_IllegalOpcode);
}

void CChip8::op5xxx(uint16_t op) {
    uint8_t v1 = v[(op & 0x0f00) >> 8];
    uint8_t v2 = v[(op & 0x00f0) >> 4];

    bool result;
    switch (op & 0x000f) {
        default:
        case 0x0://SE Vx, Vy
            result = v1 == v2;
            break;
        case 0x1://SGT Vx, Vy
            result = v1 > v2;
            break;
        case 0x2://SLT Vx, Vy
            result = v1 < v2;
            break;
        case 0x3://SNE Vx, Vy
            result = v1 != v2;
            break;
    }

    pc += result ? 4 : 2;
}

void CChip8::op8xxx(uint16_t op) {
    const uint8_t x = (op & 0x0f00) >> 8;
    const uint8_t y = (op & 0x00f0) >> 4;

    switch (op & 0x000f) {
        default:
            error(EC_IllegalOpcode);
            return;
        case 0x0: //LD Vx, Vy
            v[x] = v[y];
            pc += 2;
            break;
        case 0x1: //OR Vx, Vy
            v[x] |= v[y];
            pc += 2;
            break;
        case 0x2: //AND Vx, Vy
            v[x] &= v[y];
            pc += 2;
            break;
        case 0x3: //XOR Vx, Vy
            v[x] ^= v[y];
            pc += 2;
            break;
        case 0x4: //ADD Vx, Vy
        {
            v[0xf] = v[y] > (0xFF - v[x]) ? 1 : 0;
            v[x] += v[y];
            pc += 2;
            break;
        }
        case 0x5: //SUB Vx, Vy
        {
            v[0xf] = v[x] >= v[y] ? 1 : 0;
            v[x] -= v[y];
            pc += 2;
            break;
        }
        case 0x6: //SHR Vx {, Vy}
            v[0xf] = (v[x] & 0x01) == 0x01 ? 1 : 0;
            v[x] = v[x] >> 1;
            pc += 2;
            break;
        case 0x7: //SUBN Vx, Vy
            v[0xf] = v[y] >= v[x] ? 1 : 0;
            v[x] = v[y] - v[x];
            pc += 2;
            break;
        case 0xe: //SHL Vx {, Vy}
            v[0xf] = (v[x] & 0x80) == 0x80 ? 1 : 0;
            v[x] = v[x] << 1;
            pc += 2;
            break;
    }
}

void CChip8::opDxxx(uint16_t op) {
    uint8_t size = op & 0x000f;

    if (size == 0) { //DRW Vx, Vy, 0
        super();
        v[0xf] = drawe(v[(op & 0x0f00) >> 8], v[(op & 0x00f0) >> 4])
                ? 0x1 : 0x0;
    } else { //DRW Vx, Vy, nibble
        v[0xf] = draw(v[(op & 0x0f00) >> 8], v[(op & 0x00f0) >> 4], size)
                ? 0x1 : 0x0;
    }
    pc += 2;
}

void CChip8::opExxx(uint16_t op) {
    const uint8_t vx = v[(op & 0x0f00) >> 8];

    switch (op & 0x00ff) {
        default:
            error(EC_IllegalOpcode);
            return;
        case 0x9e: //SKP Vx
            pc += m_keyStatus[vx] == 1 ? 4 : 2;
            break;
        case 0xa1: //SKNP Vx
            pc += m_keyStatus[vx] != 1 ? 4 : 2;
            break;
    }
}

void CChip8::opFxxx(uint16_t op) {
    const uint8_t x = (op & 0x0f00) >> 8;

    switch (op & 0x00ff) {
        default:
            error(EC_IllegalOpcode);
            return;
        case 0x07: //LD Vx, DT
            v[x] = (uint8_t) m_timerDelay;
            pc += 2;
            break;
        case 0x0a: //LD Vx, K
        {
            for (int j = 0; j < KEYS; j++) {
                if (m_keyStatus[j] == 0) {
                    continue;
                }

                v[x] = j;
                pc += 2;
                break;
            }

            break;
        }
        case 0x15: //LD ST, Vx
            m_timerDelay = v[x];
            pc += 2;
            break;
        case 0x18: //LD ST, Vx
            m_timerSound = v[x];
            pc += 2;
            break;
        case 0x1e: //ADD I, Vx
            i += v[x];
            v[0xf] = (i & 0xf000) != 0 ? 1 : 0;
            i &= 0xfff;
            pc += 2;
            break;
        case 0x29: //LD F, Vx
            i = FONT + (v[x] & 0xf) * 5;
            pc += 2;
            break;
        case 0x30: //LD XF, Vx
        {
            super();
            i = S_FONT + (v[x] & 0xf) * 10;
            pc += 2;
            break;
        }
        case 0x33: //LD B, Vx
        {
            const uint8_t vx = v[x];
            ram[(i + 0x0) & 0xfff] = vx / 100;
            ram[(i + 0x1) & 0xfff] = (vx % 100) / 10;
            ram[(i + 0x2) & 0xfff] = vx % 10;
            pc += 2;
            break;
        }
        case 0x55: //LD [I], Vx
        {
            for (int j = 0; j <= x; j++) {
                ram[(i + j) & 0xfff] = v[j];
            }
            pc += 2;
            break;
        }
        case 0x65: //LD Vx, [I]
        {
            for (int j = 0; j <= x; j++) {
                v[j] = ram[(i + j) & 0xfff];
            }
            pc += 2;
            break;
        }
        case 0x75: //LD R, Vx
        {
            super();
            for (int j = 0; j <= x; j++) {
                rpl[j] = v[j];
            }
            pc += 2;
            break;
        }
        case 0x85: //LD Vx, R
        {
            super();
            for (int j = 0; j <= x; j++) {
                v[j] = rpl[j];
            }
            pc += 2;
            break;
        }
    }
}
