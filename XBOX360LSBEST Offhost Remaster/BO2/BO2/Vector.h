#ifndef __VECTOR_H__
#define __VECTOR_H__

class vec2 {
public:
	vec2();
	vec2(float x, float y);

	bool operator==(const vec2 vec);
	bool operator!=(const vec2 vec);
	bool empty() {
		return x == 0.0f && y == 0.0f;
	}

	float distance(const vec2 vec);

	float x, y;
};

class vec3 {
public:
	vec3();
	vec3(float X, float Y, float Z);

	vec3 cross(const vec3 vec);
	vec3 scale(float scale);
	vec3 lerp(vec3 end, float time);
	vec3 negate();
	vec3 convertToAngles();

	bool operator!=(const vec3 vec);
	bool operator==(const vec3 vec);
	bool copy(vec3 dataToCopy);

	vec3 operator-(const vec3 vec);
	vec3 operator-(const float value);
	vec3 operator+(const vec3 vec);
	vec3 operator+(const float value);
	vec3 operator*(const vec3 vec);
	vec3 operator*(const float value);
	vec3 operator/(const float value);
	vec3 operator=(const float* value);
	vec3 operator+=(const vec3 vec);
	vec3 operator()(float x, float y, float z);
	vec3 operator-=(const vec3 vec);
	vec3 operator-=(const float value);
	vec3 operator*=(const vec3 vec);
	vec3 operator*=(const float value);

	float getLength() const;
	float getMagnitude() const;
	float distanceTo(vec3 pos);
	float dot(vec3& vec);

	void normalize();
	void normalizeAngles();
	bool IsNull();
	void NormalizeNew();
	vec3& NormalizeInline();
	void zero();

	float x, y, z;
};

class vec4 {
public:
	vec4();
	vec4(float X, float Y, float Z, float W);

	vec4 lerp(vec4 vec, vec4 endpos, float time);

	bool operator!=(const vec4 vec);
	bool operator==(const vec4 vec);

	vec4 operator-(const vec4 vec);
	vec4 operator+(const vec4 vec);
	vec4 operator*(const vec4 vec);
	vec4 operator*(const float value);

	void zero();

	float x, y, z, w;
};

class color {
public:
	color();
	color(float red, float green, float blue, float alpha);

	void alphaTransitionFade(float alphaToFadeTo, float transitionTime) {
		if (a > alphaToFadeTo)
			a -= transitionTime;

		else if (a < alphaToFadeTo)
			a += transitionTime;

		if (a == alphaToFadeTo)
			return;
	}

	float r, g, b, a;
};

extern float rainbowcolor[50][4];

extern color colorRed;
extern color colorGreen;
extern color colorBlue;
extern color colorWhite;
extern color colorYellow;
extern color colorBackground;
extern color colorGrey;

extern color colorScrollbar;

//Visual colors
extern color colorEnemy;
extern color colorFriendly;
extern color colorBones;
extern color colorWallbangable;
extern color colorVisible;
extern color colorPrioritized;
extern color colorWhitelisted;

#endif //__VECTOR_H__