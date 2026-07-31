#ifndef LIBP101_THREAD_THREAD_H
#define LIBP101_THREAD_THREAD_H

/*
 * Copyright 2026 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 */

#include <p101_env/env.h>
#include <p101_error/attributes.h>
#include <pthread.h>
#include <signal.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int                     p101_pthread_atfork(const struct p101_env *env, struct p101_error *err, void (*prepare)(void), void (*parent)(void), void (*child)(void));
    int                     p101_pthread_attr_destroy(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr);
    int                     p101_pthread_attr_getdetachstate(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *attr, int *detachstate);
    int                     p101_pthread_attr_getguardsize(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, size_t *restrict guardsize);
    int                     p101_pthread_attr_getinheritsched(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, int *restrict inheritsched);
    int                     p101_pthread_attr_getschedparam(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, struct sched_param *restrict param);
    int                     p101_pthread_attr_getschedpolicy(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, int *restrict policy);
    int                     p101_pthread_attr_getscope(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, int *restrict contentionscope);
    int                     p101_pthread_attr_getstack(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, void **restrict stackaddr, size_t *restrict stacksize);
    int                     p101_pthread_attr_getstacksize(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, size_t *restrict stacksize);
    int                     p101_pthread_attr_init(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr);
    int                     p101_pthread_attr_setdetachstate(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int detachstate);
    int                     p101_pthread_attr_setguardsize(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, size_t guardsize);
    int                     p101_pthread_attr_setinheritsched(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int inheritsched);
    int                     p101_pthread_attr_setschedparam(const struct p101_env *env, struct p101_error *err, pthread_attr_t *restrict attr, const struct sched_param *restrict param);
    int                     p101_pthread_attr_setschedpolicy(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int policy);
    int                     p101_pthread_attr_setscope(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int contentionscope);
    int                     p101_pthread_attr_setstack(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, void *stackaddr, size_t stacksize);
    int                     p101_pthread_attr_setstacksize(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, size_t stacksize);
    int                     p101_pthread_cancel(const struct p101_env *env, struct p101_error *err, pthread_t thread);
    int                     p101_pthread_create(const struct p101_env *env, struct p101_error *err, pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
    int                     p101_pthread_detach(const struct p101_env *env, struct p101_error *err, pthread_t thread);
    int                     p101_pthread_equal(const struct p101_env *env, pthread_t t1, pthread_t t2);
    P101_ATTR_NORETURN void p101_pthread_exit(const struct p101_env *env, void *value_ptr);
    int                     p101_pthread_getschedparam(const struct p101_env *env, struct p101_error *err, pthread_t thread, int *restrict policy, struct sched_param *restrict param);
    void                   *p101_pthread_getspecific(const struct p101_env *env, pthread_key_t key);
    int                     p101_pthread_join(const struct p101_env *env, struct p101_error *err, pthread_t thread, void **value_ptr);
    int                     p101_pthread_key_create(const struct p101_env *env, struct p101_error *err, pthread_key_t *key, void (*destructor)(void *));
    int                     p101_pthread_key_delete(const struct p101_env *env, struct p101_error *err, pthread_key_t key);
    int                     p101_pthread_kill(const struct p101_env *env, struct p101_error *err, pthread_t thread, int sig);
    pthread_t               p101_pthread_self(const struct p101_env *env);
    int                     p101_pthread_setcancelstate(const struct p101_env *env, struct p101_error *err, int state, int *oldstate);
    int                     p101_pthread_setcanceltype(const struct p101_env *env, struct p101_error *err, int type, int *oldtype);
    int                     p101_pthread_setschedparam(const struct p101_env *env, struct p101_error *err, pthread_t thread, int policy, const struct sched_param *param);
    int                     p101_pthread_setspecific(const struct p101_env *env, struct p101_error *err, pthread_key_t key, const void *value);
    int                     p101_pthread_sigmask(const struct p101_env *env, struct p101_error *err, int how, const sigset_t *restrict set, sigset_t *restrict oset);
    void                    p101_pthread_testcancel(const struct p101_env *env);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_THREAD_THREAD_H
