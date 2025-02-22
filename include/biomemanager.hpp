#include "block.hpp"
#include <FastNoiseLite.h>
#include <chunk.hpp>

enum class Biome
{
    plains,
    mountains,
    desert,
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
    float minHumidity, maxHumidity, minTemperature, maxTemperature;
    BiomeBlockPalette palette;
};

class BiomeManager
{
  private:
    int seed;
    const float BIOME_POS_SCALE = 0.1;

    FastNoiseLite humidityNoise;
    FastNoiseLite temperatureNoise;

  public:
    BiomeManager(int seed);
    Biome GetBiome(float x, float y);
    void GetHeightMap(float x, float y);
};
