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

#ifndef HPB_HYPE_INTERFACE_H_INCLUDED_
#define HPB_HYPE_INTERFACE_H_INCLUDED_

#include <hype/hype.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

//Request the Hype services to start
void hpb_hype_interface_request_to_start();

//Request the Hype services to stop
void hpb_hype_interface_request_to_stop();

//Add resolved intances
void hpb_hype_interface_instance_resolved_add(HypeInstance * instance);

//Remove lost intances
void hpb_hype_interface_intance_remove(HypeInstance * intance);


#endif /* HPB_HYPE_INTERFACE_H_INCLUDED_ */
