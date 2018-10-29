//
// Copyright (C) 2018 Hype Labs - All Rights Reserved
//
// NOTICE: All information contained herein is, and remains the property of Hype
// Labs. The intellectual and technical concepts contained herein are proprietary
// to Hype Labs and may be covered by U.S. and Foreign Patents, patents in process,
// and are protected by trade secret and copyright law. Dissemination of this
// information or reproduction of this material is strictly forbidden unless prior
// written permission is obtained from Hype Labs.
//

#include <hype_pub_sub/hpb_hype_interface.h>
#include <hype_pub_sub/hpb_constants.h>
#include <hype_pub_sub/hpb_clients_list.h>
#include <hype_pub_sub/hype_pub_sub.h>
#include <stdio.h>

//Hype callbacks definition
static void hpb_hype_on_start()
{
    printf("Hype started!\n");

    //Signal the start of hype service
    if (pthread_cond_signal(&cond) != 0) {
        perror("pthread_cond_signal() error");
        exit(4);
    }

    fflush(stdout);

}

static void hpb_hype_on_stop(HypeError * err)
{
    char * description = "null";
    if (err != NULL)
    {

        // The error parameter will usually be null if the framework stopped because
        // it was requested to stop. This might not always happen, as even if requested
        // to stop the framework might do so with an error.
        description = err->description;
    }

    printf("Hype stopped [%s]\n", description);

    // The framework has stopped working for some reason. If it was asked to do so (by
    // calling stop) the error parameter is null. If, on the other hand, it was forced
    // by some external means, the error parameter indicates the cause. Common causes
    // include the user turning the Bluetooth adapter off. When the later
    // happens, you shouldn't attempt to start the Hype services again. Instead, the
    // framework triggers a onReady delegate method call if recovery from the failure
    // becomes possible.

    fflush(stdout);
}

static void hpb_hype_on_start_failed(HypeError * err)
{
    printf("Hype failed starting [%s]\n", err->description);

    // The framework couldn't start for some reason. Common causes include the Bluetooth
    // adapter being turned off. The error parameter always indicates the
    // cause for the failure, it's never null.

    fflush(stdout);
}

static void hpb_hype_on_state_change()
{
    printf("Hype state change\n");

    // State change updates are triggered before their corresponding, specific, observer
    // call. For instance, when Hype starts, it transits to the State.Running state,
    // triggering a call to this method, and only then is hype_on_start() called. Every
    // such event has a corresponding observer method, so state change notifications
    // are mostly for convenience. This method is often not used.

    fflush(stdout);
}

static void hpb_hype_on_ready()
{
    printf("Hype ready \n");

    // This Hype delegate event indicates that the framework believes that it's capable
    // of recovering from a previous start failure. This event is only triggered once.
    // It's not guaranteed that starting the services will result in success, but it's
    // known to be highly likely. If the services are not needed at this point it's
    // possible to delay the execution for later, but it's not guaranteed that the
    // recovery conditions will still hold by then.

    hype_start();

    fflush(stdout);
}

static const char * hpb_hype_on_request_access_token(uint32_t user_identifier)
{
    printf("Hype request access token to user identifier: %d\n", (int)user_identifier);

    // This method is called because Hype is requiring a new digital certificate. This
    // may happen because no certificate exists or the current one has already expired.
    // The access token will be sent to the HypeLabs backend, which requires access to
    // the Internet. The backend validates this token against the configurations set on
    // the HypeLabs dashboard for this app. By default, this template uses a token used
    // for testing. It's recommended that a backend is implemented and configured to
    // generate and validate access tokens before the app is deployed. The test token
    // for this app is given below, but it's only valid for 10 deployments.

    return HPB_HYPE_TOKEN_IDENTIFIER;
}

static void hpb_hype_on_instance_found(HypeInstance * instance)
{
    printf("Hype Found instance:  \n");
    printf("instance->string_identifier= %s ", instance->string_identifier);

    // Resolving an instance consists of forcing the two devices to perform an handshake,
    // a necessary step for communicating. In this demo all instances are resolved, but
    // implementations should first assert whether the found instance is interesting,
    // whatever that means in the context of the app. Only instances deemed interesting
    // should be resolved, saving network overhead. In case of success, the SDK calls
    // the hype_instance_resolved called. In case of failure, the method
    // hype_on_fail_resolving is called instead.
    hype_resolve(instance);

    fflush(stdout);
}

static void hpb_hype_on_instance_lost(HypeInstance * instance, HypeError * err)
{
    // An instance being lost means that communicating with it is no longer possible.
    // This usually happens by the link being broken. This can happen if the connection
    // times out or the device goes out of range. Another possibility is the user turning
    // the adapters off, in which case not only are all instances lost but the framework
    // also stops with an error.
    printf("Hype lost instance: %s [%s]\n", instance->string_identifier, err->description);

    fflush(stdout);
}

static void hpb_hype_on_instance_resolved(HypeInstance * instance)
{
    printf("Hype resolve instance: %s\n", instance->string_identifier);

    // An instance being resolved means that it's ready for communicating. In this
    // case, the implementation sends an "Hello World" string encoded in UTF-8 format.
    // Although this is showing a simple scenario, application level protocols can be
    // as complex as necessary.

    const char * msg = "Hello World";
    size_t size = strlen(msg)+1;

    hype_send((void *)msg, size, instance, true);

    fflush(stdout);
}

