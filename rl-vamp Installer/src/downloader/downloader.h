#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "../networking/net.h"
#include <windows.h>
#include <Lmcons.h>
#include <deque>
#include <string>

typedef struct DownloadItem {
	HANDLE threadHandle;
	std::string url;
	std::string filename;
	std::string outputPath; // because cannot pass the class members in the thread
};

class Downloader {
public:
	Downloader();
	~Downloader();
public:
	static DWORD WINAPI DownloadSingleItem(LPVOID item);
	void RunDownloadAsync();
private:
	std::string _bakkesmodLocation;
	std::string _localUsername;
	std::deque<DownloadItem> _downloadItem;
};

#endif