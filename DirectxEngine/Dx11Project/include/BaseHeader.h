#ifndef __BASEHEADER_H__
#define __BASEHEADER_H__


// Including SDKDDKVer.h defines the highest available Windows platform.
// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.
#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include "windows.h"
#include "combaseapi.h"

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//////////////////////////////////////////////////////////////////////////

#define  Quote_It( It )  #It
#define D_OPENCVLIBPATH(__X)  Quote_It(../common/OpenCV/lib/__X)


#endif