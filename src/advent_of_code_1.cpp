#include <iostream>

using namespace std;

void empty_array(char* char_array)
{
	for(int i = 0; i < 20; i++)
		*(char_array++) = '\0';
}

int read_file_find_maximum()
{
	int maximum = 0;
	int temp_int = 0;
	int temp_ch_counter = 0;
	char input_ch;
	char temp_ch[20];
	char last_ch = '0';
	FILE *fp;

	fp = fopen("input_adv1.txt", "r");

	if( fp == NULL)
	{
		printf("File does not exist");
	}
	else
	{
		while((input_ch = fgetc(fp)) != EOF)
		{
			if(input_ch == '\n' && last_ch == '\n')
			{
				if(temp_int > maximum)
				{
					maximum = temp_int;
				}
				temp_int = 0;
			}
			if(input_ch == '\n')
			{
				temp_ch[temp_ch_counter + 1] = '\0';
				temp_int += atoi(temp_ch);
				empty_array(temp_ch);
				temp_ch_counter = 0;
				//printf("%d\n", temp_int);
			}
			else
			{
				temp_ch[temp_ch_counter] = input_ch;
				temp_ch_counter += 1;
			}
			//printf("%c", input_ch);
			//printf("%c", temp_ch[temp_ch_counter]);
			last_ch = input_ch;
		}
	}

	fclose(fp);

	return maximum;
}

int* find_minimum(int* input_array)
{
	int* min_pointer = NULL;

	for(int i = 0 ; i < 3 ; i++)
	{
		//printf("Top three value array: %d\n", input_array[i]);
		for(int j = 0; j < 3; j++)
		{
			if(input_array[j] < input_array[i])
			{
				min_pointer = &input_array[j];
			}
		}
	}
	//printf("Minimum: %d\n", *min_pointer);

	return min_pointer;
}

void compare_values(int number, int *value_array)
{
	int* min_pointer = NULL;

	for(int i = 0; i < 3; i++)
	{
		if(value_array[i] == 0)
		{
			value_array[i] = number;
			break;
		}
	}

	if(number > value_array[0] || number > value_array[1] ||number > value_array[2])
	{
		if((min_pointer = find_minimum(value_array)) != NULL)
		{
			*min_pointer = number;
		}
	}
}

int read_file_find_top_three()
{
	int top_three_sum = 0;
	int top_three_values[3] = {0,0,0};
        int temp_int = 0;
        int temp_ch_counter = 0;
        char input_ch;
        char temp_ch[20];
        char last_ch = '0';
        FILE *fp;

        fp = fopen("input_adv1.txt", "r");

        if( fp == NULL)
        {
                printf("File does not exist");
        }
        else
        {
                while((input_ch = fgetc(fp)) != EOF)
                {
                        if(input_ch == '\n' && last_ch == '\n')
                        {
				compare_values(temp_int, top_three_values);
				//printf("%d\n", temp_int);
                                temp_int = 0;
                        }
                        if(input_ch == '\n')
                        {
                                temp_ch[temp_ch_counter + 1] = '\0';
                                temp_int += atoi(temp_ch);
                                empty_array(temp_ch);
                                temp_ch_counter = 0;
                                //printf("%d\n", temp_int);
                        }
                        else
                        {
                                temp_ch[temp_ch_counter] = input_ch;
                                temp_ch_counter += 1;
                        }
                        //printf("%c", input_ch);
                        //printf("%c", temp_ch[temp_ch_counter]);
                        last_ch = input_ch;
                }
        }

        fclose(fp);

	for(int i = 0; i < 3; i++)
	{
		//printf("%d\n", top_three_values[i]);
		top_three_sum += top_three_values[i];
	}

	return top_three_sum;
}

int main()
{
	int maximum = 0;
	int top_three_sum = 0;

	maximum = read_file_find_maximum();
	top_three_sum = read_file_find_top_three();

	printf("The maximum is: %d\n", maximum);
	printf("The top three count is: %d\n", top_three_sum);

	return 0;
}
