//////////////////////////////////////////////////////////////////////////
//
//    加密基础数据集.cpp
//
//    SG 2019.9.27
//
//////////////////////////////////////////////////////////////////////////

#include "加密基础数据集.h"
#include "crypt_interface.h"

int main()
{
	string in_path = "F:\\下载数据\\常用文件数据集\\上传github\\基础数据集\\";
	string out_path = "F:\\下载数据\\常用文件数据集\\上传github\\加密基础数据集\\";

	//查找所有文件，并把全路径写入临时文件
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
		newname = new_name(in_path, infilename);
		outfilename = out_path + newname;
		if (!AES_encrypt(infilename.c_str(), outfilename.c_str()))
		{
			printf("AES加密%s失败\n", infilename);
			return 0;
		}
		if (!DES_encrypt(infilename.c_str(), outfilename.c_str()))
		{
			printf("3DES加密%s失败\n", infilename);
			return 0;
		}
		if (!IDEA_encrypt(infilename.c_str(), outfilename.c_str()))
		{
			printf("加密%s失败\n", infilename);
			return 0;
		}
	}
	infile.close();
	DeleteFile(path_tmp.c_str());
	return 1;
}


int find_file(string in_path, string target_file_type, string out_path)
{
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
			filenum += find_file(in_path + fileinfo.cFileName + "\\", target_file_type, out_path);
		}
		else
		{
			outfile << in_path << fileinfo.cFileName << "\n";
			filenum++;
		}
	}
	FindClose(hfind);
	return filenum;
}

string new_name(string in_path, string in_name)
{
	string newname;
	newname = in_name.substr(in_path.length(), in_name.length());
	replace(newname.begin(), newname.end(), '\\', '_');
	return newname;
}

