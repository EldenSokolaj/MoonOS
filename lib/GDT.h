#ifndef GDT_H
#define GDT_H

/* The GDT
 *  [ Null Discriptor ]
 *  [ Code Segment D. ]
 *  [ Data Segment D. ]
 *  
 *  Note: There is no TSS segment which I may want to add later
 * 
 *  diskID: Null = 0, Code = 1, Data = 2
 * 
 *  Importent Note: if an invalid GDT is used, it causes the code to crash IN SOME CIRCUMSTANCES
 *                  just becuase it does not crash does not mean it worked. Also actually it might
 *                  not be the GDT's fault at all, who knows
 */

#include "types.h"
#include "io.h"

extern "C" void loadGDT(long GDTP);

class GlobalDiscriptorTable{
    public:
        struct discriptor{
            uint16 limit_lo;
            uint16 base_lo;
            byte base_mid;
            byte access;
            byte limit_and_flags;
            byte base_hi;
        }__attribute__((packed));

        struct GDT_pointer{
            uint16 limit;               // The upper 16 bits of all selector limits
            uint64 base;                // The address of the first GDT discriptor
        }__attribute__((packed));

        discriptor GDT[3];

        void setDiscriptor(char discID, uint32 limit, uint32 base, byte disc){
            
        }

        uint32 getBase(char discID){

        }

        uint32 getLimit(char discID){

        }

        uint16 segmentOffset(char discID){
            return (byte*)&GDT[discID] - (byte*)GDT;
        }

        GlobalDiscriptorTable(){
            setDiscriptor(0, 0, 0, 0);                 //set null discriptor
            setDiscriptor(1, 64*1024*1024, 0, 0x9A);  //set code discriptor
            setDiscriptor(2, 64*1024*1024, 0, 0x92); //set data discriptor

            GDT_pointer p{(uint16)sizeof(GDT), (uint64)&GDT};

            loadGDT((uint64)&p);
        }
};

#endif