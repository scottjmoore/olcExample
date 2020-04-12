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

	int nLayerBackground1, nLayerBackground2, nLayerBackground3;

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		sprImage = new olc::Sprite("./Images/bell.png");
		decImage = new olc::Decal(sprImage);

		nLayerBackground1 = CreateLayer();
		nLayerBackground2 = CreateLayer();
		nLayerBackground3 = CreateLayer();

		SetDrawTarget(nLayerBackground1);
		Clear(olc::BLANK);
		for (auto i = 0; i < 15000; i++)
		{
			auto colour = rand() % 255;
			Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc::Pixel(colour, 0, 0, colour));
		}
		EnableLayer(nLayerBackground1, true);
		
		SetDrawTarget(nLayerBackground2);
		Clear(olc::BLANK);
		for (auto i = 0; i < 15000; i++)
		{
			auto colour = rand() % 255;
			Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc::Pixel(0, colour, 0, colour));
		}
		EnableLayer(nLayerBackground2, true);

		SetDrawTarget(nLayerBackground3);
		Clear(olc::BLANK);
		for (auto i = 0; i < 15000; i++)
		{
			auto colour = rand() % 255;
			Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc::Pixel(0, 0, colour, colour));
		}
		EnableLayer(nLayerBackground3, true);

		SetDrawTarget(nullptr);
		Clear(olc::BLANK);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		SetLayerOffset(nLayerBackground1, { fAngle * 0.4f, fAngle * 0.4f });
		SetLayerOffset(nLayerBackground2, { fAngle * 0.2f, fAngle * 0.2f });
		SetLayerOffset(nLayerBackground3, { fAngle * 0.1f, fAngle * 0.1f });

		fAngle += fElapsedTime * 0.1f;
		DrawRotatedDecal({ float(GetMouseX()), float(GetMouseY())}, decImage, fAngle, {sprImage->width / 2.0f, sprImage->height / 2.0f}, { 0.1f, 0.1f });
		DrawRotatedDecal({ float(GetMouseX()), float(GetMouseY())}, decImage, -fAngle, {sprImage->width / 2.0f, sprImage->height / 2.0f}, { 0.1f, 0.1f });

		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(192, 108, 10, 10, false, false))
		demo.Start();

	return 0;
}
