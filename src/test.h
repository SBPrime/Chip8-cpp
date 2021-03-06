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
 * File:   test.h
 * Author: SBPrime
 */

#ifndef _TEST_H
#define _TEST_H


/**
 * Roms downlaoded from https://www.zophar.net/pdroms/chip8.html
 */
const uint8_t __PONG[] = {
/*   0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f    */  
  0x6a, 0x02, 0x6b, 0x0c, 0x6c, 0x3f, 0x6d, 0x0c, 0xa2, 0xea, 0xda, 0xb6, 0xdc, 0xd6, 0x6e, 0x00,   //0x200-0x20f
  0x22, 0xd4, 0x66, 0x03, 0x68, 0x02, 0x60, 0x60, 0xf0, 0x15, 0xf0, 0x07, 0x30, 0x00, 0x12, 0x1a,   //0x210-0x21f
  0xc7, 0x17, 0x77, 0x08, 0x69, 0xff, 0xa2, 0xf0, 0xd6, 0x71, 0xa2, 0xea, 0xda, 0xb6, 0xdc, 0xd6,   //0x220-0x22f
  0x60, 0x01, 0xe0, 0xa1, 0x7b, 0xfe, 0x60, 0x04, 0xe0, 0xa1, 0x7b, 0x02, 0x60, 0x1f, 0x8b, 0x02,   //0x230-0x23f
  0xda, 0xb6, 0x60, 0x0c, 0xe0, 0xa1, 0x7d, 0xfe, 0x60, 0x0d, 0xe0, 0xa1, 0x7d, 0x02, 0x60, 0x1f,   //0x240-0x24f
  0x8d, 0x02, 0xdc, 0xd6, 0xa2, 0xf0, 0xd6, 0x71, 0x86, 0x84, 0x87, 0x94, 0x60, 0x3f, 0x86, 0x02,   //0x250-0x25f
  0x61, 0x1f, 0x87, 0x12, 0x46, 0x02, 0x12, 0x78, 0x46, 0x3f, 0x12, 0x82, 0x47, 0x1f, 0x69, 0xff,   //0x260-0x26f
  0x47, 0x00, 0x69, 0x01, 0xd6, 0x71, 0x12, 0x2a, 0x68, 0x02, 0x63, 0x01, 0x80, 0x70, 0x80, 0xb5,   //0x270-0x27f
  0x12, 0x8a, 0x68, 0xfe, 0x63, 0x0a, 0x80, 0x70, 0x80, 0xd5, 0x3f, 0x01, 0x12, 0xa2, 0x61, 0x02,   //0x280-0x28f
  0x80, 0x15, 0x3f, 0x01, 0x12, 0xba, 0x80, 0x15, 0x3f, 0x01, 0x12, 0xc8, 0x80, 0x15, 0x3f, 0x01,   //0x290-0x29f
  0x12, 0xc2, 0x60, 0x20, 0xf0, 0x18, 0x22, 0xd4, 0x8e, 0x34, 0x22, 0xd4, 0x66, 0x3e, 0x33, 0x01,   //0x2a0-0x2af
  0x66, 0x03, 0x68, 0xfe, 0x33, 0x01, 0x68, 0x02, 0x12, 0x16, 0x79, 0xff, 0x49, 0xfe, 0x69, 0xff,   //0x2b0-0x2bf
  0x12, 0xc8, 0x79, 0x01, 0x49, 0x02, 0x69, 0x01, 0x60, 0x04, 0xf0, 0x18, 0x76, 0x01, 0x46, 0x40,   //0x2c0-0x2cf
  0x76, 0xfe, 0x12, 0x6c, 0xa2, 0xf2, 0xfe, 0x33, 0xf2, 0x65, 0xf1, 0x29, 0x64, 0x14, 0x65, 0x00,   //0x2d0-0x2df
  0xd4, 0x55, 0x74, 0x15, 0xf2, 0x29, 0xd4, 0x55, 0x00, 0xee, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,   //0x2e0-0x2ef
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00                                                                //0x2f0-0x2ff
};

