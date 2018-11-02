
#include <hpb_test_utils.h>
#include <hype/hype.h>

HpbClient * hpb_test_utils_get_client_from_id(HLByte *id, size_t size)
{
    HypeBuffer *buffer_id = hype_buffer_create_from(id, size);
    HypeInstance *instance = hype_instance_create(buffer_id, NULL, false);
    HpbClient *client = hpb_client_create(instance);
    hype_buffer_release(buffer_id);
    hype_instance_release(instance);
    return client;
}
