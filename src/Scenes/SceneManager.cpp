#include "SceneManager.h"

#include <Collector.h>
#include <Engine.h>
#include <Settings.h>
#include <AssetManagement/Domains/Domain.h>

#include <Callbacks/IInit.h>
#include <Callbacks/ISceneLoaded.h>

#include <Scenes/Scene.h>
#include <Serialization/JsonSerializer.h>
#include "AssetManagement/AssetDatabase.h"

namespace Tristeon
{
	std::unique_ptr<Scene> SceneManager::_current = nullptr;
	String SceneManager::_cachedName;
	json SceneManager::_cachedData;

	Scene* SceneManager::current()
	{
		return _current.get();
	}

	void SceneManager::load(const String& name)
	{
		_cachedName = name;
		_cachedData = {}; //Reset cached data because now this function has precedence 
	}

	void SceneManager::load(const json& data)
	{
		if (data.empty())
			throw std::invalid_argument("The scene's json data can't be empty");
		
		_cachedData = data;
		_cachedName = ""; //Reset cached name because now this function has precedence
	}

	void SceneManager::reload()
	{
		load(_current->_name);
	}

	void SceneManager::save(Scene* scene, const String& filepath)
	{
		if (scene == nullptr)
			throw std::invalid_argument("Scene can't be nullptr!");
		
		if (filepath.empty())
			throw std::invalid_argument("Filepath can't be empty!");

		auto const data = scene->serialize();
		JsonSerializer::save(Domain::resolve(filepath), data);

		AssetDatabase::add(filepath);
	}

	void SceneManager::saveCurrent()
	{
		if (current()->path().empty())
		{
			TRISTEON_WARNING("Current scene doesn't have a path therefore it can't be saved automatically. Use save(current(), filePath) instead");
			return;
		}
		save(current(), current()->path());
	}

	void SceneManager::processCachedLoad()
	{
		json toLoad;
		String path;
		
		if (!_cachedData.empty())
		{
			toLoad = _cachedData;
			path = _cachedData.value("path", "");
		}
		else if (!_cachedName.empty())
		{
			path = AssetDatabase::find(_cachedName, ".scene");
			if (path.empty())
			{
				TRISTEON_WARNING("Couldn't find scene: " + _cachedName);
				_current.reset();
				_current = std::make_unique<Scene>(); // load empty scene
				postLoad();
				return;
			}
			toLoad = JsonSerializer::load(path);
		}
		else //Don't load a scene if there's nothing to load
		{
			return;
		}

		_current = std::make_unique<Scene>();
		_current->deserialize(toLoad);
		_current->_name = _cachedName;
		_current->_path = path;

		postLoad();
	}

	void SceneManager::postLoad()
	{
		if (Engine::playMode())
		{
			for (auto* init : Collector<IInit>::all()) init->init();
			current()->safeCleanup();
		}

		for (auto* loaded : Collector<ISceneLoaded>::all()) loaded->sceneLoaded(_current.get());
		current()->safeCleanup();

		_cachedName = "";
		_cachedData = json();
	}

	void SceneManager::reset()
	{
		_current.reset();
	}
}