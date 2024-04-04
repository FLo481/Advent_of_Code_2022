#include <iostream>

using namespace std;

void read_input_fill_arr(char* input_chars)
{
    FILE* fp;
    fp = fopen("input_adv6.txt", "r");
    char input_ch;

    if(fp == NULL)
    {
        printf("File does not exist\n");
    }
    else
    {
        while((input_ch = fgetc(fp)) != EOF)
        {
            if(input_ch != '\n')
            {
                *(input_chars++) = input_ch;
                //printf("%c", input_ch);
            }
        }
        
        *input_chars = '\0';
    }
}

int search_marker_pos(const char* input_chars)
{
    int duplicate_char_pos = 0;
    int duplicate_found;
    int marker_pos = 0;
    int marker_len = 4;

    for(int i = 0 ; input_chars[i] != '\0' ; i++)
    {
        duplicate_found = 0;
        
        for(int j = i + 1; j - i < marker_len ; j++)
        {
            if(input_chars[i] == input_chars[j])
            {
                duplicate_found = 1;
                break;
            }
        }
        
        if(duplicate_found)
            continue;
        
        if(i < duplicate_char_pos)
            continue;
        
        if(input_chars[i + 1] == input_chars[i + 2])
        {
            duplicate_char_pos = i + 2;
        }
        else if(input_chars[i + 1] == input_chars[i + 3])
        {
            duplicate_char_pos = i + 2;
        }
        else if(input_chars[i + 2] == input_chars[i + 3])
        {
            duplicate_char_pos = i + 3;
        }
        
        if(i >= duplicate_char_pos)
        {
            marker_pos = i + marker_len;
            break;
        }
    }

    return marker_pos;
}

int search_message_marker_pos(const char* input_chars)
{
    int duplicate_char_pos = -1;
    int duplicate_found = 0;
    int marker_pos = 0;
    int marker_len = 14;

    for(int i = 0; input_chars[i] != '\0' ; i++)
    {
        if(i <= duplicate_char_pos)
           continue;
        
        for(int j = i + 1; j - i < marker_len ; j++)
        {
            duplicate_found = 0;
            
            if(input_chars[i] == input_chars[j])
            {
                duplicate_char_pos = i;
                break;
            }

            for(int h = j + 1; h - i < marker_len; h++)
            {
                if(input_chars[j] == input_chars[h])
                {
                    duplicate_char_pos = j;
                    duplicate_found = 1;
                    break;
                }
            }

            if(duplicate_found)
                break;
        }

        if(i > duplicate_char_pos)
        {
            marker_pos = i + marker_len;
            break;
        }
    }

    return marker_pos;    
}

int main()
{
    int marker_pos = 0;
    int mmarker_pos = 0;
    char input_chars[4097];
    
    read_input_fill_arr(input_chars);
    
    marker_pos = search_marker_pos(input_chars);
    mmarker_pos = search_message_marker_pos(input_chars);
    
    //for(int i = 0; i < 4096; i++)
    //    printf("%c", input_chars[i]);
    
    printf("Marker position is: %d\n", marker_pos);
    printf("Message marker position: %d\n", mmarker_pos);

    return 0;
}
