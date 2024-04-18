#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "map.h"
#include "list_str.h"

int
main(void) {
      //HashMap *table = calloc(1, sizeof(table));
      //char* str = calloc(10e4, sizeof(str));
    HashMap table;
    init(&table);
    printf("inited\n");
    char* str = "hello";
    //h_insert(&table, "str");
    //h_erase(&table, "str");
    insert_item(&table, "dick.xyz", "hah");
    insert_item(&table, "dick2.xyz", "hah");
    insert_item(&table, "dick3.xyz", "hah");
    erase_item(&table, "dick4.xyz", "hah");
    erase_item(&table, "dick.xyz", "hah");
    sl2_print(find_array(&table, "hah"));
    insert_item(&table, "bogdan_loh.xyz", "bogdan");
    insert_item(&table, "loh_bogdan", "bogdan");
    //insert_item(&table, "dick3.xyz", "bogdan");
    erase_item(&table, "dick4.xyz", "bogdan");
    erase_item(&table, "dick.xyz", "bogdan");
    sl2_print(find_array(&table, "bogdan"));
    return 0;
  }
