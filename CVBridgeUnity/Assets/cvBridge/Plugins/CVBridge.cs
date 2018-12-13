using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

namespace cvBridge
{
    public class CVBridge
    {
        [DllImport("CVBridge")]
        public static extern int GetVersion();

        [DllImport("CVBridge")]
        public static extern int GetMajorVersion();

        [DllImport("CVBridge")]
        public static extern int GetSubVersion();


        [DllImport("CVBridge")]
        public static extern void SetCVTexture(int procIdx, int texIndex, int width, int height, int texture);

        [DllImport("CVBridge")]
        public static extern void SetInteger(int procIdx, int intIndex, int value);

        [DllImport("CVBridge")]
        public static extern IntPtr GetRenderEventFunc();
    }
}
