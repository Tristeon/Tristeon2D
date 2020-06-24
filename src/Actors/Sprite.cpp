#include "Sprite.h"

#include <Actors/Actor.h>
#include <Rendering/Texture.h>

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <Resources.h>

#include "Math/Math.h"

namespace Tristeon
{
	REGISTER_ACTOR_CPP(Sprite)
	REGISTER_TYPE_CPP(Sprite)
	
	Sprite::Sprite()
	{
		texture = Resources::assetLoad<Texture>(Texture::defaultPath);
	}

	json Sprite::serialize()
	{
		json j = Graphic::serialize();
		j["typeID"] = TRISTEON_TYPENAME(Sprite);
		j["width"] = width;
		j["height"] = height;
		j["flipX"] = flipX;
		j["flipY"] = flipY;
		j["colour"] = colour;
		j["texturePath"] = texturePath;
		return j;
	}

	void Sprite::deserialize(json j)
	{
		Graphic::deserialize(j);
		
		width = j.value("width", 1);
		height = j.value("height", 1);

		flipX = j.value("flipX", false);
		flipY = j.value("flipY", false);

		colour = j.value("colour", Colour());

		std::string const newPath = j.value("texturePath", "");
		if (newPath != texturePath) //Update if new path
		{
			texture = Resources::assetLoad<Texture>(newPath);
			texturePath = newPath;
		}
		
		if (!texture)
			texture = Resources::assetLoad<Texture>(Texture::defaultPath);
	}

	void Sprite::setTexture(std::string const& path, bool const& setSize)
	{
		texture = Resources::assetLoad<Texture>(path);
		texturePath = path;
		
		if (!texture)
		{
			texture = Resources::assetLoad<Texture>(Texture::defaultPath);
			texturePath = Texture::defaultPath;
		}
		
		if (setSize)
		{
			width = texture->width();
			height = texture->height();
		}
	}

	Texture* Sprite::getTexture()
	{
		return texture;
	}

	void Sprite::render(QOpenGLShaderProgram* program)
	{
		QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
		f->glActiveTexture(GL_TEXTURE0);
		texture->bind();

		//Sprite info
		program->setUniformValue("sprite.width", width);
		program->setUniformValue("sprite.height", height);
		program->setUniformValue("sprite.colour", colour.r, colour.g, colour.b, colour.a);

		program->setUniformValue("sprite.flipX", flipX);
		program->setUniformValue("sprite.flipY", flipY);
		
		program->setUniformValue("actor.position", position.x, position.y);
		program->setUniformValue("actor.scale", scale.x, scale.y);
		program->setUniformValue("actor.rotation", -rotation);

		f->glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	Shader* Sprite::getShader()
	{
		static Shader shader = Shader("Internal/Shaders/Sprite.vert", "Internal/Shaders/Sprite.frag");
		return &shader;
	}

	bool Sprite::withinBounds(Vector2 const& worldPos)
	{
		return getAABB().contains(worldPos);
	}

	Graphic::AABB Sprite::getAABB()
	{
		Vector2 const halfSize = { width / 2.0f * scale.x, height / 2.0f * scale.y };
		return AABB{ position - halfSize, position + halfSize };
	}
}
