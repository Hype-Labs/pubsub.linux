
#include "hype_pub_sub/subscription.h"

Subscription *hpb_subscription_create(char *serv_name, size_t serv_name_len, byte man_id[HPB_ID_BYTE_SIZE])
{
    Subscription *subs = (Subscription *) malloc(sizeof(Subscription));

    subs->service_name = (char *) malloc ((serv_name_len + 1) * sizeof(char)); // +1 -> \0
    strncpy(subs->service_name, (const char*) serv_name, serv_name_len);
    sha1_digest((const BYTE *) serv_name, serv_name_len, subs->service_key);
    memcpy(subs->manager_id, man_id, HPB_ID_BYTE_SIZE * sizeof(byte));

    return subs;
}

void hpb_subscription_destroy(Subscription **subs)
{
    if((*subs) == NULL)
        return;

    free((*subs)->service_name);
    free(*subs);
    (*subs) = NULL;
}
