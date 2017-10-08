#include "UWPFileLoaderService.h"
#include <ppltasks.h>
#include <locale>
#include <codecvt>
#include <string>

using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Concurrency;

namespace GT
{
	UWPFileLoaderService::UWPFileLoaderService()
	{
		//Nothing to do here
	}

	UWPFileLoaderService::~UWPFileLoaderService()
	{
		//Nothing to do here
	}

	void UWPFileLoaderService::Load(const std::string& i_ofilePath, std::vector<uint8_t>& o_oFileData) const
	{
		bool bLoadFinished = false;

		auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wFilePath = converter.from_bytes(i_ofilePath);

		create_task(folder->GetFileAsync(Platform::StringReference(wFilePath.c_str()))).then([](StorageFile^ file)
		{
			return FileIO::ReadBufferAsync(file);
		})
		.then([&o_oFileData, &bLoadFinished](Streams::IBuffer^ fileBuffer)
		{
			o_oFileData.resize(fileBuffer->Length);
			Streams::DataReader::FromBuffer(fileBuffer)->ReadBytes(Platform::ArrayReference<byte>(o_oFileData.data(), fileBuffer->Length));
			bLoadFinished = true;
		});

		while (!bLoadFinished);
	}
}