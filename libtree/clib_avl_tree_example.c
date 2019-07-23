#include <stdio.h>
#include "clib_avl_tree.h"

int my_compare(void* value1, void* value2) {

    if (*(int*)value1 > *(int*)value2) {
        return 1;
    } else if (*(int*)value1 < *(int*)value2) {
        return -1;
    }

    return 0;
}

void my_print(void* key) {
    printf("%d\t", *((int*)key));
}

int main() {
    avl_tree_t* tree = avl_tree_new(my_compare);
    if (NULL == tree) {
        puts("初始化失败!");
    }
    unsigned int i;
    int values[] = { 0, 1, 2, 3, 4, 5, 6 , 7, 7, 1};

    printf("要插入的值\n");
    for (i = 0; i < sizeof (values) / sizeof (int); ++ i) {
        printf("%d|%d\t", i, values[i]);
        avl_tree_insert(tree, &values[i], &values[i]);
    }

    printf("\n树的节点的数 %d\n", avl_tree_num(tree));
    printf("\n前序遍历:\n");
    preorder_print_tree(avl_tree_root_node(tree), my_print);
    puts("\n=====\n=====\n");

    int key = values[1];

    printf("要查询的值：%d", key);

    void* res = avl_tree_lookup_value(tree, &key);
    if (NULL == res) {
        printf("\nNOT FOUND!\n");
    } else {
        printf("\n查询到的值是：%d\n", *(int*)res);
    }

    printf("\n树的节点个数：%d\n", avl_tree_num(tree));

    avl_tree_remove_node(tree, avl_tree_lookup_node(tree, res));

    printf("\n删除后的节点 %d\n", avl_tree_num(tree));

    printf("\n前序遍历:\n");
    preorder_print_tree(avl_tree_root_node(tree), my_print);

    printf("\n中序遍历:\n");
    midorder_print_tree(avl_tree_root_node(tree), my_print);

    printf("\n后序遍历:\n");
    postorder_print_tree(avl_tree_root_node(tree), my_print);

    avl_tree_free(tree);
    printf("\n\n");

    return 0;
}