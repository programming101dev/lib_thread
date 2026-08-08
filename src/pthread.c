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

#include "p101_thread/p101_pthread.h"
#include <p101_env/resource_classes.h>
#include <p101_env/wrapper.h>

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

enum
{
    P101_HEX_SHIFT            = 4,
    P101_HEX_MASK             = 15,
    P101_THREAD_METADATA_SIZE = 8 + (sizeof(pthread_t) * 2) + 1,
    P101_MUTEX_OWNER_ID_SIZE  = P101_ENV_POINTER_RESOURCE_ID_SIZE + P101_THREAD_METADATA_SIZE + 1
};

void p101_pthread_resource_metadata(const struct p101_env *env, pthread_t thread, char *text, size_t text_size)
{
    static const char digits[] = "0123456789abcdef";
    static const char prefix[] = "thread=";

    P101_TRACE(env);

    if(text != NULL && text_size > 0U)
    {
        const unsigned char *bytes;
        size_t               offset;

        bytes = (const unsigned char *)&thread;
        for(offset = 0U; offset < sizeof(prefix) - 1U && offset + 1U < text_size; offset++)
        {
            text[offset] = prefix[offset];
        }
        for(size_t i = 0U; i < sizeof(pthread_t) && offset + 2U < text_size; i++)
        {
            text[offset++] = digits[(bytes[i] >> P101_HEX_SHIFT) & P101_HEX_MASK];
            text[offset++] = digits[bytes[i] & P101_HEX_MASK];
        }
        text[offset] = '\0';
    }

    P101_TRACE_EXIT(env);
}

static void pthread_track_joinable(const struct p101_env *env, p101_env_resource_kind event, pthread_t thread, const char *file_name, const char *function_name, int line_number)
{
    char resource_id[P101_THREAD_METADATA_SIZE];

    p101_pthread_resource_metadata(env, thread, resource_id, sizeof(resource_id));
    p101_env_track_resource(env, event, P101_RESOURCE_CLASS_PTHREAD_JOINABLE_THREAD, resource_id, NULL, 0U, NULL, file_name, function_name, line_number);
}

static void pthread_track_join_wait(const struct p101_env *env, p101_env_resource_kind event, pthread_t target, const char *file_name, const char *function_name, int line_number)
{
    char      current_id[P101_THREAD_METADATA_SIZE];
    char      target_id[P101_THREAD_METADATA_SIZE];
    pthread_t current;

    current = p101_pthread_self(env);
    p101_pthread_resource_metadata(env, current, current_id, sizeof(current_id));
    p101_pthread_resource_metadata(env, target, target_id, sizeof(target_id));
    p101_env_track_resource(env, event, P101_RESOURCE_CLASS_PTHREAD_JOIN_WAIT, current_id, target_id, 0U, current_id, file_name, function_name, line_number);
}

#define P101_PTHREAD_TRACK_JOINABLE_ACQUIRE(env, thread) pthread_track_joinable((env), P101_ENV_RESOURCE_ACQUIRE, (thread), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_JOINABLE_RELEASE(env, thread) pthread_track_joinable((env), P101_ENV_RESOURCE_RELEASE, (thread), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_JOIN_WAIT_ACQUIRE(env, thread) pthread_track_join_wait((env), P101_ENV_RESOURCE_ACQUIRE, (thread), __FILE__, __func__, __LINE__)
#define P101_PTHREAD_TRACK_JOIN_WAIT_RELEASE(env, thread) pthread_track_join_wait((env), P101_ENV_RESOURCE_RELEASE, (thread), __FILE__, __func__, __LINE__)

