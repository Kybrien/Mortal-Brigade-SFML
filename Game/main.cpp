#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/DefaultScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/ChooseMap.h"
#include "Scenes/Map1.h"
#include "Scenes/Map2.h"
#include "Scenes/SelectCharacter.h"
#include "Scenes/QuotasReached.h"
#include "Scenes/GameOver.h"

int main()
{
	const Engine* engine = Engine::GetInstance();

	engine->Init();

	SceneModule* scene_module = engine->GetModuleManager()->GetModule<SceneModule>();
	scene_module->SetScene<GameOver>();

	engine->Run();

	return 0;
}
