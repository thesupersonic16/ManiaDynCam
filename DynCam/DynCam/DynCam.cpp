// DynCam.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <ManiaModLoader.h>

extern "C"
{

    // Structures
    struct Vector2i
    {
        int X = 0;
        int Y = 0;
    };

    enum GameStates : BYTE
    {
        GameState_NotRunning = 0b0000,
        GameState_Running = 0b0001,
        GameState_SoftPause = 0b0010,
        GameState_HardPause = 0b0100,
        GameState_DevMenu = 0b1000
    };

    // DataPointers
	DataPointer(Vector2i, CameraOffset, 0x00479F34);
    DataPointer(GameStates, GameState, 0x00A535E2);
    // TODO: Add this to Player Struct (PlayerData + 0x0000002C)
    DataPointer(int, Player1Speed, 0x00469A3C);

    // Globals
    static int Speed1 = 1;
    static int Speed2 = 2;

    __declspec(dllexport) void OnFrame()
    {
        if (GameState & GameState_Running)
        {
            if (Player1Speed >= 400000)
            {
                if (CameraOffset.X < 0)
                    CameraOffset.X += Speed2;
                else if (CameraOffset.X <= 128)
                    CameraOffset.X += Speed1;
            }
            else if (Player1Speed <= -400000)
            {
                if (CameraOffset.X > 0)
                    CameraOffset.X -= Speed2;
                else if (CameraOffset.X >= -128)
                    CameraOffset.X -= Speed1;
            }
            else if (CameraOffset.X < 0)
                CameraOffset.X += Speed1;
            else if (CameraOffset.X > 0)
                CameraOffset.X -= Speed1;
        }
    }

    __declspec(dllexport) void Init(const char *path)
    {

    }

    __declspec(dllexport) ModInfo ManiaModInfo = { ModLoaderVer, GameVer };

}