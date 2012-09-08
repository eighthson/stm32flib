#include "stm32flib.h"

int __inline__ list_init(struct list *list) {
#if defined(DO_PARAM_CHECKING)
	if (list == NULL)
		return -1;
#endif

	list->head = NULL;
	list->tail = NULL;

	return 0;
}

int __inline__ list_node_init(struct list_node *node) {
#if defined(DO_PARAM_CHECKING)
	if (node == NULL)
		return -1;
#endif

	node->list = NULL;
	node->prev = NULL;
	node->next = NULL;

	return 0;
}

int list_add_head(struct list *list, struct list_node *node) {
#if defined(DO_PARAM_CHECKING)
	if (list == NULL || node == NULL)
		return -1;
#endif

	if (node->list != NULL)
		return -1;

	if (list->head == NULL) {
		list->head = list->tail = node;
		node->prev = node->next = NULL;
	}
	else {
		node->prev = NULL;
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}

	node->list = list;
	return 0;
}

int list_add_tail(struct list *list, struct list_node *node) {
#if defined(DO_PARAM_CHECKING)
	if (list == NULL || node == NULL)
		return -1;
#endif

	if (node->list != NULL)
		return -1;

	if (list->head == NULL) {
		list->head = list->tail = node;
		node->prev = node->next = NULL;
	}
	else {
		node->prev = list->tail;
		node->next = NULL;
		list->tail->next = node;
		list->tail = node;
	}

	node->list = list;
	return 0;
}

int list_insert_before(struct list_node *ref, struct list_node *node) {
#if defined(DO_PARAM_CHECKING)
	if (ref == NULL || node == NULL || ref->list == NULL)
		return -1;
#endif

	if (node->list != NULL)
		return -1;

	node->prev = ref->prev;
	node->next = ref;
	ref->prev = node;
	node->list = ref->list;

	if (node->prev == NULL)
		ref->list->head = node;

	return 0;
}

int list_insert_after(struct list_node *ref,	struct list_node *node) {
#if defined(DO_PARAM_CHECKING)
	if (ref == NULL || node == NULL || ref->list == NULL)
		return -1;
#endif

	if (node->list != NULL)
		return -1;

	node->prev = ref;
	node->next = ref->next;
	ref->next = node;
	node->list = ref->list;

	if (node->next == NULL)
		ref->list->tail = node;

	return 0;
}

int list_off(struct list_node *node) {
	register struct list *list;

#if defined(DO_PARAM_CHECKING)
	if (node == NULL)
		return -1;
#endif

	list = (struct list *)node->list;
	if (list == NULL)
		return -1;

	if (node == list->head) {
		list->head = node->next;
		if (list->head != NULL) {
			list->head = node->next;
			list->head->prev = NULL;
		}
		else
			list->tail = NULL;
	}
	else if (node == list->tail) {
		list->tail = node->prev;
		if (list->tail != NULL) {
			list->tail = node->prev;
			list->tail->next = NULL;
		}
		else
			list->head = NULL;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	node->list = NULL;
	return 0;
}
