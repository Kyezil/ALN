/** \file chrono.hh
 *  \brief Simple class to get time elapsed
 *  \author Louis Clergue
 *  \date April 2015
 */

#ifndef CHRONO_HH
#define CHRONO_HH
#include <chrono>
class Chrono {
    typedef std::chrono::high_resolution_clock::time_point tp;
    private: tp t;
    public :
        ///\pre true
        Chrono() { ///< Constructor, starts chrono
            t = std::chrono::high_resolution_clock::now();
        }
        ///\post Implicit parameter is initialized and chrono has started

        ///\pre true
        void reset() { ///< Put chrono time to 0
            t = std::chrono::high_resolution_clock::now();
        }
        /// \post Restart chrono to 0

        ///\pre true
        double lap() { ///< Get time elapsed
            tp t2 = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(t2 - t).count() / 1.0e3L;
        }
        ///\post return time elapsed since running or reset
};
#endif
