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
	Music* head;
	Music* current;
	Music* tail;

public:
	void add(std::string name) {
		if (head == NULL) {
			Music* new_music = new Music{ name, nullptr, nullptr };
			new_music->prev = new_music;
			new_music->next = new_music;
			head = new_music;
			current = new_music;
			tail = new_music;
		}
		else {
			Music* new_music = new Music{ name, nullptr, nullptr };
		}

	}
	void remove() {

	}
		
};