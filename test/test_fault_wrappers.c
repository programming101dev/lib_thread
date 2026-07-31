#include <errno.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <p101_thread/thread.h>
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

struct fault_state
{
    int checks;
};

static int fail_next_call(const struct p101_env *env, const char *call_name, void *user_data)
{
    struct fault_state *state;

    (void)env;
    (void)call_name;
    state = user_data;
    state->checks++;
    return EIO;
}

/* P101_TEST_CASE(p101_pthread_atfork) */
static void test_p101_pthread_atfork(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_atfork(env, err, NULL, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_destroy) */
static void test_p101_pthread_attr_destroy(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_destroy(env, err, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_getdetachstate) */
static void test_p101_pthread_attr_getdetachstate(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_getdetachstate(env, err, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_getguardsize) */
static void test_p101_pthread_attr_getguardsize(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_getguardsize(env, err, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_getinheritsched) */
static void test_p101_pthread_attr_getinheritsched(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_getinheritsched(env, err, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_getschedparam) */
static void test_p101_pthread_attr_getschedparam(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_getschedparam(env, err, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_getschedpolicy) */
static void test_p101_pthread_attr_getschedpolicy(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_getschedpolicy(env, err, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_getscope) */
static void test_p101_pthread_attr_getscope(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_getscope(env, err, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_getstack) */
static void test_p101_pthread_attr_getstack(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_getstack(env, err, NULL, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_getstacksize) */
static void test_p101_pthread_attr_getstacksize(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_getstacksize(env, err, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_init) */
static void test_p101_pthread_attr_init(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_init(env, err, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_setdetachstate) */
static void test_p101_pthread_attr_setdetachstate(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_setdetachstate(env, err, NULL, 0);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_setguardsize) */
static void test_p101_pthread_attr_setguardsize(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_setguardsize(env, err, NULL, 0);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_setinheritsched) */
static void test_p101_pthread_attr_setinheritsched(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_setinheritsched(env, err, NULL, 0);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_setschedparam) */
static void test_p101_pthread_attr_setschedparam(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_setschedparam(env, err, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_setschedpolicy) */
static void test_p101_pthread_attr_setschedpolicy(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_setschedpolicy(env, err, NULL, 0);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_setscope) */
static void test_p101_pthread_attr_setscope(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_setscope(env, err, NULL, 0);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_setstack) */
static void test_p101_pthread_attr_setstack(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_setstack(env, err, NULL, NULL, 0);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_attr_setstacksize) */
static void test_p101_pthread_attr_setstacksize(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_attr_setstacksize(env, err, NULL, 0);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_cancel) */
static void test_p101_pthread_cancel(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_cancel(env, err, (pthread_t){0});
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_create) */
static void test_p101_pthread_create(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_create(env, err, NULL, NULL, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_detach) */
static void test_p101_pthread_detach(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_detach(env, err, (pthread_t){0});
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_getschedparam) */
static void test_p101_pthread_getschedparam(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_getschedparam(env, err, (pthread_t){0}, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_join) */
static void test_p101_pthread_join(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_join(env, err, (pthread_t){0}, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_key_create) */
static void test_p101_pthread_key_create(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_key_create(env, err, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_key_delete) */
static void test_p101_pthread_key_delete(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_key_delete(env, err, 0);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_kill) */
static void test_p101_pthread_kill(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_kill(env, err, (pthread_t){0}, 0);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_setcancelstate) */
static void test_p101_pthread_setcancelstate(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_setcancelstate(env, err, 0, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_setcanceltype) */
static void test_p101_pthread_setcanceltype(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_setcanceltype(env, err, 0, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_setschedparam) */
static void test_p101_pthread_setschedparam(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_setschedparam(env, err, (pthread_t){0}, 0, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_setspecific) */
static void test_p101_pthread_setspecific(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_setspecific(env, err, 0, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_pthread_sigmask) */
static void test_p101_pthread_sigmask(struct p101_env *env, struct p101_error *err)
{
    struct fault_state state = {0};

    p101_env_set_fault_injector(env, fail_next_call, &state);
    int result = p101_pthread_sigmask(env, err, 0, NULL, NULL);
    (void)result;
    EXPECT(state.checks == 1);
    EXPECT(p101_error_has_error(err));
    p101_error_reset(err);
    p101_env_set_fault_injector(env, NULL, NULL);
}

int main(void)
{
    struct p101_error *err;
    struct p101_env   *env;

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
    test_p101_pthread_atfork(env, err);
    test_p101_pthread_attr_destroy(env, err);
    test_p101_pthread_attr_getdetachstate(env, err);
    test_p101_pthread_attr_getguardsize(env, err);
    test_p101_pthread_attr_getinheritsched(env, err);
    test_p101_pthread_attr_getschedparam(env, err);
    test_p101_pthread_attr_getschedpolicy(env, err);
    test_p101_pthread_attr_getscope(env, err);
    test_p101_pthread_attr_getstack(env, err);
    test_p101_pthread_attr_getstacksize(env, err);
    test_p101_pthread_attr_init(env, err);
    test_p101_pthread_attr_setdetachstate(env, err);
    test_p101_pthread_attr_setguardsize(env, err);
    test_p101_pthread_attr_setinheritsched(env, err);
    test_p101_pthread_attr_setschedparam(env, err);
    test_p101_pthread_attr_setschedpolicy(env, err);
    test_p101_pthread_attr_setscope(env, err);
    test_p101_pthread_attr_setstack(env, err);
    test_p101_pthread_attr_setstacksize(env, err);
    test_p101_pthread_cancel(env, err);
    test_p101_pthread_create(env, err);
    test_p101_pthread_detach(env, err);
    test_p101_pthread_getschedparam(env, err);
    test_p101_pthread_join(env, err);
    test_p101_pthread_key_create(env, err);
    test_p101_pthread_key_delete(env, err);
    test_p101_pthread_kill(env, err);
    test_p101_pthread_setcancelstate(env, err);
    test_p101_pthread_setcanceltype(env, err);
    test_p101_pthread_setschedparam(env, err);
    test_p101_pthread_setspecific(env, err);
    test_p101_pthread_sigmask(env, err);
    p101_env_destroy(env);
    p101_error_destroy(err);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
