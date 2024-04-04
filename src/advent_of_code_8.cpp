#include <iostream>

using namespace std;

const int grid_len = 99;

void print_arr(int input_grid[][grid_len])
{
    for(int i = 0; i < grid_len ; i++)
    {
        for(int j = 0; j < grid_len; j++)
        {
            printf("%d", input_grid[i][j]);
        }
        
        printf("\n");
    }    
}

void read_input_fill_arr(int input_grid[][grid_len])
{
    FILE* fp;
    fp = fopen("input_adv8.txt", "r");
    char input_ch;
    int c_pos = 0;
    int r_pos = 0;
    
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
                input_grid[r_pos][c_pos] = input_ch - '0';
                c_pos++;
            }
            else
            {
                r_pos++;
                c_pos = 0;
            }
        }
    }
}

int tree_already_counted(int visible_tree_pos[][2], int visible_tree_num, int pos_x, int pos_y)
{
    if(pos_x == grid_len - 1 || pos_y == grid_len - 1 || pos_x == 0 || pos_y == 0)
        return 1;

    if(visible_tree_num == 0)
        return 0;
    
    for(int i = 0; i < visible_tree_num; i++)
    {
        if(visible_tree_pos[i][0] == pos_x &&
           visible_tree_pos[i][1] == pos_y)
            return 1;
    }

    return 0;
}

int count_visible_trees(const int input_grid[][grid_len], int visible_tree_pos[][2])
{
    unsigned int tree_counter = 0;
    unsigned int outer_tree_count = 0;
    unsigned int visible;

    // Count trees on the outer lines
    outer_tree_count = 2 * grid_len + 2 * (grid_len - 2);

    //printf("Tree count (only outermost ones): %d\n", outer_tree_count);

    for(int i = 1; i < grid_len - 1; i++)
    {
        for(int j = 1; j < grid_len - 1; j++)
        {
            // LEFT CHECK            
            for(int h = 0; h < j; h++)
            {   
                visible = 1;

                if(input_grid[i][h] >= input_grid[i][j])
                {
                    break;
                }
                else
                {
                    // 33549
                    //    ^
                    // 4 must not be counted
                    for(int k = 0; k < j ; k++)
                        if(input_grid[i][j] <= input_grid[i][k])
                            visible = 0;
                    
                    if(!tree_already_counted(visible_tree_pos, tree_counter, j, i) && visible)
                    {
                        //printf("X: %d Y: %d\n", j, i);
                        visible_tree_pos[tree_counter][0] = j;
                        visible_tree_pos[tree_counter][1] = i;
                        tree_counter++;
                    }
                }
            }

            // RIGHT CHECK
            for(int h = j + 1; h < grid_len; h++)
            {   
                visible = 1;
                
                if(input_grid[i][h] >= input_grid[i][j])
                {
                    break;
                }
                else
                {
                    for(int k = j + 1; k < grid_len ; k++)
                        if(input_grid[i][j] <= input_grid[i][k])
                            visible = 0;
                    
                    if(!tree_already_counted(visible_tree_pos, tree_counter, j, i) && visible)
                    {
                        //printf("X: %d Y: %d\n", j, i);
                        visible_tree_pos[tree_counter][0] = j;
                        visible_tree_pos[tree_counter][1] = i;
                        tree_counter++;
                    }
                }
            }

            // TOP CHECK
            for(int h = 0; h < i; h++)
            {
                visible = 1;

                if(input_grid[h][j] >= input_grid[i][j])
                {
                    break;
                }
                else
                {
                    for(int k = 0; k < i ; k++)
                        if(input_grid[i][j] <= input_grid[k][j])
                            visible = 0;
                    
                    if(!tree_already_counted(visible_tree_pos, tree_counter, j, i) && visible)
                    {
                        //printf("X: %d Y: %d\n", j, i);
                        visible_tree_pos[tree_counter][0] = j;
                        visible_tree_pos[tree_counter][1] = i;
                        tree_counter++;
                    }
                }
            }

            // BOTTOM CHECK
            for(int h = i + 1; h < grid_len; h++)
            {
                visible = 1;
                
                if(input_grid[h][j] >= input_grid[i][j])
                {
                    break;
                }
                else
                {
                    for(int k = i + 1; k < grid_len ; k++)
                        if(input_grid[i][j] <= input_grid[k][j])
                            visible = 0;
                    
                    if(!tree_already_counted(visible_tree_pos, tree_counter, j, i) && visible)
                    {
                        //printf("X: %d Y: %d\n", j, i);
                        visible_tree_pos[tree_counter][0] = j;
                        visible_tree_pos[tree_counter][1] = i;
                        tree_counter++;
                    }
                }
            }
        }
    }

    visible_tree_pos[tree_counter][0] = visible_tree_pos[tree_counter][1] = -2;

    // Print visible tree positions
    //for(int i = 0; visible_tree_pos[i][0] != -2; i++)
    //    printf("Nr.: %d X: %d Y: %d\n", i, visible_tree_pos[i][0] + 1, visible_tree_pos[i][1] + 1);
    
    return tree_counter + outer_tree_count;
}

