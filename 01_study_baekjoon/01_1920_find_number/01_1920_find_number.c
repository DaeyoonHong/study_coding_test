/***********************
 * 체이닝을 이용한 해시 테이블
 ***********************/

/**********************
 * include libraries
 **********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************
 * define datatypes
 **********************/
typedef int value_type;

typedef struct tag_node
{
    value_type value; /* key 로 사용할 데이터와 value 가 동일 */ 
    struct tag_node * next; /* 체인 */
} node;

typedef node * list;

typedef struct tag_hash_table
{
    int table_size;
    list * table;
} hash_table;

/**********************
 * function prototypes
 **********************/
hash_table * cht_create_hash_table(int table_size);
void cht_destroy_hash_table(hash_table * ht);
node * cht_create_node(value_type value);
void cht_destroy_node(node * the_node);
void cht_destroy_list(list l);
void cht_set(hash_table * ht, value_type value);
int cht_get(hash_table * ht, value_type value);
int cht_hash(value_type value, int table_size);

/***********************
 * main function
 ***********************/
int main(void)
{
    int n = 0;
    scanf("%d", &n);

    hash_table * ht = cht_create_hash_table(n);

    int value = 0;
    for(int i = 0; i < n ; i ++)
    {
        scanf("%d", &value);
        cht_set(ht, value);
    }

    int m = 0;
    int target = 0;
    scanf("%d", &m);
    for(int i = 0 ; i < m ; i++)
    {
        scanf("%d", &target);
        printf("%d\n", cht_get(ht, target));
    }
    cht_destroy_hash_table(ht);
    
    return 0;
}

/************************
 * define functions
 ************************/
hash_table * cht_create_hash_table(int table_size)
{
    hash_table * ht = (hash_table *)malloc(sizeof(hash_table));
    ht -> table = (list *)malloc(sizeof(list) * table_size);

    memset(ht -> table, 0, sizeof(list) * table_size); /* 메모리 블럭 초기화 */

    ht -> table_size = table_size;

    return ht;
}
void cht_destroy_hash_table(hash_table * ht)
{
    for(int i = 0 ; i < ht -> table_size ; i++)
    {
        list l = ht -> table[i];
        /* ht -> table : list *, ht -> table[0] : list */
        cht_destroy_list(l);
    }
    free(ht -> table);
    free(ht);
}
node * cht_create_node(value_type value)
{
    node * new_node = (node *)malloc(sizeof(node));
    new_node -> value = value;
    new_node -> next = NULL;

    return new_node;
}
void cht_destroy_node(node * the_node)
{
    free(the_node);
}
void cht_set(hash_table * ht, value_type value)
{
    int address = cht_hash(value, ht -> table_size);
    node * new_node = cht_create_node(value);

    if(ht -> table[address] == NULL)
    {
        ht -> table[address] = new_node;
    }
    else
    {
        #if 0
        node * current_node = ht -> table[address] -> next;
        while(current_node != NULL)
        {
            current_node = current_node -> next;
        }
        current_node -> next = new_node;
        #endif
        /* 새로운 노드를 맨 앞에 삽입 */
        list l = ht -> table[address];
        new_node -> next = l;
        ht -> table[address] = new_node;
    }
}
int cht_get(hash_table * ht, value_type value)
{
    int address = cht_hash(value, ht -> table_size);

    list the_list = ht -> table[address];
    list target = NULL;

    if(the_list == NULL)
    {
        return 0;
    }
    while(1)
    {
        if(the_list -> value == value)
        {
            target = the_list;
            break;
        }
        if(the_list -> next == NULL)
        {
            break;
        }
        else
        {
            the_list = the_list -> next;
        }
    }
    if(target == NULL)
    {
        return 0;
    }
    return 1;
}
int cht_hash(value_type value, int table_size)
{
    int i = 0;
    int hash_value = 0;

    hash_value = value % table_size;

    return hash_value;
}
void cht_destroy_list(list l)
{
    if(l == NULL)
    {
        return;
    }
    
    if(l -> next != NULL)
    {
        cht_destroy_list(l -> next);
    }

    cht_destroy_node(l);
}


