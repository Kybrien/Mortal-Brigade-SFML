#pragma once
#include <vector>

#include "Module.h"
#include "Scene.h"
#include "TimeModule.h"
#include "WindowModule.h"

class SceneModule final : public Module
{
public:
	SceneModule();
	~SceneModule() = default;

	void Start() override;
	void Render() override;
	void RenderGui() override;
	void Update() override;

	template<typename T>
	Scene* SetScene(bool _replace_scenes = true);

	Scene* GetMainScene() const { return mainScene; }
	Scene* GetScene(const std::string& _scene_name) const;
	bool SetMainScene(const std::string& _scene_name);
	bool RemoveScene(const std::string& _scene_name);

private:
	std::vector<Scene*> scenes;
	Scene* mainScene = nullptr;

	WindowModule* windowModule = nullptr;
	TimeModule* timeModule = nullptr;
};

template<typename T>
Scene* SceneModule::SetScene(const bool _replace_scenes)
{
	if (_replace_scenes)
	{
		for (Scene* scene : scenes)
		{
			scene->MarkForDeletion();
		}
		
	}
	//scenes.clear();
	Scene* scene = static_cast<Scene*>(new T());
	scenes.push_back(scene);

	if (_replace_scenes)
		mainScene = scene;

	return scene;
}