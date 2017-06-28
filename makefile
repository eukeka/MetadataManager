OBJDIR  = ./bin/
BIN   	= ./bin/


make_metadata: ./bin/metadata_format.o   ./bin/make_metadata.o ./bin/hash.o ./bin/serialize-dir_entry.o ./bin/serialize-metadata.o ./bin/metadata_io.o
	g++ -lboost_serialization -lcrypto  ./bin/metadata_format.o  ./bin/serialize-dir_entry.o  ./bin/serialize-metadata.o  ./bin/hash.o ./bin/make_metadata.o ./bin/metadata_io.o  -o make_metadata 


read_dir: ./bin/read_dir.o ./bin/hash.o ./bin/metadata_format.o  ./bin/serialize-dir_entry.o ./bin/serialize-metadata.o  ./bin/metadata_io.o
	g++ -lboost_serialization -lcrypto ./bin/metadata_format.o  ./bin/serialize-dir_entry.o  ./bin/serialize-metadata.o  ./bin/hash.o ./bin/read_dir.o  ./bin/metadata_io.o  -o read_dir 

read_fstat: ./bin/read_fstat.o ./bin/hash.o ./bin/metadata_format.o  ./bin/serialize-dir_entry.o ./bin/serialize-metadata.o  ./bin/metadata_io.o
	g++ -lboost_serialization -lcrypto ./bin/metadata_format.o ./bin/serialize-dir_entry.o  ./bin/serialize-metadata.o  ./bin/hash.o ./bin/read_fstat.o   ./bin/metadata_io.o  -o read_fstat 

$(BIN)hash.o:hash.cpp
	g++ -c hash.cpp -o ./bin/hash.o

$(BIN)serialize-dir_entry.o:serialize-dir_entry.cpp
	g++ -c serialize-dir_entry.cpp -o ./bin/serialize-dir_entry.o

$(BIN)serialize-metadata.o:serialize-metadata.cpp
	g++ -c serialize-metadata.cpp -o ./bin/serialize-metadata.o

$(BIN)searchMetaData.o:searchMetaData.cpp
	g++ -c searchMetaData.cpp -o ./bin/searchMetaData.o

$(BIN)make_metadata.o:make_metadata.cpp
	g++ -c make_metadata.cpp -o ./bin/make_metadata.o


$(BIN)read_dir.o:read_dir.cpp
	g++ -c read_dir.cpp -o ./bin/read_dir.o
$(BIN)read_fstat.o:read_fstat.cpp
	g++ -c read_fstat.cpp -o ./bin/read_fstat.o


$(BIN)metadata_format.o:metadata_format.cpp
	g++ -c metadata_format.cpp -o ./bin/metadata_format.o
	
$(BIN)metadata_io.o:metadata_io.cpp
	g++ -c metadata_io.cpp -o ./bin/metadata_io.o


clean:
	rm -f $(BIN)*.o 
	rm -f ./searchMetaData 
	rm -f ./make_metadata
	rm -f ./read_dir
	rm -f ./read_fstat
