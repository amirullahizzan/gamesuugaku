#include "Main.h"
#include "Game.h"

int npc_image;
int npc_x;
int npc_y;

int mouse_x;
int mouse_y;

int click_count;


bool isMainMenu = true;
bool isGame = false;
bool isEndGame = false;

struct NPC
{
public:

	bool IsMouseHover()
	{
		if (mouse_x > npc_x && mouse_x < npc_x + 50 && mouse_y > npc_y && mouse_y < npc_y + 50)
		{
		return  true;
		}
		else
		{
		return false;
		}
	}

	void OnClick()
	{
		if (IsMouseHover() == true && PushMouseInput(0x0001))
		{
			npc_x = GetRand(SCREEN_W - 50);
			npc_y = GetRand(SCREEN_H - 50);
			click_count++;
		}
	}
		

};


void GameInit()
{

	mouse_x = 0;
	mouse_y = 0;
	click_count = 0;
	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 300;
	npc_y = 200;

}

struct UIManager 
{
	void DebugGrid()
	{
		DrawLine(0,SCREEN_H/2, SCREEN_W,SCREEN_H/2,GetColor(255,255,0),1);
		DrawLine(SCREEN_W/2,0, SCREEN_W/2,SCREEN_H,GetColor(255,255,0),1);
	}

	void DisplayMainMenu()
	{
		DrawString(SCREEN_W/2-60, (SCREEN_H/2)-20, "PepeSouls", GetColor(255, 255, 255));
		DrawString(SCREEN_W/2-100, (SCREEN_H/2)+80, "Press SPACE to play", GetColor(255, 255, 255));
	}
	
	void DisplayScore()
	{
		DrawFormatString(SCREEN_W/2-70, SCREEN_H/2, GetColor(255, 0, 0),"あなたのスコア : %d", click_count);
	}

};

struct Timer
{

	int timerms = 0;
	int timersec = 0;
	int timelimit = 10;

	int msTick()
	{
		timerms++;
		return timerms;
	}

	int secTick()
	{
		if (msTick() > 60) //automatically runs the msTick to get the value!
		{
			timersec++;
			timerms = 0;
			timelimit--;
			return timersec;
		}
	}

	void TimeOutHandler()
	{
		if (timelimit < 1)
		{
			isGame = false;
			isEndGame = true;
		}
	}

	

	void DisplayTimer()
	{
		DrawFormatString(20, 60, GetColor(255, 255, 0), "Time Elapsed 経った時間 %2d:%2d", timersec, timerms);
		DrawFormatString(20, 80, GetColor(255, 255, 0), "Time Remaining 残り時間 %2d", timelimit);
	}
};

UIManager uimanager;
Timer timer;



void GameUpdate()
{
	if (isMainMenu)
	{
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			isMainMenu = false;
			isGame = true;
		}

	}
	if (isGame)
	{
		NPC npc;
		GetMousePoint(&mouse_x, &mouse_y);
		npc.OnClick();
		
		timer.secTick();
		timer.TimeOutHandler();
	}

	

	//if(PushMouseInput(0x0001))
	// 
	//int mouse_x = GeMouseX();
	//int mouse_y = GeMouseY();
	


}


void GameRender()
{
	uimanager.DebugGrid();

	if (isMainMenu)
	{
		uimanager.DisplayMainMenu();
	}
	if (isGame)
	{
		DrawGraph(npc_x, npc_y, npc_image, TRUE);

		DrawString(20, 20, "ＮＰＣクリック：座標をランダムに設定", GetColor(255, 255, 255));
		DrawFormatString(20, 40, GetColor(255, 255, 255), "NPC クリック回数 %d", click_count);

		timer.DisplayTimer();

	}
	if (isEndGame)
	{
		uimanager.DisplayScore();
	}
}


void GameExit()
{
	DeleteGraph( npc_image );
}
