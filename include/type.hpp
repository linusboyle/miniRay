#ifndef TYPE_CPP
#define TYPE_CPP

#include "config.h"

namespace graphics {
#ifdef USE_FLOAT
    using coordinate_type = float;
#else
    using coordinate_type = double;
#endif
}

#endif /* ifndef TYPE_CPP */
