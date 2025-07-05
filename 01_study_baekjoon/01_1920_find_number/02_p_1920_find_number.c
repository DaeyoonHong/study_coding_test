#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long value_type;
typedef struct tag_node
{
    value_type value;
    struct tag_node *next;
} node;
typedef node *list;
typedef struct tag_hash_table
{
    int table_size;
    list *table; 
    /* list 형 데이터를 원소로 갖는 배열 */
    /* node ** 형으로 표현하는게 더 이해하기 쉬운데.. */
} hash_table;

hash_table * cht_create_hash_table(int table_size);
void cht_destroy_hash_table(hash_table * ht);
node * cht_create_node(value_type value);
void cht_destroy_node(node * the_node);
void cht_destroy_list(list l);
void cht_set(hash_table * ht, value_type value);
int cht_get(hash_table * ht, value_type value);
int cht_hash(value_type value, int table_size);

int main(void)
{
    int n = 0;
    scanf("%d", &n);

    hash_table * ht = cht_create_hash_table(n);

    long value = 0;
    for(int i = 0; i < n ; i ++)
    {
        scanf("%ld", &value);
        cht_set(ht, value);
    }

    int m = 0;
    long target = 0;
    scanf("%d", &m);
    for(int i = 0 ; i < m ; i++)
    {
        scanf("%ld", &target);
        printf("%d\n", cht_get(ht, target));
    }
    cht_destroy_hash_table(ht);
    
    return 0;
}



hash_table *cht_create_hash_table(int table_size)
{
    hash_table *ht = (hash_table *)malloc(sizeof(hash_table));
    ht->table = (list *)malloc(sizeof(list) * table_size);

    memset(ht->table, 0, sizeof(list) * table_size);

    ht->table_size = table_size;

    return ht;
}
#if 0
void cht_destroy_hash_table(hash_table *ht)
{
    for(int i = 0; i < ht->table_size; i++)
    {
        if(ht->table[i] != NULL)
        {
            cht_destroy_list(ht->table[i]);
        }
    }
    free(ht->table);
    free(ht);
}
#endif
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
void cht_set(hash_table *ht, value_type value)
{
    int address = cht_hash(value, ht->table_size);
    node *new_node = cht_create_node(value);
    if(ht->table[address] == NULL)
    {
        ht->table[address] = new_node;
    }
    else
    {
        new_node->next = ht->table[address];
        ht->table[address] = new_node;
    }
}
int cht_get(hash_table *ht, value_type value)
{
    int address = cht_hash(value, ht->table_size);

    list the_list = ht->table[address];
    list target = NULL;
    
    if(the_list == NULL)
    {
        return 0;
    }    

    while(1)
    {
        if(the_list->value == value)
        {
            target = the_list;
            break;
        }
        
        if(the_list->next != NULL)
        {
            the_list = the_list -> next;
        }
        else
        {
            break;
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

    hash_value = (value * value) % table_size;

    return hash_value;
}
#if 0
void cht_destroy_list(list l)
{
    /* 내 머리에서는 이런 코드가 나오기 힘들 거 같다 */
    if(l->next != NULL)
    {
        cht_destroy_list(l->next);
    }
    cht_destroy_list(l);
}
#endif

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