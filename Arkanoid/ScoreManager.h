// ScoreManager.h
#pragma once
#include <vector>
#include <string>

class ScoreManager {
public:
    ScoreManager(const std::string& filename);
    void addScore(int score);
    void saveScores() const;
    void loadScores();
    const std::vector<int>& getScores() const;

private:
    std::vector<int> scores;
    std::string filename;
};
