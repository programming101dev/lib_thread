/*
 * Copyright 2021-2024 D'Arcy Smith.
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

#include "p101_thread/thread.h"
#include <p101_env/wrapper.h>

int p101_pthread_attr_getinheritsched(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, int *restrict inheritsched)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_attr_getinheritsched(attr, inheritsched);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_getschedpolicy(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, int *restrict policy)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_attr_getschedpolicy(attr, policy);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_getscope(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, int *restrict contentionscope)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_attr_getscope(attr, contentionscope);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_getstack(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, void **restrict stackaddr, size_t *restrict stacksize)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_attr_getstack(attr, stackaddr, stacksize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_getstacksize(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, size_t *restrict stacksize)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_attr_getstacksize(attr, stacksize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_setinheritsched(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int inheritsched)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_attr_setinheritsched(attr, inheritsched);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_setschedpolicy(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int policy)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_attr_setschedpolicy(attr, policy);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_setscope(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int contentionscope)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_attr_setscope(attr, contentionscope);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_setstack(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, void *stackaddr, size_t stacksize)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_attr_setstack(attr, stackaddr, stacksize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_attr_setstacksize(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, size_t stacksize)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_attr_setstacksize(attr, stacksize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_getschedparam(const struct p101_env *env, struct p101_error *err, pthread_t thread, int *restrict policy, struct sched_param *restrict param)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_getschedparam(thread, policy, param);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_setschedparam(const struct p101_env *env, struct p101_error *err, pthread_t thread, int policy, const struct sched_param *param)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err);
    ret_val = pthread_setschedparam(thread, policy, param);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}
