#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/DefaultScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/ChooseMap.h"
#include "Scenes/GameOverScene.h"

int main()
{
	const Engine* engine = Engine::GetInstance();

	engine->Init();

	SceneModule* scene_module = engine->GetModuleManager()->GetModule<SceneModule>();
	scene_module->SetScene<GameOver>();

	engine->Run();

	return 0;
}