int find_max(int* arr, int len)
{
    int max = 0;
    
    for(int* p_arr = arr; (p_arr - arr) < len; p_arr++)
    {
        //printf("%d\n", *p_arr);
        
        if(*p_arr > max)
            max = *p_arr;
    }
    
    return max;
}

int calc_scenic_score(const int input_grid[][grid_len], const int visible_trees_pos[][2])
{
    unsigned int scenic_score_left = 0;
    unsigned int scenic_score_right = 0;
    unsigned int scenic_score_top = 0;
    unsigned int scenic_score_bottom = 0;
    unsigned int max_scenic_score = 0;
    int scenic_score_arr[10000];
    int index = 0;
    
    //for(int i = 0; visible_trees_pos[i][0] != -2; i++)
    //    printf("Nr.: %d X: %d Y: %d\n", i, visible_trees_pos[i][0] + 1, visible_trees_pos[i][1] + 1);
    
    for(int j = 0; visible_trees_pos[j][0] != -2 ; j++)
    {
        //printf("X_Pos: %d Y_Pos: %d\n", visible_trees_pos[j][0], visible_trees_pos[j][1]);
        
        // LEFT
        for(int i = visible_trees_pos[j][0] - 1; i >= 0 ; i--)
        {
            if(visible_trees_pos[j][0] == 1)
            {
                scenic_score_left = 1;
                //printf("left score: %d\n", scenic_score_left);
                break;
            }

            if(input_grid[visible_trees_pos[j][1]][visible_trees_pos[j][0]]
               <= input_grid[visible_trees_pos[j][1]][i])
            {
                scenic_score_left = visible_trees_pos[j][0] - i;
                //printf("left score: %d\n", scenic_score_left);
                break;
            }
            
            if(i == 0)
            {
                scenic_score_left = visible_trees_pos[j][0] - i;
                //printf("left score: %d\n", scenic_score_left);
            }
        }

        // RIGHT
        for(int i = visible_trees_pos[j][0] + 1; i < grid_len; i++)
        {
            if(visible_trees_pos[j][0] == grid_len - 1)
            {
                scenic_score_right = 1;
                //printf("right score: %d\n", scenic_score_right);
                break;
            }
            
            if(input_grid[visible_trees_pos[j][1]][visible_trees_pos[j][0]]
               <= input_grid[visible_trees_pos[j][1]][i])
            {
                scenic_score_right = i - visible_trees_pos[j][0];
                //printf("right score: %d\n", scenic_score_right);
                break;
            }
            
            if(i == grid_len - 1)
            {
                scenic_score_right = i - visible_trees_pos[j][0];
                //printf("right score: %d\n", scenic_score_right);
            }
        }
        
        // TOP
        for(int i = visible_trees_pos[j][1] - 1; i >= 0; i--)
        {
            if(visible_trees_pos[j][1] == 1)
            {
                scenic_score_top = 1;
                //printf("top score: %d\n", scenic_score_top);
                break;
            }
            
            if(input_grid[visible_trees_pos[j][1]][visible_trees_pos[j][0]]
               <= input_grid[i][visible_trees_pos[j][0]])
            {
                scenic_score_top = visible_trees_pos[j][1] - i;
                //printf("top score: %d\n", scenic_score_top);
                break;
            }
            
            if(i == 0)
            {
                scenic_score_top = visible_trees_pos[j][1] - i;
                //printf("top score: %d\n", scenic_score_top);
            }
        }
        
        // BOTTOM
        for(int i = visible_trees_pos[j][1] + 1; i < grid_len; i++)
        {
            if(visible_trees_pos[j][1] == grid_len - 1)
            {
                scenic_score_bottom = 1;
                //printf("top bottom: %d\n", scenic_score_bottom);
                break;
            }
            
            if(input_grid[visible_trees_pos[j][1]][visible_trees_pos[j][0]]
               <= input_grid[i][visible_trees_pos[j][0]])
            {
                scenic_score_bottom = i - visible_trees_pos[j][1];
                //printf("bottom score: %d\n", scenic_score_bottom);
                break;
            }
            
            if(i == grid_len - 1)
            {
                scenic_score_bottom = i - visible_trees_pos[j][1];
                //printf("bottom score: %d\n", scenic_score_bottom);
            }
        }

        if(scenic_score_left * scenic_score_right * scenic_score_top * scenic_score_bottom != 0)
        {
            scenic_score_arr[index] = scenic_score_left * scenic_score_right * scenic_score_top * scenic_score_bottom;
            //printf("%d\n", scenic_score_arr[index]);
            index++;
        }

        scenic_score_left = scenic_score_right = scenic_score_top = scenic_score_bottom = 0;
    }
    
    max_scenic_score = find_max(scenic_score_arr, index);
    
    return max_scenic_score;
}

int main()
{
    int visible_trees_count = 0;
    int max_scenic_score = 0;
    int input_grid[grid_len][grid_len];
    int visible_tree_pos[10000][2];
    
    read_input_fill_arr(input_grid);
    
    //print_arr(input_grid);
    
    visible_trees_count = count_visible_trees(input_grid, visible_tree_pos);
    
    printf("There are %d visible trees.\n", visible_trees_count);
    
    max_scenic_score = calc_scenic_score(input_grid, visible_tree_pos);
    
    printf("Maximum scenic score: %d\n", max_scenic_score);
    
    return 0;    
}
