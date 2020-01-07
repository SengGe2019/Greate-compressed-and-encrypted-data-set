//////////////////////////////////////////////////////////////////////////
//
//    crypt_interface.h
//
//    SG 2019.9.27
//
//////////////////////////////////////////////////////////////////////////


#include "crypt_interface.h"

bool AES_encrypt(const char * in_file, const char * out_file)
{
	int i;
	char infile[256], outfile[256];
	strcpy_s(infile, in_file);
	strcpy_s(outfile, out_file);
	strcat_s(outfile, ".aes");
	printf("%s", outfile);
	bool encrypt_ok = false;
	char key[36], iv[AES::BLOCKSIZE + 4];
	char filename[256];
	const char *p = strrchr(outfile, '\\');
	strcpy_s(filename, p+1);
	i = strlen(filename);
	if (i > 32)
		strncpy_s(key, 33, filename, _TRUNCATE);
	else
		strcpy_s(key, filename);
	if (i > AES::BLOCKSIZE)
		strncpy_s(iv, AES::BLOCKSIZE + 1, filename, _TRUNCATE);
	else
		strcpy_s(iv, filename);
	encrypt_ok = AES_CBC_Encrypt(key, iv, infile, outfile);
	return true;
}

bool DES_encrypt(const char * in_file, const char * out_file)
{
	int i;
	char infile[256], outfile[256];
	strcpy_s(infile, in_file);
	strcpy_s(outfile, out_file);
	strcat_s(outfile, ".3des");
	printf("%s", outfile);
	bool encrypt_ok = false;
	char key[DES_EDE3::KEYLENGTH + 4], iv[DES_EDE3::BLOCKSIZE + 4];
	char filename[256];
	const char *p = strrchr(outfile, '\\');
	strcpy_s(filename, p+1);
	i = strlen(filename);
	if (i > DES_EDE3::KEYLENGTH)
		strncpy_s(key, DES_EDE3::KEYLENGTH + 1, filename, _TRUNCATE);
	else
		strcpy_s(key, filename);
	if (i > DES_EDE3::BLOCKSIZE)
		strncpy_s(iv, DES_EDE3::BLOCKSIZE + 1, filename, _TRUNCATE);
	else
		strcpy_s(iv, filename);
	encrypt_ok = DES_CBC_Encrypt(key, iv, infile, outfile);
	return true;
}

bool IDEA_encrypt(const char * in_file, const char * out_file)
{
	int i;
	char infile[256], outfile[256];
	strcpy_s(infile, in_file);
	strcpy_s(outfile, out_file);
	strcat_s(outfile, ".idea");
	printf("%s", outfile);
	bool encrypt_ok = false;
	char key[IDEA::KEYLENGTH + 4], iv[IDEA::BLOCKSIZE + 4];
	char filename[256];
	const char *p = strrchr(outfile, '\\');
	strcpy_s(filename, p+1);
	i = strlen(filename);
	if (i > IDEA::KEYLENGTH)
		strncpy_s(key, IDEA::KEYLENGTH + 1, filename, _TRUNCATE);
	else
		strcpy_s(key, filename);
	if (i > IDEA::BLOCKSIZE)
		strncpy_s(iv, IDEA::BLOCKSIZE + 1, filename, _TRUNCATE);
	else
		strcpy_s(iv, filename);
	encrypt_ok = IDEA_CBC_Encrypt(key, iv, infile, outfile);
	return true;
}


bool AES_CBC_Encrypt(const char * hexKey, const char * hexIV, const char * infile, const char * outfile)
{
	SecByteBlock key((byte*)hexKey, strlen(hexKey));
	SecByteBlock iv((byte *)hexIV, strlen(hexIV));
	int key_len = 8 * ((strlen(hexKey) % 3) + 2);
	printf("	 *******key===%d\n", key_len);
	CBC_Mode<AES>::Encryption aes(key, key_len, iv);//key=16,24,32
	FileSource(infile, true, new StreamTransformationFilter(aes, new FileSink(outfile)));
	return true;
}

bool DES_CBC_Encrypt(const char * hexKey, const char * hexIV, const char * infile, const char * outfile)
{
	SecByteBlock key((byte*)hexKey, strlen(hexKey));
	SecByteBlock iv((byte *)hexIV, strlen(hexIV));
	printf("	*******,key===%d\n", strlen(hexKey));
	CBC_Mode<DES_EDE3>::Encryption des_ede3(key, DES_EDE3::KEYLENGTH, iv);//key24
	FileSource(infile, true, new StreamTransformationFilter(des_ede3, new FileSink(outfile)));
	return true;
}

bool IDEA_CBC_Encrypt(const char * hexKey, const char * hexIV, const char * infile, const char * outfile)
{
	SecByteBlock key((byte*)hexKey, strlen(hexKey));
	SecByteBlock iv((byte *)hexIV, strlen(hexIV));
	printf("	*******,key===%d\n", strlen(hexKey));
	CBC_Mode<IDEA>::Encryption idea(key, IDEA::KEYLENGTH, iv);//key16
	FileSource(infile, true, new StreamTransformationFilter(idea, new FileSink(outfile)));
	return true;
}
