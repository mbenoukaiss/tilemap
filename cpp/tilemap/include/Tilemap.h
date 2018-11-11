#ifndef TILEMAP_TILEMAP_H
#define TILEMAP_TILEMAP_H

#include <SFML/Graphics.hpp>
#include "../include/Layer.h"

namespace tiles {

/*!
 * \brief Drawable tilemap
 */
class Tilemap : public sf::Drawable {

    public:
    /*!
     * \brief Constructs a tilemap of the given size.
     *
     * \param size The size of the tilemap in pixels
     * \param origin The origin of the tilemap, which is the
     * first pixel drawn in the top left corner of the tilemap
     */
    explicit Tilemap(sf::Vector2u size, sf::Vector2f origin = sf::Vector2f(0.0f, 0.0f));

    /*!
     * \brief Destructor
     */
    ~Tilemap() override;

    /*!
     * \brief Changes the origin by a given offset.
     *
     * \param offset Offset
     */
    void translate(sf::Vector2f offset);

    /*!
     * \brief Resizes the tilemap
     *
     * \param size Size
     */
    void resize(sf::Vector2u size);

    /*!
     * \brief Changes the origin by a given offset.
     *
     * \param offset Offset
     */
    void translate(float ox, float oy);

    /*!
     * \brief Resizes the tilemap
     *
     * \param size Size
     */
    void resize(unsigned int width, unsigned int height);

    void loadTileset(const std::string& tileset, unsigned int tileSize);

    void setTilemapSize(const sf::Vector2u& tilesCount);

    /*!
     * \brief Adds a layer to the tilemap
     *
     * The layer will be added on top of all the other
     * existing layers. Only a copy of the layer will
     * be kept by the tilemap.
     *
     * \param layer Layer
     */
    void addLayer(const Layer& layer);

    /*!
     * \brief Draws the tilemap to a render target
     *
     * \param target Render target to draw to
     * \param states Render states
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    protected:
    sf::Texture m_texture;
    unsigned int m_tileSize;

    std::vector<Layer> m_layers;
    sf::Vector2u m_mapSize;

    sf::Vector2u m_size;
    sf::Vector2f m_origin;

};

} // namespace tiles


#endif //TILEMAP_TILEMAP_H
