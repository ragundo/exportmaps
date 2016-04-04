#include "../../include/dfhack.h"
#include "DFHackVersion.h"
#include "modules/Filesystem.h"

using namespace std;

static unsigned int address_Windows = 0x0; // Default for DF42.06
static unsigned int address_Linux   = 0x090406F0; // Default for DF42.06
static unsigned int address_Mac     = 0x0;         // Default for DF42.06




/**************************************************************************
 Forward declarations
**************************************************************************/

void delete_world_site_realization_Linux(unsigned int    address_DF_sub,
                                         df::world_site* world_site
                                        );

void delete_world_site_realization_OSX(unsigned int    address_DF_sub,
                                       df::world_site* world_site
                                      );

void delete_world_site_realization_Windows(unsigned int    address_DF_sub,
                                           df::world_site* world_site
                                          );

/**************************************************************************
 Main function
 This function calls a DF subroutine with a df::world_site parameter.

 The DF sub dows the hard work of deleting all the
 structures that make a world site realization

 The routine calls one version for Linux and another for Windows
**************************************************************************/

void delete_world_site_realization(df::world_site* world_site)
{

  // Below is the address of the subroutine for different OSs
#ifdef _LINUX // Linux
  unsigned int address_DF_sub = address_Linux;

#endif

#ifdef _DARWIN // MacOS X
  unsigned int address_DF_sub = address_Mac;
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
  unsigned int address_DF_sub = address_Windows;
#endif


#if defined(_DARWIN) // Mac
//  delete_world_site_realization_OSX(address_DF_sub,
//                                  world_site)
#endif // Mac

#if defined(_LINUX) // Linux
  delete_world_site_realization_Linux(address_DF_sub,
                                    world_site);
#endif // Linux

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
  delete_world_site_realization_Windows(address_DF_sub,
                                      world_site);
#endif // WINDOWS

}


/**************************************************************************
 Local function

**************************************************************************/
void delete_world_site_realization_Linux(unsigned int    address_DF_sub,
                                       df::world_site* world_site)
{
    #if defined(_LINUX)

  // Setup the stack and then call DF routine

  asm volatile ("movl %0    ,%%eax;    "  /* address_DF_sub to eax                                  */
                "movl %1    ,%%ecx;    "  /* pointer to world_site to ecx                           */
                "sub  $0x10 ,%%esp;    "  /* make space in the stack for the parameters             */
                "mov  %%ecx ,0(%%esp); "  /* store param 1                                          */
                "call *%%eax;          "  /* call the DF subroutine                                 */
                "add  $0x10 ,%%esp;    "  /* release the space used in the stack for the parameters */
                :
                : "m" (address_DF_sub),   /* input parameter to inline assembly                     */
                  "m" (world_site)        /* input parameter to inline assembly                     */
                : "eax","ecx"             /* used registers                                         */
                );

    #endif
}

/**************************************************************************
 Local function
**************************************************************************/
void delete_world_site_realization_Windows(unsigned int address_DF_sub,
                                         df::world_site* world_site)
{
  // Windows DF has Address Space Randomization active, so the virtual address
  // doesn't have to be the same every time DF is running.
  // DFHack solves this for us
  unsigned int delta = DFHack::Core::getInstance().vinfo->getRebaseDelta();
  unsigned int address_DF_sub_Win = address_DF_sub + delta; // Corrected subroutine address

  #if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)

  __asm xor  eax, eax                          /* eax = 0                                       */
  __asm push eax                               /* 2nd parameter to the stack = 0                */
  __asm push world_site                        /* 1st parameter to the stack = df_world_site*   */
  __asm mov  eax, address_DF_sub_Win               /* eax = address DF subroutine                   */
  __asm call address_DF_sub_Win                    /* call DF subroutine                            */

//    __asm xor  eax, eax                          /* eax = 0                       */
//    __asm push eax                               /* 5th parameter to the stack    */
//    __asm push eax                               /* 4th parameter to the stack    */
//    __asm mov  eax, world_pos_y                  /* 3th parameter to the stack    */
//    __asm push eax
//    __asm mov  edx, world_pos_x                  /* 2nd parameter in register edx */
//    __asm mov  ecx, address_world_region_details /* 1st parameter in register ecx */
//    __asm mov  eax, address_DF_sub_Win               /* eax = address DF subroutine   */
//    __asm call address_DF_sub                    /* call the DF subroutine        */

#endif // WINDOWS
}
