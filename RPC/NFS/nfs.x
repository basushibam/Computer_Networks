struct data{
	
	char arr[1000];
};

program READ_FILE_PROG{
	version READ_FILE_VERS{
		data get_file_contents(data)=1;
	}=2;

} = 0x23456789;