#include <p101_env/env.h>
#include <p101_error/error.h>
#include <p101_thread/p101_pthread.h>
#include <p101_thread/p101_signal.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int failures;

#define EXPECT(condition)                                                                                                                                                                                                                                          \
    do                                                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                              \
        if(!(condition))                                                                                                                                                                                                                                           \
        {                                                                                                                                                                                                                                                          \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition);                                                                                                                                                                                   \
            failures++;                                                                                                                                                                                                                                            \
        }                                                                                                                                                                                                                                                          \
    } while(0)

static void *exit_thread(void *argument)
{
    const struct p101_env *env = argument;

    /* P101_TEST_CASE(p101_pthread_exit) */
    p101_pthread_exit(env, argument);
    return NULL;
}

int main(void)
{
    struct p101_error *err;
    struct p101_env   *env;
    pthread_t          self;
    pthread_t          thread;
    pthread_key_t      key;
    void              *value;
    void              *thread_result;
    int                marker;

    err = p101_error_create(false);
    if(err == NULL)
    {
        return EXIT_FAILURE;
    }
    env = p101_env_create(err, NULL);
    if(env == NULL)
    {
        p101_error_destroy(err);
        return EXIT_FAILURE;
    }

    /* P101_TEST_CASE(p101_pthread_self) */
    self = p101_pthread_self(env);
    /* P101_TEST_CASE(p101_pthread_equal) */
    EXPECT(p101_pthread_equal(env, self, pthread_self()) != 0);

    EXPECT(pthread_key_create(&key, NULL) == 0);
    marker = 42;
    EXPECT(pthread_setspecific(key, &marker) == 0);
    /* P101_TEST_CASE(p101_pthread_getspecific) */
    value = p101_pthread_getspecific(env, key);
    EXPECT(value == &marker);
    EXPECT(pthread_key_delete(key) == 0);

    /* P101_TEST_CASE(p101_pthread_testcancel) */
    p101_pthread_testcancel(env);

    EXPECT(pthread_create(&thread, NULL, exit_thread, env) == 0);
    EXPECT(pthread_join(thread, &thread_result) == 0);
    EXPECT(thread_result == env);

    p101_env_destroy(env);
    p101_error_destroy(err);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