/* cppcheck-suppress funcArgNamesDifferentUnnamed */
int p101_pthread_atfork(const struct p101_env *env, struct p101_error *err, void (*prepare)(void), void (*parent)(void), void (*child)(void))
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_atfork(prepare, parent, child);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_destroy(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_attr_destroy(attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_TRACK_POINTER_RESOURCE_RELEASE(env, P101_RESOURCE_CLASS_PTHREAD_ATTRIBUTES, (const void *)attr, NULL);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_getdetachstate(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *attr, int *detachstate)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_attr_getdetachstate(attr, detachstate);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_getguardsize(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, size_t *restrict guardsize)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_attr_getguardsize(attr, guardsize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_getschedparam(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, struct sched_param *restrict param)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_attr_getschedparam(attr, param);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_init(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_attr_init(attr);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_TRACK_POINTER_RESOURCE_ACQUIRE(env, P101_RESOURCE_CLASS_PTHREAD_ATTRIBUTES, (const void *)attr, 0U, NULL);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_setdetachstate(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int detachstate)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_attr_setdetachstate(attr, detachstate);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_setguardsize(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, size_t guardsize)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_attr_setguardsize(attr, guardsize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_setschedparam(const struct p101_env *env, struct p101_error *err, pthread_attr_t *restrict attr, const struct sched_param *restrict param)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_attr_setschedparam(attr, param);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_cancel(const struct p101_env *env, struct p101_error *err, pthread_t thread)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_cancel(thread);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

/* cppcheck-suppress funcArgNamesDifferentUnnamed */
int p101_pthread_create(const struct p101_env *env, struct p101_error *err, pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg)
{
    int p101_single_result_;
    int detach_state;
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    detach_state = PTHREAD_CREATE_JOINABLE;
    if(attr != NULL)
    {
        ret_val = pthread_attr_getdetachstate(attr, &detach_state);
        if(ret_val != 0)
        {
            P101_ERROR_RAISE_ERRNO(err, ret_val);
            P101_WRAPPER_DONE(env);
            p101_single_result_ = ret_val;
            goto p101_single_exit_;
        }
    }
    errno   = 0;
    ret_val = pthread_create(thread, attr, start_routine, arg);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else if(detach_state == PTHREAD_CREATE_JOINABLE)
    {
        P101_PTHREAD_TRACK_JOINABLE_ACQUIRE(env, *thread);
    }

    P101_TRACE_EXIT(env);
    p101_single_result_ = ret_val;
    goto p101_single_exit_;

p101_single_exit_:
    return p101_single_result_;
}

int p101_pthread_detach(const struct p101_env *env, struct p101_error *err, pthread_t thread)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_detach(thread);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_PTHREAD_TRACK_JOINABLE_RELEASE(env, thread);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_equal(const struct p101_env *env, pthread_t t1, pthread_t t2)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pthread_equal(t1, t2);

    P101_TRACE_EXIT(env);
    return ret_val;
}

void p101_pthread_exit(const struct p101_env *env, void *value_ptr)
{
    P101_TRACE(env);
    errno = 0;
    P101_TRACE_EXIT(env);
    pthread_exit(value_ptr);
}

void *p101_pthread_getspecific(const struct p101_env *env, pthread_key_t key)
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pthread_getspecific(key);

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_join(const struct p101_env *env, struct p101_error *err, pthread_t thread, void **value_ptr)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    P101_PTHREAD_TRACK_JOIN_WAIT_ACQUIRE(env, thread);
    errno   = 0;
    ret_val = pthread_join(thread, value_ptr);
    P101_PTHREAD_TRACK_JOIN_WAIT_RELEASE(env, thread);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }
    else
    {
        P101_PTHREAD_TRACK_JOINABLE_RELEASE(env, thread);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_key_create(const struct p101_env *env, struct p101_error *err, pthread_key_t *key, void (*destructor)(void *))
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_key_create(key, destructor);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_key_delete(const struct p101_env *env, struct p101_error *err, pthread_key_t key)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_key_delete(key);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

pthread_t p101_pthread_self(const struct p101_env *env)
{
    pthread_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pthread_self();

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_pthread_setcancelstate(const struct p101_env *env, struct p101_error *err, int state, int *oldstate)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_setcancelstate(state, oldstate);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_setcanceltype(const struct p101_env *env, struct p101_error *err, int type, int *oldtype)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_setcanceltype(type, oldtype);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_setspecific(const struct p101_env *env, struct p101_error *err, pthread_key_t key, const void *value)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    errno   = 0;
    ret_val = pthread_setspecific(key, value);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

void p101_pthread_testcancel(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    pthread_testcancel();
    P101_TRACE_EXIT(env);
}

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

int p101_pthread_attr_getinheritsched(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, int *restrict inheritsched)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_attr_getinheritsched(attr, inheritsched);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_getschedpolicy(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, int *restrict policy)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_attr_getschedpolicy(attr, policy);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_getscope(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, int *restrict contentionscope)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_attr_getscope(attr, contentionscope);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_getstack(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, void **restrict stackaddr, size_t *restrict stacksize)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_attr_getstack(attr, stackaddr, stacksize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_getstacksize(const struct p101_env *env, struct p101_error *err, const pthread_attr_t *restrict attr, size_t *restrict stacksize)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_attr_getstacksize(attr, stacksize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_setinheritsched(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int inheritsched)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_attr_setinheritsched(attr, inheritsched);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_setschedpolicy(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int policy)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_attr_setschedpolicy(attr, policy);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_setscope(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, int contentionscope)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_attr_setscope(attr, contentionscope);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_setstack(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, void *stackaddr, size_t stacksize)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_attr_setstack(attr, stackaddr, stacksize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_attr_setstacksize(const struct p101_env *env, struct p101_error *err, pthread_attr_t *attr, size_t stacksize)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_attr_setstacksize(attr, stacksize);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_getschedparam(const struct p101_env *env, struct p101_error *err, pthread_t thread, int *restrict policy, struct sched_param *restrict param)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_getschedparam(thread, policy, param);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

int p101_pthread_setschedparam(const struct p101_env *env, struct p101_error *err, pthread_t thread, int policy, const struct sched_param *param)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_CODE(env, err, ret_val);
    ret_val = pthread_setschedparam(thread, policy, param);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}
