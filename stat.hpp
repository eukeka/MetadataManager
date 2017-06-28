#ifndef _STAT_
#define _STAT_


#include <boost/serialization/serialization.hpp>
#include <sys/stat.h>
#include "metadata.h"

 namespace boost {
   namespace serialization {
    template <class Archive>
       void serialize(Archive& ar, f_inf & st, const unsigned int version) 
       {
				 ar & st.fname;	
         ar & st.fstat.st_dev;
				 ar & st.fstat.st_ino;
				 ar & st.fstat.st_nlink;
				 ar & st.fstat.st_uid;
				 ar & st.fstat.st_gid;
				 ar & st.fstat.st_rdev;
				 ar & st.fstat.st_size;
				 ar & st.fstat.st_blksize;
				 ar & st.fstat.st_blocks;
				 ar & st.fstat.st_atime;
				 ar & st.fstat.st_mtime;
				 ar & st.fstat.st_ctime;
       }
   }
 }

#endif
