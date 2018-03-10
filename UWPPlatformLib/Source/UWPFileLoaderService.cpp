#include "UWPFileLoaderService.h"
#include "File.h"
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

	std::unique_ptr<IFile> UWPFileLoaderService::Load(const std::string& i_ofilePath) const
	{
		std::unique_ptr<File> poFile = std::make_unique<File>();
		bool bLoadFinished = false;

		auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wFilePath = converter.from_bytes(i_ofilePath);

		create_task(folder->GetFileAsync(Platform::StringReference(wFilePath.c_str()))).then([](StorageFile^ file)
		{
			return FileIO::ReadBufferAsync(file);
		}, task_continuation_context::use_arbitrary())
		.then([&poFile, &bLoadFinished](Streams::IBuffer^ fileBuffer)
		{
			poFile->GetData().resize(fileBuffer->Length);
			Streams::DataReader::FromBuffer(fileBuffer)->ReadBytes(Platform::ArrayReference<byte>(poFile->GetData().data(), fileBuffer->Length));
			bLoadFinished = true;
		}, task_continuation_context::use_arbitrary());

		while (!bLoadFinished);

		return poFile;
	}
}