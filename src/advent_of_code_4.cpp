#include <iostream>

using namespace std;

void clear_array(char* arr, int len)
{
	for(char* p_temp = arr; (p_temp - arr) <= len ; p_temp++)
	{
		*arr = '\0';
	}
}

int check_fully_contain(int* range_1,int* range_2)
{
	int fully_contain = 0;

	if((range_1[0] >= range_2[0] && range_1[1] <= range_2[1]) || (range_2[0] >= range_1[0] && range_2[1] <= range_1[1]))
		fully_contain = 1;

	return fully_contain;
}

int check_overlap(int* range_1, int* range_2)
{
	int overlapping = 0;

	if(check_fully_contain(range_1, range_2) == 1)
		return 1;

	if((range_1[1] >= range_2[0] && range_1[1] < range_2[1]) || (range_2[1] >= range_1[0] && range_2[1] < range_1[1]))
		overlapping = 1;
	else if((range_1[1] > range_2[0] && range_1[1] <= range_2[1]) || (range_2[1] > range_1[0] && range_2[1] <= range_1[1]))
		overlapping = 1;

	return overlapping;
}

int read_file_find_containment_count()
{
	int count = 0;
	int is_upper_range_limit = 0;
        char input_ch;
	int input_range_1[2] = {0, 0};
	int input_range_2[2] = {0, 0};
        char temp_ch[2];
	int temp_ch_len = 0;
        FILE *fp;

        fp = fopen("input_adv4.txt", "r");

        if(fp == NULL)
        {
                printf("File does not exist");
        }
        else
        {
                while((input_ch = fgetc(fp)) != EOF)
                {
			if(input_ch == '-')
			{
				if(!is_upper_range_limit)
				{
					is_upper_range_limit = 1;
					if(temp_ch_len == 1)
						temp_ch[1] = '\0';
					//printf("%c %c Length: %d\n", temp_ch[0], temp_ch[1], temp_ch_len);
					input_range_1[0] = atoi(temp_ch);
					clear_array(temp_ch, temp_ch_len);
					temp_ch_len = 0;
				}
				else
				{
					is_upper_range_limit = 0;
					if(temp_ch_len == 1)
                                                temp_ch[1] = '\0';
					input_range_2[0] = atoi(temp_ch);
					clear_array(temp_ch, temp_ch_len);
					temp_ch_len = 0;
				}
			}
			else if(input_ch == ',')
			{
				input_range_1[1] = atoi(temp_ch);
				clear_array(temp_ch, temp_ch_len);
				temp_ch_len = 0;
			}
			else if(input_ch == '\n')
			{
				input_range_2[1] = atoi(temp_ch);
				clear_array(temp_ch, temp_ch_len);
				temp_ch_len = 0;
	                        //printf("Range 1: %d %d; Range 2: %d %d\n", input_range_1[0], input_range_1[1], input_range_2[0], input_range_2[1]);
				// FOR PART 1
				//count += check_fully_contain(input_range_1, input_range_2);
				// FOR PART 2
				count += check_overlap(input_range_1, input_range_2);
				input_range_1[0] = input_range_1[1] = input_range_2[0] = input_range_2[1] = 0;
			}
			else
			{
				if(input_ch != '\n')
				{
					temp_ch[temp_ch_len] = input_ch;
					temp_ch_len++;
				}
			}
                }
                        //printf("%c", input_ch);
        }

        fclose(fp);

        return count;
}

int main()
{
	int count = 0;

	count = read_file_find_containment_count();
	// FOR PART 1
	//printf("%d fully contain others\n", containment_count);
	// FOR PART 2
	printf("%d are overlapping\n", count);

	return 0;
}
