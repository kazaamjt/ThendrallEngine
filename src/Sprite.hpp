#pragma once
#include <GL/glew.h>

class Sprite {
public:
	Sprite(float x, float y, float width, float height);
	~Sprite();

	void update(float x, float y);
	void draw();

private:
	float x;
	float y;
	float width;
	float height;

	GLuint vbo_id;
};
