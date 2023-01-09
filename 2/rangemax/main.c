#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct{
    int *seq_data;
    size_t *index_of_max_item_from_prefix;
    int **table;
    size_t N;

    int needs_to_be_updated;
    size_t leftmost_updated_index;
} Table;


typedef enum {
    Normal,
    TableStructAlloc,
    IndicesStorageAlloc,
    TableAlloc,
    ArrayAlloc
} TableCreationCodes;


TableCreationCodes table_new(Table **dst, size_t N) {
    Table *table = malloc(sizeof(Table));
    if (table == NULL) {
        return TableStructAlloc;
    }
    
    if ((table->table = malloc(sizeof(int *) * N)) == NULL) {
        return TableAlloc;
    }

    for (size_t i = 0; i <  N; ++i) {
        if ((table->table[i] = malloc(sizeof(int) * (N - i))) == NULL) {
            return IndicesStorageAlloc;
        }
    }

    if ((table->index_of_max_item_from_prefix = malloc(sizeof(int) * N)) == NULL) {
        return TableAlloc;
    }

    if ((table->seq_data=malloc(sizeof(int) * N)) == NULL) {
        return ArrayAlloc;
    }

    (table)->N=N;
    (table)->needs_to_be_updated=0;
    (table)->leftmost_updated_index=0;

    *dst = table;
    return Normal;
}


static inline void free_table(Table *table) {
    for (size_t i = 0; i < table->N; ++i) {
        free(table->table[i]);
    }
    free(table->table);
    free(table->seq_data);
    free(table->index_of_max_item_from_prefix);
    free(table);
}


static inline int *table_at(const Table *table, size_t row, size_t col) {
    return &table->table[row][col - row];
}


static inline int safe_table_at(const Table *table, size_t row, size_t col, int *res) {
    if (row > table->N || col > table->N) {
        return 1;
    }

    *res = *table_at(table, row, col);
    return 0;
}


static inline int safe_table_set(Table *table, size_t row, size_t col, int data) {
    if (row > table->N || col > table->N) {
        return 1;
    }

    *table_at(table, row, col) = data;
    return 0;
}


static inline size_t table_get_index_of_max_item_from_prefix(const Table *table, size_t i) {
    return table->index_of_max_item_from_prefix[i];
}


static inline int safe_table_get_index_of_max_item_from_prefix(const Table *table, size_t i, size_t *dst_ptr) {
    if (i >= table->N) {
        return 1;
    }
    *dst_ptr = table_get_index_of_max_item_from_prefix(table, i);
    return 0; 
}


#define panicing_table_get_index_of_max_item_from_prefix(table_ptr, i, dst_ptr) {\
    int _res = safe_table_get_index_of_max_item_from_prefix((table_ptr), i, dst_ptr);\
    if (_res) {\
        printf("%s:%d Couldn't get new index for max item in prefix of length %zu\n", __func__, __LINE__, (size_t)(i));\
        exit(1);\
    }\
}


static inline void table_set_index_of_max_item_from_prefix(const Table *table, size_t i, size_t new_index) {
    table->index_of_max_item_from_prefix[i] = new_index;
}


static inline int safe_table_set_index_of_max_item_from_prefix(const Table *table, size_t i, size_t new_index) {
    if (i >= table->N) {
        return 1;
    }
    
    table_set_index_of_max_item_from_prefix(table, i, new_index);
    return 0;
}


#define panicing_table_set_index_of_max_item_from_prefix(table_ptr, i, new_index) {\
    int _res = safe_table_set_index_of_max_item_from_prefix((table_ptr), (i), (new_index));\
    if (_res) {\
        printf("%s:%d Couldn't set new index for max item in prefix of length %zu\n", __func__, __LINE__, (size_t)(i));\
        exit(1);\
    }\
}


#define panicing_table_at(table_ptr, row, col, dst_ptr) {\
    int _res = safe_table_at((table_ptr), (row), (col), (dst_ptr));\
    if (_res) {\
        printf("%s:%d Couldn't get item from table[%zu][%zu]\n", __func__, __LINE__, (size_t)(row), (size_t)(col));\
        exit(1);\
    }\
}


#define panicing_table_set(table_ptr, row, col, item) {\
    int _res = safe_table_set((table_ptr), (row), (col), (item));\
    if (_res) {\
        printf("%s:%d Couldn't set item to table[%zu][%zu]\n", __func__, __LINE__, (size_t)(row), (size_t)(col));\
        exit(1);\
    }\
}


void print_table(Table *table) {
    for (size_t i = 0; i < table->N; ++i) {
        for (size_t j = 0; j < table->N; ++j) {
            int item;
            panicing_table_at(table, i, j, &item);
            printf("%5d ", item);
        }
        puts("\n");
    }
}


