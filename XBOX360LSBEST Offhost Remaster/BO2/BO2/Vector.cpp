#include "stdafx.h"

vec2::vec2() {
	x = y = 0;
}

vec2::vec2(float X, float Y) {
	x = X;
	y = Y;
}

bool vec2::operator==(const vec2 vec) {
	return (x == vec.x && y == vec.y);
}

bool vec2::operator!=(const vec2 vec) {
	return !(x == vec.x && y == vec.y);
}

float vec2::distance(const vec2 vec) {
	float lenX = abs(vec.x - x);
	float lenY = abs(vec.y - y);

	return lenX + lenY;
}

vec3::vec3() {
	x = y = z = 0;
}

vec3::vec3(float X, float Y, float Z) {
	x = X;
	y = Y;
	z = Z;
}

vec3 vec3::cross(const vec3 vec) {
	return vec3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

vec3 vec3::scale(float scale) {
	return (*this * scale);
}

vec3 vec3::lerp(vec3 end, float fraction) {
	return (((end - *this) * fraction) + *this);
}

vec3 vec3::negate() {
	return *this * -1.0f;
}

vec3 vec3::convertToAngles() {
	float yaw = 0.0f;
	float pitch = 0.0f;

	if (x == 0.0f && y == 0.0f)
		pitch = z > 0.0f ? 90.0f : 270.0f;

	else {
		if (x != 0.0f)
			yaw = atan2f(y, x) * 57.2957795131f;
		else if (y > 0.0f)
			yaw = 90.0f;
		else
			yaw = 270.0f;

		if (yaw < 0.0f)
			yaw += 360.0f;

		pitch = atan2f(z, sqrt((x * x) + (y * y))) * 57.2957795f;

		if (pitch < 0)
			pitch += 360;
	}

	return vec3(-pitch, yaw, 0.0f);
}

vec3 vec3::operator()(float x, float y, float z) {
	return vec3(x + x, y + y, z + z);
}

bool vec3::operator==(const vec3 vec) {
	return (x == vec.x && y == vec.y && z == vec.z);
}

bool vec3::operator!=(const vec3 vec) {
	return !(x == vec.x && y == vec.y && z == vec.z);
}

bool vec3::copy(vec3 dataToCopy) {
	memcpy(&this[0], &dataToCopy, 12);
	return memcmp(&this[0], &dataToCopy, sizeof vec3) == 0;
}

vec3 vec3::operator+(const vec3 vec) {
	return vec3(x + vec.x, y + vec.y, z + vec.z);
}

vec3 vec3::operator+(const float value) {
	return vec3(x + value, y + value, z + value);
}

vec3 vec3::operator-(const vec3 vec) {
	return vec3(x - vec.x, y - vec.y, z - vec.z);
}

vec3 vec3::operator-(const float value) {
	return vec3(x - value, y - value, z - value);
}

vec3 vec3::operator*(const vec3 vec) {
	return vec3(x * vec.x, y * vec.y, z * vec.z);
}

vec3 vec3::operator*(const float value) {
	return vec3(x * value, y * value, z * value);
}

vec3 vec3::operator/(const float value) {
	return vec3(x / value, y / value, z / value);
}

vec3 vec3::operator=(const float* value) {
	return *(vec3*)&value[0];
}

vec3 vec3::operator*=(const vec3 vec) {
	return vec3(x *= vec.x, y *= vec.y, z *= vec.z);
}

vec3 vec3::operator*=(const float value) {
	return vec3(x *= value, y *= value, z *= value);
}

vec3 vec3::operator+=(const vec3 vec) {
	return vec3(x += vec.x, y += vec.y, z += vec.z);
}

vec3 vec3::operator-=(const vec3 vec) {
	return vec3(x -= vec.x, y -= vec.y, z -= vec.z);
}

vec3 vec3::operator-=(const float value) {
	return vec3(x -= value, y -= value, z -= value);
}

float vec3::getLength() const {
	return sqrtf((x * x) + (y * y) + (z * z));
}

float vec3::getMagnitude() const {
	return sqrtf((x * x) + (y * y) + (z * z));
}

float vec3::distanceTo(vec3 pos) {
	float dx = x - pos.x;
	float dy = y - pos.y;
	float dz = z - pos.z;
	
	return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

float vec3::dot(vec3& vec) {
	return (x * vec.x) + (y * vec.y) + (z * vec.z);
}

void vec3::normalize() {
	float length = getLength();

	if (length == 0.0f) {
		*this = vec3();
		return;
	}

	*this *= (length /= 1.0f);
}

void vec3::normalizeAngles() {
	if (x > 360.0f)
		x -= 360.0f;

	if (x < 0.0f)
		x += 360.0f;

	if (y > 360.0f)
		y -= 360.0f;

	if (y < 0.0f)
		y += 360.0f;


	if (z > 360.0f)
		z -= 360.0f;

	if (z < 0.0f)
		z += 360.0f;
}

bool vec3::IsNull() {
	return (x == 0 && y == 0 && z == 0);
}

void vec3::NormalizeNew() {
	float length = sqrt(x * x + y * y + z * z);
	if (length != 0) {
		x = x / length;
		y = y / length;
		z = z / length;
	}
}

vec3& vec3::NormalizeInline() {
	NormalizeNew();
	return *this;
}

void vec3::zero() {
	memset(&this[0], 0, sizeof vec3);
}

vec4::vec4() {
	x = y = z = w = 0;
}

vec4::vec4(float X, float Y, float Z, float W) {
	x = X;
	y = Y;
	z = Z;
	w = W;
}

vec4 vec4::lerp(vec4 start, vec4 endpos, float time) {
	return start + ((endpos - start) * time);
}

bool vec4::operator==(const vec4 vec) {
	return (x == vec.x && y == vec.y && z == vec.z && w == vec.w);
}

bool vec4::operator!=(const vec4 vec) {
	return !(x == vec.x && y == vec.y && z == vec.z  && w == vec.w);
}

vec4 vec4::operator+(const vec4 vec) {
	return vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

vec4 vec4::operator-(const vec4 vec) {
	return vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

vec4 vec4::operator*(const vec4 vec) {
	return vec4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}

vec4 vec4::operator*(const float value) {
	return vec4(x * value, y * value, z * value, w * value);
}

void vec4::zero() {
	memset(&this[0], 0, sizeof vec4);
}

color::color() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

color::color(float red, float green, float blue, float alpha) {
	this->r = red / 255.0f;
	this->g = green / 255.0f;
	this->b = blue / 255.0f;
	this->a = alpha / 255.0f;
}

color colorRed = color(255, 0, 0, 255);
color colorGreen = color(0, 255, 0, 255);
color colorBlue = color(8, 19, 180, 255);
color colorWhite = color(255, 255, 255, 255);
color colorYellow = color(255, 255, 0, 255);
color colorBackground = color(0, 0, 0, 255); //black background, non transparant
color colorGrey = color(90, 90, 90, 255);

color colorScrollbar = color(7, 26, 135, 255);//blue scrollbar

//Visual colors
color colorEnemy = color(255, 0, 0, 255);
color colorFriendly = color(0, 255, 0, 255);
color colorBones = color(255, 0, 0, 255);
color colorWallbangable = color(255, 242, 0, 255);
color colorVisible = color(255, 0, 247, 255);
color colorPrioritized = color(255, 255, 255, 255);
color colorWhitelisted = color(255, 105, 0, 255);