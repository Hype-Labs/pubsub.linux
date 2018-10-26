
#include "hype_pub_sub/hpb_subscription.h"

HpbSubscription *hpb_subscription_create(char *serv_name, size_t serv_name_len, HypeInstance * instance)
{
    HpbSubscription *subs = (HpbSubscription *) malloc(sizeof(HpbSubscription));

    // serv_name_len+1 to consider \0
    subs->service_name = (char *) calloc ((serv_name_len + 1), sizeof(char));
    strncpy(subs->service_name, (const char*) serv_name, serv_name_len);
    sha1_digest((const BYTE *) serv_name, serv_name_len, subs->service_key);

    subs->manager_instance = hype_instance_create(instance->identifier,instance->announcement, instance->is_resolved);

    return subs;
}

void hpb_subscription_destroy(HpbSubscription **subs)
{
    if((*subs) == NULL)
        return;

    free((*subs)->service_name);
    free(*subs);
    (*subs) = NULL;
}
