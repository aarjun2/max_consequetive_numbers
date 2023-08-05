#include <stdio.h>
void max_consecutive_integers(int arr[][5], int noofrows, int noofcols, int* address_num, int** return_value);

int main()
{
    int arr[4][5] = { -5, 6,0,2,2,2,2,2,9,3,3,3, 2, 1, -8, 7, -2, 6,0,4 };
    int noofrows = 4;
    int noofcols = 5;
    int* address_num = NULL;
    int** return_value = NULL;

    max_consecutive_integers(arr, noofrows, noofcols, address_num, return_value);

    // Now print address from the first pointer output
    printf("\n Address of starting sequence is %p", address_num);
    printf("\n Value at the starting sequence is %d", *address_num);

    return 1;
}

void max_consecutive_integers(int arr[][5], int noofrows, int noofcols, int* address_num, int** return_value)
{
    //int arr[4][5] = { -5, 6,0,2,2,2,2,2,9,3,3,3, 2, 1, -8, 7, -2, 6,0,4};
    int prev_val = arr[0][0];
    int start_row = 0;
    int start_col = 0;
    int count = 1;
    int values[50][4];
    int index = -1;
    int row = noofrows;
    int col = noofcols;

    //printing the address to confirm
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("\n add = %p %d", &arr[i][j], arr[i][j]);
        }
    }

    // Find the repeative sequence and store the details of index etc in an array
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == 0 && j == 0) continue;
            if (arr[i][j] == prev_val)
            {

                count = count + 1;
            }
            else
            {
                if (count > 1)
                {
                    // store the prev value, its row, col and count if the sequence is changing
                    index = index + 1;
                    values[index][0] = count;
                    values[index][1] = start_row;
                    values[index][2] = start_col;
                    values[index][3] = prev_val;
                    //printf("\n storting row cal value = %d %d", values[index][1], values[index][2]);

                    count = 1;
                }
                prev_val = arr[i][j];
                start_row = i;
                start_col = j;
                address_num = &arr[i][j];
                count = 1;
            }
            if (arr[i][j] == prev_val && (i + 1) == row && (j + 1) == col)
            {
                // store the prev value if the end of the array is reaching and value continue to be the same
                index = index + 1;
                values[index][0] = count;
                values[index][1] = start_row;
                values[index][2] = start_col;
                values[index][3] = arr[i][j];
            }
        }
    }

    // find the greatest count and its associated index 
    int max_value = values[0][0];
    int max_val_index = 0;

    for (int i = 1; i <= index; i++)
    {
        if (values[i][0] > max_value)
        {
            max_value = values[i][0];
            max_val_index = i;
        }
    }

    // One of the return pointer is starting address of the sequence.
    start_row = values[max_val_index][1];
    start_col = values[max_val_index][2];
    address_num = &arr[start_row][start_col];


    // Now construct the pointer to pointer. This will have the following
    // element 0: pointer to the number of occurances
    // element 1 - n (n being the total occurance in the sequence): pointer to the value in the array for the sequence

    return_value = NULL;

    // allocate the space for the pointer to pointer
    return_value = malloc(sizeof(*return_value) * (max_value + 1));

    // first value will be pointer to the count of sequence
    start_row = values[max_val_index][1];
    start_col = values[max_val_index][2];
    return_value[0] = &values[max_val_index][0];


    // Now the rest of the values will be pointer to the sequence value
    for (int i = 1; i <= max_value; i++)
    {
        return_value[i] = &arr[start_row][start_col];
        start_col++;
        // if we go beyond the column, slip to the next row
        if (start_col == col)
        {
            start_row++;
            start_col = 0;
        }
    }


    // Now print everything from the pointer
    for (int i = 0; i <= max_value; i++)
    {
        printf("\n Output is %d", *(return_value[i]));
    }



    return 0;
}