static inline int table_get_item_from_undelying_array(Table *table, size_t i) {
    if (i >= table->N) {
        printf("%s:%d Couldn't get table->array[%zu]", __func__, __LINE__,  i);
        exit(1);
    }
    return table->seq_data[i];
}


void fill_table(Table *table, size_t start, int update_flag) {
    panicing_table_set(table, start, start, table_get_item_from_undelying_array(table, start));

    size_t index_of_max_on_prev_prefix;
    if (start) {
        panicing_table_get_index_of_max_item_from_prefix(table, start - 1, &index_of_max_on_prev_prefix);
    } else { 
        index_of_max_on_prev_prefix = 0;
    }
    int prev_max_on_prefix = table_get_item_from_undelying_array(table, index_of_max_on_prev_prefix);
    
    for (int i = start + 1; i < table->N; ++i) {
        panicing_table_set(table, i, i, table_get_item_from_undelying_array(table, i));

        size_t index_of_max_on_current_prefix;
        if (prev_max_on_prefix <= table_get_item_from_undelying_array(table, i)) {
            panicing_table_set_index_of_max_item_from_prefix(table, i, i);
            index_of_max_on_current_prefix = i;
        } else {
            if (update_flag) {
                return;
            }

            panicing_table_get_index_of_max_item_from_prefix(table, i - 1, &index_of_max_on_current_prefix);
            panicing_table_set_index_of_max_item_from_prefix(table, i,      index_of_max_on_current_prefix);
        }

        int max_on_current_prefix = table_get_item_from_undelying_array(table, index_of_max_on_current_prefix);
        prev_max_on_prefix = max_on_current_prefix;

        for (size_t j = 0; j <= index_of_max_on_current_prefix; ++j) {
            panicing_table_set(table, j, i, max_on_current_prefix);
        }

        for (size_t filling_row_index = index_of_max_on_current_prefix + 1; filling_row_index < i; ++filling_row_index) {
            int prev_max_of_filling_row;
            panicing_table_at(table, filling_row_index, i - 1, &prev_max_of_filling_row);

            if (prev_max_of_filling_row < table_get_item_from_undelying_array(table, i)) {
                panicing_table_set(table, filling_row_index, i, table_get_item_from_undelying_array(table ,i));
            } else {
                panicing_table_set(table, filling_row_index, i, prev_max_of_filling_row);
            }
        }
    }
}


#define min(x, y) ((x) < (y)) ? (x) : (y)


void table_update_seq_data(Table *table, size_t updating_index, int new_item) {
    assert(updating_index < table->N);
    
    table->seq_data[updating_index] = new_item;
    table->needs_to_be_updated = 1;
    table->leftmost_updated_index = min(table->leftmost_updated_index, updating_index);
}


int table_get_max_with_update(Table *table, size_t row, size_t col) {
    printf("1");
    if (table->needs_to_be_updated) {
        if (!table->leftmost_updated_index) {
            fill_table(table, 0, 1);
        } else {
            fill_table(table, table->leftmost_updated_index - 1, 1);
        }
        table->needs_to_be_updated = 0;
    }

    int res;
    panicing_table_at(table, row, col, &res);
    return res;
}


int main() {
    FILE* input_file = fopen("./input.txt", "r");

    size_t n;
    fscanf(input_file, "%zu", &n);

    Table *table;
    TableCreationCodes creation_code;
    switch (creation_code = table_new(&table, n))
    {
    case Normal:
        break;
    case TableStructAlloc:
        printf("couldn't allocate struct for a table");
        exit(1);
        break;    
    case TableAlloc:
        printf("couldn't allocate table of size %zu X %zu", n, n);
        exit(1);
        break;
    case ArrayAlloc:
        printf("couldn't allocate array of size %zu", n);
        exit(1);
        break;
    default:
        printf("unknown return from table_new: %d", creation_code);
        exit(1);
        break;
    }

    for (size_t i = 0; i < n; ++i) {
        fscanf(input_file, "%d", table->seq_data + i);
    }

    fill_table(table, 0, 0);
    
    char buffer[4];
    buffer[3] = '\0';
    
    int c;
    while ((c = getc(input_file)) != EOF) {
        buffer[0] = getc(input_file);
        buffer[1] = getc(input_file);
        buffer[2] = getc(input_file);
        
        if (!strcmp(buffer, "END")) {
            break;
        } else if (!strcmp(buffer, "MAX")) {
            size_t row, col;
            fscanf(input_file, "%zu %zu", &row, &col);

            int res = table_get_max_with_update(table, row, col);
            printf("%d\n", res);
        } else if (!strcmp(buffer, "UPD")) {
            size_t index;
            int new_value;
            fscanf(input_file, "%zu %d", &index, &new_value);
            
            table_update_seq_data(table, index, new_value);
        } else {
            printf("afsdads");
        }
    }

    free_table(table);
    return 0;
}