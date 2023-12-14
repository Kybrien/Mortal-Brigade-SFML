#include "Components/TileMap.h"

bool TileMap::Load(sf::Vector2u tileSize, std::string tileFile, const std::vector<int> tiles, unsigned int width, unsigned int height)
{
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile("../Assets/Tilesets/" + tileFile))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    sf::VertexArray* layer_vertices = new sf::VertexArray;

    layer_vertices->setPrimitiveType(sf::Quads);
    layer_vertices->resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // on récupère le numéro de tuile courant
            int tileNumber = tiles[i + j * width] - 1;

            if (tileNumber >= 0) {
                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &(*layer_vertices)[(i + j * width) * 4];

                // on définit ses quatre coins
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // on définit ses quatre coordonnées de texture
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        }

    m_layers.push_back(layer_vertices);

    return true;
}

bool TileMap::Unload() {
    m_layers.clear();

    return 1;
}

bool TileMap::AddCollider(sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height, Scene& scene) {
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            int tileNumber = tiles[i + j * width] - 1;

            if (tileNumber >= 0) {
                tileNumber = 0;
                GameObject* colliderobj = new GameObject;
                colliderobj->SetPosition(Maths::Vector2f(i * tileSize.x, j * tileSize.y));
                SquareCollider* collider = new SquareCollider;
                collider->SetWidth(static_cast<float>(tileSize.x));
                collider->SetHeight(static_cast<float>(tileSize.y));
                colliderobj->AddComponent(collider);
                scene.AddCollider(collider);
            }
        }

    AddLightCollider(tileSize, tiles, width, height, scene);

    return true;
}

bool TileMap::AddLightCollider(sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height, Scene& scene) {
    std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false));

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            if (!visited[i][j] && tiles[i + j * width] - 1 >= 0) {
                visited[i][j] = true;

                // Fusionner horizontalement
                unsigned int colliderWidth = 1;
                while (i + colliderWidth < width && tiles[i + colliderWidth + j * width] - 1 >= 0) {
                    visited[i + colliderWidth][j] = true;
                    ++colliderWidth;
                }

                // Fusionner verticalement
                unsigned int colliderHeight = 1;
                while (j + colliderHeight < height) {
                    bool canMerge = true;
                    for (unsigned int k = 0; k < colliderWidth; ++k) {
                        if (i + k < width && j + colliderHeight < height && tiles[i + k + (j + colliderHeight) * width] - 1 < 0) {
                            canMerge = false;
                            break;
                        }
                    }

                    if (canMerge) {
                        for (unsigned int k = 0; k < colliderWidth; ++k) {
                            if (i + k < width && j + colliderHeight < height) {
                                visited[i + k][j + colliderHeight] = true;
                            }
                        }
                        ++colliderHeight;
                    }
                    else {
                        break;
                    }
                }

                // Créer la collision en une seule pièce
                GameObject* colliderobj = new GameObject;
                colliderobj->SetPosition(Maths::Vector2f(i * tileSize.x, j * tileSize.y));
                SquareCollider* collider = new SquareCollider;
                collider->SetWidth(static_cast<float>(colliderWidth * tileSize.x));
                collider->SetHeight(static_cast<float>(colliderHeight * tileSize.y));
                colliderobj->AddComponent(collider);
                scene.AddLightCollider(collider);
            }
        }
    }

    return true;
}

bool TileMap::LoadMap(const std::string& tileset, Scene& scene) {
    std::ifstream mapf("../Assets/Maps/" + tileset + ".json");
    json data = json::parse(mapf);

    //for (int i = 0; i < data["tilesets"].size(); i++) {
    //    sf::Texture* newTileset = new sf::Texture;
    //    std::string tilesetName = data["tilesets"][i]["name"];
    //    newTileset->loadFromFile("assets/tilesets/" + tilesetName + ".png");
    //    std::cout << "TILESET " + tilesetName + " LOADED SUCCESSFULLY." << std::endl;
    //}

    for (int i = 0; i < data["layers"].size(); i++) {
        if (data["layers"][i]["type"] == "tilelayer") {
            const std::vector<int> level = data["layers"][i]["data"];

            unsigned int width = data["layers"][i]["width"];
            unsigned int height = data["layers"][i]["height"];
            sf::Vector2u tileSize(data["tilesets"][0]["tilewidth"], data["tilesets"][0]["tileheight"]);

            m_size.SetXY(width * data["tilesets"][0]["tilewidth"], height * data["tilesets"][0]["tileheight"]);

            if (data["layers"][i]["name"] != "Collision") {
                Load(tileSize, data["tilesets"][0]["image"], level, width, height);
                std::cout << "LAYER " << data["layers"][i]["name"] << " LOADED SUCCESSFULLY." << std::endl;
            }
            else {
                AddCollider(tileSize, level, width, height, scene);
                std::cout << "COLLISION LAYER " << data["layers"][i]["name"] << " LOADED SUCCESSFULLY." << std::endl;
            }
        }
    }

    return true;
}

int TileMap::GetWidth() {
    return m_size.x;
}

int TileMap::GetHeight() {
    return m_size.y;
}