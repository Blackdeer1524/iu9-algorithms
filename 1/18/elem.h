#ifndef IU_ALGOS_ELEM_H
#define IU_ALGOS_ELEM_H

struct Elem {
    /* «Тег», описывающий тип значения в «головe» списка */
    enum {
        INTEGER,
        FLOAT,
        LIST
    } tag;

    /* Само значение в «голове» списка */
    union {
        int i;
        float f;
        struct Elem *list;
    } value;

    /* Указатель на «хвост» списка */
    struct Elem *tail;
};

#endif //IU_ALGOS_ELEM_H
