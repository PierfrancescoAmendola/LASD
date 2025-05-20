
#ifndef CONTAINERTEST_HPP
#define CONTAINERTEST_HPP

#include <cstdint>
#include "../../container/container.hpp"
#ifndef ulong
	#define ulong unsigned long int
#endif  

/* ************************************************************************** */

// Container member functions!

void Empty(uint &, uint &, const lasd::Container &, bool);

void Size(uint &, uint &, const lasd::Container &, bool, ulong);

/* ************************************************************************** */

#endif
