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
		cerr << "Error : Need to specify a file name" << endl;
		return 0;
	}
	if(strlen(argv[1]) > MAX_FNAME ) {
		cerr << "Error : File name is too long" << endl;
		return 0;
	}
	char * q_name = argv[1];

	make_metadata(q_name);	

	cout<<"write metadata"<<endl;	
	return 0;
}



/** 
 * 指定したパスのメタデータ情報を保存する
 * @param q_name 格納したいファイルorディレクトリの名前
 */
void make_metadata(char * q_name){
	// ファイル名 & パス情報
	char store_path 		[ MAX_PATH 	]={}; // メタデータの保存先
	char full_path			[ MAX_PATH 	]={}; // 絶対パス
	char fname					[ MAX_FNAME ]={}; // ファイル名
	char store_dir_path	[ MAX_PATH 	]={}; // 保存先ディレクトリパス(スラッシュ必須)

	// メタデータファイル名（絶対パスのhash）
	char fileinfo_fname_hash[ MAX_FNAME ]={};  // ファイル情報の保存名
	char direntry_fname_hash[ MAX_FNAME ]={};  // ディレクトリファイルの保存名

	// ファイル情報(メタデータ)
	f_inf fileinfo;
	// ディレクトリ以下のファイル名リスト
	vector<string> dir_entry;	


	
	metadata_format mf;

	// 絶対パスを取得
	mf.get_full_path( q_name, full_path );	
	
	// ファイル名を取得
	mf.get_fname( full_path, fname);
	// 保管先ィレクトリパスを取得
	mf.get_store_dir_path( full_path, store_dir_path );

	// ディレクトリパスとファイルパスからハッシュを求める
	conv_hash( full_path, fileinfo_fname_hash );
	conv_hash( store_dir_path,  direntry_fname_hash );

	// メタデータの保存先の取得
	strncpy( store_path, STORE_DIR, MAX_PATH );
	// メタデータとディレクトリファイルの保管先の作成
	mf.make_store_dir( store_path );


	metadata_io m_io;

	// ディレクトリファイルの操作
	m_io.read_dir_file( &dir_entry, store_path, direntry_fname_hash );
	m_io.add_dir_entry( dir_entry, fname );
	m_io.write_dir_file( &dir_entry, store_path, direntry_fname_hash );	


	// メタデータファイルの操作
	m_io.read_fileinfo( &fileinfo, store_path, fileinfo_fname_hash );
	m_io.get_finf( &fileinfo, full_path, fname );	
	m_io.write_fileinfo( &fileinfo, store_path, fileinfo_fname_hash );	
}













