#pragma once
#include <random>
#include <assert.h>
#include <iostream>


class RNG
{
private:


public:
    RNG();
    ~RNG();

    float RandomNumberMovement()
    {
        std::mt19937 engine;
        std::random_device randomDevice;

        unsigned int seed = randomDevice();
        engine.seed(seed);

        std::uniform_real_distribution<float> distribution(-1.0, 1.0);
        float randomNumber = distribution(engine);
#ifdef _DEBUG
        {
            std::cout << seed << std::endl;
        }
#endif
        return(randomNumber);
    }


    int RandomLocation()
    {
        std::mt19937 engine;
        std::random_device randomDevice;

        int seed = randomDevice();
        engine.seed(seed);

        std::uniform_int_distribution<int> distribution(0, 600);
        int randomNumber = distribution(engine);
#ifdef _DEBUG
        {
            std::cout << seed << std::endl;
        }
#endif
        return(randomNumber);
    }

    // UNSURE IF WORKS? Makes sense with reading it.. that it fills a vector with random...

    /*void RandomVector()
    {
        std::random_device randomDevice;

        std::mt19937 engine(randomDevice());
        std::uniform_int_distribution<int> distribution(0, 10);
        std::vector<int> randomVector;
        for (int i = 0; i < randomVector.size(); ++i)
        {
            randomVector.push_back(distribution(engine));
            std::cout << randomVector[i];
        }
    }
    */
};

