#pragma once

#include <vector>
#include <map>

struct SSphereElement;

class CFrameBuffer
{
public:
	CFrameBuffer(const int iWidth, const int iHeight);
	~CFrameBuffer();

	void Clear();

	//! \param fScreenX [-1..1]
	//! \param fScreenY [-1..1]
	//! \param fScreenZ [0..1]
	//! \param fScreenRadius >0 (-1..1 = 2 means full screen)
	void RenderSphere(float fScreenX, float fScreenY, float fScreenZ, float fScreenRadius, unsigned int ARGB);

	const unsigned int* GetFrameBuffer() const;

	int GetWidth() const { return m_iWidth; }
	int GetHeight() const { return m_iHeight; }

	// render pass for spheres
	void renderFrameBuffer(std::vector<SSphereElement>& rSpheres);

private:
	std::vector<unsigned int> m_FramebufferArray;

	int m_iWidth, m_iHeight;
};
