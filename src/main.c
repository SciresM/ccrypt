#include "mkhax.h"

#include "types.h"
#include "compat.h"
#include "svc.h"
#include "ctru.h"

int main();

__attribute__ ((section (".text.start"), naked))
void entry()
{
	main();
}

size_t strlen(const char *s)
{
	size_t sz = 0;

	for(; *s; s++)
		sz++;

	return sz;
}

int main()
{
	init_compat();
	Result ret;
	u8 *buffer = (void*)0x18410000;
	IFILE fin_cert, fout_cert;
	IFILE fin_key, fout_key;
	unsigned int read_count;

	compat.app.svcSleepThread(0x400000LL);

	arm11_kernel_exploit_setup();
	patch_srv_access();

	Handle PS_handle;
	const char* svcName = "ps:ps";
	if((ret = compat.app.srvGetServiceHandle(&PS_handle, svcName, strlen(svcName))) != 0)
		svcExitThread();

	_memset(&fin_cert, 0, sizeof(fin_cert));
	_memset(&fout_cert, 0, sizeof(fout_cert));
	compat.app.IFile_Open(&fin_cert, L"dmc:/ctr-common-1-cert.bin", FILE_R);
	compat.app.IFile_Read(&fin_cert, &read_count, buffer, 1264);

	if((ret = PS_EncryptDecryptAes(PS_handle, 1248, buffer + 16, buffer + 1264, 1, 0, buffer)) != 0)
		svcExitThread();

	compat.app.IFile_Open(&fout_cert, L"dmc:/ctr-common-1-cert.dec", FILE_W);
	compat.app.IFile_Write(&fout_cert, &read_count, buffer + 1264, 1248, 1);

	_memset(&fin_key, 0, sizeof(fin_key));
	_memset(&fout_key, 0, sizeof(fout_key));
	compat.app.IFile_Open(&fin_key, L"dmc:/ctr-common-1-key.bin", FILE_R);
	compat.app.IFile_Read(&fin_key, &read_count, buffer, 1232);

	if((ret = PS_EncryptDecryptAes(PS_handle, 1216, buffer + 16, buffer + 1264, 1, 0, buffer)) != 0)
		svcExitThread();

	compat.app.IFile_Open(&fout_key, L"dmc:/ctr-common-1-key.dec", FILE_W);
	compat.app.IFile_Write(&fout_key, &read_count, buffer + 1264, 1216, 1);

	svcCloseHandle(PS_handle);
	svcExitThread();

	return 0;
}

