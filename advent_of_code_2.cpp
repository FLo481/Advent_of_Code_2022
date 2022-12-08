#include <iostream>

using namespace std;

int calc_score(char elf, char self)
{
	int round_score = 0;

	if(self == 'X')
	{
		round_score += 1;
	}
	else if(self == 'Y')
	{
		round_score += 2;
	}
	else if(self == 'Z')
	{
		round_score += 3;
	}

	if((elf == 'A' && self == 'Y') || (elf == 'B' && self == 'Z') || (elf == 'C' && self == 'X')) //win
	{
		round_score += 6;
	}
	else if((elf == 'A' && self == 'Z') || (elf == 'B' && self == 'X') || (elf == 'C' && self == 'B')) //loss
	{
		round_score += 0;
	}
	else if((elf == 'A' && self == 'X') || (elf == 'B' && self == 'Y') || (elf == 'C' && self == 'Z')) //draw
	{
		round_score += 3;
	}

	return round_score;
}

int figure_out_calc_score(char elf, char self)
{
	int round_score = 0;

	if(self == 'X')
        {
                round_score += 0;
        }
        else if(self == 'Y')
        {
                round_score += 3;
        }
        else if(self == 'Z')
        {
                round_score += 6;
        }

        if((elf == 'C' && self == 'Z') || (elf == 'B' && self == 'X') || (elf == 'A' && self == 'Y')) // self = rock
        {
                round_score += 1;
        }
        else if((elf == 'A' && self == 'Z') || (elf == 'C' && self == 'X') || (elf == 'B' && self == 'Y')) // self = paper
        {
                round_score += 2;
        }
        else if((elf == 'C' && self == 'Y') || (elf == 'A' && self == 'X') || (elf == 'B' && self == 'Z')) // self = scissors
        {
                round_score += 3;
        }

	return round_score;
}

int read_file_calc_score()
{
        int score = 0;
        char input_ch;
        char temp_ch_1 = '\0';
	char temp_ch_2 = '\0';
        FILE *fp;

        fp = fopen("input_adv2.txt", "r");

        if( fp == NULL)
        {
                printf("File does not exist");
        }
        else
        {
                while((input_ch = fgetc(fp)) != EOF)
                {
                        if(input_ch == '\n')
                        {
				//printf("%c %c\n", temp_ch_1, temp_ch_2);
				// FOR PART 1
				//score += calc_score(temp_ch_1, temp_ch_2);
				// FOR PART 2
				score += figure_out_calc_score(temp_ch_1, temp_ch_2);
				temp_ch_1 = '\0';
				temp_ch_2 = '\0';
                        }
                        else if(input_ch != ' ')
                        {
				//printf("%c\n", input_ch);
				if(temp_ch_1 == '\0')
				{
					//printf("%c\n", input_ch);
					temp_ch_1 = input_ch;
					continue;
				}

				if(temp_ch_2 == '\0')
				{
					temp_ch_2 = input_ch;
					continue;
				}
                        }
                }
        }

        fclose(fp);

        return score;
}


int main()
{
	int score = 0;

	score = read_file_calc_score();
	printf("Final score is: %d\n", score);

	return 0;
}
