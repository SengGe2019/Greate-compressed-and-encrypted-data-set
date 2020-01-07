#pragma once

#define CRYPTOPP_DEFAULT_NO_DLL
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <aes.h>
#include <Hex.h>      // StreamTransformationFilter  
#include <modes.h>    // CFB_Mode  
#include <files.h>
#include <des.h>
#include <idea.h>
#include <tchar.h>

using namespace CryptoPP;
using namespace std;
#pragma comment(lib, "cryptlib.lib" ) 


bool AES_encrypt(const char *in_file, const char *out_file);
bool DES_encrypt(const char *in_file, const char *out_file);
bool IDEA_encrypt(const char *in_file, const char *out_file);
bool AES_CBC_Encrypt(const char *hexKey, const char *hexIV, const char *infile, const char *outfile);
bool DES_CBC_Encrypt(const char *hexKey, const char *hexIV, const char *infile, const char *outfile);
bool IDEA_CBC_Encrypt(const char *hexKey, const char *hexIV, const char *infile, const char *outfile);