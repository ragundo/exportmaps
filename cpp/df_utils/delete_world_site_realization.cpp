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

using namespace std;

/*****************************************************************************
    Module local variables
*****************************************************************************/
unsigned int delete_world_site_realization_address = 0;

/*****************************************************************************
    Local functions forward declaration
*****************************************************************************/

void delete_world_site_realization_Linux_OSX(df::world_site* world_site);

void delete_world_site_realization_Windows(df::world_site* world_site);

/**************************************************************************
    Main function
    This function calls a DF subroutine with a df::world_site parameter.

    The DF sub dows the hard work of deleting all the
    structures that make a world site realization

    The routine calls one version for Linux and another for Windows
**************************************************************************/
void delete_world_site_realization(df::world_site* world_site)
{
#if defined(_LINUX) || defined(_DARWIN)
    delete_world_site_realization_Linux_OSX(world_site);
#endif // Linux or Mac

#if defined(WIN32)
    delete_world_site_realization_Windows(world_site);
#endif // WINDOWS
}

//----------------------------------------------------------------------------//
// Utility function
//
//----------------------------------------------------------------------------//
void delete_world_site_realization_Linux_OSX(df::world_site* world_site)
{
#if defined(_LINUX) || defined(_DARWIN)

    // Setup the stack and then call DF routine

    asm volatile("movl %0    ,%%eax;    " /* address_DF_sub to eax                                  */
                 "movl %1    ,%%ecx;    " /* pointer to world_site to ecx                           */
                 "sub  $0x10 ,%%esp;    " /* make space in the stack for the parameters             */
                 "mov  %%ecx ,0(%%esp); " /* store param 1                                          */
                 "call *%%eax;          " /* call the DF subroutine                                 */
                 "add  $0x10 ,%%esp;    " /* release the space used in the stack for the parameters */
                 :
                 : "m"(delete_world_site_realization_address), /* input parameter to inline assembly                     */
                   "m"(world_site) /* input parameter to inline assembly                     */
                 : "eax", "ecx" /* used registers                                         */
    );

#endif
}

//----------------------------------------------------------------------------//
// Utility function
//
//----------------------------------------------------------------------------//
void delete_world_site_realization_Windows(df::world_site* world_site)
{
    // Windows DF has Address Space Randomization active, so the virtual address
    // doesn't have to be the same every time DF is running.
    // DFHack solves this for us
    // Not needed anymore as gettint the address from symbols.xml
    // returns the address already ready
    // unsigned int delta = DFHack::Core::getInstance().vinfo->getRebaseDelta();
    unsigned int delta = 0;

    // Corrected subroutine address
    //unsigned int address_DF_sub_Win = delete_world_site_realization_address + delta;

#if defined(WIN32)

    typedef void (*df_delete_world_site_realization_fn)(df::world_site*);
    static df_delete_world_site_realization_fn df_dwsr_fn = reinterpret_cast<df_delete_world_site_realization_fn>(0x000140AD4F90);

    df_dwsr_fn(world_site);

    //__asm push world_site                        /* 1st parameter to the stack = df_world_site*   */
    //__asm mov  eax, address_DF_sub_Win           /* eax = address DF subroutine                   */
    //__asm call address_DF_sub_Win                /* call DF subroutine                            */

#endif // WINDOWS
}
