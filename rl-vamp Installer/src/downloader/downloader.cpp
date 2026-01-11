#include "downloader.h"

Downloader::Downloader() {
	_localUsername.resize(UNLEN + 1);
	DWORD size = UNLEN + 1;
	GetUserName(_localUsername.data(), &size);
	_localUsername.resize(size - 1);
	this->_bakkesmodLocation = std::string(R"(C:\Users\)") + this->_localUsername + R"(\AppData\Roaming\bakkesmod\bakkesmod\plugins\)";

	DownloadItem releaseVer;
	releaseVer.url = "https://github.com/hindsighttt/rl-vamp/releases/download/v1.0.1/rl-vamp_Release.dll";
	releaseVer.filename = "rl-vamp_Release.dll";

	DownloadItem debugVer;
	debugVer.url = "https://github.com/hindsighttt/rl-vamp/releases/download/v1.0.1/rl-vamp_Debug.dll";
	debugVer.filename = "rl-vamp_Debug.dll";

	this->_downloadItem.push_back(releaseVer);
	this->_downloadItem.push_back(debugVer);
}

Downloader::~Downloader() {
	for (auto& item : this->_downloadItem) {
		if (item.threadHandle) {
			WaitForSingleObject(item.threadHandle, INFINITE);
			CloseHandle(item.threadHandle);
			item.threadHandle = nullptr;
		}
	}
	std::cout << "[Downloader::~Downloader]: The installation process is done!" << std::endl;
}

DWORD WINAPI Downloader::DownloadSingleItem(LPVOID item) {
	DownloadItem* downloadItem = reinterpret_cast<DownloadItem*>(item);

	NetworkManager downloadHandle;
	downloadHandle.DownloadTextFile(downloadItem->url, downloadItem->outputPath + downloadItem->filename);

	return 0;
}

void Downloader::RunDownloadAsync() {
	for (size_t i = 0; i < this->_downloadItem.size(); i++) {
		std::cout << "[Downloader::DownloadSingleItem]: Downloading " << this->_downloadItem[i].filename << " from " << this->_downloadItem[i].url << std::endl;
		this->_downloadItem[i].outputPath = this->_bakkesmodLocation;
		this->_downloadItem[i].threadHandle = CreateThread(NULL, 0, DownloadSingleItem, (LPVOID)(&this->_downloadItem[i]), 0, NULL);
	}
}
