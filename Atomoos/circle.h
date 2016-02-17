#pragma once
#include "polygon.h"
#include "mooTypes.h"
#include "shaderProgram.h"
namespace MooGL
{
	class Circle
	{
	public:
		Circle() {}
		Circle(MooGL::Polygon polygon, MooGL::coord2d* center, MooGL::colorRGB color);
		Circle(GLsizei n, GLfloat r, MooGL::coord2d* center, MooGL::colorRGB color);

		void draw();

		MooGL::coord2d * center;
		MooGL::colorRGB color;

		static GLfloat * generateVertices(GLsizei n, GLfloat r);

	private:
		MooGL::Polygon polygon;

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