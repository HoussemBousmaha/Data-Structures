#define TABLE_SIZE 100
#define MAX_NAME 20

// Define the hash table item here
typedef struct
{
    char *key, *value;
} hash_table_item;

// Define the Linkedlist here
typedef struct LinkedList LinkedList;
struct LinkedList
{
    hash_table_item *item;
    LinkedList *next;
};

// Define the hash table here
typedef struct
{
    // Contains an array of pointers
    // to hash_table_items
    hash_table_item **hash_table_items;
    LinkedList **overflow_buckets;
    int size;
    int count;
} hash_table;




