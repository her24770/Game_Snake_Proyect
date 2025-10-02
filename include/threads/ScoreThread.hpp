#ifndef SCORE_THREAD_HPP
#define SCORE_THREAD_HPP

#include <vector>
#include <string>
#include <atomic>
#include <mutex>

struct ScoreEntry {
    std::string name;
    int score;
    std::string time;
};

struct ScoreThreadData {
    std::vector<ScoreEntry> scores;
    std::mutex scoreMutex;
    std::atomic<bool> running;
    std::atomic<bool> needsUpdate;
};

void* scoreThreadFunction(void* arg);
void saveScore(ScoreThreadData* data, const std::string& name, int score, const std::string& time);
int getLowestTopScore(ScoreThreadData* data);
void addScoreImmediate(ScoreThreadData* data, const std::string& name, int score, const std::string& time);

#endif