#pragma once

#include "SinglyLinkedList.h"

namespace Gdiplus
{
	class Bitmap;
}

class Resources
{
private:
	SinglyLinkedList<Gdiplus::Bitmap*> images;


};