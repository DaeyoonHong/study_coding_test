/*****************************
 * include libraries
 *****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************
 * define datatypes
 *****************************/
typedef struct tag_node
{
    int order;
    char *car_num;
    struct tag_node *next;
} st_node;

int n;
/*****************************
 * function prototypes
 *****************************/
st_node *create_node(char *car_num, int order);
void add_to_hash_table(st_node **hash_table, st_node *new_node);
int calculate_hash(char *car_num);
void count_overtaking(int *out_cars, int *overtaking_cnt, int out_order);
void destroy_hash_table(st_node **hash);
void record_out_cars(st_node **hash_table, char *car_num, int *out_cars, int out_order);

/*****************************
 * main function
 *****************************/
int main(void)
{
    scanf("%d", &n);

    st_node **hash_table = (st_node **)malloc(sizeof(st_node *) * n);
    for (int i = 0; i < n; i++)
    {
        hash_table[i] = NULL;
    }

    char car_num[9];

    for (int i = 0; i < n; i++)
    {
        scanf("%s", car_num);
        st_node *new_node = create_node(car_num, i);
        add_to_hash_table(hash_table, new_node);
    }

    int overtaking_cnt = 0;
    int *out_cars = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        out_cars[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%s", car_num);
        record_out_cars(hash_table, car_num, out_cars, i);
        count_overtaking(out_cars, &overtaking_cnt, i);
    }
    
    printf("%d", overtaking_cnt);

    destroy_hash_table(hash_table);

    return 0;
}

/*****************************
 * define functions
 *****************************/
st_node *create_node(char *car_num, int order)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));
    new_node->car_num = (char *)malloc(sizeof(char) * 9);

    strcpy(new_node->car_num, car_num);
    new_node->next = NULL;
    new_node->order = order;

    return new_node;
}

void add_to_hash_table(st_node **hash_table, st_node *new_node)
{
    int idx = calculate_hash(new_node->car_num);

    if (hash_table[idx] == NULL)
    {
        hash_table[idx] = new_node;
    }
    else
    {
        st_node *current = hash_table[idx];

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = new_node;
    }
}

int calculate_hash(char *car_num)
{
    /* 문자열 해시 계산 : 자릿수 접기 */
    int hash_val = 0;
    int i = 0;
    while (car_num[i] != '\0')
    {
        hash_val = hash_val + car_num[i];
        i++;
    }

    return hash_val = hash_val % n;
}

void count_overtaking(int *out_cars, int *overtaking_cnt, int out_order)
{
    for (int i = 0; i < out_order; i++)
    {
        if (out_cars[i] > out_cars[out_order])
        {
            (*overtaking_cnt)++;
            out_cars[i] = -1;
        }
    }
}

void destroy_hash_table(st_node **hash)
{
    for (int i = 0; i < n; i++)
    {
        if (hash[i] != NULL)
        {
            st_node *current = hash[i];
            while (current->next != NULL)
            {
                st_node *temp = current;
                current = current->next;
                free(temp);
            }
        }
    }

    free(hash);
}

void record_out_cars(st_node **hash_table, char *car_num, int *out_cars, int out_order)
{
    int hash_val = calculate_hash(car_num);

    st_node *current = hash_table[hash_val];
    
    while((strcmp(current->car_num, car_num) != 0))
    {
        current = current->next;
    }

    out_cars[out_order] = current->order;
}
