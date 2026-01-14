#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

class Student {
  private:
    std::pair<int, int> name;
    bool vaccinated;

  public:
    Student(std::pair<int, int> _name, bool _vaccinated) : name(_name), vaccinated(_vaccinated) {}

    std::pair<int, int> get_name() { return name; }
    bool is_vaccinated() { return vaccinated; }

    bool operator==(const Student& p) const {
        return this->name == p.name;
    }
    bool operator<(const Student& p) const {
        return this->name < p.name;
    }
    bool operator> (const Student& p) const {
        return this->name > p.name;
    }
};

auto generate_random_Student(int max)
{
    std::random_device rd;
    std::mt19937 rand(rd());

    // 학생 ID 범위는 [1, max]로 지정
    std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, max);

    // 임의의 학생 정보 생성
    auto random_name = std::make_pair(uniform_dist(rand), uniform_dist(rand));
    bool is_vaccinated = uniform_dist(rand) % 2 ? true : false;

    return Student(random_name, is_vaccinated);
}

bool needs_vaccination(Student p, std::vector<Student>& people) {
    auto first = people.begin();
    auto last = people.end();

    while (true) {
        int distance = std::distance(first, last);
        int half_distance = std::floor(0.5 * distance);
        Student mid_student = *(first + half_distance);

        if (mid_student == p && !mid_student.is_vaccinated())
            return true;
        else if (mid_student == p && mid_student.is_vaccinated())
            return false;
        else if (mid_student > p)
            std::advance(last, -half_distance);
        else if (mid_student < p)
            std::advance(first, half_distance);

        if (distance == 1)
            return true;
    }
}

void search_test(int size, Student p) {
    std::vector<Student> people;

    for (int i = 0; i < size; i++)
        people.emplace_back(generate_random_Student(size));

    std::sort(people.begin(), people.end());

    auto begin = std::chrono::steady_clock::now();

    bool search_result = needs_vaccination(p, people);

    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    std::cout << "이진 검색 소요 시간: " << diff.count() << "us" << std::endl;

    if (search_result)
        std::cout << "(" << p.get_name().first << " " << p.get_name().second << ") "
        << "학생은 예방 접종이 필요합니다." << std::endl;
    else
        std::cout << "(" << p.get_name().first << " " << p.get_name().second << ") "
        << "학생은 예방 접종이 필요하지 않습니다." << std::endl;
}



int main()
{
    auto p = generate_random_Student(1000);

    search_test(1000, p);
    search_test(10000, p);
    search_test(100000, p);

    return 0;
}