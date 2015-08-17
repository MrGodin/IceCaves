
#include "GuiFrame.h"

class BackGround : public GuiFrame
{
public:
	BackGround(GuiFrameDesc desc)
		:
		GuiFrame(desc)
	{

	}
	virtual void SetColor(const QuadVertexColors c)override
	{
		frameDesc.baseColor = c;
	}
	virtual HRESULT Rasterize()
	{
		DrawFrame();
		return S_OK;
	}
	void Redraw(long vpX,long vpY,long screenHeight, long screenWidth)
	{
		frameDesc.originX = vpX;
		frameDesc.originY = vpY;
		frameDesc.width = screenWidth;
		frameDesc.height = screenHeight;
		Init();
	}
	void SetBorderColor(QuadVertexColors c)
	{
		frameDesc.innerBorderColor = frameDesc.outerBorderColor = c;
	}
	void Update(float dt)
	{
		static bool flip = false;
		dt *= 0.01f;
		if (frame[0].tu > 1.0f)
		{
			flip = true;
		}
		if (frame[0].tu < 0.0f)
		{
			flip = false;
		}

		if (flip)
		{
			frame[0].tu -= dt;
			frame[0].tv -= dt;
			frame[1].tu += dt;
			frame[1].tv -= dt;
			frame[2].tu -= dt;
			frame[2].tv += dt;
			frame[3].tu += dt;
			frame[3].tv += dt;
		}
		else
		{
			frame[0].tu += dt;
			frame[0].tv += dt;
			frame[1].tu -= dt;
			frame[1].tv += dt;
			frame[2].tu += dt;
			frame[2].tv -= dt;
			frame[3].tu -= dt;
			frame[3].tv -= dt;
		}

		/*
		*/
	}
};