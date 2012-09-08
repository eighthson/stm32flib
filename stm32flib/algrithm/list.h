#ifndef __LIST_H__
#define __LIST_H__

struct list_node {
	struct list *list;
	struct list_node *prev;
	struct list_node *next;
};

struct list {
	struct list_node *head;
	struct list_node *tail;
};

#ifdef __cplusplus
extern "C" {
#endif

int list_init(struct list *list);
int list_node_init(struct list_node *node);
int list_add_head(struct list *list, struct list_node *node);
int list_add_tail(struct list *list, struct list_node *node);
int list_insert_before(struct list_node *ref, struct list_node *node);
int list_insert_after(struct list_node *ref, struct list_node *node);
int list_node_off(struct list_node *node);

#ifdef __cplusplus
}
#endif

#endif // __LIST_H__
