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

        //public void Caculate()
        //{
            //Debug.Log(leftCamera.name + ":\n" + leftCamera.worldToCameraMatrix);
            //Debug.Log(rightCamera.name + ":\n" + rightCamera.worldToCameraMatrix);

            //Vector3[] points = new Vector3[features.childCount];
            //for (int i = 0; i < features.childCount; i++)
            //{
            //    points[i] = features.GetChild(i).position;
            //}

            //int m, n;
            //float[] M, N;
            //PrepareData(out m, out n, out M, out N, points);


            float[] x = new float[16];

        //EigenSharp.cal_line_equation(ref x, m, n, M, N);
        for (int i = 0; i < 16; i++)
        {
            x[i] = CVBridge.GetFloat(0, i);
        }

            Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[0], x[1], x[2], x[3]));
            Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[4], x[5], x[6], x[7]));
            Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[8], x[9], x[10], x[11]));
            Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[12], x[13], x[14], x[15]));
            //   Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[16], x[17], x[18], x[19]));
            //        Debug.Log(string.Format("{0:F5}:{1:F5}:{2:F5}:{3:F5}:", x[20], x[21], x[22], x[23]));

            Vector3 RL0 = new Vector3(x[0], x[1], x[2]);
            Vector3 RL1 = new Vector3(x[4], x[5], x[6]);
            Vector3 RL2 = -Vector3.Cross(RL0, RL1);

            Vector3 RR0 = new Vector3(x[8], x[9], x[10]);
            Vector3 RR1 = new Vector3(x[12], x[13], x[14]);
            Vector3 RR2 = -Vector3.Cross(RR0, RR1);

            Matrix4x4 ML = Matrix4x4.zero;
            ML[0, 0] = RL0.x; ML[0, 1] = RL0.y; ML[0, 2] = RL0.z; ML[0, 3] = x[3];
            ML[1, 0] = RL1.x; ML[1, 1] = RL1.y; ML[1, 2] = RL1.z; ML[1, 3] = x[7];
            ML[2, 0] = RL2.x; ML[2, 1] = RL2.y; ML[2, 2] = RL2.z; ML[2, 3] = 0;
            ML[3, 0] = 0; ML[3, 1] = 0; ML[3, 2] = 0; ML[3, 3] = 1;

            Matrix4x4 MR = Matrix4x4.zero;
            MR[0, 0] = RR0.x; MR[0, 1] = RR0.y; MR[0, 2] = RR0.z; MR[0, 3] = x[11];
            MR[1, 0] = RR1.x; MR[1, 1] = RR1.y; MR[1, 2] = RR1.z; MR[1, 3] = x[15];
            MR[2, 0] = RR2.x; MR[2, 1] = RR2.y; MR[2, 2] = RR2.z; MR[2, 3] = 0;
            MR[3, 0] = 0; MR[3, 1] = 0; MR[3, 2] = 0; MR[3, 3] = 1;



            ////Vector3 pw = points[9];
            //float xxl = ML[0, 0] * pw.x + ML[0, 1] * pw.y + ML[0, 2] * pw.z + ML[0, 3];
            ////Debug.Log(string.Format("x':{0:F5}", xxl));
            //float xxxl = Mathf.Tan(30 * Mathf.Deg2Rad) * WorldToClip(pw, leftCamera).x;
            ////Debug.Log(string.Format("x'':{0:F5}", xxxl));
            //float tmp = ML[2, 0] * pw.x + ML[2, 1] * pw.y + ML[2, 2] * pw.z;
            ////Debug.Log(string.Format("tmp'':{0:F5}", tmp));
            //float ml23 = -xxl / xxxl - tmp;



            //float xxr = MR[0, 0] * pw.x + MR[0, 1] * pw.y + MR[0, 2] * pw.z + MR[0, 3];
            //float xxxr = Mathf.Tan(30 * Mathf.Deg2Rad) * WorldToClip(pw, rightCamera).x;
            //float mr23 = -xxr / xxxr - (MR[2, 0] * pw.x + MR[2, 1] * pw.y + MR[2, 2] * pw.z);

            //ML[2, 3] = ml23;
            //MR[2, 3] = mr23;




            Debug.Log("ML:\n" + ML);
            Debug.Log("MR:\n" + MR);
       // }





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
