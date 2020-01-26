struct directory_contents{
	char dir_contents[1000];
};

struct directory_name
{
	char dir_name[100];
};

program get_contents_prog{
	version get_contents_vers{
		directory_contents get_contents(directory_name)=1;
	}=2;

}=0x23456789;