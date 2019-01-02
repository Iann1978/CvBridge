using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using cvBridge;
using System.Runtime.InteropServices;
using System;

public class CalibrationApp: MonoBehaviour {

    [DllImport("Calibration")]
    public static extern IntPtr GetCVProcess();

    private void Awake()
    {
        Debug.Log("CalibrationApp.Awake()");
        IntPtr cvProcess = GetCVProcess();
        CVBridge.SetCVProcess(0, cvProcess);
    }

    private void Start()
    {
        
        StartCoroutine(CallPluginAtEndOfFrames());
    }

    private void Update()
    {
        //Debug.Log(string.Format("Camera Parameter: position:{0:F4},{1:F4},{2:F4}; rotation:{3:F4},{4:F4},{5:F4},{6:F4}"
        //    , CVBridge.GetFloat(0, 0), CVBridge.GetFloat(0, 1), CVBridge.GetFloat(0, 2)
        //    , CVBridge.GetFloat(0, 3), CVBridge.GetFloat(0, 4), CVBridge.GetFloat(0, 5), CVBridge.GetFloat(0, 6)));

        Debug.Log(string.Format("GoodFuture0: position:{0:F4},{1:F4},{2:F4}, pl:{3:F4},{4:F4}, pr:{5:F4},{6:F4} "
            , CVBridge.GetFloat(0, 0), CVBridge.GetFloat(0, 1), CVBridge.GetFloat(0, 2)
            , CVBridge.GetFloat(0, 3), CVBridge.GetFloat(0, 4)
            , CVBridge.GetFloat(0, 5), CVBridge.GetFloat(0, 6)
            ));



    }



    private IEnumerator CallPluginAtEndOfFrames()
    {
        while (true)
        {
            // Wait until all frame rendering is done
            yield return new WaitForEndOfFrame();

            // Set time for the plugin
            //SetTimeFromUnity(Time.timeSinceLevelLoad);

            // Issue a plugin event with arbitrary integer identifier.
            // The plugin can distinguish between different
            // things it needs to do based on this ID.
            // For our simple plugin, it does not matter which ID we pass here.
            GL.IssuePluginEvent(CVBridge.GetRenderEventFunc(), 1);
        }
    }
}
