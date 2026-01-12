#include <iostream>
#include <unordered_map>

class URL {
private:
    std::unordered_map<std::string, std::string> urls;
public:
    std::pair<bool, std::string> lookup(const std::string& url) const {
        auto it = urls.find(url);
        if (it == urls.end())
            return std::make_pair(false, std::string());
        else
            return std::make_pair(true, it->second);
    }

    bool registerURL(const std::string& actual_url, const std::string& tiny_url) {
        auto found = lookup(tiny_url).first;

        if (found)
            return false;

        urls[tiny_url] = actual_url;
        return true;
    }

    bool deregisterURL(const std::string& tiny_url) {
        auto found = lookup(tiny_url).first;

        if (found) {
            urls.erase(tiny_url);
            return true;
        }
        return false;
    }

    void printURLs() const {
        for (const auto& url : urls) {
            std::cout << url.first << "->" << url.second << std::endl;
        }
        std::cout << std::endl;
    }
};

int main()
{
	URL service;

	if (service.registerURL("https://www.gilbut.co.kr/book/view?bookcode=BN002245", "https://py_dojang"))
	{
		std::cout << "https://py_dojang 등록" << std::endl;
	}
	else
	{
		std::cout << "https://py_dojang 등록 실패" << std::endl;
	}

	if (service.registerURL("https://www.gilbut.co.kr/book/view?bookcode=BN001484", "https://c_dojang"))
	{
		std::cout << "https://c_dojang 등록" << std::endl;
	}
	else
	{
		std::cout << "https://c_dojang 등록 실패" << std::endl;
	}

	if (service.registerURL("https://www.gilbut.co.kr/book/view?bookcode=BN002402", "https://opencv4"))
	{
		std::cout << "https://opencv4 등록" << std::endl;
	}
	else
	{
		std::cout << "https://opencv4 등록 실패" << std::endl;
	}

	auto pythonBook = service.lookup("https://py_dojang");
	if (pythonBook.first)
	{
		std::cout << "https://py_dojang 원본 URL: " << pythonBook.second << std::endl;
	}
	else
	{
		std::cout << "https://py_dojang 원본 URL을 찾을 수 없습니다." << std::endl;
	}

	auto cppBook = service.lookup("https://cpp_dojang");
	if (cppBook.first)
	{
		std::cout << "https://cpp_dojang 원본 URL: " << cppBook.second << std::endl;
	}
	else
	{
		std::cout << "https://cpp_dojang 원본 URL을 찾을 수 없습니다." << std::endl;
	}

	if (service.deregisterURL("https://c_dojang"))
	{
		std::cout << "c_dojang 책 URL 등록 해제" << std::endl;
	}
	else
	{
		std::cout << "c_dojang 책 URL 등록 해제 실패" << std::endl;
	}

	auto findQtBook = service.lookup("https://c_dojang");
	if (findQtBook.first)
	{
		std::cout << "https://c_dojang 원본 URL: " << findQtBook.second << std::endl;
	}
	else
	{
		std::cout << "https://c_dojang 원본 URL을 찾을 수 없습니다." << std::endl;
	}

	std::cout << "등록된 URL 리스트:" << std::endl;
	service.printURLs();
}


