#include <stdio.h>
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>

#include "stat.hpp" 
#include "serialize.h" 
#include <sys/stat.h>
#include <vector>
#include <map>

using namespace std;

/*! @brief ディレクトリのエントリをエンコードして保存
 * @param char * encode_path 保存先パス
 * @param vector dir_entry 保存するディレクトリエントリ 
 */
void encode_dir_entry( char * encode_path, vector<string> * dir_entry){
	DirEntry_Serialize de;
	de.dir_entry = * dir_entry;

	ofstream ofs(encode_path);
	boost::archive::binary_oarchive oa(ofs);
	oa << ( const DirEntry_Serialize& )de;
	ofs.close();
}
/*! @brief dir_entryをデコードして読み込み 
 * @param char * decode_path 保存先パス
 * @return vector dir_entry ディレクトリエントリ
 */
vector<string> decode_dir_entry( char * decode_path ){
	DirEntry_Serialize de;

  ifstream ifs( decode_path );
  boost::archive::binary_iarchive ia(ifs);
  ia >> de;
	ifs.close();
	
	return de.dir_entry;
}


/*! @brief ファイル情報をエンコードして書き込み
 * @param decode_path エンコードするパス（保存パス）
 * @param metadata 書き込むファイル情報 
 */ 
void write_serialize_metadata(char * decode_path, f_inf * metadata){
	Metadata_Serialize md;
	md.metadata = *metadata;        

	ofstream ofs(decode_path);
	boost::archive::binary_oarchive oa(ofs);
	oa << (const Metadata_Serialize&)md;
	ofs.close();
}

/*! @brief ファイル情報をデコードして読み込み
 * @param decode_path デコードするためのパス
 * @return f_inf ファイル情報の構造体 
 */
f_inf read_serialize_metadata( char * decode_path )
{
	Metadata_Serialize md;
	ifstream ifs( decode_path );
	boost::archive::binary_iarchive ia(ifs);
	ia >> md;
	ifs.close();

	return md.metadata;
}



