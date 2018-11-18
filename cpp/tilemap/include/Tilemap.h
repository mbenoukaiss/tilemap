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
     * \brief Default constructor.
     */
    Tilemap();

    /*!
     * \brief Destructor.
     */
    ~Tilemap() override;

    /*!
     * \brief Adds a layer to the tilemap.
     *
     * The layer will be added on top of all the other
     * existing layers. Only a copy of the layer will
     * be kept by the tilemap.
     * If the layer exceeds the current boundaries
     * (set by previous layers), boundaries will be
     * updated to include the new layer, which means
     * adding a layer that is outside the background
     * boundaries will allow to "scroll" outside of the
     * tilemap (until the limits of the new layer are
     * reached).
     *
     * \param layer Layer
     */
    void addLayer(const Layer& layer);

    /*!
     * \brief Draws the tilemap to a render target.
     *
     * \param target Render target to draw to
     * \param states Render states
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /*!
     * \brief Get the boundaries of the tilemap.
     *
     * Boundaries represent smallest area which contains
     * all of the different layer's tiles.
     *
     * \return Boundaries
     */
    const sf::FloatRect& boundaries() const;

    protected:
    std::vector<Layer> m_layers;
    sf::FloatRect m_boundaries;

};

} // namespace tiles


#endif //TILEMAP_TILEMAP_H
