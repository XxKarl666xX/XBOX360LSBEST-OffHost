#pragma once

enum eJustify {
	JustifyLeft,
	JustifyCenter,
	JustifyRight
};

class Render {
public:
	static void Initialize();

	static void DrawText(char* text, float x, float y, DWORD font, float fontScale, color color);
	static void DrawShader(float x, float y, float width, float height, DWORD materials, color color);
	static void DrawShaderWithOutline(float x, float y, float w, float h, color backgroundColor, color outlineColor, float lineWidth);
	static void DrawShaderOnlyRight(float x, float y, float w, float h, color backgroundColor, color lineColor, float lineWidth);
	static void DrawCheckBox(float centerX, float centerY, color checkColor, color outlineBoxColor, bool isToggled);
	static void DrawColorPreview(float centerX, float centerY, color Color);
	static void DrawLine(float X1, float Y1, float X2, float Y2, float width, color color, DWORD Shader);
	static void DrawCenteredText(char* text, float x, float y, float width, DWORD font, float fontScale, color color);
	static float CalculateXValueWithAlign(float x, char* text, DWORD font, float scale, eJustify justify);
	static void DrawString(char* text, float x, float y, DWORD font, float scale, color color, eJustify justify);
	static void MakeLines(vec3 Origin, FLOAT X1, FLOAT Y1, FLOAT Z1, FLOAT X2, FLOAT Y2, FLOAT Z2, color Color, int Size);
	static void DrawESPLine(vec3 center, float x1, float y1, float z1, float x2, float y2, float z2, color color);
	static void DrawBox(FLOAT X, FLOAT Y, FLOAT W, FLOAT H, color Color);
	static void DrawTextWithBackground(char *text, float x, float y, DWORD font, float fontScale, color color);
	static void DrawTopRightText(char* text, float x, float y, DWORD font, float fontScale, color color, int Index);
};