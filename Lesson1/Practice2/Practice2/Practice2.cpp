#include <iostream>
#include <queue>

class Printer 
{
public:
	struct Job
	{
		int ID = -1;
		std::string user_name = "";
		int page = -1;
	};

private:
	std::queue<Job> printer_queue;

public:
	Printer() = default;

	void printing() {
		if (printer_queue.empty()) {
			std::cout << "출력작업이 없습니다" << std::endl;
			std::cout << std::endl;;

		}
		while(!printer_queue.empty()){
			std::cout << "ID:" << printer_queue.front().ID << "  user_name:" << printer_queue.front().user_name << "  page:" << printer_queue.front().page << std::endl;
			std::cout << "출력완료" << std::endl;
			std::cout << std::endl;
			printer_queue.pop();
		}
	}

	void print(Job work) {
		printer_queue.push(work);
		std::cout << "추가" << std::endl;
		std::cout << "ID:" << work.ID << "  user_name:" << work.user_name << "  page:" << work.page << std::endl;
		std::cout << std::endl;
	}
};

int main()
{
	Printer printer;
	printer.printing();

	printer.print({ 0, "김윤수", 21 });
	printer.print({ 1, "서원영", 17 });
	printer.print({ 2, "김태연", 5 });
	printer.printing();
}


