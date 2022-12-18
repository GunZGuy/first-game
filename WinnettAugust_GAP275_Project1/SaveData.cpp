#include "SaveData.h"
#include <direct.h>
#include <fstream>
#include <iostream>

SaveData::SaveData()
{
}

SaveData::~SaveData()
{
}

bool SaveData::Save(int x)
{
    // Separate files possible to save to
    //Opening, writing, and closing files
    _mkdir(s_kDirectory);
    std::string path;
    if (x == 1)
    {
        path = s_kDirectory + std::string(s_kCustomFileName);
    }
    if (x == 2)
    {
        path = s_kDirectory + std::string(s_kCustomFileName2);
    }
    if (x == 3)
    {
        path = s_kDirectory + std::string(s_kCustomFileName3);
    }
    std::ofstream file;
    file.open(path, std::ios::out);
    if (!file.is_open())
    {
        std::cout << "Failed to open" << path << std::endl;
        return false;
    }

    file.write((char*)&m_data, sizeof(m_data));

    file.close();

    return true;
}

bool SaveData::Load(int x)
{
    //Picking between all custom files
    //Open, Reading, and closing files
    std::string path;
    if (x == 1)
    {
        path = s_kDirectory + std::string(s_kCustomFileName);
    }
    if (x == 2)
    {
        path = s_kDirectory + std::string(s_kCustomFileName2);
    }
    if (x == 3)
    {
        path = s_kDirectory + std::string(s_kCustomFileName3);
    }

    std::ifstream file;
    file.open(path, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Failed to open" << path << std::endl;
        return false;
    }
    file.read((char*)&m_data, sizeof(m_data));
    file.close();
    m_isLoaded = true;

    return true;
}
