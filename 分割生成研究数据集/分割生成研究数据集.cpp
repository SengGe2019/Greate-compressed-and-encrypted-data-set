//////////////////////////////////////////////////////////////////////////
//
//    分割生成研究数据集.cpp
//
//    SG 2019.10.15
//
//////////////////////////////////////////////////////////////////////////

#include "分割生成研究数据集.h"

int CUT_SIZE;

int main()
{
	int i, j;
	string out_path = "F:\\下载数据\\常用文件数据集\\上传github\\研究数据集\\";
	string in_encrypt_path = "F:\\下载数据\\常用文件数据集\\上传github\\加密基础数据集\\";
	string in_compress_path = "F:\\下载数据\\常用文件数据集\\上传github\\压缩基础数据集\\";

	string target_file_type = "*.*";
	string path_tmp = out_path + "filename.dat";
	ifstream infile;
	string infilename, outfilename, newname;
	int file_amount;
	std::ostringstream ostr;
	string command;

	//查找所有加密文件，并把全路径写入临时文件
	file_amount = find_file(in_encrypt_path, target_file_type, path_tmp);
	//分割加密文件
	for (i=0,j=1;i<7;i++)
	{
		infile.open(path_tmp, ios::in);
		CUT_SIZE = j * 1024;
		while (!infile.eof())
		{
			getline(infile, infilename);
			if (infilename.length() < in_encrypt_path.length())
				continue;
			printf("%s\n", infilename.c_str());
			newname = new_name(in_encrypt_path, infilename);
			ostr.str("");
			ostr << out_path << "D_" << j << "KB\\";
			outfilename = ostr.str();
			if (GetFileAttributes(outfilename.c_str())==-1)
				CreateDirectory(outfilename.c_str(), NULL);
			outfilename = ostr.str() + newname;
			write_file(infilename, outfilename);
		}
		infile.close();
		j = j << 1;
	}	
	DeleteFile(path_tmp.c_str());

	//查找所有压缩文件，并把全路径写入临时文件
	file_amount = find_file(in_compress_path, target_file_type, path_tmp);
	//分割压缩文件
	for (i=0,j=1;i<7;i++)
	{
		infile.open(path_tmp, ios::in);
		CUT_SIZE = j * 1024;
		while (!infile.eof())
		{
			getline(infile, infilename);
			if (infilename.length() < in_encrypt_path.length())
				continue;
			printf("%s\n", infilename.c_str());
			newname = new_name(in_encrypt_path, infilename);
			ostr.str("");
			ostr << out_path << "D_" << j << "KB\\";
			outfilename = ostr.str();
			if (GetFileAttributes(outfilename.c_str()) == -1)
				CreateDirectory(outfilename.c_str(), NULL);
			outfilename = ostr.str() + newname;
			write_file(infilename, outfilename);
		}
		infile.close();
		j = j << 1;
	}
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
	outfile.close();
	FindClose(hfind);
	return filenum;
}

string new_name(string in_path, string in_name)
{
	string newname;
	newname = in_name.substr(in_path.length(), in_name.length());
	string a = newname.substr(0, newname.find('_'));
	string b = newname.substr(newname.find_last_of('.') + 1, newname.length());
	return a + "_" + b + ".dat";
}

int write_file(string in_name, string out_name)
{
	int i, j;
	int count = 0;
	HANDLE hin;
	unsigned int filesize;
	DWORD readnum;
	FILE *fp_out;
	unsigned char *file_tmp;

	hin = CreateFile(in_name.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hin == INVALID_HANDLE_VALUE)
	{
		printf("can not open %s\n", in_name);
		return -1;
	}
	filesize = GetFileSize(hin, &readnum);
	if (filesize < CUT_SIZE)
	{
		CloseHandle(hin);
		return count;
	}
	file_tmp = new unsigned char[filesize + 2];
	ReadFile(hin, file_tmp, filesize, &readnum, NULL);
	if (readnum != filesize)
	{
		printf("read file flase\n");
		return -1;
	}
	CloseHandle(hin);
	if (fopen_s(&fp_out, out_name.c_str(), "a") != 0)
	{
		printf("can not open %s\n", out_name);
		return -1;
	}
	for (i = 0; i < filesize - CUT_SIZE; i += CUT_SIZE)
	{
		for (j = 0; j < CUT_SIZE; j++)
			fprintf_s(fp_out, "%02x", file_tmp[i + j]);
		fprintf_s(fp_out, "\n");
		count++;
	}
	delete file_tmp;
	fclose(fp_out);
	return count;
}
