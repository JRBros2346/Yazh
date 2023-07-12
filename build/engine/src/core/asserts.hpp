#pragma once

#include"defines.hpp"

namespace Yazh::Core::Logger {
	// Disable assertions by commenting out the below line.
#define YASSERTIONS_ENABLED
	
#ifdef YASSERTIONS_ENABLED
#	if _MSC_VER
#		include<intrin.h>
#		define debugBreak() __debugBreak()
#	else
#		define debugBreak() __builtin_trap()
#	endif
	
	YAPI void reportAssertionFailure(std::string, std::string, std::string, i32);
	
#	define YASSERT(expr)                                                              	\
		{                                                                             	\
			if (expr) {                                                               	\
			} else {                                                                  	\
				reportAssertionFailure(#expr, "", __FILE__, __LINE__);	\
				debugBreak();                                                         	\
			}                                                                         	\
		}
	
#	define YASSERT_MSG(expr, message)                                                      	\
		{                                                                                  	\
			if (expr) {                                                                    	\
			} else {                                                                       	\
				reportAssertionFailure(#expr, message, __FILE__, __LINE__);	\
				debugBreak();                                                              	\
			}                                                                              	\
		}
	
#	ifdef _DEBUG
#		define YASSERT_DEBUG(expr)                                                        	\
			{                                                                             	\
				if (expr) {                                                               	\
				} else {                                                                  	\
					reportAssertionFailure(#expr, "", __FILE__, __LINE__);	\
					debugBreak();                                                         	\
				}                                                                         	\
			}
#	else
#		define YASSERT_DEBUG(plat, expr) // Does nothing at all
#	endif
	
#else
#	define YASSERT(expr)             	// Does nothing at all
#	define YASSERT_MSG(expr, message)	// Does nothing at all
#	define YASSERT_DEBUG(expr)       	// Does nothing at all
#endif
} // namespace Yazh::Core::Logger