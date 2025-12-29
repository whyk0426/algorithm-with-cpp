#include <iostream>

struct Music
{
	std::string name;
	Music* prev;
	Music* next;
};

class Playlist 
{
 private:
	Music* head = nullptr;   // 초기화 안하니까 이상한 값 들어가서 if (head == nullptr) 성립x
	Music* current = nullptr;
	Music* tail = nullptr; 

public:
	struct Playlist_iterator
	{
	private:
		Music* ptr;

	public:
		Playlist_iterator(Music* p) : ptr(p){}

		std::string& operator*() { return ptr->name; }

		Music* get() { return ptr; }

		Playlist_iterator& operator++() {   // 원본을 수정할 수 있어야
			ptr = ptr->next;
			return *this;
		}

		Playlist_iterator operator++(int) {
			Playlist_iterator result = *this;
			++(*this);
			return result;
		}

		Playlist_iterator& operator--() {
			ptr = ptr->prev;
			return *this;
		}

		Playlist_iterator operator--(int) {
			Playlist_iterator result = *this;
			--(*this);
			return result;
		}

		friend bool operator==(const Playlist_iterator& left, const Playlist_iterator& right) {
			return left.ptr == right.ptr;
		}

		friend bool operator!=(const Playlist_iterator& left, const Playlist_iterator& right) {
			return left.ptr != right.ptr;
		}
	};
	Playlist_iterator begin() { return Playlist_iterator(head); }
	Playlist_iterator end() { return Playlist_iterator(tail); }
	Playlist_iterator begin() const { return Playlist_iterator(head); }
	Playlist_iterator end() const { return Playlist_iterator(tail); }

	Playlist() = default;
	Playlist(const Playlist& other) : head(nullptr), current(nullptr), tail(nullptr) {     // 복사 생성자. 나중에 다시 봐야
		Playlist_iterator it = other.begin();

		head = new Music{ *it, nullptr, nullptr };

		Music* cur = head;
		++it;

		while (it != other.begin()) {
			Music* new_music = new Music{ *it, cur, nullptr };

			cur->next = new_music;

			cur = new_music;
			++it;
		}
		tail = cur;

		tail->next = head;
		head->prev = tail;

		current = head;
	}

	void previous() {
		current = current->prev;

		std::cout << "이전 음악으로 ->" << current->name << std::endl;
		std::cout << std::endl;
	}

	void next() {
		current = current->next;

		std::cout << "다음 음악으로 ->" << current->name << std::endl;
		std::cout << std::endl;
	}

	void printall() {
		std::cout << "현재 플레이리스트" << std::endl;
		for (Playlist_iterator it = this->begin(); it != this->end(); it++) {
			std::cout << "[" << *it << "]" << std::endl;
		}
		Playlist_iterator last = this->end();
		std::cout << "[" << *last << "]" << std::endl;
		std::cout << std::endl;
	}

	void print_current() {
		std::cout << "현재음악 ->" << current->name << std::endl;
		std::cout << std::endl;
	}

	void insert(std::string name) {
		if (head == nullptr) {
			Music* new_music = new Music{ name, nullptr, nullptr };
			new_music->prev = new_music;
			new_music->next = new_music;
			head = new_music;
			current = new_music;
			tail = new_music;
		}
		else {
			Music* new_music = new Music{ name, nullptr, nullptr };
			new_music->prev = tail;
			new_music->next = head;

			tail->next = new_music;
			head->prev = new_music;

			tail = new_music;
		}
		std::cout << "INSERTED ->" << tail->name << std::endl;
		std::cout << std::endl;
	}

	void erase() {
		if (head == tail) {
			delete head;
			head = nullptr;
			current = nullptr;
			tail = nullptr;
		}
		Music* target = current;
		Music* prev_music = current->prev;
		Music* next_music = current->next;

		prev_music->next = next_music;
		next_music->prev = prev_music;

		if (target == head) head = next_music;
		if (target == tail) tail = prev_music;

		current = next_music;

		std::cout << "DELETED ->" << target->name << std::endl;
		std::cout << std::endl;
		delete target;
	}
};

int main() {
	Playlist p1;
	p1.insert("피터팬");
	p1.insert("54321");
	p1.insert("alright");
	p1.printall();
	p1.previous();
	p1.next();
	p1.next();

	Playlist p2 = p1;
	p2.printall();
	p2.print_current();
	p2.erase();
	p2.printall();
}