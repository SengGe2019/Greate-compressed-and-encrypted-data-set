//////////////////////////////////////////////////////////////////////////
//
//    加密基础数据集.h
//
//    SG 2019.9.27
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

int find_file(string in_path, string target_file_type, string out_path = nullptr);
string new_name(string in_path, string in_name);
