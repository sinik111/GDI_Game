#include "Resources.h"

#include <windows.h>
#include <gdiplus.h>

#include "DebugUtility.h"

Resources& Resources::GetInstance()
{
	static Resources instance;

	return instance;
}

void Resources::AddImage(const std::string& name, Gdiplus::Bitmap* image, ResourceGroup group)
{
	Gdiplus::Bitmap* dummy = nullptr;

	if (images_map[(int)group].Find(name, dummy))
	{
		DebugLog("이미 있는 이름입니다. %s - Resources::AddImage()", name.c_str());

		return;
	}

	images_map[(int)group].Insert(name, image);
}

Gdiplus::Bitmap* Resources::GetImage(const std::string& name, ResourceGroup group)
{
	Gdiplus::Bitmap* image = nullptr;

	if (!images_map[(int)group].Find(name, image))
	{
		DebugLog("없는 이름입니다. %s - Resources::GetImage()", name.c_str());

		return nullptr;
	}

	return image;
}

void Resources::ReleaseResources(ResourceGroup group)
{
	for (auto iter = images_map[(int)group].Begin(); !iter.IsEnd(); ++iter)
	{
		if (*iter != nullptr)
		{
			delete* iter;

			*iter = nullptr;
		}
	}

	images_map[(int)group].Clear();
}
