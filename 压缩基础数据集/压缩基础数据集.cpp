//////////////////////////////////////////////////////////////////////////
//
//    ѹ���������ݼ�.cpp
//
//    SG 2019.9.24
//
//////////////////////////////////////////////////////////////////////////


#include "ѹ���������ݼ�.h"
#include "zip.h"

extern "C"
{
#include "zipmem.h"
}

int main()
{
	int i, j;
	string in_path = "F:\\��������\\�����ļ����ݼ�\\�ϴ�github\\�������ݼ�\\";
	string out_path = "F:\\��������\\�����ļ����ݼ�\\�ϴ�github\\ѹ���������ݼ�\\";

	//���������ļ�������ȫ·��д����ʱ�ļ�
	string target_file_type = "*.*";
	string path_tmp = out_path + "filename.dat";
	int file_amount = find_file(in_path, target_file_type, path_tmp);

	ifstream infile;
	string infilename, outfilename, newname;
	infile.open(path_tmp, ios::in);
	while (!infile.eof())
	{
		getline(infile, infilename);
		if (infilename.length() < in_path.length())
			continue;
		printf("%s\n", infilename.c_str());
		newname = new_name(in_path, infilename);
		outfilename = out_path + newname;
		if (!Rar_compress(infilename,outfilename))
		{
			printf("RARѹ��%sʧ��\n", infilename);
			return 0;
		}
		if (!Zip_compress(infilename, outfilename))
		{
			printf("ZIPѹ��%sʧ��\n", infilename);
			return 0;
		}
		if (!Gzip_compress(infilename, outfilename))
		{
			printf("Gzipѹ��%sʧ��\n", infilename);
			return 0;
		}
	}
	infile.close();
	DeleteFile(path_tmp.c_str());
	return 1;
}

int find_file(string in_path, string target_file_type, string out_path)
{
	int i, j;
	int filenum = 0;
	HANDLE hfind;
	WIN32_FIND_DATA fileinfo;
	ofstream outfile;
	outfile.open(out_path, ios::out | ios::app);
	hfind = FindFirstFile((in_path + target_file_type).c_str(), &fileinfo);
	if (hfind == INVALID_HANDLE_VALUE)
	{
		printf("can not open find handle.\n");
		return 0;
	}
	while (FindNextFile(hfind, &fileinfo))
	{
		if (strcmp(fileinfo.cFileName, ".") == 0 || strcmp(fileinfo.cFileName, "..") == 0)
			continue;
		if (fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			outfile.close();
			i = find_file(in_path + fileinfo.cFileName + "\\", target_file_type, out_path);
			filenum += i;
		}
		else
		{
				outfile << in_path << fileinfo.cFileName << "\n";
				filenum++;
		}
	}
	outfile.close();
	FindClose(hfind);
	return filenum;
}

string new_name(string in_path, string in_name)
{
	int i, j;
	string newname;
	newname = in_name.substr(in_path.length(), in_name.length());
	replace(newname.begin(), newname.end(), '\\', '_');
//	replace(newname.begin(), newname.end(), '.', '_');
	return newname;
}

bool Rar_compress(string in_file, string out_file)
{
	string commond;
	commond = "C:\\\"program files\"\\WinRAR\\Rar.exe a -ep -inul " + out_file + ".rar" + " " + in_file;
	system(commond.c_str());
	return true;
}

bool Zip_compress(string in_file, string out_file)
{

	string outfile_tmp = out_file + ".zip";
	string filename = out_file.substr(out_file.rfind("\\"));
	HZIP hz = CreateZip(outfile_tmp.c_str(), NULL);
	ZipAdd(hz, filename.c_str(), in_file.c_str());
	CloseZip(hz);
	return true;
}

bool Gzip_compress(string in_file, string out_file)
{
	string outfile_tmp = out_file + ".gz";
	HANDLE hin;
	unsigned int filesize, comopress_len;
	DWORD readnum, writenum;
	char *out_tmp, *compress_tmp;

	hin = CreateFile(in_file.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hin==INVALID_HANDLE_VALUE)
	{
		printf("can not open %s\n", in_file.c_str());
		return false;
	}
	filesize = GetFileSize(hin, &readnum);
	out_tmp = new char[filesize + 2];
	compress_tmp = new char[filesize + 2048000];
	ReadFile(hin, out_tmp, filesize, &readnum, NULL);
	if (readnum!=filesize)
	{
		printf("��ȡ�ļ�����\n");
		return false;
	}
	CloseHandle(hin);
	memset(compress_tmp, 0x00, filesize + 2048000);
	comopress_len = zipmem(out_tmp, filesize, compress_tmp);
	hin = CreateFile(outfile_tmp.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hin == INVALID_HANDLE_VALUE)
	{
		printf("can not open %s\n", out_file.c_str());
		return false;
	}
	WriteFile(hin, compress_tmp, comopress_len, &writenum, NULL);
	if (writenum!=comopress_len)
	{
		printf("write file false\n");
		return false;
	}
	CloseHandle(hin);
	delete(compress_tmp);
	delete(out_tmp);
	return true;
}

bool SevenZ_compress(string in_file, string out_file)
{
	string outfile_tmp = out_file + ".7z";
	HINSTANCE hDLL;
	SevenZip zip;
	hDLL = LoadLibrary("7z.dll");//���ض�̬���ӿ�MyDll.dll�ļ���
	zip = (SevenZip)GetProcAddress(hDLL, "Zip");

	zip(outfile_tmp.c_str(),in_file.c_str());
	FreeLibrary(hDLL);
	return true;
}
