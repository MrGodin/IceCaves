#include "GuiInputBox.h"

HRESULT GuiInputBox::Rasterize()
{
	DrawFrame();
	for (UINT i = 0; i < children.size(); i++)
	{
		GuiFrame* frm = (GuiFrame*)children[i];
		if (frm)
			frm->Rasterize();
	}
	return S_OK;
};
bool  GuiInputBox::OnKeyPress(GuiControl::GuiEvent& Event)
{
	int len = text.Length();
	
		if (len > 0)
		{
			if (Event.Key == VK_RETURN)
			{
				Event.Action = BTN_OK;
				Event.Sender = this;
				return true;
			}
		}
		if (Event.Key == VK_BACK)// backspace
		{

			if (len > 0)
			{
				char t[512];
				strncpy_s(t, text.c_str(), len - 1);
				text = t;
				pText->SetText(text.w_char());
			}
		}
		else
		{
			if (len >= maxPlayerNameLength - 1)
			{
				return false;
			}
			TString temp = TString(GetChar(Event.Key));
			if (temp.Length())
			{
				text += temp;
				
				pText->SetText(text.w_char());
			}

		}
		
		return false;
}
void  GuiInputBox::Create()
{
	GuiFrameDesc desc = frameDesc;
	desc.type = GUIOBJECT_UNDEFINED;
	AddChild(new GuiText(frameDesc, L"", TEXTALIGN_LEFT, 16));
	pText = (GuiText*)GetLastChild();
	pText->SetFont(pFont);
	pText->SetColor(Color(255, 0, 0, 0));
};
TString GuiInputBox::GetChar(WPARAM key)
{
	switch (key)
	{
	case 'A':
		return "A";
	case 'B':
		return "B";
	case 'C':
		return "C";
	case 'D':
		return "D";
	case 'E':
		return "E";
	case 'F':
		return "F";
	case 'G':
		return "G";
	case 'H':
		return "H";
	case 'I':
		return "I";
	case 'J':
		return "J";
	case 'K':
		return "K";
	case 'L':
		return "L";
	case 'M':
		return "M";
	case 'N':
		return "N";
	case 'O':
		return "O";
	case 'P':
		return "P";
	case 'Q':
		return "Q";
	case 'R':
		return "R";
	case 'S':
		return "S";
	case 'T':
		return "T";
	case 'U':
		return "U";
	case 'V':
		return "V";
	case 'W':
		return "W";
	case 'X':
		return "X";
	case 'Y':
		return "Y";
	case 'Z':
		return "Z";
	case '?':
		return "?";
	case '1':
		return "1";
	case '2':
		return "2";
	case '3':
		return "3";
	case '4':
		return "4";
	case '5':
		return "5";
	case '6':
		return "6";
	case '7':
		return "7";
	case '8':
		return "8";
	case '9':
		return "9";
	case '_':
		return "_";
	case VK_SPACE:
		return " ";
	default:
		return "";
	}
}