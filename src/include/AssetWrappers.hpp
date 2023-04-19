#ifndef ASSET_WRAPPERS_HPP
#define ASSET_WRAPPERS_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>

static const std::string UNCOVERED_TILE_PATHS[9] = {
    "tiles/TileEmpty.png", "tiles/Tile1.png", "tiles/Tile2.png",
    "tiles/Tile3.png",     "tiles/Tile4.png", "tiles/Tile5.png",
    "tiles/Tile6.png",     "tiles/Tile7.png", "tiles/Tile8.png"};

struct Assets {
  inline static std::vector<sf::Texture> tile_textures;
  inline static sf::Texture flag_texture;
  inline static sf::Texture mine_texture;
  inline static sf::Texture exploded_texture;
  inline static sf::Texture covered;
  inline static sf::Font font_regular;
  inline static sf::Font font_bold;
  inline static sf::Font font_light;

  inline static std::string get_assets_path(const std::string &path) {
    char *assets_dir = std::getenv("ASSETS_DIR");
    if (assets_dir == nullptr) {
      return "assets/" + path;
    }
    return std::string(assets_dir) + "/" + path;
  }

  inline static void load_assets() {
    for (std::string path : UNCOVERED_TILE_PATHS) {
      sf::Texture texture;
      texture.loadFromFile(get_assets_path(path));
      tile_textures.push_back(texture);
    }
    flag_texture.loadFromFile(get_assets_path("tiles/TileFlag.png"));
    mine_texture.loadFromFile(get_assets_path("tiles/TileMine.png"));
    exploded_texture.loadFromFile(get_assets_path("tiles/TileExploded.png"));
    covered.loadFromFile(get_assets_path("tiles/TileUnknown.png"));
    font_regular.loadFromFile(get_assets_path("fonts/Ubuntu-Medium.ttf"));
    font_bold.loadFromFile(get_assets_path("fonts/Ubuntu-Bold.ttf"));
    font_light.loadFromFile(get_assets_path("fonts/Ubuntu-Light.ttf"));
  }
};

#endif
