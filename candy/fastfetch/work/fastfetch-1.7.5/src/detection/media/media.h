#pragma once

#ifndef FF_INCLUDED_detection_media
#define FF_INCLUDED_detection_media

#include "fastfetch.h"

typedef struct FFMediaResult
{
    FFstrbuf error;
    FFstrbuf busNameShort; //e.g. plasma-browser-integration
    FFstrbuf player; // e.g. Google Chrome
    FFstrbuf song;
    FFstrbuf artist;
    FFstrbuf album;
    FFstrbuf url;
    FFstrbuf status;
} FFMediaResult;

const FFMediaResult* ffDetectMedia(const FFinstance* instance);

#endif
