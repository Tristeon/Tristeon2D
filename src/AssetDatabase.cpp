#include <AssetDatabase.h>

#include <QFileSystemModel>
#include <QFile>

#include <Serialization/JsonSerializer.h>

namespace Tristeon
{
	std::map<String, Vector<String>> AssetDatabase::assets;

	void AssetDatabase::add(String const& path)
	{
		QFile const file{ QString(path.c_str()) };
		QFileInfo const info{ file };

		String const suffix = info.suffix().toStdString();
		
		if (assets.find(suffix) == assets.end())
			assets[suffix] = Vector<String>();

		if (!assets[suffix].contains(path))
			assets[suffix].push_back(path);
	}

	void AssetDatabase::remove(String const& path)
	{
		QFile const file{ QString(path.c_str()) };
		QFileInfo const info{ file };

		if (assets.find(info.suffix().toStdString()) == assets.end())
			assets[info.suffix().toStdString()] = Vector<String>();
		assets[info.suffix().toStdString()].remove(info.path().toStdString());
	}

	Vector<String> AssetDatabase::get(String const& extension)
	{
		if (assets.find(extension) != assets.end())
			return assets[extension];
		return Vector<String>();
	}

	String AssetDatabase::findByName(String const& name)
	{
		for (auto pair : assets)
		{
			for (String path : pair.second)
			{
				QFile const file{ QString(path.c_str()) };
				QFileInfo info{ file };

				if (info.baseName().toStdString() == name)
					return path;
			}
		}
		return "";
	}

	String AssetDatabase::findByName(String const& name, String const& extension)
	{
		Vector<String> paths = get(extension);
		for (String path : paths)
		{
			QFile const file{ QString(path.c_str()) };
			QFileInfo info{ file };

			if (info.baseName().toStdString() == name)
				return path;
		}

		return "";
	}

	void AssetDatabase::save()
	{
		json j = json::array_t();

		for(auto const& asset : assets)
		{
			json subJ;
			subJ["name"] = asset.first;
			
			json contents = json::array_t();
			for (auto const& filepath : asset.second)
				contents.push_back(filepath);
			
			subJ["contents"] = contents;

			j.push_back(subJ);
		}

		JsonSerializer::save("Project/AssetDatabase.json", j);
	}

	void AssetDatabase::load()
	{
		assets.clear();
		detectAll();
		//if (!QFile::exists("Project/AssetDatabase.json"))
		//{
		//	detectAll();
		//}
		//else
		//{
		//	json j = JsonSerializer::load("Project/AssetDatabase.json");

		//	for (auto item : j)
		//	{
		//		assets[item["name"]] = Vector<String>();

		//		for (auto const& path : item["contents"])
		//		{
		//			assets[item["name"]] = path;
		//		}
		//	}
		//}
	}

	void AssetDatabase::detectAll()
	{
		QDir const dir = QDir("Project");
		readDir(dir);
	}

	void AssetDatabase::readDir(QDir const& dir)
	{
		for (auto const& entry : dir.entryInfoList())
		{
			if (entry.isDir())
			{
				if (entry.fileName() == "." || entry.fileName() == ".." || entry.fileName().toLower().contains("tmp"))
					continue;
				std::cout << "Path: " << entry.filePath().toStdString() << std::endl;
				readDir(entry.filePath());
			}
			else
			{
				if (assets.find(entry.suffix().toStdString()) == assets.end())
					assets[entry.suffix().toStdString()] = Vector<String>();

				assets[entry.suffix().toStdString()].push_back(entry.filePath().toStdString());
			}
		}
	}
}