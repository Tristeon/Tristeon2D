#pragma once
#include "Actors/Actor.h"
#include <Rendering/Shader.h>

namespace Tristeon
{
	class ActorLayer;
	
	/**
	 * Graphic is the base class for 2D renderable actors.
	 *
	 * Inheriting classes must override the render() and getShader() functions.
	 */
	class Graphic : public Actor
	{
		friend ActorLayer;
	protected:
		/**
		 * Render the graphic to the GameView, called for each graphic by the ActorLayer.
		 *
		 * Inheriting classes should override this function to implement rendering behaviour.
		 */
		virtual void render(QOpenGLShaderProgram* program) = 0;

		/**
		 * Get a pointer to the Graphic's shader.
		 * Inheriting classes are recommended to own a static version of their own shader,
		 * initialized within this function as follows:
		 *
		 * Shader* InheritingClass::getShader() {
		 *		static Shader shader = Shader("VertexPath", "FragmentPath");
		 *
		 *		return &shader;
		 * }
		 *
		 * This way, the implementation cost is minimal and the result is performant as the shader is only created once.
		 */
		virtual Shader* getShader() = 0;
	};
}