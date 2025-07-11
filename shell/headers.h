#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>


#include "prompt.h"
#include "getCommands.h"
#include "identifyCmd.h"
#include "tokenize.h"
#include "warp.h"
#include "peek.h"
#include "proclore.h"
#include "run.h"
#include "seek.h"
#include "main.h"
#include "pastevents.h"

#endif