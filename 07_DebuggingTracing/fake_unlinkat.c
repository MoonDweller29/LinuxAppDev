#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
 
extern int errno;
typedef int (*orig_unlinkat_f)(int dirfd, const char *pathname, int flags);


int unlinkat(int dirfd, const char *pathname, int flags)
{
	if(strstr(pathname, "FIX") != NULL)
	{
		errno = EPERM;
		return EPERM;
	}

	orig_unlinkat_f orig_unlinkat;
    orig_unlinkat = dlsym(RTLD_NEXT,"unlinkat");
    return orig_unlinkat(dirfd, pathname, flags);
}