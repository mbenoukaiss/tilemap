#ifndef TILEMAP_TILESET_H
#define TILEMAP_TILESET_H

#include <SFML/Graphics.hpp>

namespace tiles {

/*!
 * \brief Holds information about tileset
 */
class Tileset {

    public:
    /*!
     * \brief Constructs a tileset using the given texture.
     *
     * \param texture An existing texture object
     * \param tileSize Size of the tiles in pixels
     */
    Tileset(const sf::Texture* texture, unsigned int tileSize);

    /*!
     * \brief Constructs a tileset using the given file.
     *
     * Throws a runtime_error if the file can't be found
     * or opened.
     *
     * \param tileset The path to the image
     * \param tileSize Size of the tiles in pixels
     */
    Tileset(const std::string& tileset, unsigned int tileSize);

    /*!
     * \brief Destructor.
     */
    virtual ~Tileset();

    /*!
     * \brief Get the texture provided by the tileset.
     *
     * The returned pointer is const, which means that you can't
     * modify the texture when you retrieve it with this function.
     *
     * \return Pointer to the texture
     */
    const sf::Texture* texture() const;

    /*!
     * \brief Get the size of the tileset.
     *
     * The returned pointer is const, which means that you can't
     * modify the texture when you retrieve it with this function.
     *
     * \return Pointer to the size object
     */
    const sf::Vector2u* size() const;

    /*!
     * \brief Get the size of a tile in pixels.
     *
     * \return Size of a tile
     */
    unsigned int tileSize() const;

    private:
    const sf::Texture* m_texture;
    const sf::Vector2u* m_size;
    const unsigned int m_tileSize;

};

} // namespace tiles

#endif //TILEMAP_TILESET_H
