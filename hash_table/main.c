#include <stdbool.h>

#include "hash_table.h"
#include "types.h"

int main() {
    hash_table *ht = init_hash_table(TABLE_SIZE);

    hash_table_insert_multiple_items(ht);

    print_hash_table(ht);

    free_table(ht);
}
