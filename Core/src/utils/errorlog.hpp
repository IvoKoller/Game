#ifndef ERRORLOG_H
#define ERRORLOG_H

#define check_error() _check_error(__FILE__,__LINE__)

namespace evo {
    void _check_error(const char *file, int line);
}

#endif /* end of include guard: ERRORLOG_H */
