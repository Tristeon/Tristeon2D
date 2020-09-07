#pragma once
#include "Rendering/Graphic.h"
#include <Rendering/Texture.h>

#include <Utils/Colour.h>
#include <Serialization/TypeRegister.h>

namespace Tristeon
{
	class ActorLayer;

	/**
	 * Sprite is a 2D quad with a texture. Its size can be adjusted through Sprite::width and Sprite::height.
	 */
	class Sprite : public Graphic
	{
		friend ActorLayer;
	public:
		/**
		 * Creates a white sprite of size 64x64.
		 */
		Sprite();
		virtual ~Sprite() = default;

		DELETE_COPY(Sprite);
		DEFAULT_MOVE(Sprite);

		json serialize() override;
		void deserialize(json j) override;

		/**
		 * The width of the sprite in pixels.
		 */
		unsigned int width = 64;

		/**
		 * The height of the sprite in pixels.
		 */
		unsigned int height = 64;

		/**
		 * If true, the sprite is flipped horizontally
		 */
		bool flipX = false;

		/**
		 * If true, the sprite is flipped vertically
		 */
		bool flipY = false;

		/**
		 * The colour of the sprite, this acts as a multiplier on top of the existing texture.
		 */
		Colour colour = Colour::white();

		/**
		 * Sets the texture of the sprite to the texture at the given path.
		 *
		 * \param path The filepath of the new texture.
		 * \param setSize If true, the sprite will take on the size of the texture.
		 */
		virtual void setTexture(std::string const& path, bool const& setSize);

		/**
		 * Returns the current texture of the sprite. May be nullptr.
		 */
		virtual Texture* texture();
		
		/**
		 * Returns the Sprite's Bounds.
		 * This is a square, defined using the position, scale, width, and height of the sprite.
		 */
		Bounds bounds() override;

	protected:
		void render() override;
		Shader* getShader() override;

		/**
		 * The 2D texture of the sprite.
		 */
		Texture* _texture = nullptr;

		/**
		 * The path to the texture.
		 */
		String _texturePath;
	};

	REGISTER_TYPE(Sprite);
}