/*
 * Copyright (c) 2014,2015 fincs, plutoo, yellows8
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Modified from ctrulib https://github.com/smealum/ctrulib/
 */


#ifndef CTRU_H
#define CTRU_H

#include "types.h"

// Copied from ctrulib cause static linking fail for the spider environment
u32* getThreadCommandBuffer(void);

Result PS_EncryptDecryptAes(Handle psHandle, u32 size, u8* in, u8* out, u32 aes_algo, u32 key_type, u8* iv);

#endif
