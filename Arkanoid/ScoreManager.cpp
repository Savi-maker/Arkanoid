// ScoreManager.cpp
#include "ScoreManager.h"
#include <fstream>
#include <algorithm>

ScoreManager::ScoreManager(const std::string& filename)
    : filename(filename) {
    loadScores();
}

void ScoreManager::addScore(int score) {
    scores.push_back(score);
    std::sort(scores.rbegin(), scores.rend()); // Sortuj malej¹co
    if (scores.size() > 10) { // Przechowuj tylko top 10 wyników
        scores.pop_back();
    }
}

void ScoreManager::saveScores() const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int score : scores) {
            file << score << std::endl;
        }
    }
}

void ScoreManager::loadScores() {
    std::ifstream file(filename);
    if (file.is_open()) {
        int score;
        while (file >> score) {
            scores.push_back(score);
        }
        std::sort(scores.rbegin(), scores.rend()); // Sortuj malej¹co
    }
}

const std::vector<int>& ScoreManager::getScores() const {
    return scores;
}
