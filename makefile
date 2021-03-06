BIN   	= ./obj/

all: make_metadata read_dir read_fstat

make_metadata: ./obj/metadata_format.o ./obj/make_metadata.o ./obj/hash.o ./obj/serialize.o ./obj/metadata_io.o
	g++ -lboost_serialization -lcrypto ./obj/metadata_format.o ./obj/serialize.o  ./obj/hash.o ./obj/make_metadata.o ./obj/metadata_io.o  -o make_metadata 


read_dir: ./obj/read_dir.o ./obj/hash.o ./obj/metadata_format.o ./obj/serialize.o ./obj/metadata_io.o
	g++ -lboost_serialization -lcrypto ./obj/metadata_format.o  ./obj/serialize.o  ./obj/hash.o ./obj/read_dir.o  ./obj/metadata_io.o  -o read_dir 

read_fstat: ./obj/read_fstat.o ./obj/hash.o ./obj/metadata_format.o ./obj/serialize.o  ./obj/metadata_io.o
	g++ -lboost_serialization -lcrypto ./obj/metadata_format.o  ./obj/serialize.o  ./obj/hash.o ./obj/read_fstat.o   ./obj/metadata_io.o  -o read_fstat 


$(BIN)hash.o:./src/hash.cpp
	g++ -c ./src/hash.cpp -o ./obj/hash.o


$(BIN)make_metadata.o:./src/make_metadata.cpp
	g++ -c ./src/make_metadata.cpp -o ./obj/make_metadata.o
$(BIN)read_dir.o:./src/read_dir.cpp
	g++ -c ./src/read_dir.cpp -o ./obj/read_dir.o
$(BIN)read_fstat.o:./src/read_fstat.cpp
	g++ -c ./src/read_fstat.cpp -o ./obj/read_fstat.o


$(BIN)serialize.o:./src/serialize.cpp
	g++ -c ./src/serialize.cpp -o ./obj/serialize.o


$(BIN)metadata_format.o:./src/metadata_format.cpp
	g++ -c ./src/metadata_format.cpp -o ./obj/metadata_format.o
$(BIN)metadata_io.o:./src/metadata_io.cpp
	g++ -c ./src/metadata_io.cpp -o ./obj/metadata_io.o


clean:
	rm -f $(BIN)*.o 
	rm -f ./searchMetaData 
	rm -f ./make_metadata
	rm -f ./read_dir
	rm -f ./read_fstat
