using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using System.IO.Ports;

public class BLUE_Hands : MonoBehaviour
{

    public InputActionProperty pinchAnimationAction;
    public InputActionProperty gripAnimationAction;
    public Animator handAnimator;

    SerialPort stream = new SerialPort("COM5", 115200);
    float[] grips = { 0, 0 };
    // Start is called before the first frame update
    void Start()
    {
        stream.Open();
    }

    // Update is called once per frame
    void Update()
    {

        string readVal = stream.ReadLine();
        string[] readVec = readVal.Split(',');
        Debug.Log(readVec[0]);
        int[] realVals = { 0, 0 };
        realVals[0] = int.Parse(readVec[0]);
        realVals[1] = int.Parse(readVec[1]);
        grips[0] = (float)realVals[0] / 180;
        grips[1] = (float)realVals[1] / 180;
        stream.BaseStream.Flush();

        handAnimator.SetFloat("Trigger", grips[1]);
        
        handAnimator.SetFloat("Grip", grips[0]);
    }
}
