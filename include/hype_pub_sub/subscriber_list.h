
#ifndef HYPE_PUB_SUB_SUBSCRIBER_LIST_H_INCLUDED_
#define HYPE_PUB_SUB_SUBSCRIBER_LIST_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "constants.h"

typedef struct Subscriber_
{
  byte* subscriber_id;
  struct Subscriber_* next_subscriber;
} Subscriber;

Subscriber* hype_pub_sub_subscriber_list_create();

int hype_pub_sub_subscriber_list_add(Subscriber* head, byte subs_id[HYPE_ID_BYTE_SIZE]);

int hype_pub_sub_subscriber_list_remove(Subscriber **head, byte subs_id[HYPE_ID_BYTE_SIZE]);

bool hype_pub_sub_subscriber_list_is_subscribed(Subscriber *head, byte subs_id[HYPE_ID_BYTE_SIZE]);

bool hype_pub_sub_subscriber_list_is_empty(Subscriber* head);

#endif /* HYPE_PUB_SUB_SUBSCRIBER_LIST_H_INCLUDED_ */
