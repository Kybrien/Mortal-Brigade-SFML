#include <iostream>
#include "SFML/Graphics.hpp"
#include <fstream>
#include "Scene.h"
#include "json.hpp"
#include "Maths/Vector2.h"
#include "Components/SquareCollider.h"
//#include "Components/ShapeRenderer.h"

using json = nlohmann::json;

class TileMap : public sf::Drawable, public sf::Transformable, public Component
{
public:
    TileMap() = default;
    ~TileMap() override = default;

    bool Load(sf::Vector2u tileSize, std::string tileFile, const std::vector<int> tiles, unsigned int width, unsigned int height);

    bool AddCollider(sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height, Scene& scene);
    bool AddLightCollider(sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height, Scene& scene);

    bool Unload();

    bool LoadMap(const std::string& tileset, Scene& scene);

    int GetWidth();

    int GetHeight();

    void Render(sf::RenderWindow* _window) override { _window->draw(*this); };

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        for (int i = 0; i < m_layers.size(); ++i) {
            // Appliquer la texture actuelle

            // Dessiner le vertexArray
            target.draw(*m_layers[i], states);
        }
    }

    std::vector<sf::VertexArray*> m_layers;
    sf::Texture m_tileset;
    Maths::Vector2<int> m_size = Maths::Vector2<int>(0, 0);
};