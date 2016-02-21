#pragma once
#include "Polygon.h"
#include "Types.h"
#include "ShaderProgram.h"
namespace Game
{
	class Circle
	{
	public:
		Circle() {}
		Circle(const Game::Polygon* polygon, coord2d* center, colorRGB* color);
		Circle(GLsizei n, GLfloat r, coord2d* center, colorRGB* color);

		void draw();

		coord2d * center;
		colorRGB * color;

		static const GLfloat * generateVertices(GLsizei n, GLfloat r);
	protected:
		const Game::Polygon * polygon;

		ShaderProgram shader;

#define PI 3.14159265358979

		static constexpr char* vertexSource = R"(
			#version 420 core
			layout (location = 0) in vec2 circ;
			uniform vec2 center;
			void main() {
				gl_Position	= vec4(circ + center, 0, 1.0);
			})";
		static constexpr char* fragmentSource = R"(
			#version 420 core
			uniform vec3 extColor;
			out vec4 color;
			void main() {
				color = vec4(extColor, 1.0f);
			})";
	};
}