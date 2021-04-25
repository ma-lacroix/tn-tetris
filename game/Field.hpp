//
//  Field.hpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 25/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#ifndef Field_hpp
#define Field_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "Messages.hpp"
#include "ResourcePath.hpp"

class Field {
private:
    std::vector<sf::RectangleShape> m_field;
    std::vector<sf::RectangleShape> m_field_hold; // copy of m_field used for drop animations
    std::vector<float> m_complete_lines;
    std::map<float,int> m_inventory;
    sf::Sound n_stop;
    sf::SoundBuffer n4;
    sf::Sound n_explode;
    sf::SoundBuffer n5;
    float m_velocity_init;
    float m_velocity;
    
public:
    Field();
    ~Field();
    enum class Status {RUN,ERASE,UPDATE,EXPLODE,GAME_OVER};
    Status m_status;
    size_t GetComplSize();
    void ResetInventory();
    void DropAdjust(float,int);
    void DropLines(float,float,std::vector<Message*>);
    void EraseLines();
    void CheckLines(float);
    void CleanUp(float);
    void Add_field(sf::RectangleShape);
    int Collision(sf::RectangleShape,sf::Vector2f,sf::Vector2f);
    bool CheckEndGame();
    void Explode(float);
    void Draw(sf::RenderWindow&,std::vector<Message*>);
};

#endif /* Field_hpp */
