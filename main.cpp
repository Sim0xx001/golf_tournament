#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


typedef struct Players {
	string last_name, first_name, club;
	float points;
	int year;
}player;

// OVERLOADS
ostream& operator << (ostream& out, player& p) {
	return out << "First name: " << p.first_name << "\nLast name: " << p.last_name << "\nYear of birth: " << p.year
		<< "\nClub: " << p.club << "\nPoints: " << p.points << endl;
}

bool operator > (player& left, player& right) {
	return left.points > right.points;
}

string operator * (string left, int right) {
	string str = "";
	for (int i = 0; i < right; i++) {
		str += left;
	}
	return str;
}

// OVERLOADS END

// Convert string to player type and fill the struct variables
void stringToPlayer(string str, player* p) {
	string reader = "";
	string arr[5];
	short counter = 0;

	for (int i = 0; i <= str.length(); i++) {
		if (str[i] != ';' && str[i] != '\0')
			reader += str[i];
		else {
			arr[counter++] = reader;
			reader = "";
		}
	}

	p->last_name = arr[0];
	p->first_name = arr[1];
	p->club = arr[2];
	p->points = stof(arr[3]);
	p->year = stoi(arr[4]);
}


// Read the file and fill the vector
void readFile(string file, vector<player>* ptr) {
	ifstream data;
	data.open(file);

	string str = "";
	while (!data.eof()) {
		getline(data, str);

		player p;
		stringToPlayer(str, &p);
		ptr->push_back(p);
	}
}

//sos
// Print players according to sorted points
void print_sort(vector<player>* ptr, bool sort) {
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 0; i < ptr->size() - 1; i++) {
			if (ptr->operator[](i) > ptr->operator[](i + 1)) {
				swap(ptr[i], ptr[i + 1]);
				sorted = false;
			}
		}
	}

	if (sort) {
		for (int i = 0; i < ptr->size(); i++) {
			cout << ptr->operator[](i) << endl;
		}
	}
	else {
		for (int i = ptr->size() - 1; i < ptr->size(); i--) {
			cout << ptr->operator[](i) << endl;
		}
	}
}


// Print player by last name and all the players with the same points
void sortByLastName(vector<player>* ptr, string last) {
	short points = 0;
	for (int i = 0; i < ptr->size(); i++) {
		if (ptr->operator[](i).last_name == last) {
			cout << ptr->operator[](i) << endl;
			points = ptr->operator[](i).points;
			break;
		}
	}

	for (int i = 0; i < ptr->size(); i++) {
		if(ptr->operator[](i).last_name != last){
			if (ptr->operator[](i).points == points)
				cout << ptr->operator[](i) << endl;
		}
	}
}


// Delete players by points
void deleteByPoints(vector<player>*ptr, float points) {
	for (int i = 0; i < ptr->size(); i++) {
		if (ptr->operator[](i).points == points) {
			ptr->erase(ptr->begin() + i);
			i--;
		}
	}
}


int main() {

	vector<player>data;

	readFile("Punteggi.txt", &data);

	cout << "b)" << endl;
	print_sort(&data, 1);
	cout << (string)"*" * 30 << endl;

	cout << "c)" << endl;
	sortByLastName(&data, "Strati");
	cout << (string)"*" * 30 << endl;

	cout << "d)" << endl;
	deleteByPoints(&data, 129.0);

	for (player x : data)
		cout << x << endl;

	system("pause");
	return 0;
}