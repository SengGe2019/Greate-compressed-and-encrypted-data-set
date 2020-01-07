//////////////////////////////////////////////////////////////////////////
//
//    压缩基础数据集.h
//
//    SG 2019.9.24
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <string>
#include <process.h>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

typedef int(__stdcall *SevenZip)(const char *args, const char *args2);
typedef int(__stdcall *UnSevenZip)(const char *args, const char *args2);

int find_file(string in_path, string target_file_type, string out_path = nullptr);
string new_name(string in_path, string in_name);
bool Rar_compress(string in_file, string out_file);
bool Zip_compress(string in_file, string out_file);
bool Gzip_compress(string in_file, string out_file);
bool SevenZ_compress(string in_file, string out_file);