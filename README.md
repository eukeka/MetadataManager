# MetadataManager

MetadataManagerはファイル情報を管理するためのツールです．<br>
ディレクトリエントリ（readdir），ファイル情報（stat）を管理します．<br>
* ソースの詳細は [docs](https://eukeka.github.io/MetadataManager/docs/html/index.html "docs") 

### 対象環境    
* 対象環境
  * Unix系OS（CentOSで確認 x86_64-redhat-linux）
  * gcc version 4.4.7 20120313 (Red Hat 4.4.7-18) (GCC)  
* 必要なライブラリ
  * openssl-devel
  * boost_1_63_0 

### ビルド方法
* "#make" 

### 実行方法 
* メタデータの保管
  * "#make_metadata file_name" 
* ディレクトリ以下の一覧を表示
  * "#read_dir dir_name" 
* ファイル情報を表示
  * "#read_fstat file_name" 
