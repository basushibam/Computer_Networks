struct data{
	int arr_size;
	int* arr_pointer;
};

program ARR_SUM_PROG{
	version ARR_SUM_VERS{
		int get_arr_sum(data) = 1;

	}=2;
	
} = 0x23456789;