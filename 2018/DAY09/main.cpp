#include <bits/stdc++.h>

int part1(int players, int lastMarble) {
	std::vector<int> score(players, 0);
	std::list<int> circle;
	int marble = 0;
	circle.push_back(marble++);
	auto currMarble = circle.begin();
	int currPlayer = 0;
	while(marble <= lastMarble) {
		if(marble % 23 == 0) {
			score[currPlayer] += marble;
			for(int i = 0; i < 7; ++i) {
				if(currMarble != circle.begin()) --currMarble;
				else currMarble = --circle.end();
			}
			score[currPlayer] += *currMarble;
			currMarble = circle.erase(currMarble);
		}
		else {
			for(int i = 0; i < 2; ++i) {
				if(currMarble != --circle.end()) ++currMarble;
				else currMarble = circle.begin();
			}
			currMarble = circle.insert(currMarble, marble);
		}
		++marble;
		currPlayer = (currPlayer + 1) % players;
	}
	return *std::max_element(score.begin(), score.end());
}

long long part2(long long players, long long lastMarble) {
	std::vector<long long> score(players, 0);
	std::list<int> circle;
	int marble = 0;
	circle.push_back(marble++);
	auto currMarble = circle.begin();
	int currPlayer = 0;
	while(marble <= lastMarble) {
		if(marble % 23 == 0) {
			score[currPlayer] += marble;
			for(int i = 0; i < 7; ++i) {
				if(currMarble != circle.begin()) --currMarble;
				else currMarble = --circle.end();
			}
			score[currPlayer] += *currMarble;
			currMarble = circle.erase(currMarble);
		}
		else {
			for(int i = 0; i < 2; ++i) {
				if(currMarble != --circle.end()) ++currMarble;
				else currMarble = circle.begin();
			}
			currMarble = circle.insert(currMarble, marble);
		}
		++marble;
		currPlayer = (currPlayer + 1) % players;
	}
	return *std::max_element(score.begin(), score.end());
}

int main() {
	// read input
	std::string str;
	std::getline(std::cin, str);
	int players = std::stoi(str.substr(0, str.find("players") - 1));
	int lastMarble = std::stoi(str.substr(str.find("worth") + 6, str.find("points") - 1));

	// part1
	std::cout << "the answer of part 1 is ";
	std::cout << part1(players, lastMarble) << std::endl;

	// part2
	std::cout << "the answer of part 2 is ";
	std::cout << part2(players, 100 * lastMarble) << std::endl;
}
