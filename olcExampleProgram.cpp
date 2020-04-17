#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <stdio.h>
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>

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

	struct libevdev *dev = NULL;
	int fd;
	int rc = 1;

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
		for (auto i = 0; i < 30000; i++)
		{
			auto colour = rand() % 255;
			Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc::Pixel(colour, 0, 0, colour));
		}
		EnableLayer(nLayerBackground1, true);
		
		SetDrawTarget(nLayerBackground2);
		Clear(olc::BLANK);
		for (auto i = 0; i < 30000; i++)
		{
			auto colour = rand() % 255;
			Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc::Pixel(0, colour, 0, colour));
		}
		EnableLayer(nLayerBackground2, true);

		SetDrawTarget(nLayerBackground3);
		Clear(olc::BLANK);
		for (auto i = 0; i < 30000; i++)
		{
			auto colour = rand() % 255;
			Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc::Pixel(0, 0, colour, colour));
		}
		EnableLayer(nLayerBackground3, true);

		SetDrawTarget(nullptr);
		Clear(olc::BLANK);

		fd = open("/dev/input/event8", O_RDONLY | O_NONBLOCK);
		rc = libevdev_new_from_fd(fd, &dev);

		if (rc < 0) {
        	fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
        	exit(1);
		}

		printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
		printf("Input device ID: bus %#x vendor %#x product %#x\n",
		
		libevdev_get_id_bustype(dev),
		libevdev_get_id_vendor(dev),
		libevdev_get_id_product(dev));

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        if (rc == 0)
                printf("Event: %s %s %d\n",
                       libevdev_event_type_get_name(ev.type),
                       libevdev_event_code_get_name(ev.type, ev.code),
                       ev.value);

		SetLayerOffset(nLayerBackground1, { fAngle * 0.4f, fAngle * 0.4f });
		SetDrawTarget(nLayerBackground1);
		DrawRotatedDecal({ float(GetMouseX()), float(GetMouseY())}, decImage, fAngle, {sprImage->width / 2.0f, sprImage->height / 2.0f}, { 0.1f, 0.1f });

		SetLayerOffset(nLayerBackground2, { fAngle * 0.2f, fAngle * 0.2f });
		SetDrawTarget(nLayerBackground2);
		DrawRotatedDecal({ float(GetMouseX()), float(GetMouseY())}, decImage, fAngle + 45.0f, {sprImage->width / 2.0f, sprImage->height / 2.0f}, { 0.1f, 0.1f });

		SetLayerOffset(nLayerBackground3, { fAngle * 0.1f, fAngle * 0.1f });
		SetDrawTarget(nLayerBackground3);
		DrawRotatedDecal({ float(GetMouseX()), float(GetMouseY())}, decImage, fAngle + 90.0f, {sprImage->width / 2.0f, sprImage->height / 2.0f}, { 0.1f, 0.1f });

		fAngle += fElapsedTime * 0.1f;
		// DrawRotatedDecal({ float(GetMouseX()), float(GetMouseY())}, decImage, fAngle, {sprImage->width / 2.0f, sprImage->height / 2.0f}, { 0.1f, 0.1f });
		// DrawRotatedDecal({ float(GetMouseX()), float(GetMouseY())}, decImage, -fAngle, {sprImage->width / 2.0f, sprImage->height / 2.0f}, { 0.1f, 0.1f });

		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(256, 320, 4, 4, false, true))
		demo.Start();

	return 0;
}
