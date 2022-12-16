#include <iostream>

using namespace std;

void read_input_fill_arr(char* input_arr)
{
    FILE* fp;
    fp = fopen("input_adv16.txt", "r");
    char input_ch;
    char last_ch;
    unsigned int index = 0;
    unsigned int lead_to_str_comes_up = 0;
    unsigned int char_counter = 1;
    unsigned int char_counter_2 = 0;
    
    if(fp == NULL)
    {
        printf("File does not exist\n");
    }
    else
    {
        while((input_ch = fgetc(fp)) != EOF)
        {
            if(char_counter == 8)
            {
                input_arr[index++] = last_ch;
                input_arr[index++] = input_ch;
                input_arr[index++] = ';';
            }
            
            if(char_counter_2 > 23)
            {
                if(input_ch != ' ' && input_ch != '\n')
                    input_arr[index++] = input_ch;
            }
            
            if(input_ch == '\n')
            {
                char_counter = 0;
                char_counter_2 = 0;
                lead_to_str_comes_up = 0;
                input_arr[index++] = '#';
            }
            else if(isdigit(input_ch))
            {
                input_arr[index++] = input_ch;
            }
            else if(input_ch == ';')
            {
                input_arr[index++] = ';';
                lead_to_str_comes_up = 1;
            }
            
            if(lead_to_str_comes_up)
                char_counter_2++;
            
            char_counter++;
            last_ch = input_ch;
        }
        
        input_arr[index] = '\0';
    }
}

void print_arr(char* input_arr)
{
    for(char* p_arr = input_arr; *p_arr != '\0'; p_arr++)
    {
        if(*p_arr == '#')
            printf("\n");
        else
            printf("%c", *p_arr);
    }
}

void find_possible_paths()
{
    
}

int calc_pressure_release()
{
    int pressure_rel = 0;
    
    return pressure_rel;
}

int main()
{
    char input_arr[5000];
    
    read_input_fill_arr(input_arr);
    
    print_arr(input_arr);
    
    return 0;
}
