#include "biomemanager.hpp"
#include "FastNoiseLite.h"
#include "block.hpp"

const BiomeParams plains {
    .name = "Plains",
    .type = Biome::plains,
    .minHumidity = 0.35,
    .maxHumidity = 0.55,
    .minTemperature = 0.45,
    .maxTemperature = 0.65,
    .palette =
        {.top = {.height = 1, .blocks = {{BlockType::Grass, 100}}},
         .ground = {.height = 18, .blocks = {{BlockType::Grass, 100}}}}
};
const BiomeParams desert {
    .name = "Desert",
    .type = Biome::desert,
    .minHumidity = 0.0,
    .maxHumidity = 0.2,
    .minTemperature = 0.8,
    .maxTemperature = 1.0,
    .palette =
        {.top = {.height = 1, .blocks = {{BlockType::Sand, 100}}},
         .ground = {.height = 18, .blocks = {{BlockType::Sand, 100}}}}
};
const BiomeParams mountains {
    .name = "Mountains",
    .type = Biome::mountains,
    .minHumidity = 0.2,
    .maxHumidity = 0.4,
    .minTemperature = 0.1,
    .maxTemperature = 0.3,
    .palette =
        {.top = {.height = 15, .blocks = {{BlockType::Stone, 40}, {BlockType::Grass, 60}}},
         .ground = {.height = 55, .blocks = {{BlockType::Stone, 70}, {BlockType::Grass, 30}}}}
};
const BiomeParams biomeParams[] = {plains, desert, mountains};

BiomeManager::BiomeManager(int seed) : seed(seed)
{
    humidityNoise.SetSeed(seed);
    humidityNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    humidityNoise.SetSeed(seed);
    temperatureNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
}

Biome BiomeManager::GetBiome(float x, float y)
{
    const int biomeCount = 3;
    std::vector<BiomeParams> validBiomes;
    float newX = x * BIOME_POS_SCALE;
    float newY = y * BIOME_POS_SCALE;

    float humidityValue = humidityNoise.GetNoise(newX, newY);
    float temperatureValue = temperatureNoise.GetNoise(newX, newY);
    for (int i = 0; i < biomeCount; i++)
    {
        if (humidityValue >= biomeParams[i].minHumidity && humidityValue <= biomeParams[i].maxHumidity)
        {
            if (temperatureValue >= biomeParams[i].minTemperature && temperatureValue <= biomeParams[i].maxTemperature)
            {
                validBiomes.emplace_back(biomeParams[i]);
            }
        }
    }
    int index = rand() % (validBiomes.size() - 1 - 0);
    BiomeParams currentBiome = validBiomes[index];
    return currentBiome.type;
}
void BiomeManager::GetHeightMap(float x, float y)
{
}
