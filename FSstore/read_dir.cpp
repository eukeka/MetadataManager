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

void make_metadata(char * q_name);

int main(int argc, char * argv[]){

	if(argc != 2){
		cerr << "Error : Need to specify a dir name" << endl;
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



void make_metadata(char * q_name){
	// ファイル名 & パス情報
	char store_path [ MAX_PATH 	]={}; // メタデータの保存先
	char full_path	[ MAX_PATH 	]={}; // 絶対パス
	char dir_path		[ MAX_PATH 	]={}; // ディレクトリパス(スラッシュ必須)

	// メタデータファイル名（絶対パスのhash）
	char direntry_fname_hash[ MAX_FNAME ]={};  // ディレクトリファイルの保存名

	// ファイル情報(メタデータ)
	f_inf fileinfo;
	// ディレクトリ以下のファイル名リスト
	vector<string> dir_entry;	

	
	metadata_format mf;

	// 絶対パスを取得
	mf.get_full_path( q_name, full_path );	
	// ディレクトリパスを取得
	mf.get_dir_path( full_path, dir_path );

	// ディレクトリパスとファイルパスからハッシュを求める
	conv_hash( dir_path, direntry_fname_hash );
	// メタデータの保存先の取得
	strncpy( store_path, STORE_DIR, MAX_PATH );


	
	metadata_io m_io;

	// 既存ディレクトリファイルの読み込み
	m_io.read_dir_file( &dir_entry, store_path, direntry_fname_hash );
}













