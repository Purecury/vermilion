#include <vermilion.h>
#include <vermilion.h>






vnstatus_t vn_entry(startinfo_t* info){
    DEBUG_INFO("HI ON THREAD %d!\n", info->tId);
    while(1){continue;}
    return VNSTATUS_SUCCESS;
}
