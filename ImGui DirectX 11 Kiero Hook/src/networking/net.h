#ifndef NET_H
# define NET_H

#include <curl/curl.h>
#include <iostream>
#include <fstream>

class NetworkManager {
public:
	NetworkManager();
	~NetworkManager();
	std::string DownloadTextFile(std::string url, std::string outputPath); // returns the content as a string and still saves it to the specified location
private:
	CURL* _curl;
};

#endif