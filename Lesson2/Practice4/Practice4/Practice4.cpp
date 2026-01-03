#include <iostream>
#include <vector>

struct File
{
    std::string name;
    bool is_dir;
    std::vector<File*> children;
};

struct File_system 
{
private:
    File* root;
    File* cwd;
public:
    File_system() {
        root = new File{ "/", true, {} };
        cwd = root;
    }
    File* find(const std::string& path) {
        if (path[0] == '/') {
            return find_impl(root, path.substr(1));
        }
        else {
            return find_impl(cwd, path);
        }
    }

private:
    File* find_impl(File* directory, const std::string& path) {
        if (path.empty())
            return directory;
        auto sep = path.find('/');
        std::string current_path = sep == std::string::npos ? path : path.substr(0, sep);
        std::string rest_path = sep == std::string::npos ? "" : path.substr(sep + 1);

    }
};


int main()
{
    std::cout << "Hello World!\n";
}
