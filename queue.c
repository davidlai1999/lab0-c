#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *empty =
        (struct list_head *) malloc(sizeof(struct list_head));

    if (!empty)  // if malloc failed, return NULL
        return NULL;
    INIT_LIST_HEAD(empty);

    return empty;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;

    element_t *it = NULL, *is = NULL;
    list_for_each_entry_safe (it, is, l, list) {
        list_del(&it->list);
        q_release_element(it);
    }
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)  // if queue is NULL
        return false;

    element_t *element = malloc(sizeof(element_t));
    if (!element)  // if malloc failed, return NULL
        return false;

    int s_len = strlen(s) + 1;  // handle the value of element
    char *str = malloc(s_len * sizeof(char));
    if (!str) {         // if malloc failed, return NULL
        free(element);  // because insert failed,release memory
        return false;
    }
    strncpy(str, s, s_len);
    element->value = str;

    list_add(&element->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)  // if queue is NULL
        return false;

    element_t *element = malloc(sizeof(element_t));
    if (!element)  // if malloc failed, return NULL
        return false;

    int s_len = strlen(s) + 1;  // handle the value of element
    char *str = malloc(s_len * sizeof(char));
    if (!str) {         // if malloc failed, return NULL
        free(element);  // because insert failed,release memory
        return false;
    }
    strncpy(str, s, s_len);
    element->value = str;

    list_add_tail(&element->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))  // if queue is NULL or head = NULL
        return NULL;

    return NULL;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    return NULL;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))  // if queue is NULL or head = NULL
        return;

    element_t *it = NULL, *is = NULL;
    list_for_each_entry_safe (it, is, head, list) {
        list_move(&it->list, head);
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
