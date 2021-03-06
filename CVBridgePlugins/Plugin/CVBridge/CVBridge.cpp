// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "GLEW/glew.h"
#include "CVTexture.h"
#include "CVProcess.h"
using namespace cvBridge;
extern "C" {
	

	__declspec(dllexport) int GetVersion()
	{
		return 15;
	}

	__declspec(dllexport) void SetCVTexture(int index, int width, int height, int texture)
	{
		CVProcess::cvTextures[index] = new CVTexture(width, height, texture);
	}

	__declspec(dllexport) void SetInteger(int index, int value)
	{
		CVProcess::intValues[index] = value;
	}

}