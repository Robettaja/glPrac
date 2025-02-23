#include "block.hpp"
#include <FastNoiseLite.h>
#include <chunk.hpp>
#include <functional>

enum class Biome
{
    Plains,
    Mountains,
    Desert,
};

template <typename T> struct Weighted
{
    T item;
    int weight;
};

struct LayerPalette
{
    int height;
    std::vector<Weighted<BlockType>> blocks;
};

struct BiomeBlockPalette
{
    LayerPalette top, ground;
};
struct BiomeParams
{
    std::string name;
    Biome type;
    std::function<float(float)> CalculateHeightMap;
    float minHumidity, maxHumidity, minTemperature, maxTemperature;
    BiomeBlockPalette palette;
};

class BiomeManager
{
  private:
    int seed;
    const float BIOME_POS_SCALE = 0.001;

    FastNoiseLite humidityNoise;
    FastNoiseLite temperatureNoise;

  public:
    BiomeManager(int seed);
    BiomeParams GetBiome(float x, float y);
    float GetHeightMap(float x, float y, BiomeParams biome);
};
