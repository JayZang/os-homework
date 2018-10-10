#!/usr/sbin/dtrace -s

syscall::open:entry
{
    if (execname == "fcp") {
        printf("Open file : %s", copyinstr(arg0));
    }
}

syscall::write:entry
{
    if (execname == "fcp") {
        printf("Writing file, length : %d", arg2);
    }
}

