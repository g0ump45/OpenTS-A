#pragma once

#include "mpu.h"
#include "timer.h"

class PentiumTimerClass
{
        public:
                unsigned int operator () (void) const {unsigned int h;unsigned int l = Get_CPU_Clock(h);return((l >> 4) | (h << 28));}
                operator unsigned int (void) const {unsigned int h;unsigned int l = Get_CPU_Clock(h);return((l >> 4) | (h << 28));}
};

class Benchmark
{
        public:
                Benchmark(void);
                void Begin(bool reset=false);
                void End(void);
                void Reset(void);
                unsigned int Value(void) const;
                unsigned int Count(void) const {return(TotalCount);}
                unsigned int Step(void);
        private:
                enum {MAXIMUM_EVENT_COUNT=256};
                BasicTimerClass<PentiumTimerClass> Clock;
                unsigned int Average;
                unsigned int Counter;
                unsigned int TotalCount;
};