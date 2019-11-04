#include "FrameBuffer.h"
#include "SphereData.h"

#include <stdio.h>
#include <math.h>
#include <algorithm>

CSphereData::CSphereData(const char* szFilename)
{
	FILE* in;
	fopen_s(&in, szFilename, "rb");

	int num = 0;
	srand(1);
	for (;;)
	{
		SSphereElement el;

		if (fscanf_s(in, "%f %f %f", &el.x, &el.y, &el.z) != 3)
			break;

		el.y -= 60;
		el.z -= 50;

		el.x *= 0.01f;
		el.y *= 0.01f;
		el.z *= 0.01f;

		el.r = 5.0f + 5.0f * (rand() % 1024) / 1024.0f;
		el.r *= 0.004f;
		el.dwARGB = rand() & 0xff;
		el.dwARGB = (el.dwARGB << 8) | (rand() & 0xff);
		el.dwARGB = (el.dwARGB << 8) | (rand() & 0xff);

		m_SphereData.push_back(el);
		//if (num++ > 100) break;
	}

	fclose(in);
}

CSphereData::~CSphereData()
{

}

void CSphereData::Render(CFrameBuffer* fb, float wi)
{
	std::vector<SSphereElement>::iterator it, end = m_SphereData.end();

	float s = sin(wi);
	float c = cos(wi);

	for (it = m_SphereData.begin(); it != end; ++it)
	{
		SSphereElement& ref = *it;
		ref.screenZ = ref.x * c + ref.z * s;

		float fX = ref.x * s - ref.z * c;
		float fY = ref.y;	// we rotate spheres only for y-axis
		float fZ = ref.screenZ;

		fZ += 1.5f;

		if (fZ < 0.001f)
			continue;

		float fScreenX = fX / fZ;
		float fScreenY = fY / fZ;
		float fScreenZ = fZ;
		float fScreenRadius = ref.r / fZ;

		// store the screen information for using in render pass
		ref.screenX = fScreenX;
		ref.screenY = fScreenY;
		ref.screenZ = fScreenZ;
		ref.screenRadius = fScreenRadius;
	}

	fb->renderFrameBuffer(m_SphereData);
}