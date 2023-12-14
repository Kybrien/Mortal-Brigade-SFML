#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/DefaultScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/ChooseMap.h"

int main()
{
	const Engine* engine = Engine::GetInstance();

	engine->Init();

	SceneModule* scene_module = engine->GetModuleManager()->GetModule<SceneModule>();
	scene_module->SetScene<ChooseMap>();

	engine->Run();

	return 0;
}
