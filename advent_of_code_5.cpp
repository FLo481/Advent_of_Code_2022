#include <iostream>

using namespace std;

// Starting positions
char starting_positions[9][100] = {{'D', 'T', 'W', 'F', 'J', 'S', 'H', 'N'},
    {'H', 'R', 'P', 'Q', 'T', 'N', 'B', 'G'},
    {'L', 'Q', 'V'},
    {'N', 'B', 'S', 'Q', 'R', 'Q'},
    {'N', 'D', 'F', 'T', 'V', 'M', 'B'},
    {'M', 'D', 'B', 'V', 'H', 'T', 'R'},
    {'D', 'B', 'Q', 'J'},
    {'D', 'N', 'J', 'V', 'R', 'Z', 'H', 'Q'},
    {'B', 'N', 'H', 'M', 'S'},
};

void clear_arr(int* arr)
{
	for(int* p_arr = arr; (p_arr - arr) < 3; p_arr++)
		*p_arr = 0;
}

char* find_top(char* arr)
{
	char* top;

	for(char* top = arr; (top - arr) < 100 ; top++)
	{
		//printf("%c\n", *top);
		if(*top == '\0')
		{
			return --top;
		}
		
		if(top == NULL)
		    return NULL;
	}
	
	return NULL;
}

void move_crates_one_by_one(int* instruction_arr)
{
	char* top_char_source;
	char* top_char_target;
	char* top_char;
	
	//printf("Move %d from %d to %d\n", instruction_arr[0], instruction_arr[1], instruction_arr[2]);

	for(int i = 0; i < instruction_arr[0]; i++)
	{
	    top_char_source = find_top(starting_positions[instruction_arr[1] - 1]);
	    top_char_target = find_top(starting_positions[instruction_arr[2] - 1]);	    
		*(++top_char_target) = *top_char_source;
		*top_char_source = '\0';
	}
}

void move_multiple_crates_at_once(int* instruction_arr)
{
    char* top_char_source;
    char* top_char_target;
    char* top_char;
    char temp_ch[100];
    
    //printf("Move %d from %d to %d\n", instruction_arr[0], instruction_arr[1], instruction_arr[2]);
    
    top_char_source = find_top(starting_positions[instruction_arr[1] - 1]);
    
    top_char_source -= (instruction_arr[0] - 1);
    
    for(char* p_temp = temp_ch; (p_temp - temp_ch) < instruction_arr[0]; p_temp++)
    {
        *p_temp = *top_char_source;
        *(top_char_source++) = '\0';
    }
        
    temp_ch[instruction_arr[0]] = '\0';
    
    for(int i = 0; i < instruction_arr[0]; i++)
    {
        top_char_target = find_top(starting_positions[instruction_arr[2] - 1]);
        *(++top_char_target) = temp_ch[i];
    }
}    

void read_input_perform_actions(char* top_chars)
{
	FILE* fp;
	fp = fopen("input_adv5.txt", "r");
	char input_ch, last_ch;
	char temp_ch[2];
	int instruction_arr[3] = {0, 0, 0};
	int counter = 0;

	if(fp == NULL)
    {
        printf("File does not exist\n");
    }
    else
    {
        while((input_ch = fgetc(fp)) != EOF)
        {
			if(counter == 3)
			{
				counter = 0;
				if(instruction_arr[0] == 1)
				    move_crates_one_by_one(instruction_arr);
				else
				    move_multiple_crates_at_once(instruction_arr);
				clear_arr(instruction_arr);
				continue;
			}
			else
			{
                if(isdigit(last_ch) && isdigit(input_ch))
                {
                    temp_ch[0] = last_ch;
                    temp_ch[1] = input_ch;
                    instruction_arr[counter] = atoi(temp_ch);
                    temp_ch[0] = temp_ch[1] = '\0';
                    input_ch = '\0';
                    counter++;
                }
                else if(isdigit(last_ch) && (input_ch == ' ' || input_ch == '\n'))
                {
                    instruction_arr[counter] = last_ch - '0';
                    counter++;
                }
			}
			
			last_ch = input_ch;
		}
    }
}

int main()
{
    char* top_char;
	char top_chars[9] = {'0', '0', '0', '0', '0', '0', '0', '0', '0'};

	read_input_perform_actions(top_chars);

	printf("The topmost characters are:\n");

   // Find top chars
    for(int i = 0; i < 9 ; i++)
    {
        top_char = find_top(starting_positions[i]);
        top_chars[i] = *top_char;
        printf("%c", top_chars[i]);
    }

	printf("\n");

	return 0;
}
