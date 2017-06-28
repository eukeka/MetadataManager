#MetadataManager

MetadataManagerはファイル情報を管理するためのツールです．
./MetadataStore以下にディレクトリファイルを配置

* 対象環境	
	* 対象環境
		* Unix系OS（CentOSで確認 x86_64-redhat-linux）
		* gcc version 4.4.7 20120313 (Red Hat 4.4.7-18) (GCC)  
	* 必要なライブラリ
		* openssl-devel
		* boost_1_63_0 

* ビルド方法
	* # make 

* 実行方法 
	* #make_metadata file_name を実行することでメタデータを保管することができる．
	* #read_dir dir_name を実行することで，ディレクトリ以下の一覧を表示できる．
	* #read_fstat file_name を実行することで，ファイル情報を表示することができる．


