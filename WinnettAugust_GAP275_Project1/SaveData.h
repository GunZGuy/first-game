#pragma once
#include "Vector2.h"
#include <string>
#include <SDL.h>

//Component for saving data to disk
class SaveData
{
public:
    //All Data to be saved to disk
    struct Data
    {
        Vector2<float> m_playerPosition;

        Vector2<float> m_enemyPosition;

        Vector2<float> m_bossPosition;

        float m_playerHealth;

        SDL_Rect m_objectPosition[20];

        int m_numOfSaves;

        std::string m_currentTime;
    };
private:
    static constexpr char s_kDirectory[] = "saves\\";

    static constexpr char s_kFileName[] = "savedata.save";

    static constexpr char s_kCustomFileName[] = "saveslot1";
    static constexpr char s_kCustomFileName2[] = "saveslot2";
    static constexpr char s_kCustomFileName3[] = "saveslot3";

    // Wether save data is loaded
    bool m_isLoaded;

    //The Save Data to be written/read
    Data m_data;

public:
    SaveData();
    ~SaveData();

    //Save data to Disk
    //True if successful
    bool Save(int x);

    //Load from disk
    //True if successful
    bool Load(int x);

    //Get if save data is loaded current session
    bool GetIsLoaded() { return m_isLoaded; }

    //Get a reference to actual save data
    Data& GetData() { return m_data; }
};

