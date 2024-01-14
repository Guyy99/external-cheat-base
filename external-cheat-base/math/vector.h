#pragma once

struct vec4
{
	float w, x, y, z;
};

struct vec3
{
	float x, y, z;
	vec3 operator+(vec3 other)
	{
		return { this->x + other.x, this->y + other.y, this->z + other.z };
	}
	vec3 operator-(vec3 other)
	{
		return { this->x - other.x, this->y - other.y, this->z - other.z };
	}

};

struct vec2
{
	float x, y;
};
