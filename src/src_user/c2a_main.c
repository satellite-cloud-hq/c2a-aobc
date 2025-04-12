#include <src_core/Library/git_revision.h>
#include <src_core/c2a_core_main.h>
#include <src_core/System/TimeManager/time_manager.h>
#include <src_core/Library/print.h>

#include <stdint.h>

#include <stddef.h>

// C2A Main functions
void C2A_main_(void)
{
  while (1)
  {
    C2A_core_main();
  }

  return;
}

void C2A_init_(void)
{
  Printf("C2A_init: user revision = %s\n", GIT_REV_USER);
  TMGR_init();                // Time Manager
  Printf("C2A_init: TMGR_init done.\n");

  C2A_core_init();

  TMGR_clear();
  return;
}
