#include "metadata.h"
#include "serialize.h"

#include <algorithm>
#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <sys/param.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

/* 
手順: 
-ファイル名からパスを取得(ファイル名:key 絶対パス)
-ファイルの情報を取得（保管用メタデータ）
-ディレクトリファイルの保管先名を取得
-ディレクトリファイルの保管先を作成
-ディレクトリファイルの保管先から既存のディレクトリファイルの読み込み(シリアライズしたバイナリデータの読み込み)
-ディレクトリファイルへメタデータを追加
-ディレクトリファイルへ更新データを書き込み

< Note TODO>
	-ディレクトリの保存を考えてない
	-ディレクトリエントリが多すぎると，メモリから溢れるかもしれない
	-ディレクトリファイル1の展開サイズを1Mほどを上限にする
	-1Mを越えればファイルを分けて書き込む(DIR名+ファイル番号)	
	-ファイル名やパスの最大値を制限する
	-ディレクトリファイルの構造をdirent構造体のリストに変更
*/

void make_metadata(char * q_name);

int main(int argc, char * argv[]){

	if(argc != 2){
		cerr << "Error : Need to specify a file name" << endl;
		return 0;
	}
	if(strlen(argv[1]) > MAX_FNAME ) {
		cerr << "Error : File name is too long" << endl;
		return 0;
	}
	char * q_name = argv[1];
	
	make_metadata(q_name);	
	
	return 0;
}


void take_dir_path( char*full_path, char*dir_path);
void make_store_dir( char*store_path );

void read_dir_file( vector<string> *dir_entry, char* metadata_store_path, char*dir_fname);
void add_dir_entry( vector<string> &dir_entry , char * full_path );
void write_dir_file( vector<string> *dir_entry, char* store_path, char*full_path);


int read_metadata(   f_inf *metadata, char* store_path, char* fullpath_hash);
void take_finf(  f_inf * finf,   char * full_path,  char * fname    );
void write_metadata( f_inf *metadata, char* store_path, char* fullpath_hash );


void make_metadata(char * q_name){
	// ファイル名(表示用)
	char fname[ MAX_FNAME ]={};
	// 絶対パス
	char full_path[ MAX_PATH ]={};
	// ディレクトリのパス(最後はスラッシュを付ける)
	char dir_path[ MAX_PATH ]={};

	// メタデータファイル名（絶対パスのhash）
	char fullpath_hash[ MAX_FNAME ]={}; 
	// ディレクトリファイル名（ディレクトリパスのハッシュ)
	char dirfname_hash[ MAX_FNAME ]={};

	// メタデータの格納先パス
	char store_path[ MAX_PATH ]={};
	
	// ファイル情報(メタデータ)
	f_inf metadata;
	// ディレクトリ以下のファイル名リスト
	vector<string> dir_entry;	

	
	// 絶対パスを取得
	get_full_path( q_name, full_path);
	// ファイル名を取得
	get_fname( full_path, fname);
	// ディレクトリパスを取得
	take_dir_path( full_path, dir_path );
	
	// ディレクトリパスとファイルパスからハッシュを求める
	conv_hash( full_path, fullpath_hash );
	conv_hash( dir_path,  dirfname_hash );
		

	// メタデータの保存先の取得
	strncpy( store_path, STORE_DIR, MAX_PATH );
	// メタデータとディレクトリファイルの保管先の作成
	make_store_dir( store_path );

	// 既存ディレクトリファイルの読み込み
	read_dir_file( &dir_entry, store_path, dirfname_hash );
	// ディレクトリファイルへの追加	
	add_dir_entry( dir_entry, fname );
	// ディレクトリファイルの書き込み
	write_dir_file( &dir_entry, store_path, dirfname_hash );	


	// 既存メタデータの読み込み
	int finddata = read_metadata( &metadata, store_path, fullpath_hash);

	// ファイルのメタデータを取得
	take_finf( &metadata, full_path, fname );	
	// メタデータの書き込み 
	write_metadata( &metadata, store_path, fullpath_hash );	
}






