#include "main.h"
#include "../AppDelegate.h"
#include "BlockManager.h"
//#include "BgaManager.h"
#include "AttackManager.h"
#include "MouseManager.h"
#include "ItemManager.h"
#include "EnemyManager.h"
#include "ResourceManager.h"
#include "RenderingManager.h"
#include "ObjectCore.h"
#include "SoundManager.h"

HINSTANCE g_hInstance;
ObjectCore* ObjectCore::instance = NULL;
SoundManager* SoundManager::instance = NULL;
BlockManager* BlockManager::instance = NULL;
ResourceManager* ResourceManager::instance = NULL;
RenderingManager* RenderingManager::instance = NULL;
EnemyManager* EnemyManager::instance = NULL;
ItemManager* ItemManager::instance = NULL;
MouseManager* MouseManager::instance = NULL;
//BgaManager* BgaManager::instance = NULL;
AttackManager* AttackManager::instance = NULL;

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	g_hInstance = hInstance;

	int nRet = 0;
	AppDelegate app;
	nRet = app.Run();

	return nRet;
}
