#ifndef TILEMAP_LAYER_H
#define TILEMAP_LAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include "Tileset.h"

namespace tiles {

class LayerBuilder;

class Layer : public sf::Drawable, public sf::Transformable {

    friend class LayerBuilder;

    public:
    /*!
     * \brief Copy constructor
     *
     * \param other Layer to copy
     */
    Layer(const Layer& other);

    /*!
     * \brief Move constructor
     *
     * \param other Layer to swap with
     */
    Layer(Layer&& other) noexcept;

    /*!
     * \brief Default destructor
     */
    ~Layer() override;

    /*!
     * \brief Get the tiles array
     *
     * One dimensional array of size width * height.
     * The tiles in this array can be modified in
     * order to animate the layer.
     *
     * \return Pointer to the tiles array
     */
    int* tiles();

    /*!
     * \brief Get the tileset
     *
     * \return Tileset
     */
    const std::shared_ptr<Tileset>& tileset() const;

    /*!
     * \brief Get the size
     *
     * In pixels
     *
     * \return Size
     */
    const sf::Vector2u& size() const;

    /*!
     * \brief Get the offset
     *
     * In pixels. The offset is calculated from
     * point (0,0) of the tilemap.
     *
     * \return Offset
     */
    const sf::Vector2f& offset() const;

    /*!
     * \brief Copy assignment operator
     *
     * \param other Layer to copy
     * \return Self
     */
    Layer& operator=(const Layer& other);

    /*!
     * \brief Move assignment operator
     *
     * \param other Layer to swap with
     * \return This
     */
    Layer& operator=(Layer&& other) noexcept;

    protected:
    /*!
     * \brief Default constructor, for the builder
     */
    Layer();

    /*!
     * \brief Make a copy of the array into this
     *
     * \param tiles Tiles to copy
     */
    void copyTiles(int* tiles);

    /*!
     * \brief Draws the tilemap to a render target
     *
     * \param target Render target to draw to
     * \param states Render states
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::shared_ptr<Tileset> m_tileset;
    int* m_tiles;
    sf::Vector2u* m_size;
    sf::Vector2f* m_offset;

};

class LayerBuilder {

    public:
    /*!
     * \brief Default constructor.
     */
    LayerBuilder();

    /*!
     * \brief Destructor.
     */
    virtual ~LayerBuilder();

    /*!
     * \brief Defines the tileset.
     *
     * \param tileset Tileset
     * \return Self
     */
    LayerBuilder& setTileset(std::shared_ptr<Tileset>& tileset);

    /*!
     * \brief Defines the tiles.
     *
     * The array will not get copied. Therefore it must
     * not get freed before the layer.
     * It must be at least the size of size.x * size.y.
     *
     * \param tiles Tiles array
     * \return Self
     */
    LayerBuilder& setTiles(int* tiles);

    /*!
     * \brief Defines the tiles.
     *
     * \param tiles Initializer list of tiles
     * \return Self
     */
    LayerBuilder& setTiles(std::initializer_list<int> tiles);

    /*!
     * \brief Set the size.
     *
     * \param width Width in pixels
     * \param height Height in pixels
     * \return Self
     */
    LayerBuilder& setSize(unsigned int width, unsigned int height);

    /*!
     * \brief Set the size.
     *
     * \param size Size in pixels
     * \return Self
     */
    LayerBuilder& setSize(sf::Vector2u& size);

    /*!
     * \brief Set the offset.
     *
     * In pixels. The offset is calculated from
     * point (0,0) of the tilemap.
     *
     * \param x Horizontal offset in pixels
     * \param y Vertical offset in pixels
     * \return Self
     */
    LayerBuilder& setOffset(float x, float y);

    /*!
     * \brief Set the offset.
     *
     * In pixels. The offset is calculated from
     * point (0,0) of the tilemap.
     *
     * \param size Offset in pixels
     * \return Self
     */
    LayerBuilder& setOffset(sf::Vector2f& offset);

    /*!
     * \brief Builds the layer.
     *
     * \return Layer
     */
    Layer* build() const;

    private:
    std::shared_ptr<Tileset> m_tileset;
    int* m_tiles;
    sf::Vector2u* m_size;
    sf::Vector2f* m_offset;

};

} // namespace tiles

#endif //TILEMAP_LAYER_H
