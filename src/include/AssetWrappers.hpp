#ifndef ASSET_WRAPPERS_HPP
#define ASSET_WRAPPERS_HPP

#include <SFML/Graphics.hpp>
#include <string>

static const std::string UNCOVERED_TILE_PATHS[9] = {
    "assets/TileEmpty.png", "assets/Tile1.png", "assets/Tile2.png",
    "assets/Tile3.png",     "assets/Tile4.png", "assets/Til5.png",
    "assets/Tile6.png",     "assets/Tile7.png", "assets/Tile8.png"};

struct Assets {
  inline static std::vector<sf::Texture> tile_textures;
  inline static sf::Texture flag_texture;
  inline static sf::Texture mine_texture;
  inline static sf::Texture exploded_texture;
  inline static sf::Texture covered;
  inline static void load_assets() {
    for (std::string path : UNCOVERED_TILE_PATHS) {
      sf::Texture texture;
      texture.loadFromFile(path);
      tile_textures.push_back(texture);
    }
    flag_texture.loadFromFile("assets/TileFlag.png");
    mine_texture.loadFromFile("assets/TileMine.png");
    exploded_texture.loadFromFile("assets/TileExploded.png");
    covered.loadFromFile("assets/TileUnknown.png");
  }
};

#endif
