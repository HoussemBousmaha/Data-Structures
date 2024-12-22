#include <stdbool.h>

#include "types.h"
#include "hash_table.h"

int main() {
    hash_table *ht = init_hash_table(TABLE_SIZE);

    hash_table_insert_multiple_items(ht);

    print_hash_table(ht);

    free_table(ht);
}
