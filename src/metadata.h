
// メタデータ操作用ヘッダ
#ifndef _PUTMETADATA_
#define _PUTMETADATA_
#include <sys/stat.h>
#include <vector>
#include <string>

// ファイル名の長さ
#define MAX_FNAME 256
// パスの長さ
#define MAX_PATH 1024
#define HASH_SIZ 33 

// メタデータとディレクトリファイルを作成するパス
#define STORE_DIR  "./MetadataStore/"

using namespace std;

// ファイル情報
typedef struct{
	char fname[MAX_FNAME];
	struct stat fstat;	
}f_inf;

// strをhashに変換
extern void conv_hash	( char * str,	char* hash );


// ファイル名 & パスのフォーマット関係 
class metadata_format 
{
	public:
		void get_full_path 			( char * q_name, char*full_path);
		void get_fname     			( char * full_path, char*fname);
		void get_dir_path  			( char * full_path, char*dir_path);
		void get_store_dir_path ( char * full_path, char*dir_path);
		void make_store_dir			( char * store_path);
};


// データ格納用
class metadata_io
{
	public:
		void read_dir_file( 
				vector<string> *dir_entry, 
				char* store_path, 
				char*dir_fname 
				);

		void write_dir_file(    
				vector<string> *dir_entry,
				char* store_path,
				char*full_path
				);

		void add_dir_entry( 
				vector<string> &dir_entry ,
				char * full_path 
				);


		// メタデータの読み書き
		void read_fileinfo( 
				f_inf *fileinfo,
				char* store_path,
				char* fileinfo_fname_hash
				);

		void write_fileinfo(
				f_inf *fileinfo,
				char* store_path,
				char* fileinfo_fname_hash
				);

		void get_finf(  f_inf * finf,
				char * full_path,
				char * fname
				);
};



#endif
