#define COMPILING_FOR_V2

#ifdef COMPILING_FOR_V1
#include "io_mapping_v1.h"
#elif defined(COMPILING_FOR_V2)
#include "io_mapping_v2.h"
#else
#error "No IO map selected. What is your target?"
#endif

