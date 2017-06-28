#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>

#include "stat.hpp" 
#include "serialize.h" 
#include <sys/stat.h>
#include <vector>
#include <stdio.h>

using namespace std;

// ディレクトリファイルのRead/Write用関数
class DirEntry {
public:
		vector<string> dir_entry;
private:
    // serialize
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int /* file_version */) 
    {
				ar & dir_entry;
    }
};

// dir_entryをエンコードして保存
void encode_dir_entry( char * encode_path, vector<string> * dir_entry){
	DirEntry de;
	de.dir_entry = * dir_entry;

	ofstream ofs(encode_path);
	boost::archive::binary_oarchive oa(ofs);
	oa << (const DirEntry&)de;
	ofs.close();
}

// dir_entryをデコードして読み込み
vector<string> decode_dir_entry( char * decode_path ){
	DirEntry de;

  ifstream ifs( decode_path );
  boost::archive::binary_iarchive ia(ifs);
  ia >> de;
	ifs.close();
	
	return de.dir_entry;
}

