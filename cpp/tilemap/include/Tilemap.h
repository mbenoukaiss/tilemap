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
     * \brief Constructs an empty tilemap.
     */
    explicit Tilemap();

    /*!
     * \brief Destructor
     */
    ~Tilemap() override;

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
    std::vector<Layer> m_layers;
    sf::FloatRect m_bounds;

};

} // namespace tiles


#endif //TILEMAP_TILEMAP_H
