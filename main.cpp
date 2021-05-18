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

ostream& operator << (ostream& out, player& p) {
	return out << "First name: " << p.first_name << "\nLast name: " << p.last_name << "\nYear of birth: " << p.year
		<< "\nClub: " << p.club << "\nPoints: " << p.points << endl;
}

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

	return;

	for (char x : str) {
		if (x != ';' && x != '\0')
			reader += x;
		else {
			arr[counter++] = reader;
			reader = "";
		}
	}
}

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


int main() {

	vector<player>data;

	readFile("Punteggi.txt", &data);

	for (player x : data)
		cout << x << endl;

	system("pause");
	return 0;
}