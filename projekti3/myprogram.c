#include "types.h"
#include "stat.h"
#include "user.h"
 
int
main(void)
{
printf(1, "System call read has been  called %d time since last reset \n", readcount(1));
printf(1, "Resetting readcount");
readcount(0);
exit();
}