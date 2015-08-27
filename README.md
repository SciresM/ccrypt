# ccrypt

Decrypts the ClCertA files.

## Usage

1. Get ClCertA (TitleID 0004001b00010002). If you get it from the CDN, remember to
   decrypt it with its decrypted titlekey in AES-128-CBC mode.
2. Decrypt the ClCertA CFA with the tool of your choice. Decrypt9, rxTools and 3DS Multi
   Decryptor both work as well.
3. Use ctrtool to extract the RomFS from the decrypted ClCertA CFA.
4. Compile ccrypt. This requires devkitPro and devkitARM or any regular
   cross-compiling gcc targeting arm-none-eabi.
5. Place the resulting `code.bin` at the root of your SD card.
6. Place `ctr-common-1-cert.bin` and `ctr-common-1-key.bin` from your ClCertA
   RomFS at the root of your SD card.
7. Visit `http://dukesrg.no-ip.org/3ds/cakes?code.bin` with your 3DS web
   browser.

The resulting files are `ctr-common-1-cert.dec` and `ctr-common-1-key.dec` at
the root of your SD card.
They are in DER format. For usage in browsers, you may need to convert it
to the PKCS#12 format or the PEM format.
