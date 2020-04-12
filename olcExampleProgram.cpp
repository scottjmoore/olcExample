#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Example";
	}

	olc::Sprite* sprImage = nullptr;
	olc::Decal* decImage = nullptr;
	float fAngle = 0.0f;

	int nLayerBackground;

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		sprImage = new olc::Sprite("./Images/bell.png");
		decImage = new olc::Decal(sprImage);

		nLayerBackground = CreateLayer();

		SetDrawTarget(nLayerBackground);
		Clear(olc::VERY_DARK_BLUE);

		for (auto x = 0; x < ScreenWidth(); x++)
			for (auto y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, 0));

		EnableLayer(nLayerBackground, true);
		SetDrawTarget(nullptr);
		Clear(olc::BLANK);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		auto colour = rand() % 255;
		Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc::Pixel(0, 0, colour, colour));

		SetLayerOffset(nLayerBackground, { fAngle * 0.1f, fAngle * 0.1f });

		fAngle += fElapsedTime * 0.1f;
		DrawRotatedDecal({ float(GetMouseX()), float(GetMouseY())}, decImage, fAngle, {sprImage->width / 2.0f, sprImage->height / 2.0f}, { 0.1f, 0.1f });

		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(192, 108, 10, 10, false, true))
		demo.Start();

	return 0;
}