static void hpb_hype_on_instance_failed_resolving(HypeInstance * instance, HypeError * err)
{
    printf("Hype failed to resolve instance: %s [%s]\n", instance->string_identifier, err->description);

    // Failing to resolve an instance may indicate that the instance went out of range.
    // It's also a possibility that the instance was an attacker in disguise, but failed
    // to perform an handshake and Hype is refusing to communicate with it. The error
    // argument indicates a proper cause for the error.

    fflush(stdout);
}

static void hpb_hype_on_message_received(HypeMessage * message, HypeInstance * instance)
{
    printf("Hype receive message from: %s | %s\n",instance->string_identifier, (char *)message->buffer->data);

    // A message has arrived from another device. In this case, the message is expected
    // to be text encoded in UTF-8 format, the same protocol that was used when sending
    // a message.

    fflush(stdout);
}

static void hpb_hype_on_message_send_failed(HypeMessageInfo * message_info, HypeInstance * instance, HypeError * err)
{
    printf("Failed to send message: %d [%s]", message_info->identifier, err->description);

    // Sending messages can fail for a lot of reasons, such as the adapters
    // (Bluetooth) being turned off by the user while the process
    // of sending the data is still ongoing. The error parameter describes
    // the cause for the failure.

}

static void hpb_hype_on_message_sent(HypeMessageInfo * message_info,HypeInstance * instance, float progress, bool done)
{

    printf("Hype is sending a message: %d | %f (%s)", message_info->identifier, progress, done ? "done" : "ongoing" );

    // A message being sent indicates that it has been written to the output streams.
    // However, the content could still be buffered for output, so it has not necessarily
    // left the device. This is useful to indicate when a message is being processed,
    // but it does not indicate delivery to the destination device. The full contents
    // of the message have been written when the boolean flag "done" is set to true.
    // To indicate delivery check onHypeMessageDelivered(MessageInfo, Instance, float, boolean).

    fflush(stdout);
}

static void hpb_hype_on_message_delivered(HypeMessageInfo * message_info, HypeInstance * instance, float progress, bool done)
{


    // A message being delivered indicates that the destination device has
    // acknowledge reception. If the "done" argument is true, then the message
    // has been fully delivered and the content is available on the destination
    // device. This method is useful for implementing progress bars.

    fflush(stdout);
}

static void hpb()
{

}

void hpb_hype_interface_request_to_start()
{
    // Adding itself as an Hype state observer makes sure that the application gets
    // notifications for lifecycle events being triggered by the Hype framework. These
    // events include starting and stopping, as well as some error handling.
    hype_set_on_start_callback(hpb_hype_on_start);
    hype_set_on_stop_callback(hpb_hype_on_stop);
    hype_set_on_start_failed_callback(hpb_hype_on_start_failed);
    hype_set_on_state_change_callback(hpb_hype_on_state_change);
    hype_set_on_ready_callback(hpb_hype_on_ready);
    hype_set_on_request_access_token_callback(hpb_hype_on_request_access_token);

    // Network observer notifications include other devices entering and leaving the
    // network. When a device is found all observers get a hype_on_instance_found notification,
    // and when they leave hype_on_instance_lost is triggered instead.
    hype_set_on_instance_found_callback(hpb_hype_on_instance_found);
    hype_set_on_instance_lost_callback(hpb_hype_on_instance_lost);
    hype_set_on_instance_resolved_callback(hpb_hype_on_instance_resolved);
    hype_set_on_instance_failed_resolving_callback(hpb_hype_on_instance_failed_resolving);

    // I/O notifications indicate when messages are sent, delivered, or fail to be sent.
    // Notice that a message being sent does not imply that it has been delivered, only
    // that it has been queued for output. This is especially important when using mesh
    // networking, as the destination device might not be connect in a direct link.
    hype_set_on_message_received_callback(hpb_hype_on_message_received);
    hype_set_on_message_send_failed_callback(hpb_hype_on_message_send_failed);
    hype_set_on_message_sent_callback(hpb_hype_on_message_sent);
    hype_set_on_message_delivered_callback(hpb_hype_on_message_delivered);


    // For generating a app identifier go to https://hypelabs.io, login, access the dashboard
    // under the Apps section and click "Create New App". The resulting app should
    // display a realm number. Copy and paste that here.
    //Hype.hype_set_app_identifier("{{app_identifier}}");
    hype_set_app_identifier(HPB_HYPE_APP_IDENTIFIER);

    hype_set_transport_type(HYPE_TRANSPORT_TYPE_WIFI_INFRA);

    hype_set_user_identifier(HPB_HYPE_USER_IDENTIFIER);

    // Requesting Hype to start is equivalent to requesting the device to publish
    // itself on the network and start browsing for other devices in proximity. If
    // everything goes well, the onStart(Hype) observer method gets called, indicating
    // that the device is actively participating on the network.
    hype_start();

}

void hpb_hype_interface_request_to_stop()
{
    printf("Stop the Hype services");
    hype_stop();
}

void hpb_hype_interface_instance_resolved_add(HypeInstance * instance)
{
    HypePubSub * hpb = hpb_get();

   //hpb->network->network_clients
   hpb_list_clients_add(hpb->network->network_clients, instance);

}

void hpb_hype_interface_instance_remove(HypeInstance * instance)
{

}

