#include "Core/Debug.h"
#include "Math/Math.h"

using namespace PIXL;
using namespace debugging;
using namespace math;

static const int INVALID_ARGUMENT = 1;

int main()
{
	Vector2 v2 = Vector2::One();

	Debug::logError("main.cpp",v2.ToString().c_str());

	return 0;
}