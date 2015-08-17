
#pragma once
#include "keyboardController.h"
#include "Player.h"
class PlayerControl : public KBControl
{
public:
	PlayerControl()
		:
		KBControl()
	{}
	void Poll(Player* player)
	{
		if (IsUpPressed())
		{
			player->SetImageindex(24);
			player->GetState()->OnCtrlJumpPress();
		}
		if (IsLeftPressed())
		{
			player->SetImageindex(26);
			player->GetState()->OnCtrlDirChange(TDirection::Left());
		}
		if (IsRightPressed())
		{
			player->SetImageindex(25);
			player->GetState()->OnCtrlDirChange(TDirection::Right());
		}
		if (IsKeyLastUp(VK_LEFT) || IsKeyLastUp(VK_RIGHT) || IsKeyLastUp(VK_UP))
		{
			if (IsKeyLastUp(VK_UP))
				player->GetState()->OnCtrlJumpRelease();
			else
			    player->GetState()->OnCtrlDirRelease();
			lastKeyUp = 0x0;
			player->SetImageindex(23);
		}
		

	}
protected:
	bool IsUpPressed(){ return IsKeyDown(VK_UP); }
	bool IsDownPressed(){ return IsKeyDown(VK_DOWN); }
	bool IsLeftPressed(){ return IsKeyDown(VK_LEFT); }
	bool IsRightPressed(){ return IsKeyDown(VK_RIGHT); }
	bool IsSpacePressed(){ return IsKeyDown(VK_SPACE); }
	bool IsF1Pressed(){ return IsKeyDown(VK_F1); }
	bool IsF2Pressed(){ return IsKeyDown(VK_F2); }
	bool IsF3Pressed(){ return IsKeyDown(VK_F3); }
	bool IsF4Pressed(){ return IsKeyDown(VK_F4); }
	bool IsF5Pressed(){ return IsKeyDown(VK_F5); }
	bool IsF6Pressed(){ return IsKeyDown(VK_F6); }
	bool IsShiftPlus(UINT_PTR key){ return IsShiftDown() && IsKeyDown(key); }
	bool IsCtrlPlus(UINT_PTR key){ return IsCtrlDown() && IsKeyDown(key); }
};