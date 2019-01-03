using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateCamera : MonoBehaviour
{
    /// <summary>
    /// Rotation Speed 
    /// </summary>
    float speed = 10f;

    /// <summary>
    /// Upadate the head's rotatio through keyboard.
    /// </summary>
    void UpdateRotation()
    {
        if (Input.GetKey("a"))
        {
            transform.Rotate(0, -1 * speed * Time.deltaTime, 0);
        }
        else if (Input.GetKey("d"))
        {
            transform.Rotate(0, 1 * speed * Time.deltaTime, 0);
        }
        else if (Input.GetKey("w"))
        {
            transform.Rotate(-1 * speed * Time.deltaTime, 0, 0);
        }
        else if (Input.GetKey("s"))
        {
            transform.Rotate(1 * speed * Time.deltaTime, 0, 0);
        }
        else if (Input.GetKey("q"))
        {
            transform.Rotate(0, 0, -1 * speed * Time.deltaTime);
        }
        else if (Input.GetKey("e"))
        {
            transform.Rotate(0, 0, 1 * speed * Time.deltaTime);
        }
    }

    private void LateUpdate()
    {
        UpdateRotation();
    }
}