unsigned char __ANT[] = {
  0x12, 0x0e, 0x5b, 0x20, 0x41, 0x6e, 0x74, 0x20, 0x76, 0x31, 0x2e, 0x30,
  0x20, 0x5d, 0x00, 0xff, 0x60, 0xfe, 0x61, 0x00, 0xaa, 0x10, 0xf1, 0x55,
  0x22, 0x4c, 0x23, 0x5c, 0x65, 0x00, 0x6a, 0x01, 0x6b, 0x00, 0x6d, 0x00,
  0x6e, 0x00, 0x23, 0x68, 0x3f, 0x00, 0x13, 0xc6, 0x45, 0xfd, 0x12, 0xd0,
  0x47, 0xcc, 0x22, 0x7a, 0x41, 0xfb, 0x14, 0xd0, 0x41, 0xfc, 0x15, 0x68,
  0x41, 0xfa, 0x15, 0xe0, 0x41, 0xf9, 0x16, 0x2c, 0x60, 0x02, 0x37, 0xcc,
  0x24, 0xc6, 0x12, 0x26, 0x6e, 0x00, 0xa7, 0xf2, 0xfe, 0x1e, 0x60, 0x2e,
  0xf0, 0x55, 0x70, 0x09, 0x61, 0x7c, 0xaa, 0xe8, 0xd1, 0x04, 0x60, 0x01,
  0x24, 0xc0, 0x60, 0x02, 0x24, 0xc6, 0x3e, 0x1f, 0x00, 0xfc, 0x7e, 0x01,
  0x3e, 0x20, 0x12, 0x4e, 0x60, 0x04, 0x61, 0x04, 0xaa, 0xf8, 0xd0, 0x10,
  0x00, 0xee, 0x4b, 0x00, 0x22, 0xe6, 0x7b, 0xff, 0xaa, 0x12, 0xf1, 0x65,
  0xa7, 0xf2, 0xfe, 0x1e, 0xf0, 0x55, 0x7e, 0x01, 0x62, 0x1f, 0x8e, 0x22,
  0x41, 0xfe, 0x12, 0xa4, 0x41, 0xff, 0x12, 0xae, 0x70, 0x09, 0x62, 0x7c,
  0xaa, 0xe8, 0xfd, 0x1e, 0xd2, 0x04, 0x00, 0xee, 0x70, 0x07, 0x61, 0x7c,
  0xab, 0x38, 0xd1, 0x04, 0x00, 0xee, 0x61, 0x00, 0x4b, 0x02, 0x61, 0x08,
  0x4b, 0x01, 0x61, 0x10, 0x4b, 0x00, 0x61, 0x18, 0xab, 0x18, 0xf1, 0x1e,
  0x61, 0x7c, 0x70, 0x01, 0xd1, 0x08, 0x70, 0x08, 0xaa, 0xe8, 0xfd, 0x1e,
  0xd1, 0x04, 0x00, 0xee, 0x47, 0xcc, 0x73, 0xfc, 0xad, 0x5c, 0xd3, 0x40,
  0x33, 0x00, 0x73, 0xfc, 0x33, 0x00, 0xd3, 0x40, 0x43, 0x00, 0x65, 0x00,
  0x12, 0x30, 0xaa, 0x10, 0xf1, 0x65, 0x70, 0x02, 0x40, 0xfe, 0x23, 0x1a,
  0xf0, 0x55, 0xa8, 0x12, 0x41, 0x01, 0xa9, 0x10, 0xf0, 0x1e, 0xf1, 0x65,
  0xaa, 0x12, 0xf1, 0x55, 0x62, 0xf0, 0x82, 0x17, 0x4f, 0x00, 0x13, 0x16,
  0x41, 0xfe, 0x13, 0x24, 0x41, 0xff, 0x13, 0x28, 0x41, 0xfd, 0x13, 0x2c,
  0x13, 0x58, 0x8b, 0x10, 0x00, 0xee, 0x61, 0x01, 0x60, 0x00, 0xaa, 0x10,
  0xf1, 0x55, 0x00, 0xee, 0x6b, 0x0c, 0x00, 0xee, 0x6b, 0x04, 0x00, 0xee,
  0x6b, 0x01, 0x65, 0xfd, 0x84, 0x00, 0x74, 0xf9, 0x60, 0x70, 0xab, 0xdc,
  0xd0, 0x40, 0x60, 0x04, 0x24, 0xc0, 0x63, 0x60, 0xad, 0x5c, 0xd3, 0x40,
  0x60, 0x02, 0x24, 0xc0, 0x60, 0x02, 0x24, 0xc6, 0x60, 0x01, 0x24, 0xc0,
  0x60, 0x70, 0xab, 0xdc, 0xd0, 0x40, 0x00, 0xee, 0x6b, 0x01, 0x00, 0xee,
  0x66, 0x00, 0x68, 0x2e, 0x6c, 0x00, 0xaa, 0x68, 0xd6, 0x80, 0x00, 0xee,
  0x67, 0x00, 0x24, 0x2e, 0x23, 0xde, 0x82, 0xc0, 0x60, 0x0c, 0xe0, 0xa1,
  0x24, 0x66, 0x60, 0x03, 0xe0, 0xa1, 0x24, 0x86, 0x80, 0x60, 0x37, 0xcc,
  0x86, 0x74, 0x81, 0x80, 0x88, 0x94, 0xaa, 0x68, 0xf2, 0x1e, 0xd0, 0x10,
  0x47, 0xcc, 0x00, 0xfc, 0xaa, 0x68, 0xfc, 0x1e, 0xd6, 0x80, 0x00, 0xee,
  0x67, 0x00, 0x24, 0x2e, 0x23, 0xde, 0x82, 0xc0, 0x60, 0x0c, 0xe0, 0xa1,
  0x24, 0x66, 0x47, 0xcc, 0x67, 0x04, 0x60, 0x03, 0xe0, 0xa1, 0x24, 0x86,
  0x80, 0x60, 0x86, 0x74, 0x81, 0x80, 0x88, 0x94, 0xaa, 0x68, 0xf2, 0x1e,
  0xd0, 0x10, 0xaa, 0x68, 0xfc, 0x1e, 0xd6, 0x80, 0x00, 0xee, 0x61, 0x00,
  0xd6, 0x80, 0x60, 0x02, 0x24, 0xc0, 0x60, 0x02, 0x24, 0xc6, 0x71, 0x01,
  0x31, 0x07, 0x13, 0xc8, 0x60, 0x1e, 0x24, 0xc6, 0x00, 0xfd, 0x60, 0x0a,
  0xe0, 0x9e, 0x14, 0x0c, 0x4a, 0x00, 0x00, 0xee, 0x4a, 0x01, 0x23, 0xfe,
  0x6a, 0x02, 0x69, 0xfc, 0xaa, 0x0e, 0xf0, 0x65, 0x58, 0x00, 0x00, 0xee,
  0x6a, 0x00, 0x69, 0xfe, 0x00, 0xee, 0x60, 0x02, 0x24, 0xc0, 0x80, 0x80,
  0x70, 0xec, 0xaa, 0x0e, 0xf0, 0x55, 0x00, 0xee, 0x4a, 0x02, 0x14, 0x28,
  0x80, 0x60, 0x24, 0x52, 0x98, 0x00, 0x14, 0x24, 0x80, 0x60, 0x70, 0x0c,
  0x24, 0x52, 0x98, 0x00, 0x14, 0x24, 0x00, 0xee, 0x6a, 0x01, 0x00, 0xee,
  0x6a, 0x00, 0x69, 0xfe, 0x00, 0xee, 0x4a, 0x02, 0x00, 0xee, 0x60, 0x04,
  0x49, 0xfe, 0x60, 0x02, 0x89, 0x00, 0x80, 0x60, 0x24, 0x52, 0x98, 0x00,
  0x69, 0x00, 0x80, 0x60, 0x70, 0x0c, 0x24, 0x52, 0x98, 0x00, 0x69, 0x00,
  0x49, 0x04, 0x6a, 0x00, 0x00, 0xee, 0x80, 0x56, 0x80, 0x56, 0x80, 0xe4,
  0x61, 0x1f, 0x80, 0x12, 0xa7, 0xf2, 0xf0, 0x1e, 0xf0, 0x65, 0x81, 0x00,
  0x00, 0xee, 0x60, 0x00, 0x4c, 0x00, 0x60, 0x20, 0x8c, 0x00, 0x80, 0x60,
  0x70, 0x10, 0x24, 0x52, 0x80, 0x85, 0x4f, 0x00, 0x00, 0xee, 0x67, 0x04,
  0x46, 0x38, 0x67, 0xcc, 0x91, 0x80, 0x14, 0xb2, 0x00, 0xee, 0x60, 0x40,
  0x4c, 0x40, 0x60, 0x60, 0x8c, 0x00, 0x46, 0x00, 0x00, 0xee, 0x80, 0x60,
  0x70, 0xfc, 0x24, 0x52, 0x80, 0x85, 0x4f, 0x00, 0x00, 0xee, 0x67, 0xfc,
  0x91, 0x80, 0x14, 0xa6, 0x00, 0xee, 0x80, 0x60, 0x24, 0x52, 0x80, 0x87,
  0x4f, 0x00, 0x69, 0xfc, 0x00, 0xee, 0x80, 0x60, 0x70, 0x0c, 0x24, 0x52,
  0x80, 0x87, 0x4f, 0x00, 0x69, 0xfc, 0x00, 0xee, 0xf0, 0x18, 0x80, 0x5e,
  0x14, 0xc6, 0xf0, 0x15, 0xf0, 0x07, 0x30, 0x00, 0x14, 0xc8, 0x00, 0xee,
  0x24, 0xe2, 0x24, 0xf6, 0x23, 0x98, 0x3f, 0x00, 0x13, 0xc6, 0x25, 0x10,
  0x46, 0x70, 0x15, 0x3c, 0x14, 0xd4, 0x60, 0x01, 0x24, 0xc0, 0xaa, 0x68,
  0xfc, 0x1e, 0xd6, 0x80, 0x76, 0xfc, 0xd6, 0x80, 0x36, 0x00, 0x14, 0xe2,
  0x00, 0xee, 0x63, 0x09, 0x64, 0x25, 0x65, 0x04, 0x60, 0x18, 0xab, 0x3c,
  0xd0, 0x30, 0x70, 0x14, 0xd0, 0x40, 0x70, 0x14, 0xd0, 0x30, 0x70, 0x14,
  0xd0, 0x40, 0x00, 0xee, 0x43, 0x09, 0x65, 0x04, 0x43, 0x25, 0x65, 0xfc,
  0xab, 0x3c, 0x60, 0x18, 0x81, 0x30, 0x83, 0x54, 0xd0, 0x10, 0xd0, 0x30,
  0x60, 0x40, 0xd0, 0x10, 0xd0, 0x30, 0x60, 0x2c, 0x81, 0x40, 0x84, 0x55,
  0xd0, 0x10, 0xd0, 0x40, 0x60, 0x54, 0xd0, 0x10, 0xd0, 0x40, 0x00, 0xee,
  0x7d, 0x04, 0x00, 0xfc, 0xa7, 0xf2, 0xfe, 0x1e, 0x60, 0x2a, 0xf0, 0x55,
  0x70, 0x09, 0x61, 0x7c, 0xaa, 0xe8, 0xfd, 0x1e, 0xd1, 0x04, 0x60, 0x01,
  0x24, 0xc0, 0x60, 0x02, 0x24, 0xc6, 0x7e, 0x01, 0x4e, 0x20, 0x6e, 0x00,
  0x76, 0xfc, 0x36, 0x00, 0x15, 0x3e, 0x12, 0x26, 0x24, 0xe2, 0x25, 0x7a,
  0x25, 0x8c, 0x23, 0x98, 0x3f, 0x00, 0x13, 0xc6, 0x46, 0x70, 0x15, 0x3c,
  0x15, 0x6c, 0x60, 0x70, 0x61, 0x0f, 0x62, 0xfe, 0x63, 0x00, 0xaa, 0x14,
  0xf3, 0x55, 0xab, 0x5c, 0xd0, 0x10, 0x00, 0xee, 0xaa, 0x14, 0xf3, 0x65,
  0x84, 0x20, 0x42, 0x02, 0x64, 0xfe, 0x42, 0xfe, 0x64, 0x02, 0x41, 0x11,
  0x25, 0xcc, 0x41, 0x21, 0x25, 0xd4, 0x82, 0x40, 0x84, 0x30, 0x73, 0x20,
  0x43, 0x80, 0x63, 0x00, 0xab, 0x5c, 0xf4, 0x1e, 0x84, 0x10, 0x81, 0x24,
  0x85, 0x00, 0x70, 0xfc, 0xd5, 0x40, 0xab, 0x5c, 0xf3, 0x1e, 0x35, 0x00,
  0xd0, 0x10, 0xaa, 0x14, 0xf3, 0x55, 0x35, 0x00, 0x00, 0xee, 0x15, 0x7a,
  0x64, 0x04, 0x42, 0xfc, 0x64, 0xfe, 0x00, 0xee, 0x64, 0xfc, 0x42, 0x04,
  0x64, 0x02, 0x44, 0x02, 0xf4, 0x18, 0x00, 0xee, 0x25, 0xf0, 0x25, 0xfc,
  0x23, 0x98, 0x3f, 0x00, 0x13, 0xc6, 0x36, 0x70, 0x15, 0xe2, 0x15, 0x3c,
  0x63, 0x70, 0x64, 0x0f, 0x65, 0x00, 0xad, 0x7c, 0xd3, 0x40, 0x00, 0xee,
  0x80, 0x30, 0x70, 0x0c, 0x24, 0x52, 0x71, 0xf9, 0x54, 0x10, 0x26, 0x22,
  0x80, 0x30, 0x73, 0xfc, 0xad, 0x7c, 0xf5, 0x1e, 0x75, 0x20, 0xd0, 0x10,
  0xad, 0x7c, 0xf5, 0x1e, 0x30, 0x00, 0xd3, 0x40, 0x30, 0x00, 0x00, 0xee,
  0x15, 0xf0, 0x81, 0x40, 0x74, 0x04, 0x60, 0x02, 0xf0, 0x18, 0x00, 0xee,
  0x24, 0xe2, 0x26, 0x5c, 0x6e, 0x00, 0x26, 0x68, 0x27, 0x48, 0x3f, 0x00,
  0x13, 0xc6, 0x46, 0x70, 0x17, 0xd6, 0x26, 0x46, 0x60, 0x03, 0x24, 0xc6,
  0x16, 0x34, 0x4d, 0x00, 0x16, 0xd0, 0x4d, 0x02, 0x16, 0xf6, 0x4d, 0x04,
  0x16, 0xa8, 0x4d, 0x06, 0x16, 0x80, 0x4d, 0x08, 0x17, 0x2e, 0x17, 0x40,
  0x63, 0x68, 0x64, 0x27, 0x65, 0x00, 0xab, 0xdc, 0xd3, 0x40, 0x00, 0xee,
  0x6b, 0x00, 0x65, 0x00, 0xaa, 0x54, 0xfe, 0x1e, 0xf0, 0x65, 0x8d, 0x00,
  0x7e, 0x01, 0x4e, 0x14, 0x6e, 0x00, 0x4d, 0x08, 0x17, 0x1c, 0x00, 0xee,
  0x64, 0x27, 0x82, 0x50, 0x75, 0x20, 0x45, 0x40, 0x65, 0x00, 0x80, 0x30,
  0x73, 0x04, 0xac, 0xdc, 0xf2, 0x1e, 0x40, 0x48, 0xab, 0xdc, 0xd0, 0x40,
  0xac, 0xdc, 0xf5, 0x1e, 0x43, 0x68, 0xab, 0xdc, 0xd3, 0x40, 0x33, 0x68,
  0x00, 0xee, 0x16, 0x68, 0x64, 0x27, 0x82, 0x50, 0x75, 0x20, 0x45, 0x40,
  0x65, 0x00, 0x80, 0x30, 0x73, 0xfc, 0xad, 0x1c, 0xf2, 0x1e, 0x40, 0x68,
  0xab, 0xdc, 0xd0, 0x40, 0xad, 0x1c, 0xf5, 0x1e, 0x43, 0x48, 0xab, 0xdc,
  0xd3, 0x40, 0x33, 0x48, 0x00, 0xee, 0x16, 0x68, 0xaa, 0x18, 0xfb, 0x1e,
  0xf2, 0x65, 0xab, 0xdc, 0xf5, 0x1e, 0xd3, 0x40, 0xab, 0xdc, 0xf2, 0x1e,
  0xd0, 0x10, 0x83, 0x00, 0x84, 0x10, 0x85, 0x20, 0x60, 0x01, 0x45, 0x20,
  0x24, 0xc0, 0x7b, 0x03, 0x3b, 0x1e, 0x00, 0xee, 0x16, 0x68, 0xaa, 0x36,
  0xfb, 0x1e, 0xf2, 0x65, 0xab, 0xdc, 0xf5, 0x1e, 0xd3, 0x40, 0xab, 0xdc,
  0xf2, 0x1e, 0xd0, 0x10, 0x83, 0x00, 0x84, 0x10, 0x85, 0x20, 0x60, 0x01,
  0x45, 0x20, 0x24, 0xc0, 0x7b, 0x03, 0x3b, 0x1e, 0x00, 0xee, 0x16, 0x68,
  0x85, 0x30, 0x75, 0xf0, 0xad, 0x5c, 0xd5, 0x40, 0x60, 0x01, 0x24, 0xc0,
  0x60, 0x01, 0x24, 0xc0, 0x00, 0xee, 0x80, 0x50, 0x75, 0xfc, 0xad, 0x5c,
  0xd0, 0x40, 0x30, 0x00, 0xd5, 0x40, 0x30, 0x00, 0x00, 0xee, 0x16, 0x68,
  0x75, 0x01, 0x35, 0x06, 0x00, 0xee, 0x16, 0x68, 0x67, 0x00, 0x27, 0xa4,
  0x27, 0x72, 0x82, 0xc0, 0x60, 0x0c, 0xe0, 0xa1, 0x27, 0xba, 0x60, 0x03,
  0xe0, 0xa1, 0x27, 0xc6, 0x80, 0x60, 0x86, 0x74, 0x81, 0x80, 0x88, 0x94,
  0xaa, 0x68, 0xf2, 0x1e, 0xd0, 0x10, 0xaa, 0x68, 0xfc, 0x1e, 0xd6, 0x80,
  0x00, 0xee, 0x60, 0x0a, 0xe0, 0x9e, 0x17, 0x90, 0x4a, 0x00, 0x00, 0xee,
  0x60, 0x02, 0x4a, 0x01, 0x24, 0xc0, 0x6a, 0x02, 0x69, 0xfc, 0x38, 0x1a,
  0x00, 0xee, 0x6a, 0x00, 0x69, 0xfe, 0x00, 0xee, 0x4a, 0x02, 0x17, 0x9e,
  0x48, 0x2e, 0x17, 0x9a, 0x00, 0xee, 0x6a, 0x01, 0x00, 0xee, 0x6a, 0x00,
  0x69, 0xfe, 0x00, 0xee, 0x4a, 0x02, 0x00, 0xee, 0x60, 0x04, 0x49, 0xfe,
  0x60, 0x02, 0x89, 0x00, 0x48, 0x2e, 0x69, 0x00, 0x49, 0x04, 0x6a, 0x00,
  0x00, 0xee, 0x60, 0x00, 0x4c, 0x00, 0x60, 0x20, 0x8c, 0x00, 0x67, 0x04,
  0x00, 0xee, 0x60, 0x40, 0x4c, 0x40, 0x60, 0x60, 0x8c, 0x00, 0x46, 0x00,
  0x00, 0xee, 0x67, 0xfc, 0x00, 0xee, 0x60, 0x01, 0xf0, 0x75, 0x60, 0x02,
  0x24, 0xc0, 0x24, 0xc6, 0x60, 0x04, 0x24, 0xc0, 0x24, 0xc6, 0x60, 0x08,
  0x24, 0xc0, 0x60, 0x1e, 0x24, 0xc6, 0x00, 0xe0, 0x00, 0xfd, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x04, 0x26, 0x04, 0x22, 0x04,
  0x1e, 0x04, 0x1a, 0x04, 0x16, 0x08, 0x2e, 0xfe, 0x16, 0x08, 0x1a, 0x04,
  0x1e, 0x04, 0x22, 0x04, 0x26, 0x04, 0x2a, 0x10, 0x2a, 0xfd, 0x22, 0x03,
  0x22, 0xff, 0x22, 0x08, 0x26, 0x10, 0x2e, 0xfe, 0x26, 0x04, 0x2a, 0x04,
  0x2a, 0xff, 0x2a, 0x06, 0x2a, 0xff, 0x2a, 0x06, 0x26, 0x0a, 0x26, 0x06,
  0x2e, 0xfe, 0x26, 0x04, 0x22, 0x04, 0x1e, 0x03, 0x1e, 0xfd, 0x1a, 0x04,
  0x16, 0x08, 0x1a, 0xff, 0x32, 0xfe, 0x2a, 0x06, 0x2a, 0x1c, 0x26, 0x04,
  0x26, 0xfc, 0x1e, 0x04, 0x2e, 0xfe, 0x1a, 0x05, 0x16, 0x04, 0x2e, 0xfe,
  0x26, 0x08, 0x26, 0xff, 0x26, 0xff, 0x1a, 0x04, 0x16, 0x08, 0x16, 0xfd,
  0x2e, 0x0e, 0x16, 0x08, 0x2e, 0xfe, 0x16, 0x04, 0x2e, 0xfe, 0x16, 0x03,
  0x2e, 0xfe, 0x16, 0x04, 0x16, 0xfd, 0x2e, 0xfe, 0x26, 0x08, 0x2e, 0x06,
  0x2a, 0x04, 0x26, 0x04, 0x22, 0x04, 0x1e, 0x04, 0x1a, 0x04, 0x16, 0x04,
  0x32, 0xff, 0x32, 0xff, 0x32, 0xff, 0x32, 0xff, 0x2e, 0x08, 0x1e, 0x04,
  0x22, 0x04, 0x26, 0x04, 0x2a, 0x04, 0x32, 0xfe, 0x2e, 0x04, 0x2e, 0xfd,
  0x2a, 0x04, 0x16, 0x03, 0x2a, 0x1c, 0x26, 0x04, 0x26, 0xfb, 0x32, 0xfe,
  0x2a, 0x04, 0x26, 0x04, 0x22, 0x04, 0x1e, 0x04, 0x1a, 0x04, 0x16, 0x04,
  0x1a, 0xff, 0x22, 0xff, 0x2a, 0xff, 0x26, 0x04, 0x1e, 0x04, 0x32, 0xfe,
  0x16, 0x03, 0x32, 0xfe, 0x1e, 0x03, 0x32, 0xfe, 0x16, 0x03, 0x16, 0xfd,
  0x32, 0xfe, 0x1e, 0x03, 0x32, 0xfe, 0x16, 0x03, 0x2e, 0xff, 0x2e, 0xff,
  0x2e, 0xff, 0x2e, 0x08, 0x2a, 0x04, 0x16, 0x06, 0x2e, 0x04, 0x2a, 0x04,
  0x26, 0x04, 0x22, 0x04, 0x1e, 0x04, 0x1a, 0x04, 0x16, 0x08, 0x16, 0xfa,
  0x2e, 0x04, 0x2e, 0xfd, 0x22, 0x03, 0x1e, 0x04, 0x2e, 0x02, 0x26, 0x02,
  0x16, 0x03, 0x1a, 0x02, 0x26, 0x05, 0x26, 0xff, 0x2e, 0x06, 0x1a, 0x03,
  0x1e, 0x03, 0x22, 0x06, 0x26, 0x04, 0x26, 0xfd, 0x16, 0x06, 0x32, 0xfe,
  0x32, 0xff, 0x2e, 0x06, 0x1a, 0x03, 0x16, 0x03, 0x1e, 0x02, 0x22, 0x02,
  0x26, 0x06, 0x1a, 0x04, 0x1e, 0x06, 0x1e, 0xfd, 0x32, 0xfe, 0x26, 0x04,
  0x16, 0x03, 0x22, 0x03, 0x1a, 0x05, 0x1a, 0xff, 0x16, 0x03, 0x16, 0xfd,
  0x2e, 0x06, 0x1e, 0x02, 0x1a, 0x02, 0x16, 0x04, 0x32, 0xfe, 0x1e, 0x04,
  0x1e, 0xfd, 0x2e, 0x08, 0x2e, 0xff, 0x2a, 0x06, 0x16, 0x04, 0x1a, 0x01,
  0x16, 0x01, 0x1a, 0x01, 0x16, 0x01, 0x1a, 0x01, 0x16, 0x01, 0x1a, 0x01,
  0x16, 0x01, 0x1a, 0x01, 0x16, 0x01, 0x1a, 0x01, 0x16, 0x01, 0x1a, 0x01,
  0x16, 0x01, 0x1a, 0x01, 0x16, 0x01, 0x1a, 0x01, 0x16, 0x01, 0x1a, 0x01,
  0x16, 0x01, 0x1a, 0x01, 0x16, 0x01, 0x1a, 0x01, 0x16, 0x04, 0x1a, 0x04,
  0x1a, 0xfd, 0x16, 0x04, 0x32, 0xfe, 0x32, 0xff, 0x2e, 0x05, 0x2a, 0x02,
  0x26, 0x03, 0x22, 0x02, 0x1e, 0x03, 0x1a, 0x02, 0x16, 0x03, 0x1a, 0x02,
  0x1e, 0xff, 0x2e, 0x06, 0x22, 0x02, 0x16, 0x08, 0x16, 0xfd, 0x2e, 0x06,
  0x16, 0x03, 0x2e, 0x06, 0x16, 0x03, 0x2e, 0x06, 0x16, 0x03, 0x2e, 0x06,
  0x16, 0x03, 0x16, 0xff, 0x16, 0x02, 0x2e, 0x06, 0x16, 0x03, 0x1e, 0xfe,
  0x1a, 0x05, 0x1e, 0x04, 0x22, 0x03, 0x26, 0x02, 0x2a, 0x01, 0x2e, 0x05,
  0x2e, 0xff, 0x2a, 0x04, 0x2e, 0x04, 0x2e, 0xff, 0x22, 0x04, 0x2e, 0x05,
  0x2a, 0xff, 0x2e, 0x06, 0x2e, 0xff, 0x2e, 0x05, 0x2e, 0xff, 0x2e, 0x05,
  0x2e, 0xff, 0x2a, 0x04, 0x32, 0xfe, 0x2e, 0x03, 0x2e, 0xfd, 0x2e, 0xff,
  0x1a, 0x04, 0x1e, 0xfe, 0x1a, 0x04, 0x2e, 0x22, 0x2e, 0xf9, 0x00, 0x00,
  0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x27, 0x20, 0x64,
  0x1d, 0x40, 0x60, 0x15, 0x60, 0x5c, 0x0f, 0x80, 0x58, 0x11, 0xa0, 0x54,
  0x0f, 0xc0, 0x50, 0x15, 0xe0, 0x4c, 0x1d, 0x40, 0x48, 0x27, 0x20, 0x48,
  0x27, 0x00, 0x48, 0x27, 0x20, 0x4c, 0x1d, 0x40, 0x50, 0x15, 0xe0, 0x54,
  0x0f, 0xc0, 0x58, 0x11, 0xa0, 0x5c, 0x0f, 0x80, 0x60, 0x15, 0x60, 0x64,
  0x1d, 0x40, 0x68, 0x27, 0x20, 0x68, 0x27, 0x00, 0x00, 0x0a, 0x08, 0x06,
  0x04, 0x08, 0x02, 0x0a, 0x08, 0x00, 0x06, 0x08, 0x0a, 0x00, 0x02, 0x08,
  0x04, 0x02, 0x0a, 0x08, 0x00, 0x11, 0x00, 0x0a, 0x78, 0x0e, 0xdd, 0xdb,
  0xbf, 0xff, 0xff, 0xee, 0x7a, 0xe0, 0xa5, 0x50, 0xa5, 0x50, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x11, 0x00, 0x0a, 0x78, 0x0e, 0xdd, 0xdb, 0xbf, 0xff, 0xff, 0xee,
  0x39, 0xf0, 0x52, 0xa8, 0x52, 0xa8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x50, 0x00,
  0x70, 0x1e, 0xdb, 0xbb, 0xff, 0xfd, 0x77, 0xff, 0x07, 0x5e, 0x0a, 0xa5,
  0x0a, 0xa5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x50, 0x00, 0x70, 0x1e, 0xdb, 0xbb,
  0xff, 0xfd, 0x77, 0xff, 0x0f, 0x9c, 0x15, 0x4a, 0x15, 0x4a, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xf0, 0x00, 0xf0, 0x50, 0xe0, 0xb0, 0xe0, 0xb0, 0xf0, 0x20, 0x80, 0xf0,
  0xf0, 0x90, 0x90, 0xf0, 0x00, 0x80, 0x00, 0xc0, 0x00, 0xe0, 0x00, 0xf0,
  0xff, 0xf8, 0xff, 0xfc, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfc,
  0xff, 0xf8, 0x00, 0xf0, 0x00, 0xe0, 0x00, 0xc0, 0x00, 0x80, 0x00, 0x00,
  0xf0, 0x80, 0xb0, 0xa0, 0xb0, 0xa0, 0x80, 0x80, 0xf0, 0x00, 0x10, 0xa0,
  0x30, 0xa0, 0x00, 0x00, 0xf0, 0x00, 0x20, 0xa0, 0xa0, 0xa0, 0x00, 0x00,
  0xf0, 0x10, 0xd0, 0xb0, 0xb0, 0xd0, 0x10, 0x10, 0x20, 0x30, 0x70, 0xf0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x21,
  0x00, 0x31, 0x00, 0xc1, 0x03, 0x2d, 0x7c, 0x8d, 0x82, 0x01, 0xff, 0xff,
  0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0xc0, 0x26, 0x20,
  0x40, 0x10, 0x80, 0x08, 0x81, 0x08, 0x40, 0x88, 0x20, 0x44, 0x20, 0x42,
  0x40, 0x42, 0x80, 0x82, 0x80, 0x02, 0x40, 0x0c, 0x20, 0x70, 0x10, 0x80,
  0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x02, 0x10, 0x1c, 0x10,
  0x20, 0x08, 0x40, 0x08, 0x83, 0x88, 0x84, 0x44, 0x88, 0x02, 0x40, 0x02,
  0x40, 0x02, 0x80, 0x02, 0x80, 0x04, 0x43, 0x08, 0x24, 0x90, 0x18, 0x60,
  0x00, 0x00, 0x00, 0xf0, 0x01, 0x08, 0x0e, 0x04, 0x30, 0x02, 0x40, 0x01,
  0x41, 0x01, 0x42, 0x02, 0x42, 0x04, 0x22, 0x04, 0x11, 0x02, 0x10, 0x81,
  0x10, 0x01, 0x08, 0x02, 0x04, 0x64, 0x03, 0x98, 0x06, 0x18, 0x09, 0x24,
  0x10, 0xc2, 0x20, 0x01, 0x40, 0x01, 0x40, 0x02, 0x40, 0x02, 0x40, 0x11,
  0x22, 0x21, 0x11, 0xc1, 0x10, 0x02, 0x10, 0x04, 0x08, 0x38, 0x08, 0x40,
  0x07, 0x80, 0x00, 0x00, 0x01, 0xf0, 0x02, 0x08, 0x02, 0x88, 0x76, 0x08,
  0xf2, 0x08, 0x59, 0xf0, 0x54, 0x40, 0x53, 0xc0, 0x70, 0x60, 0x00, 0x50,
  0x00, 0x48, 0x00, 0xa4, 0x01, 0x20, 0x0a, 0x10, 0x04, 0x08, 0x00, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x04, 0x10, 0x05, 0x10, 0x0c, 0x10,
  0x04, 0x10, 0x3b, 0xe0, 0x78, 0x80, 0x2f, 0xc0, 0x28, 0xa0, 0x28, 0x90,
  0x3b, 0x90, 0x02, 0x80, 0x02, 0xe0, 0x06, 0x20, 0x01, 0xf0, 0x02, 0x08,
  0x02, 0x88, 0x76, 0x08, 0xf2, 0x08, 0x59, 0xf2, 0x54, 0x44, 0x53, 0xf8,
  0x70, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0xa0, 0x01, 0x10, 0x0a, 0x08,
  0x04, 0x04, 0x00, 0x08, 0x04, 0x00, 0x0a, 0x00, 0x11, 0x20, 0x20, 0xa0,
  0x49, 0x20, 0x22, 0x40, 0x15, 0x80, 0x19, 0x80, 0x42, 0x40, 0xfc, 0x20,
  0x50, 0x1f, 0xa8, 0x11, 0x14, 0x10, 0x08, 0x10, 0x00, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x00, 0x02, 0x02, 0x79, 0x05, 0x85, 0x08, 0x85, 0x10,
  0x87, 0xe0, 0xa5, 0x10, 0x85, 0x08, 0x79, 0x04, 0x12, 0x02, 0x04, 0x04,
  0x1f, 0x80, 0x18, 0x80, 0x1f, 0x80, 0x08, 0x00, 0x10, 0x00, 0x20, 0x20,
  0x10, 0x50, 0x08, 0x80, 0x05, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x0e,
  0x1f, 0xca, 0x22, 0x2a, 0x4f, 0x9a, 0x10, 0x4f, 0x10, 0x6e, 0x11, 0x40,
  0x10, 0x40, 0x0f, 0x80, 0x00, 0x10, 0x01, 0xf8, 0x01, 0x18, 0x01, 0xf8,
  0x20, 0x20, 0x40, 0x48, 0x20, 0x9e, 0x10, 0xa1, 0x08, 0xa5, 0x07, 0xe1,
  0x08, 0xa1, 0x10, 0xa1, 0xa0, 0x9e, 0x40, 0x40, 0x00, 0x20, 0x00, 0x00,
  0x14, 0x00, 0x0e, 0x20, 0x14, 0x50, 0x2d, 0x88, 0x55, 0x24, 0x24, 0x82,
  0x02, 0x44, 0x01, 0xa8, 0x01, 0x90, 0x02, 0x40, 0x84, 0x38, 0xf8, 0x00,
  0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x18, 0x00, 0x0f, 0x80, 0x10, 0x40,
  0x11, 0x40, 0x10, 0x6e, 0x10, 0x4f, 0x0f, 0x9a, 0x02, 0x2a, 0x07, 0xca,
  0x0a, 0x0e, 0x12, 0x00, 0x12, 0x00, 0x05, 0x00, 0x08, 0x80, 0x10, 0x50,
  0x20, 0x20, 0x10, 0x00, 0x0f, 0x80, 0x10, 0x40, 0x11, 0x40, 0x10, 0x6e,
  0x10, 0x4f, 0x0f, 0x9a, 0x02, 0x2a, 0x07, 0xca, 0x06, 0x0e, 0x06, 0x00,
  0x03, 0x00, 0x02, 0x00, 0x02, 0x00, 0x06, 0x00, 0x0a, 0x00, 0x07, 0x00,
  0x01, 0xf0, 0x02, 0x08, 0x02, 0x88, 0x76, 0x08, 0xf2, 0x08, 0x59, 0xf0,
  0x54, 0x40, 0x53, 0xe0, 0x70, 0x50, 0x00, 0x48, 0x00, 0x48, 0x00, 0xa0,
  0x01, 0x10, 0x0a, 0x08, 0x04, 0x04, 0x00, 0x08, 0x01, 0xf0, 0x02, 0x08,
  0x02, 0x88, 0x76, 0x08, 0xf2, 0x08, 0x59, 0xf0, 0x54, 0x40, 0x53, 0xe0,
  0x70, 0x60, 0x00, 0x60, 0x00, 0xc0, 0x00, 0x40, 0x00, 0x40, 0x00, 0x60,
  0x00, 0x50, 0x00, 0xe0, 0x3c, 0x00, 0x6b, 0x00, 0xd5, 0x40, 0xaa, 0xa8,
  0xd5, 0x55, 0xaa, 0xa8, 0xd5, 0x40, 0x6b, 0x00, 0x3c, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xc0, 0x18, 0x30, 0x20, 0x08, 0x40, 0x04, 0x4c, 0x64,
  0x9e, 0xf2, 0x96, 0xb2, 0x8c, 0x62, 0x80, 0x02, 0x80, 0x02, 0x43, 0x84,
  0x44, 0x44, 0x20, 0x08, 0x18, 0x30, 0x07, 0xc0, 0x00, 0x00, 0x07, 0xc0,
  0x18, 0x30, 0x20, 0x08, 0x40, 0xc4, 0x41, 0xe4, 0x81, 0xa2, 0x8c, 0xc2,
  0x9e, 0x02, 0x9a, 0x1a, 0x8c, 0x22, 0x40, 0x44, 0x40, 0x84, 0x20, 0x88,
  0x18, 0x30, 0x07, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x18, 0x30, 0x20, 0x08,
  0x46, 0x04, 0x4f, 0x04, 0x8d, 0x12, 0x86, 0x22, 0x80, 0x22, 0x86, 0x22,
  0x8f, 0x12, 0x4d, 0x04, 0x46, 0x04, 0x20, 0x08, 0x18, 0x30, 0x07, 0xc0,
  0x00, 0x00, 0x07, 0xc0, 0x18, 0x30, 0x20, 0x88, 0x40, 0x84, 0x4c, 0x44,
  0x9a, 0x22, 0x9e, 0x1a, 0x8c, 0x02, 0x81, 0x82, 0x83, 0x42, 0x43, 0xc4,
  0x41, 0x84, 0x20, 0x08, 0x18, 0x30, 0x07, 0xc0, 0x00, 0x00, 0x07, 0xc0,
  0x18, 0x30, 0x20, 0x08, 0x44, 0x44, 0x43, 0x84, 0x80, 0x02, 0x80, 0x02,
  0x8c, 0x62, 0x9a, 0xd2, 0x9e, 0xf2, 0x4c, 0x64, 0x40, 0x04, 0x20, 0x08,
  0x18, 0x30, 0x07, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x18, 0x30, 0x22, 0x08,
  0x42, 0x04, 0x44, 0x64, 0x88, 0xb2, 0xb0, 0xf2, 0x80, 0x62, 0x83, 0x02,
  0x85, 0x82, 0x47, 0x84, 0x43, 0x04, 0x20, 0x08, 0x18, 0x30, 0x07, 0xc0,
  0x00, 0x00, 0x07, 0xc0, 0x18, 0x30, 0x20, 0x08, 0x40, 0xc4, 0x41, 0x64,
  0x91, 0xe2, 0x88, 0xc2, 0x88, 0x02, 0x88, 0xc2, 0x91, 0x62, 0x41, 0xe4,
  0x40, 0xc4, 0x20, 0x08, 0x18, 0x30, 0x07, 0xc0, 0x00, 0x00, 0x07, 0xc0,
  0x18, 0x30, 0x20, 0x08, 0x43, 0x04, 0x47, 0x84, 0x85, 0x82, 0x83, 0x02,
  0x80, 0x62, 0xb0, 0xf2, 0x88, 0xb2, 0x44, 0x64, 0x42, 0x04, 0x22, 0x08,
  0x18, 0x30, 0x07, 0xc0
};

#define __TEST __ANT

#endif /* _TEST_H */

