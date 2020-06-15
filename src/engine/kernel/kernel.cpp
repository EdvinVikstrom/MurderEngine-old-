#include "kernel.hpp"

/* Linux */
#ifdef __linux__

  #include "sys/types.h"
  #include "sys/sysinfo.h"

  struct sysinfo memInfo;

  uint64_t mem_use()
  {
    
  }
  uint64_t mem_available()
  {

  }
  uint64_t mem_pro_use()
  {

  }

  uint32_t cpu_use()
  {

  }
  uint32_t cpu_available()
  {

  }
  uint32_t cpu_pro_use()
  {

  }

#endif

/* macintosh */
#ifdef __MACH__
#endif

/* Windows */
#ifdef _WIN32
#endif
