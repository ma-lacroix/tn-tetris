//
//  Messages.hpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 09/04/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#ifndef Messages_hpp
#define Messages_hpp
#include <stdio.h>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "ResourcePath.hpp"

class Message{
private:
    sf::Font m_font;
    int m_font_size;
    std::string m_message;
    sf::Vector2f m_position;
    float m_speed;
    sf::Text m_text;
    std::vector<sf::Sound> m_sounds;
    sf::Sound n_good;
    sf::SoundBuffer n8;
    sf::Sound n_all_right;
    sf::SoundBuffer n9;
    sf::Sound n_yyy;
    sf::SoundBuffer n10;
    sf::Sound n_onbc;
    sf::SoundBuffer n11;
    
public:
    Message(sf::Font,int,std::string,sf::Vector2f,float);
    ~Message();
    void Move(float);
    void Reset();
    void Play_noise(int c_ind);
    void Draw(sf::RenderWindow&);
    
};

#endif /* Messages_hpp */
