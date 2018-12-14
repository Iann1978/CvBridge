// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "GLEW/glew.h"
#include "CVTexture.h"
#include "CVProcess.h"
using namespace cvBridge;
extern "C" {
	

	__declspec(dllexport) int GetVersion()
	{
		return 0;
	}

	__declspec(dllexport) int GetMajorVersion()
	{
		return 0;
	}

	__declspec(dllexport) int GetSubVersion()
	{
		return 2;
	}

	__declspec(dllexport) void SetCVProcess(int procIdx, CVProcess *cvProcess)
	{
		CVProcess::cvProcs[procIdx] = cvProcess;
	}

	__declspec(dllexport) void SetCVTexture(int procIdx, int texIndex, int width, int height, int texture)
	{
		CVProcess::cvProcs[procIdx]->cvTextures[texIndex] = new CVTexture(width, height, texture);
	}

	__declspec(dllexport) void SetInteger(int procIdx, int intIndex, int value)
	{
		CVProcess::cvProcs[procIdx]->intValues[intIndex] = value;
	}

}