#ifndef _HEAD_
#define _HEAD_


#include <sys/stat.h>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include "metadata.h"
#include "stat.hpp" 

#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>


using namespace std;

/*! @brief ディレクトリファイルをシリアライズするクラス */
class DirEntry_Serialize {
	public:
		vector<string> dir_entry;
	private:
		friend class boost::serialization::access;
		template<class Archive>
			void serialize(Archive &ar, const unsigned int ) 
			{
				ar & dir_entry;
			}
};

/*! @ brief  ファイル情報をシリアライズするクラス */
class Metadata_Serialize {
	public:
		f_inf metadata;
	private:
		friend class boost::serialization::access;
		template<class Archive>
			void serialize(Archive &ar, const unsigned int ) 
			{
				ar & metadata;
			}
};

    
/*! @brief シリアライズ化されたディレクトリエントリを書き込む */
extern void 					encode_dir_entry( char * encode_path, vector<string> * dir_entry);
/*! @brief シリアライズ化されたディレクトリエントリを読み込む */
extern vector<string> decode_dir_entry( char * decode_path );


/*! @brief シリアライズ化されたメタデータ(ファイル情報）を書き込む */
extern void		write_serialize_metadata( char * decode_path, f_inf * metadata);
/*! @brief シリアライズ化されたメタデータを読み込む */
extern f_inf	read_serialize_metadata(  char * decode_path );


#endif
