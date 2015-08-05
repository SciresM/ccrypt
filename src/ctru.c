/*
 * Copyright (c) 2014,2015 fincs, plutoo, smealum, WinterMute, yellows8
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

#include "ctru.h"
#include "compat.h"
#include "svc.h"

inline void* getThreadLocalStorage(void)
{
	void* ret;
	asm volatile("mrc p15, 0, %[data], c13, c0, 3" : [data] "=r" (ret));
	return ret;
}

u32* getThreadCommandBuffer(void)
{
	return (u32*)((u8*)getThreadLocalStorage() + 0x80);
}

/* cue copypasta from ctrulib we can't link in because static linkage fail */
Result PS_EncryptDecryptAes(Handle psHandle, u32 size, u8* in, u8* out, u32 aes_algo, u32 key_type, u8* iv)
{
	Result ret = 0;
	u32 *cmdbuf = getThreadCommandBuffer();

	u32 *_iv = (u32*)iv;

	/* This was changed from ctrulib to match 3dbrew:
	 * http://3dbrew.org/wiki/PS:EncryptDecryptAes
	 */
	cmdbuf[0] = 0x00040204;
	cmdbuf[1] = size;
	cmdbuf[2] = size;
	cmdbuf[3] = _iv[0];
	cmdbuf[4] = _iv[1];
	cmdbuf[5] = _iv[2];
	cmdbuf[6] = _iv[3];
	cmdbuf[7] = aes_algo;
	cmdbuf[8] = key_type;
	cmdbuf[9] = (size << 4) | 10;
	cmdbuf[10] = (u32)in;
	cmdbuf[11] = (size << 4) | 12;
	cmdbuf[12] = (u32)out;

	if((ret = svcSendSyncRequest(psHandle))!=0)return ret;

	_iv[0] = cmdbuf[2];
	_iv[1] = cmdbuf[3];
	_iv[2] = cmdbuf[4];
	_iv[3] = cmdbuf[5];

	return (Result)cmdbuf[1];
}
