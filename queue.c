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

    element_t *element = list_first_entry(head, element_t, list);
    list_del_init(&element->list);

    if (sp != NULL) {
        strncpy(sp, element->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return element;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))  // if queue is NULL or head = NULL
        return NULL;

    element_t *element = list_last_entry(head, element_t, list);
    list_del_init(&element->list);

    if (sp != NULL) {
        strncpy(sp, element->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return element;
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

    if (!head || list_empty(head))
        return false;

    struct list_head *fast = head->next, *slow = head->next;
    do {
        slow = slow->next;
        fast = fast->next->next;
    } while (fast->next != head && fast->next->next != head);

    element_t *mid = list_entry(slow, element_t, list);
    list_del(slow);
    q_release_element(mid);

    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (list_empty(head))
        return false;

    element_t *entry = NULL, *safe = NULL, *temp = NULL;
    list_for_each_entry_safe (entry, safe, head, list) {
        if (temp != NULL && strcmp(temp->value, entry->value)) {
            list_del(&entry->list);
            q_release_element(entry);
            continue;
        }
        temp = entry;
    }

    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // ttps://leetcode.com/problems/swap-nodes-in-pairs/

    if (!head)
        return;
    q_reverseK(head, 2);
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
    if (!head || list_empty(head))  // if queue is NULL or head = NULL
        return;

    int count = 1;
    struct list_head *node = NULL, *safe = NULL, *temp = head;
    list_for_each_safe (node, safe, head) {
        if (count % k == 0) {
            for (int i = 0; i < k; i++) {
                list_move(node, temp);
                temp = temp->next;
                node = safe->prev;
            }
        }

        count++;
    }
}

void split(struct list_head **front, struct list_head **back)
{
    struct list_head *fast = *front, *slow = *front;
    while (fast->next != *front && fast->next->next != *front) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *back = slow->next;
    slow->next = *front;
    (*back)->prev = (*front)->prev;
    (*front)->prev->next = *back;
    (*front)->prev = slow;
}

struct list_head *mergelist(struct list_head *front, struct list_head *back)
{
    struct list_head *result = NULL, *temp = NULL, *walk1 = front,
                     *walk2 = back;
    struct list_head *front_tail = front->prev, *back_tail = back->prev;
    front_tail->next = NULL, back_tail->next = NULL;

    while (walk1 != NULL && walk2 != NULL) {
        element_t *element1 = list_entry(walk1, element_t, list);
        element_t *element2 = list_entry(walk2, element_t, list);
        if (strcmp(element1->value, element2->value) < 0) {
            if (!result) {
                result = walk1;
                temp = result;
            } else {
                temp->next = walk1;
                walk1->prev = temp;
                temp = temp->next;
            }

            walk1 = walk1->next;
        } else {
            if (!result) {
                result = walk2;
                temp = result;
            } else {
                temp->next = walk2;
                walk2->prev = temp;
                temp = temp->next;
            }

            walk2 = walk2->next;
        }
    }

    if (walk2 == NULL) {
        temp->next = walk1;
        walk1->prev = temp;
        front_tail->next = result;
        result->prev = front_tail;
    } else {
        temp->next = walk2;
        walk2->prev = temp;
        back_tail->next = result;
        result->prev = back_tail;
    }

    return result;
}

void mergesort(struct list_head **head)
{
    if ((*head)->next == *head)
        return;
    struct list_head *front = *head, *back = NULL;
    split(&front, &back);

    mergesort(&front);
    mergesort(&back);

    *head = mergelist(front, back);
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head)
{
    if (!head || list_empty(head))  // if queue is NULL or head = NULL
        return;

    struct list_head *front = head->next;
    list_del_init(head);

    mergesort(&front);
    head->prev = front->prev;
    head->next = front;
    front->prev->next = head;
    front->prev = head;

}

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
