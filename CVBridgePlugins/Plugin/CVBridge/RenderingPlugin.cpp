// Example low level rendering Unity plugin

#include "PlatformBase.h"
#include "RenderDevice.h"
#include "CVTexture.h"
#include <assert.h>
#include <math.h>
#include <vector>
#include "RenderDevice.h"
#include <opencv2/opencv.hpp>
#include "CVProcess.h"



using namespace cv;
using namespace cvBridge;


static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);

static IUnityInterfaces* s_UnityInterfaces = NULL;
static IUnityGraphics* s_Graphics = NULL;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;

extern "C" void	UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
	// Initialize CVProcess
	memset(CVProcess::cvProcs, sizeof(CVProcess *) * 32, 0);
	//CVProcess::cvProcs[0] = (CVProcess *)new CVProcess_AVM();
	//CVProcess::cvProcs[1] = (CVProcess *)new CVProcess_Calibration();
	

	s_UnityInterfaces = unityInterfaces;
	s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
	s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);
	// Run OnGraphicsDeviceEvent(initialize) manually on plugin load
	OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
	s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
}




static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	// Create graphics API implementation upon initialization
	if (eventType == kUnityGfxDeviceEventInitialize)
	{
		assert(RenderDevice::ins == NULL);
		s_DeviceType = s_Graphics->GetRenderer();
		RenderDevice::ins = RenderDevice::Create(s_DeviceType);
	}

	// Let the implementation process the device related events
	if (RenderDevice::ins)
	{
		RenderDevice::ins->ProcessDeviceEvent(eventType, s_UnityInterfaces);
	}

	// Cleanup graphics API implementation upon shutdown
	if (eventType == kUnityGfxDeviceEventShutdown)
	{
		delete RenderDevice::ins;
		RenderDevice::ins = NULL;
		s_DeviceType = kUnityGfxRendererNull;
	}
}





//char *image = nullptr;

//GLuint tempTexture = 0;
//Mat** inputs = nullptr;
//Mat** outputs = nullptr;
static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	if (eventID == 1)
	{
	

		// deal cv process
		for (int i = 0; i < 32; i++)
		{
			CVProcess *cvProc = CVProcess::cvProcs[i];
			if (cvProc)
			{
				// Convert CVTexture to cv::Mat
				for (int i = 0; i < 32; i++)
				{
					CVTexture* texture = cvProc->cvTextures[i];
					if (texture)
					{
						RenderDevice::ins->Texture2Mat(texture);
					}
				}

				cvProc->Process(nullptr, nullptr);


				// Convert cv::Mat to CVTexture
				for (int i = 16; i < 32; i++)
				{
					if (cvProc->cvTextures[i])
					{
						RenderDevice::ins->Mat2Texture(cvProc->cvTextures[i]);
					}
				}

				// Release resources
				for (int i = 0; i < 32; i++)
				{
					if (cvProc->cvTextures[i])
					{
						if (cvProc->cvTextures[i]->mat)
						{
							delete cvProc->cvTextures[i]->mat;
							cvProc->cvTextures[i]->mat = nullptr;
						}
					}
				}
			}
		}
	}

	return;

}


// --------------------------------------------------------------------------
// GetRenderEventFunc, an example function we export which is used to get a rendering event callback function.

extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc()
{
	return OnRenderEvent;
}

