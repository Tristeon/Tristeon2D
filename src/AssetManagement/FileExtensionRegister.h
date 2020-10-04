﻿#pragma once
#include "MetaFiles/MetaFile.h"
#include "Serialization/Register.h"

namespace Tristeon
{
	template<typename T>
	class FileExtensionRegister : Register<MetaFile>
	{
	public:
		FileExtensionRegister(String fileExtension)
		{
			getMap()->emplace(fileExtension,&CreateInstance<T,MetaFile>);
		}
	};

#define FILE_EXTENSION_TYPE(type,extension) static const FileExtensionRegister<type> extensionRegister_##type(extension)
}
