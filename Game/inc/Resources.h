#pragma once

#include <string>

#include "HashMap.h"

enum class ResourceGroup
{
	Game,
	Title,
	Play,
	MAX
};

namespace Gdiplus
{
	class Bitmap;
}

class Resources
{
private:
	HashMap<Gdiplus::Bitmap*> images_map[(int)ResourceGroup::MAX];

private:
	Resources() = default;

public:
	static Resources& GetInstance();

public:
	void AddImage(const std::string& name, Gdiplus::Bitmap* image, ResourceGroup group);
	Gdiplus::Bitmap* GetImage(const std::string& name, ResourceGroup group);

public:
	void ReleaseResources(ResourceGroup group);
};