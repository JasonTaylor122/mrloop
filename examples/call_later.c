
#include "mrloop.h"

static mr_loop_t *loop = NULL;

int cb( void *user_data ) { 
  static int cnt = 0;
  cnt += 1;
  printf("tick\n");
  if ( cnt >= 10 ) mr_stop(loop);
  else mr_call_after( loop, cb, 1000, NULL );
  return 0;
}

static void sig_handler(const int sig) {
  printf("Signal handled: %s.\n", strsignal(sig));
  exit(EXIT_SUCCESS);
}

int main() {

  loop = mr_create_loop(sig_handler);
  mr_call_after(loop, cb, 1000, NULL);
  mr_run(loop); // Returns after mr_stop is called
  mr_free(loop);

}
