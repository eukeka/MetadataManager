#ifndef _HEAD_
#define _HEAD_


#include<sys/stat.h>
#include<string>
#include<map>
#include<vector>
#include "metadata.h"

using namespace std;

// ディレクトリエントリ用シリアライズ関数
extern void 					encode_dir_entry( char * encode_path, vector<string> * dir_entry);
extern vector<string> decode_dir_entry( char * decode_path );


// metadta用シリアライズ関数
extern void		write_serialize_metadata( char * decode_path, f_inf * metadata);
extern f_inf	read_serialize_metadata(  char * decode_path );


#endif
