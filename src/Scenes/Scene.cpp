#include "Scene.h"
#include <stdexcept>

#include <Scenes/HUD.h>
#include <Scenes/Layers/Layer.h>

namespace Tristeon
{
	REGISTER_TYPE_CPP(Scene)

	Scene::Scene()
	{
		camera = std::make_unique<Camera>();
		hud = std::make_unique<HUD>();
	}

	json Scene::serialize()
	{
		json j;
		j["typeID"] = TRISTEON_TYPENAME(Scene);
		j["camera"] = camera->serialize();
		j["hud"] = hud->serialize();

		json serializedLayers = json::array_t();
		for (auto& layer : layers)
			serializedLayers.push_back(layer->serialize());
		j["layers"] = serializedLayers;
		return j;
	}

	void Scene::deserialize(json j)
	{
		camera->deserialize(j["camera"]);
		hud->deserialize(j["hud"]);

		layers.clear(); //TODO: Could detect and reuse existing layers as opposed to clearing every time
		for (auto serializedLayer : j["layers"])
		{
			Unique<Serializable> serializable = TypeRegister::createInstance(serializedLayer["typeID"]);
			serializable->deserialize(serializedLayer);
			layers.push_back(Unique<Layer>((Layer*)serializable.release()));
		}
	}

	Layer* Scene::getLayer(unsigned int const& index) const
	{
		if (index < 0 || index > layers.size() - 1)
			throw std::invalid_argument("Index must be more than 0 and less than the amount of layers");

		return layers[index].get();
	}

	Layer* Scene::findLayer(std::string const& name) const
	{
		for (const auto& layer : layers)
		{
			if (layer->name == name)
				return layer.get();
		}
		return nullptr;
	}

	Layer* Scene::addLayer(String const& type)
	{
		Unique<Serializable> serializable = TypeRegister::createInstance(type);
		auto* layer = dynamic_cast<Layer*>(serializable.get());
		if (layer != nullptr)
		{
			layer = (Layer*)serializable.release();
			layers.push_back(std::unique_ptr<Layer>(layer));
			return layer;
		}
		return nullptr;
	}

	unsigned int Scene::getLayerCount() const
	{
		return layers.size();
	}

	void Scene::destroyLayer(Layer* layer)
	{
		int const index = indexOf(layer);
		if (index == -1)
			return;
		layers[index].reset();
		layers.removeAt(index);
	}

	HUD* Scene::getHUD() const
	{
		return hud.get();
	}

	Camera* Scene::getCamera() const
	{
		return camera.get();
	}

	void Scene::setIndex(Layer* layer, int const& i)
	{
		int const old = indexOf(layer);
		if (old == -1)
			return;

		auto unique = std::move(layers[old]);
		layers.removeAt(old);
		layers.insert(layers.begin() + i, std::move(unique));
	}

	int Scene::indexOf(Layer* layer)
	{
		for (size_t i = 0; i < layers.size(); i++)
		{
			if (layers[i].get() == layer)
			{
				return i;
			}
		}
		return -1;
	}
}