// ディレクトリ名を取得
void take_dir_path( char*full_path, char*dir_path){
	int len1=0, len2=0, len=0;	

	char tmppath[MAX_PATH]={};
	strcpy( tmppath, full_path );

	char *tmp; 
	tmp = strtok(tmppath,"/");

	if(strtok(NULL, "/") == NULL){
		len1 = strlen( tmp );	
		len2 = strlen( full_path );	
		len = len2 - len1;
		memcpy( dir_path, full_path, len );
		dir_path[len] = '\0';

		return;
	}

	char res[MAX_FNAME]={0};
	int i=1;
	while(tmp != NULL){
		tmp = strtok(NULL,"/");
		if(tmp != NULL){
			memcpy(res, tmp, strlen(tmp)+1);
		}
	}

	len1 = strlen( res );	
	len2 = strlen( full_path );	
	len = len2 - len1;
	memcpy( dir_path, full_path, len );
	dir_path[len] = '\0';
	
}




// メタデータに追加するためのファイル情報を取得
void take_finf(f_inf * metadata, char*full_path, char*fname){
	struct stat st;
	stat(full_path, &st);
	memcpy(metadata->fname, fname, MAX_FNAME);
	metadata->fstat = st; 		
}


// メタデータ保管先ディレクトリの作成 
void make_store_dir( char * store_path ){
	struct stat st={};
	if(stat( store_path , &st ) < 0) {
		mkdir( store_path ,0775 );
	}
}


// ディレクトリエントリからの読込
void read_dir_file( vector<string> *dir_entry, char* metadata_store_path, char*dir_fname){
	char direntry_filepath[MAX_PATH]={};
	strcpy(direntry_filepath, metadata_store_path );
	strcat(direntry_filepath, "/");
	strcat(direntry_filepath, dir_fname );

	struct stat st={};
	if(stat(direntry_filepath, &st) == 0 ){
		*dir_entry = decode_dir_entry( direntry_filepath );	
	}else{
		//cout<<"not found dir_entry file"<<endl;
	}

	vector<string> tmp = *dir_entry;
	cout<<"\n---------dir_entry--------"<<endl;
	int siz = tmp.size();		
	for(int i=0; i<siz; i++){
		cout<<tmp[i]<<endl;
	}
	cout<<"--------------------------\n"<<endl;
}

void add_dir_entry( vector<string> &dir_entry , char * full_path ){
	vector<string>::iterator itr = find(dir_entry.begin(), dir_entry.end(), full_path);
	if( itr == dir_entry.end() ){
		//cout<<"additional entry data"<<endl;	
		dir_entry.push_back(full_path);
	}else{
		//cout<<"file is already registerd direntry_file"<<endl;	
	}
}

// ディレクトリエントリへの書き込み
void write_dir_file( vector<string> *dir_entry, char* store_path, char* dirfname_hash ){
	char direntry_filepath[MAX_PATH]={};
	strcpy(direntry_filepath, store_path );
	strcat(direntry_filepath, dirfname_hash );
	
	encode_dir_entry( direntry_filepath, dir_entry);	
}





// メタデータの読み込み（ファイルがなければ読み込まない）
int read_metadata( f_inf *metadata, char* store_path, char* fullpath_hash ){
	int res=0;

	char metadata_path[MAX_PATH]={};
	strcat( metadata_path, store_path );
	strcat( metadata_path, fullpath_hash );

	struct stat st;
	if(stat( metadata_path, &st ) == 0){
		*metadata = read_serialize_metadata( metadata_path );       
		//cout<<"metadata found"<<endl;
		res=1;
	}else{
		//cout<<"metadata not found!!"<<endl;
		res=0;
	}
		
	if( res == 1){
		cout<<"\n-------metadata--------"<<endl;
		printf("file name   %s\n",  metadata->fname);
		printf("st_dev      %10d\n", (int)metadata->fstat.st_dev);
		printf("st_ino      %10d\n", (int)metadata->fstat.st_ino);
		printf("st_mode     %10d\n", (int)metadata->fstat.st_ino);
		cout<<"--------------------------\n"<<endl;
	}
	return res;
}

// メタデータの書き込み
void write_metadata( f_inf *metadata, char* store_path, char* fullpath_hash){
	char metadata_path[MAX_PATH]={};
	strcat(metadata_path, store_path);
	strcat(metadata_path, fullpath_hash );
	
	write_serialize_metadata( metadata_path, metadata);	
	//cout<<"metadata write"<<endl;
}










