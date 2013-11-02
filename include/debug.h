#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#include <HardwareSerial.h>
#include <serstream>
#include <iomanip>  // for setprecision()
#include <sstream>
std::ohserialstream serial(Serial);
#define LOG serial
#else
#ifdef __AVR__
#include <serstream>
#endif // __AVR__
#include <ostream>
struct nullstream : std::ostream {
    nullstream() : std::ios(0), std::ostream(0) {}
};

#if 0
#ifndef __AVR__
#include <iosfwd>
namespace std {
	template <class charT, class traits> _UCXXEXPORT basic_ostream<charT,traits>&
		crlf(basic_ostream<charT,traits>& os)
	{
		typename basic_ostream<charT,traits>::sentry s(os);
		os.put('\r');
		os.put('\n');
		os.flush();
		return os;
	}
};
#endif
#endif

static nullstream logstream;
#define LOG if(0) logstream
#endif

#endif // DEBUG_H

