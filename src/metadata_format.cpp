#ifndef _METADATA_FORMAT_
#define _METADATA_FORMAT_
#include "metadata.h" 

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <string.h>

using namespace std;

/*! @brief フルパスを取得する 
* @param q_name 	変換したい名前  
* @param full_path	変換後の絶対パス  
*/
void metadata_format::get_full_path(char*q_name, char*full_path){
 if( realpath( q_name, full_path ) == NULL ){
  cerr<<"Error : File is not exist" << endl;
  exit(0);
 }
}


/*! @brief ファイル名を取得
* @param full_path 絶対パス 
* @param fname ファイル名 
 */
void metadata_format::get_fname(char*full_path, char*fname){
	char tmppath[MAX_PATH]={};
	memcpy( tmppath, full_path, MAX_PATH );

	char *tmp; 
	tmp = strtok(tmppath,"/");

	if(strtok(NULL, "/") == NULL){
		strcpy(fname, tmp);
		
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
	memcpy( fname, res, MAX_FNAME );
}


// ディレクトリ名を取得
void metadata_format::get_dir_path( char*full_path, char*dir_path){

	// ディレクトリの場合はディレクトリ名を返す
	struct stat st={};
	stat(full_path, &st);

	if( (st.st_mode & S_IFMT) == S_IFDIR ){
		strcat(dir_path, full_path);	
		if( strcmp(dir_path, "/") != 0 ){
			strcat(dir_path, "/");	
		}
		return;	
	}

	int len1=0, len2=0, len=0;      

	char tmppath[MAX_PATH]={};
	strcpy( tmppath, full_path );

	char *tmp; 
	tmp = strtok(tmppath,"/");

	// rootディレクトリの判別
	if(tmp==NULL){
		strcpy( dir_path, "/" );
		return;
	}

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


// 保管先ディレクトリ名を取得
void metadata_format::get_store_dir_path( char*full_path, char*dir_path){

	// ディレクトリの場合はディレクトリ名を返す
	struct stat st={};
	stat(full_path, &st);
/*
	if( (st.st_mode & S_IFMT) == S_IFDIR ){
		strcat(dir_path, full_path);	
		if( strcmp(dir_path, "/") != 0 ){
			strcat(dir_path, "/");	
		}
		return;	
	}
*/

	int len1=0, len2=0, len=0;      

	char tmppath[MAX_PATH]={};
	strcpy( tmppath, full_path );

	char *tmp; 
	tmp = strtok(tmppath,"/");

	// rootディレクトリの判別
	if(tmp==NULL){
		strcpy( dir_path, "/" );
		return;
	}

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



// メタデータ保管先ディレクトリの作成 
void metadata_format::make_store_dir( char * store_path ){
	struct stat st={};
	if(stat( store_path , &st ) < 0) {
		mkdir( store_path ,0775 );
	}
}


#endif 
