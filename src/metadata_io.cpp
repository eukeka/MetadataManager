#include "metadata.h"
#include "serialize.h"
#include <vector>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sys/types.h>
#include <time.h>


// ディレクトリエントリからの読込
void metadata_io::read_dir_file( 
		vector<string> *dir_entry,
		char* store_path,
		char*direntry_fname_hash		)
{

	char direntry_filepath[MAX_PATH]={};
	strcpy(direntry_filepath, store_path );
	strcat(direntry_filepath, direntry_fname_hash );

		
	struct stat st={};
	if(stat(direntry_filepath, &st) == 0 ){
		*dir_entry = decode_dir_entry( direntry_filepath );     

		vector<string> tmp = *dir_entry;
		cout<<"\n---------dir_entry--------"<<endl;
		int siz = tmp.size();           
		for(int i=0; i<siz; i++){
			cout<<tmp[i]<<endl;
		}
		cout<<"--------------------------\n"<<endl;
	}else{
		cout<<"not found dir_entry file"<<endl;
	}

}


// ディレクトリエントリへの書き込み
void metadata_io::write_dir_file( 
			vector<string> *dir_entry,
			char* store_path,
			char* direntry_fname_hash )
{
	char direntry_filepath[MAX_PATH]={};
	strcpy(direntry_filepath, store_path );
	strcat(direntry_filepath, direntry_fname_hash );

	encode_dir_entry( direntry_filepath, dir_entry);        
}


void metadata_io::add_dir_entry( 
		vector<string> &dir_entry , 
		char * full_path )
{
	vector<string>::iterator itr = find(dir_entry.begin(), dir_entry.end(), full_path);
	if( itr == dir_entry.end() ){
		//cout<<"additional entry data"<<endl;  
		dir_entry.push_back(full_path);
	}else{
		//cout<<"file is already registerd direntry_file"<<endl;        
	}
}





// メタデータの読み込み（ファイルがなければ読み込まない）
void metadata_io::read_fileinfo( 
		f_inf *fileinfo, 
		char* store_path, 
		char* fileinfo_fname_hash )
{
	int res=0;

	char finf_path[MAX_PATH]={};
	strcat( finf_path, store_path );
	strcat( finf_path, fileinfo_fname_hash );

	struct stat st;
	if(stat( finf_path, &st ) == 0){
		*fileinfo = read_serialize_metadata( finf_path );       
		res=1;
	}else{
		res=0;
	}

	if( res == 1){
		cout<<"\n-------fileinfo--------"<<endl;
		printf("file name   %s\n",  fileinfo->fname);
		printf("st_dev      %10d\n", (int)fileinfo->fstat.st_dev);
		printf("st_ino      %10d\n", (int)fileinfo->fstat.st_ino);
		printf("st_mode     %10d\n", (int)fileinfo->fstat.st_mode);
		printf("st_nlink    %10d\n", (int)fileinfo->fstat.st_nlink);
		printf("st_uid      %10d\n", (int)fileinfo->fstat.st_uid);
		printf("st_gid      %10d\n", (int)fileinfo->fstat.st_gid);
		printf("st_rdev     %10d\n", (int)fileinfo->fstat.st_rdev);
		printf("st_size     %10d\n", (int)fileinfo->fstat.st_size);
		printf("st_blksize  %10d\n", (int)fileinfo->fstat.st_blksize);
		printf("st_blocks   %10d\n", (int)fileinfo->fstat.st_blocks);
		printf("st_atim     %10d\n", (int)fileinfo->fstat.st_atime);
		printf("st_mtim     %10d\n", (int)fileinfo->fstat.st_mtime);
		printf("st_ctim     %10d\n", (int)fileinfo->fstat.st_ctime);
		cout<<"--------------------------\n"<<endl;
	}else{
		cout<<"file not registered"<<endl;
	}
}


// メタデータの書き込み
void metadata_io::write_fileinfo( 
		f_inf *fileinfo, 
		char* store_path, 
		char* fileinfo_fname_hash )
{
	char finf_path[MAX_PATH]={};
	strcat( finf_path, store_path);
	strcat( finf_path, fileinfo_fname_hash );

	write_serialize_metadata( finf_path, fileinfo );        
}


// メタデータに追加するためのファイル情報を取得
void metadata_io::get_finf(
		f_inf * fileinfo, 
		char*full_path, 
		char*fname )
{
	struct stat st;
	stat(full_path, &st);
	memcpy( fileinfo->fname, fname, MAX_FNAME);
	fileinfo->fstat = st;           
}

