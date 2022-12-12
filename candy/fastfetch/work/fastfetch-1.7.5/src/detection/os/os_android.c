#include "os.h"
#include "common/settings.h"

void ffDetectOSImpl(FFOSResult* os, const FFinstance* instance)
{
    FF_UNUSED(instance);

    ffStrbufInit(&os->name);
    ffStrbufSetS(&os->name, "Android");

    ffStrbufInit(&os->prettyName);
    ffStrbufSetS(&os->prettyName, "Android");

    ffStrbufInit(&os->id);
    ffStrbufSetS(&os->id, "android");

    ffStrbufInit(&os->version);
    ffSettingsGetAndroidProperty("ro.build.version.release", &os->version);

    ffStrbufInit(&os->versionID);
    ffSettingsGetAndroidProperty("ro.build.version.release", &os->versionID);

    ffStrbufInit(&os->codename);
    ffSettingsGetAndroidProperty("ro.build.version.codename", &os->codename);

    ffStrbufInit(&os->buildID);
    ffSettingsGetAndroidProperty("ro.build.id", &os->buildID);

    ffStrbufInit(&os->systemName);
    ffStrbufSetS(&os->systemName, instance->state.utsname.sysname);

    ffStrbufInit(&os->architecture);
    ffStrbufSetS(&os->architecture, instance->state.utsname.machine);

    ffStrbufInitA(&os->idLike, 0);
    ffStrbufInitA(&os->variant, 0);
    ffStrbufInitA(&os->variantID, 0);
}
