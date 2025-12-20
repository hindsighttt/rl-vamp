#include "net.h"

static size_t CurlCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	size_t totalSize = size * nmemb;
	std::string* output = reinterpret_cast<std::string*>(userp);
	output->append(reinterpret_cast<char*>(contents), totalSize);
	return totalSize;
}

NetworkManager::NetworkManager() {
	CURL* curl = curl_easy_init();
	if (!curl)
		std::cerr << "[NetworkManager::NetworkManager]: Failed to initialize CURL" << std::endl;
	this->_curl = curl;
}

NetworkManager::~NetworkManager() {
	if (!this->_curl) {
		std::cerr << "[NetworkManager::~NetworkManager]: No CURL instance to clean" << std::endl;
		return;
	}
	curl_easy_cleanup(this->_curl);
}

std::string NetworkManager::DownloadTextFile(std::string url, std::string outputPath)
{
	if (!this->_curl) {
		std::cerr << "[NetworkManager::DownloadTextFile]: CURL was not initialized" << std::endl;
		return std::string();
	}
	curl_easy_reset(this->_curl);
	
	std::string content;
	curl_easy_setopt(this->_curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(this->_curl, CURLOPT_WRITEFUNCTION, CurlCallback);
	curl_easy_setopt(this->_curl, CURLOPT_WRITEDATA, &content);
	curl_easy_setopt(this->_curl, CURLOPT_FOLLOWLOCATION, 1L);

	CURLcode response = curl_easy_perform(this->_curl);
	if (response != CURLE_OK) {
		std::cerr << "[NetworkManager::DownloadTextFile]: " << curl_easy_strerror(response) <<std::endl;
		return std::string();
	}

	std::ofstream outputFile(outputPath);
	if (!outputFile.is_open()) {
		std::cerr << "[NetworkManager::DownloadTextFile]: Couldn't open output file for writing" << std::endl;
		return content;
	}
	outputFile.write(content.c_str(), content.length());
	outputFile.close();
	return content;
}
