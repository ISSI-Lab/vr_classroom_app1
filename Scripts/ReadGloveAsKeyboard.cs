using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem;

public class ReadGloveAsKeyboard : MonoBehaviour
{
    /*
    IMPORTANT
    Turn off the built-in animator, as it will override the values here.
    */

    public GameObject hand;
    GameObject[,] fingers;

    Keyboard board;
    bool[] vals;
    bool[] last;

    bool cont;

    string output;

    string[,] fingerNames;

    UnityEngine.Quaternion[,] starterAngles;
    UnityEngine.Quaternion[,] enderAngles;

    // Start is called before the first frame update
    void Start()
    {
        vals = new bool[5];
        last = new bool[5];
        starterAngles = new Quaternion[5,3];
        enderAngles = new Quaternion[5,3];
        fingers = new GameObject[5,3];
        fingerNames = new string[5,3];

        enderAngles[0,0] = new Quaternion((float)0.245962307, (float)0.945037007, (float)-0.0319942869, (float)0.213035211);
        enderAngles[0,1] = new Quaternion((float)0.090636313, (float)-0.086621359, (float)-0.276767403, (float)0.952723265);
        enderAngles[0,2] = new Quaternion((float)-0.148160726, (float)-0.138815537, (float)-0.169883698, (float)0.964322686);
        enderAngles[1,0] = new Quaternion((float)-0.200879067, (float)0.592819631, (float)0.740095377, (float)0.245909482);
        enderAngles[1,1] = new Quaternion((float)-0.0421681106, (float)0.0681166425, (float)-0.696204185, (float)0.713359594);
        enderAngles[1,2] = new Quaternion((float)-0.202249497, (float)0.110711589, (float)-0.802879512, (float)0.549747705);
        enderAngles[4, 0] = new Quaternion((float)-0.0195530485, (float)0.00454074703, (float)0.972945869, (float)0.230159581);
        enderAngles[4,1] = new Quaternion((float)0, (float)0, (float)-0.636751354, (float)0.771069229);
        enderAngles[4,2] = new Quaternion((float)0, (float)0, (float)-0.60390377, (float)0.797057211);
        for (int i = 2; i < 4; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                enderAngles[i,j] = enderAngles[1,j];
            }
        }
        //this is a very rudamentary way to do this right now. I want to make it a lot better when I have time.


        fingerNames[0,0] = "hands:b_l_thumb1";
        fingerNames[1,0] = "hands:b_l_index1";
        fingerNames[2,0] = "hands:b_l_middle1";
        fingerNames[3,0] = "hands:b_l_ring1";
        fingerNames[4,0] = "hands:b_l_pinky0/hands:b_l_pinky1";

        fingerNames[0, 1] = fingerNames[0, 0] + "/hands:b_l_thumb2";
        fingerNames[1, 1] = fingerNames[1, 0] + "/hands:b_l_index2";
        fingerNames[2, 1] = fingerNames[2, 0] + "/hands:b_l_middle2";
        fingerNames[3, 1] = fingerNames[3, 0] + "/hands:b_l_ring2";
        fingerNames[4, 1] = fingerNames[4, 0] + "/hands:b_l_pinky2";

        fingerNames[0, 2] = fingerNames[0, 1] + "/hands:b_l_thumb3";
        fingerNames[1, 2] = fingerNames[1, 1] + "/hands:b_l_index3";
        fingerNames[2, 2] = fingerNames[2, 1] + "/hands:b_l_middle3";
        fingerNames[3, 2] = fingerNames[3, 1] + "/hands:b_l_ring3";
        fingerNames[4, 2] = fingerNames[4, 1] + "/hands:b_l_pinky3";


        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                fingers[i, j] = hand.transform.Find(fingerNames[i,j]).gameObject;
            }
        }

        for (int i = 0; i < 5; i++)
        {
            vals[i] = false;
            last[i] = false;
            for (int j  = 0; j < 3; ++j)
            {
                starterAngles[i,j] = fingers[i, j].transform.localRotation;
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        board = Keyboard.current;
        vals[0] = board.hKey.isPressed;
        vals[1] = board.uKey.isPressed;
        vals[2] = board.iKey.isPressed;
        vals[3] = board.oKey.isPressed;
        vals[4] = board.pKey.isPressed;

        cont = (vals[0] == last[0]) && (vals[1] == last[1]) && (vals[2] == last[2]) && (vals[3] == last[3]) && (vals[4] == last[4]);

        if (cont)
        {
            return;
        }

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                //fingers[i, 0].SetActive(!vals[i]);
                if (vals[i])
                {
                    fingers[i,j].transform.localRotation = enderAngles[i,j];
                    //fingers[i,j].transform.localRotation = Quaternion.Slerp(starterAngles[i,j], enderAngles[i,j], 0.5f);
                }
                else
                {
                    fingers[i, j].transform.localRotation = starterAngles[i, j];
                    //fingers[i,j].transform.localRotation = Quaternion.Slerp(enderAngles[i,j], starterAngles[i,j], 0.5f);
                }
            }
        }

        for (int i = 0; i < 5;i++)
        {
            last[i] = vals[i];
        }

        output = "0:" + vals[0].ToString() + ", 1:" + vals[1].ToString() + ", 2:" + vals[2].ToString() + ", 3:" + vals[3].ToString() + ", 4:" + vals[4].ToString();
        Debug.Log(output);
    }
}
