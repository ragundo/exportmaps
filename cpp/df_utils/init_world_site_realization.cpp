/*
    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.
*/

// You can always find the latest version of this plugin in Github
// https://github.com/ragundo/exportmaps

#include "../../include/dfhack.h"
#include "DFHackVersion.h"
#include "modules/Filesystem.h"
#include <cstdint>

using namespace std;

/*****************************************************************************
    Module local variables

*****************************************************************************/
unsigned int init_world_site_realization_address = 0;

/*****************************************************************************
    Local functions forward declaration
*****************************************************************************/

void init_world_site_realization_Linux_OSX(df::world_site* world_site);

void init_world_site_realization_Windows(df::world_site* world_site);

/**************************************************************************
    Main function
    This function calls a DF subroutine with a df::world_site parameter.

    The DF sub dows the hard work of creating and initializing all the
    structures that make a world site realization

    The routine calls one version for Linux and another for Windows
**************************************************************************/

void init_world_site_realization(df::world_site* world_site)
{
#if defined(_DARWIN) // Mac
    init_world_site_realization_Linux_OSX(world_site);
#endif // Mac

#if defined(_LINUX) // Linux
    init_world_site_realization_Linux_OSX(world_site);
#endif // Linux

#if defined(_WIN32)
    init_world_site_realization_Windows(world_site);
#endif // WINDOWS
}

//----------------------------------------------------------------------------//
// Utility function
//
//----------------------------------------------------------------------------//
void init_world_site_realization_Linux_OSX(df::world_site* world_site)
{
#if defined(_LINUX) || defined(_DARWIN)

    // Setup the stack and then call DF routine

    // About the strange 0x18 stack size when only 2 parameters are used
    // As DF for linux use MMX instructions, the parameters
    // must be aligned to a 16 byte frame.  If not, the call
    // to DF crashes inside a MOVAPS assembly instruction

    //    asm volatile("movl %0    ,%%eax;    " /* address_DF_sub to eax                                  */
    //                 "movl %1    ,%%ecx;    " /* pointer to world_site to ecx                           */
    //                 "sub  $0x18 ,%%esp;    " /* make space in the stack for the parameters             */
    //                 "mov  %%ecx ,0(%%esp); " /* store param 1                                          */
    //                 "movl $0    ,4(%%esp); " /* store param 2                                          */
    //                 "call *%%eax;          " /* call the DF subroutine                                 */
    //                 "add  $0x18 ,%%esp;    " /* release the space used in the stack for the parameters */
    //                 :
    //                 : "m"(init_world_site_realization_address), /* input parameter                                         */
    //                   "m"(world_site) /* input parameter                                         */
    //                 : "eax", "ecx" /* used registers                                          */
    //);

#endif
}

//----------------------------------------------------------------------------//
// Utility function
//
//----------------------------------------------------------------------------//
void init_world_site_realization_Windows(df::world_site* world_site)
{
    // Windows DF has Address Space Randomization active, so the virtual address
    // doesn't have to be the same every time DF is running.
    // DFHack solves this for us
    // Not needed anymore as gettint the address from symbols.xml
    // returns the address already ready
    uint64_t delta = DFHack::Core::getInstance().vinfo->getRebaseDelta();

    // Corrected subroutine address
    uint64_t address_DF_sub_Win = 0x0140AB9BD0 + delta;

#if defined(_WIN32)

    typedef void (*df_init_world_site_realization_fn)(df::world_site*, uint8_t);
    static df_init_world_site_realization_fn df_iwsr_fn = reinterpret_cast<df_init_world_site_realization_fn>(address_DF_sub_Win);

    df_iwsr_fn(world_site, 0);

    //__asm xor  eax, eax                /* eax = 0                                       */
    //__asm push eax                     /* 2nd parameter to the stack = 0                */
    //__asm push world_site              /* 1st parameter to the stack = df_world_site*   */
    //__asm mov  eax, address_DF_sub_Win /* eax = address DF subroutine                   */
    //__asm call address_DF_sub_Win      /* call DF subroutine                            */

#endif // WINDOWS
}
