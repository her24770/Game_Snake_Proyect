#ifndef FOOD_HPP
#define FOOD_HPP

#include <utility>
#include <vector>

class Food {
private:
    std::pair<int, int> position;
    bool exists;
    
public:
    Food();
    void generate(const std::vector<std::pair<int, int>>& snake1Body, 
                  const std::vector<std::pair<int, int>>& snake2Body);
    std::pair<int, int> getPosition() const;
    bool isActive() const;
    void consume();
};

#endif