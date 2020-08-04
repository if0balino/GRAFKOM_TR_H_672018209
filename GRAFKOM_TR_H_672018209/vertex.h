#pragma once
struct vec3 {
	double x;
	double y;
	double z;
};

struct Vertex {
	struct vec3 pos;
	struct vec3 normal;
	struct vec3 binormal;
	struct vec3 tangen;
	struct vec3 uv;
};