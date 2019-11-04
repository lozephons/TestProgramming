
#include "FrameBuffer.h"
#include <math.h>

#include "SphereData.h"

struct Vec3
{
	double x, y, z;

	Vec3 normalize()
	{
		double d = sqrt(x * x + y * y + z * z);
		Vec3 vec;
		vec.x = x / d;
		vec.y = y / d;
		vec.z = z / d;
		return vec;
	}
};

// Global light
Vec3 Light;

//////////////////////////////////////////////////////////////////////////

CFrameBuffer::CFrameBuffer(const int iWidth, const int iHeight)
	:m_iWidth(iWidth), m_iHeight(iHeight)
{
	m_FramebufferArray.resize(iWidth * iHeight, 0);

	Light.x = 1.f;
	Light.y = -0.5f;
	Light.z = 0.7f;
	Light = Light.normalize();
}

CFrameBuffer::~CFrameBuffer()
{

}

void CFrameBuffer::Clear()
{
	memset(&m_FramebufferArray[0], 0, m_iWidth * m_iHeight * 4);

	Light.x -= 0.02f; // some light animation
	Light = Light.normalize();
}

const unsigned int* CFrameBuffer::GetFrameBuffer() const
{
	return static_cast<const unsigned int*>(&m_FramebufferArray[0]);
}

void CFrameBuffer::renderFrameBuffer(std::vector<SSphereElement>& rSpheres)
{
	for (auto& SphereElement : rSpheres)
	{
		RenderSphere(SphereElement.screenX, SphereElement.screenY, SphereElement.screenZ, SphereElement.screenRadius, SphereElement.dwARGB);
	}
}

void CFrameBuffer::RenderSphere(float fScreenX, float fScreenY, float fScreenZ, float fScreenRadius, unsigned int ARGB)
{
	float centerX = fScreenX * m_iWidth / 2 + m_iWidth / 2;
	float centerY = fScreenY * m_iWidth / 2 + m_iWidth / 2;

	float RX = fScreenRadius * m_iWidth / 2;
	float RY = fScreenRadius * m_iWidth / 2;

	for (int x = centerX - RX * 2; x <= centerX + RX * 2; ++x)
	{
		for (int y = centerY - RY * 2; y <= centerY + RY * 2; ++y)
		{
			int dx = x - centerX;
			int dy = y - centerY;

			if (dx * dx + dy * dy > RX* RY)
				continue;
			if (y < 0 || y >= m_iHeight)
				continue;
			if (x < 0 || x >= m_iWidth)
				continue;

			m_FramebufferArray[x + y * m_iWidth] = ARGB;
		}
	}
}
