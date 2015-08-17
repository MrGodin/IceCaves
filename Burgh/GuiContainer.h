
#pragma once
#include "GuiButton.h"
enum{GuiAlign_Vertical = 0xff22,GuiAlign_Horizontal};
class GuiButtonContainer : public GuiControl
{
public:
	struct GuiContainerDesc
	{
		GuiFrameDesc frameDesc;
		UINT numbObjects = 0;
		long objWidth;
		long objHeight;
		long width;
		long height;
		Vec2L origin;
		long indent;
		UINT align = GuiAlign_Vertical;
	};
protected:
	GuiContainerDesc desc;
	UINT index = 0;
	int* placement;
public:
	void Create()
	{
		switch (desc.align)
		{
		case GuiAlign_Horizontal:
		{
			long start = desc.frameDesc.originX + desc.indent;
			desc.width = (desc.objWidth * desc.numbObjects) + (desc.indent * (desc.numbObjects)) + (desc.indent);
			desc.height = (desc.objHeight) + (desc.indent * 2);
			for (UINT c = 0; c < desc.numbObjects; c++)
			{
				placement[c] = start;
				start += desc.objWidth + desc.indent;
			}
		}
		break;
		case GuiAlign_Vertical:
		{
			long start = desc.frameDesc.originY + desc.indent;
			desc.height = (desc.objHeight * desc.numbObjects) + (desc.indent * (desc.numbObjects)) + (desc.indent);
			desc.width = (desc.objWidth) + (desc.indent * 2);
			for (UINT c = 0; c < desc.numbObjects; c++)
			{
				placement[c] = start;
				start += desc.objHeight + desc.indent;
			}

		}
		break;
		}
		GuiFrame* frm = (GuiFrame*)_parent;

		frameDesc.width = frm->Width() - 32;
		frameDesc.height = desc.height;
		frameDesc.originX = desc.frameDesc.originX;
		frameDesc.originY = desc.frameDesc.originY;
		
		

		Init();
	}
public:
	GuiButtonContainer(GuiContainerDesc d)
	:
	GuiControl(d.frameDesc),
	desc(d)
	{
		placement = new int[desc.numbObjects];
		
		//Create();
	}
	virtual ~GuiButtonContainer()
	{
		SAFE_DELETE_ARRAY(placement);
	}
	
	
	GuiObject* Add(GuiButton::GuiButtonDesc btnDesc )
	{
		btnDesc.frameDesc.height = desc.objHeight;
		btnDesc.frameDesc.width = desc.objWidth;
		switch (desc.align)
		{
			case GuiAlign_Horizontal:
			{
				btnDesc.frameDesc.originX = (long)placement[index];
				btnDesc.frameDesc.originY = desc.frameDesc.originY + desc.indent;
				index++;
			}
			break;
			case GuiAlign_Vertical:
			{
				btnDesc.frameDesc.originY = (long)placement[index];
				btnDesc.frameDesc.originX = desc.frameDesc.originX + desc.indent;
				index++;
			}
			break;
		}

		if (btnDesc.clientAlign == GuiClientAlignRight)
		{
			btnDesc.frameDesc.originX = (desc.frameDesc.originX + frameDesc.width) - (btnDesc.frameDesc.width + desc.indent);
		}
		
			AddChild(new GuiButton(btnDesc));
			GuiButton* btn = (GuiButton*)GetLastChild();
			btn->SetFont(pFont);
			return btn;
		

	}
	GuiObject* Child(UINT index)
	{
		if (GetChild(index))
			return GetChild(index);

		return NULL;
	}
	virtual bool OnMouseClick(GuiEvent& Event)
	{
		if (PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
		{
			GuiButton* btn = NULL;
			for (UINT i = 0; i < children.size(); i++)
			{

				if ((btn = (GuiButton*)GetChild(i)) != NULL)
				{
					if (btn->OnMouseClick(Event))
					{
						Event.Sender = btn;
						Event.Action = btn->GetAction();
						Event.Event = GuiEvent_Capture;
						return true;
					}
				}
			}
		}
		return false;
	}
	virtual bool OnMouseMove(GuiEvent& Event)
	{
		//desc.numbObjects;
		if (PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
		{
			GuiButton* btn = NULL;
			for (UINT i = 0; i < children.size(); i++)
			{

				if ((btn = (GuiButton*)GetChild(i)) != NULL)
					if (btn->OnMouseMove(Event))
					{
						Event.Sender = btn;
						
						return true;
					};

			}
		}
		return false;
	}
	virtual HRESULT Rasterize()
	{
		DrawFrame();
		GuiButton* btn = NULL;
		for (UINT i = 0; i < children.size(); i++)
		{

			if ((btn = (GuiButton*)GetChild(i)) != NULL)
				btn->Rasterize();

		}
			

		return S_OK;
	}

};