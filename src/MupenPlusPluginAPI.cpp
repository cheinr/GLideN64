#include "PluginAPI.h"
#include "Types.h"
#include "mupenplus/GLideN64_mupenplus.h"
#include "N64.h"

extern "C" {

EXPORT int CALL
#if (!M64P_STATIC_PLUGINS)
RomOpen
#else
RomOpenVideo
#endif
(void)
{
	if (rdram_size != nullptr)
		RDRAMSize = *rdram_size - 1;
	else
		RDRAMSize = 0;

	return api().RomOpen();
}

EXPORT m64p_error CALL
#if (!M64P_STATIC_PLUGINS)
PluginGetVersion
#else
PluginGetVersionVideo
#endif
(m64p_plugin_type * _PluginType,
	int * _PluginVersion,
	int * _APIVersion,
	const char ** _PluginNamePtr,
	int * _Capabilities
)
{
	return api().PluginGetVersion(_PluginType, _PluginVersion, _APIVersion, _PluginNamePtr, _Capabilities);
}

EXPORT m64p_error CALL
#if (!M64P_STATIC_PLUGINS)
PluginStartup
#else
PluginStartupVideo
#endif
(m64p_dynlib_handle CoreLibHandle,
	void *Context,
	void (*DebugCallback)(void *, int, const char *)
)
{
	return api().PluginStartup(CoreLibHandle);
}

#ifdef M64P_GLIDENUI
EXPORT m64p_error CALL PluginConfig(void)
{
	return api().PluginConfig();
}
#endif // M64P_GLIDENUI

EXPORT m64p_error CALL
#if (!M64P_STATIC_PLUGINS)
PluginShutdown
#else
PluginShutdownVideo
#endif
(void)
{
	return api().PluginShutdown();
}

EXPORT void CALL ReadScreen2(void *dest, int *width, int *height, int front)
{
	api().ReadScreen2(dest, width, height, front);
}

EXPORT void CALL SetRenderingCallback(void (*callback)(int))
{
	api().SetRenderingCallback(callback);
}

EXPORT void CALL ResizeVideoOutput(int width, int height)
{
	api().ResizeVideoOutput(width, height);
}

} // extern "C"
