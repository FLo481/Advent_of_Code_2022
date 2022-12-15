#include <iostream>
#include <cstring>

using namespace std;

char CRT_screen[241];

void print_arr(char* input_arr)
{
    for(char* p_arr = input_arr; *p_arr != '\0'; p_arr++)
    {
        if(*p_arr != '#')
           printf("%c", *p_arr);
        else
            printf("\n");
    }
}

void read_input_fill_arr(char* input_arr)
{
    FILE* fp;
    fp = fopen("input_adv10.txt", "r");
    char input_ch;
    unsigned int index = 0;
    
    if(fp == NULL)
    {
        printf("File does not exist\n");
    }
    else
    {
        while((input_ch = fgetc(fp)) != EOF)
        {
            if(input_ch == ' ')
            {
                input_arr[index++] = '&';
            }
            else if(input_ch == '\n')
            {
                input_arr[index++] = '#';
            }
            else
            {
                input_arr[index++] = input_ch;
            }
        }
        
        input_arr[index] = '\0';
    }
}

void del_arr(char* arr, int len)
{
    for(char* p_arr = arr; (p_arr - arr) < len ; p_arr++)
        *p_arr = '\0';
}

int calc_signal_strength(unsigned int cycle_counter, unsigned int x_value)
{
    int signal_strength = 0;
    
    switch (cycle_counter)
    {
        case 20:
            //printf("X value %dth cycle: %d\n", cycle_counter, x_value);
            signal_strength += x_value * cycle_counter;
            //printf("Signal strength: %d\n", signal_strength);
            break;
        case 60:
            //printf("X value %dth cycle: %d\n", cycle_counter, x_value);
            signal_strength += x_value * cycle_counter;
            //printf("Signal strength: %d\n", signal_strength);
            break;
        case 100:
            //printf("X value %dth cycle: %d\n", cycle_counter, x_value);
            signal_strength += x_value * cycle_counter;
            //printf("Signal strength: %d\n", signal_strength);
            break;
        case 140:
            //printf("X value %dth cycle: %d\n", cycle_counter, x_value);
            signal_strength += x_value * cycle_counter;
            //printf("Signal strength: %d\n", signal_strength);
            break;
        case 180:
            //printf("X value %dth cycle: %d\n", cycle_counter, x_value);
            signal_strength += x_value * cycle_counter;
            //printf("Signal strength: %d\n", signal_strength);
            break;
        case 220:
            //printf("X value %dth cycle: %d\n", cycle_counter, x_value);
            signal_strength += x_value * cycle_counter;
            //printf("Signal strength: %d\n", signal_strength);
            break;
    }
    
    return signal_strength;
}

void draw_on_CRT(int x_value, int cycle_counter)
{
    int CRT_matrix_pos = cycle_counter - 1;
    int sprite_pos = x_value; // Middle position of sprite
    
    if(cycle_counter > 40 && cycle_counter < 81)
        sprite_pos += 40;
    else if(cycle_counter > 80 && cycle_counter < 121)
        sprite_pos += 80;
    else if(cycle_counter > 120 && cycle_counter < 161)
        sprite_pos += 120;
    else if(cycle_counter > 160 && cycle_counter < 201)
        sprite_pos += 160;
    else if(cycle_counter > 200 && cycle_counter < 241)
        sprite_pos += 200;
    
    //printf("Cycle counter: %d X register: %d\n", cycle_counter, x_value);
    
    if(CRT_matrix_pos == sprite_pos - 1 || CRT_matrix_pos == sprite_pos || CRT_matrix_pos == sprite_pos + 1)
    {
        CRT_screen[CRT_matrix_pos] = '#';
        //printf("%c\n", CRT_screen[CRT_matrix_pos]);
    }
    else
    {
        CRT_screen[CRT_matrix_pos] = '.';
        //printf("%c\n", CRT_screen[CRT_matrix_pos]);
    }
    
    if(cycle_counter == 240)
        CRT_screen[cycle_counter] = '\0';
}

int read_instructions(char* input_arr)
{
    unsigned int signal_strength = 0;
    unsigned int x_value = 1;
    unsigned int cycle_counter = 0;
    const char* noop_instr = "noop";
    const char* addx_instr = "addx";
    char* p_arr = input_arr;
    char* pp_arr;
    char* ppp_arr;

    char temp_arr[4]   = {'\0', '\0', '\0', '\0'};
    char temp_arr_2[4] = {'\0', '\0', '\0', '\0'};
    
    for( ; *p_arr != '\0' ; p_arr++)
    {
        pp_arr = p_arr;
        
        for( ; *pp_arr != '\0'; pp_arr++)
        {
            if(*pp_arr == '&')
            {
                strncpy(temp_arr, p_arr, pp_arr - p_arr);
                
                //printf("%s\n", temp_arr);

                if(strcmp(addx_instr, temp_arr) == 0)
                {
                    cycle_counter++;
                    //printf("%d\n", cycle_counter);
                    signal_strength += calc_signal_strength(cycle_counter, x_value);
                    draw_on_CRT(x_value, cycle_counter);
                    cycle_counter++;
                    //printf("%d\n", cycle_counter);
                    signal_strength += calc_signal_strength(cycle_counter, x_value);
                    draw_on_CRT(x_value, cycle_counter);
                }
                
                pp_arr++;
                ppp_arr = pp_arr;
                
                for( ; *ppp_arr != '\0'; ppp_arr++)
                {
                    if(*ppp_arr == '#')
                    {
                        strncpy(temp_arr_2, pp_arr, ppp_arr - pp_arr);
                        x_value += atoi(temp_arr_2);
                        //printf("X value: %d\n", x_value);
                        //printf("Add value: %s\n", temp_arr_2);
                        del_arr(temp_arr_2, ppp_arr - pp_arr);
                        break;
                    }
                }
                
                del_arr(temp_arr, pp_arr - p_arr);

                if(ppp_arr + 1 != NULL)
                    p_arr = ppp_arr++;
                
                break;
            }

            if(*pp_arr == '#')
            {
                strncpy(temp_arr, p_arr, pp_arr - p_arr);
                
                //printf("%s\n", temp_arr);
                
                if(strcmp(noop_instr, temp_arr) == 0)
                {
                    cycle_counter++;
                    //printf("%d\n", cycle_counter);
                    signal_strength += calc_signal_strength(cycle_counter, x_value);
                    draw_on_CRT(x_value, cycle_counter);
                }
                
                del_arr(temp_arr, pp_arr - p_arr);

                if(pp_arr + 1 != NULL)
                    p_arr = pp_arr++;

                break;
            }
        }
    }

    return signal_strength;
}

void print_CRT_screen()
{
    int index = 1;
    
    for(int i = 0; CRT_screen[i] != '\0' ; i++)
    {
        printf("%c", CRT_screen[i]);
                
        if(index % 40 == 0)
            printf("\n");
        
        index++;
    }
}

int main()
{
    char input_arr[2000];
    int signal_strength;
    
    read_input_fill_arr(input_arr);
    
    //print_arr(input_arr);
    
    signal_strength = read_instructions(input_arr);
    
    printf("Total signal strength is %d\n", signal_strength);
    
    print_CRT_screen();
    
    return 0;    
}
