#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/map.hpp>

#include "stat.hpp" 
#include "serialize.h" 
#include <sys/stat.h>
#include <map>
#include <stdio.h>

using namespace std;

class MyClass {
	public:
		map<string,f_inf> mp;
	private:
		// serialize
		friend class boost::serialization::access;
		template<class Archive>
			void serialize(Archive &ar, const unsigned int /* file_version */) 
			{
				ar & mp;
			}
};

class Metadata {
	public:
		f_inf metadata;
	private:
		// serialize
		friend class boost::serialization::access;
		template<class Archive>
			void serialize(Archive &ar, const unsigned int /* file_version */) 
			{
				ar & metadata;
			}
};


void write_serialize_metadata(char * decode_path, f_inf * metadata){
	Metadata md;
	md.metadata = *metadata;	

	ofstream ofs(decode_path);
	boost::archive::binary_oarchive oa(ofs);
	oa << (const Metadata&)md;
	ofs.close();
}

f_inf read_serialize_metadata( char * decode_path )
{
	Metadata md;
	ifstream ifs( decode_path );
	boost::archive::binary_iarchive ia(ifs);
	ia >> md;
	ifs.close();

	return md.metadata;
}





void put_data(char * decode_path, map<string, f_inf> * dir_entry_map)
{
	MyClass myclass;
	myclass.mp = *dir_entry_map;	

	ofstream ofs(decode_path);
	boost::archive::binary_oarchive oa(ofs);
	oa << (const MyClass&)myclass;
	ofs.close();
}

map<string, f_inf> get_data( char * decode_path )
{
	MyClass myclass;

	ifstream ifs( decode_path );
	boost::archive::binary_iarchive ia(ifs);
	ia >> myclass;
	ifs.close();

	return myclass.mp;
}


