// ****************************************************************************
//
// 文件名称(File Name):			PanCamera
//
// 功能描述(Description):		触摸屏下控制相机的旋转与缩放
//
// 作者(Author): 				Iann
//
// 日期(Create Date): 			2017.9.27
//
// 修改记录(Revision History):	
//
// ****************************************************************************
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class PanCamera : MonoBehaviour
{
    public Transform target;
    public float rotSpeedX = 100;
    public float rotSpeedY = 100;
    public float scaleSpeed = 1;
    public float eulerX = 0;
    public float eulerY = 0;
    public float dis = 1;

    private void Update()
    {
        if (Input.GetMouseButton(0))
        {
            eulerX -= Input.GetAxis("Mouse Y") * Time.deltaTime * rotSpeedX;
            eulerY += Input.GetAxis("Mouse X") * Time.deltaTime * rotSpeedY;
        }

        dis *= 1 - Input.GetAxis("Mouse ScrollWheel") * scaleSpeed;



    }
    private void LateUpdate()
    {
        Quaternion rot = Quaternion.Euler(eulerX, eulerY, 0);
        transform.rotation = rot;
        transform.position = target.position - dis * transform.forward;
    }



}