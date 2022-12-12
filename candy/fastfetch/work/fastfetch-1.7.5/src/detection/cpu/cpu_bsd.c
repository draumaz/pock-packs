#include "cpu.h"
#include "common/sysctl.h"

void ffDetectCPUImpl(const FFinstance* instance, FFCPUResult* cpu, bool cached)
{
    FF_UNUSED(instance);

    cpu->temperature = FF_CPU_TEMP_UNSET;

    if(cached)
        return;

    ffSysctlGetString("hw.model", &cpu->name);

    cpu->coresPhysical = (uint16_t) ffSysctlGetInt("hw.ncpu", 1);
    cpu->coresLogical = cpu->coresPhysical;
    cpu->coresOnline = cpu->coresPhysical;

    cpu->frequencyMin = ffSysctlGetInt("hw.clockrate", 0) / 1000.0;
    cpu->frequencyMax = cpu->frequencyMin;
}
