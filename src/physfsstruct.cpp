#ifdef MEMORY_MANAGER
#include "Fluid_Studios_Memory_Manager/nommgr.h"
#endif

#include <memory>

#ifdef MEMORY_MANAGER
#include "Fluid_Studios_Memory_Manager/mmgr.h"
#endif

#include "physfsstruct.h"
#include "console.h"

using namespace std;

unsigned int PhysFSLoadFile(const char *file, char *&buffer)
{
    PHYSFS_file *f = PHYSFS_openRead(file);
    if (f == NULL)
    {
        buffer = NULL;
        return 0;
    }

    PHYSFS_sint64 len = PHYSFS_fileLength(f);
    if (len <= 0)
    {
        PHYSFS_close(f);
        buffer = NULL;
        return 0;
    }

    buffer = new (nothrow) char[len+1];
    if (buffer == NULL)
    {
        PHYSFS_close(f);
        if (App::developermode)
        {
            App::console << "PhysFSLoadFile failed to create a buffer of " << len+1 << " bytes" << std::endl;
            App::FlushConsole();
        }
        return 0;
    }

    buffer[len] = '\0';
    PHYSFS_read(f, (void*)buffer, 1, len);
    PHYSFS_close(f);

    return len;
}
