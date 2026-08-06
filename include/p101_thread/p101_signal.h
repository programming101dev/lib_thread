#ifndef LIBP101_THREAD_P101_SIGNAL_H
#define LIBP101_THREAD_P101_SIGNAL_H

/*
 * Copyright 2026 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBP101_THREAD_SHARED_DECLARATIONS
    #define LIBP101_THREAD_SHARED_DECLARATIONS
    #include <p101_env/env.h>
    #include <p101_error/attributes.h>
    #include <pthread.h>
    #include <signal.h>
#endif    // LIBP101_THREAD_SHARED_DECLARATIONS

#ifdef __cplusplus
extern "C"
{
#endif

    int p101_pthread_kill(const struct p101_env *env, struct p101_error *err, pthread_t thread, int sig);
    int p101_pthread_sigmask(const struct p101_env *env, struct p101_error *err, int how, const sigset_t *restrict set, sigset_t *restrict oset);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_THREAD_P101_SIGNAL_H
