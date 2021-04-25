//
//  Background.hpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 23/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#ifndef Background_hpp
#define Background_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pieces.hpp"

class Background {
private:
    sf::Vector2f m_s_size;
    sf::RectangleShape m_intro_bg;
    sf::Texture m_intro_texture;
    sf::RectangleShape m_menu_bg;
    sf::Texture m_menu_texture;
    sf::RectangleShape m_flicker_bg;
    sf::Texture m_flicker_texture;
    sf::RectangleShape m_press_space_bg;
    sf::Texture m_press_space_texture;
    sf::RectangleShape m_background_bg;
    sf::Texture m_background_texture;
    sf::RectangleShape m_main_bg;
    sf::Texture m_main_texture;
    sf::RectangleShape m_second_bg;
    sf::Texture m_second_texture;
    sf::RectangleShape m_third_bg;
    sf::Texture m_third_texture;
    sf::RectangleShape m_rose1;
    sf::RectangleShape m_rose2;
    sf::RectangleShape m_rose3;
    sf::RectangleShape m_rose4;
    sf::Texture m_rose_texture;
    sf::Color m_color;
    sf::Font m_font;
    sf::Text m_score;
    int m_lines;
    
public:
    Background(float, float,sf::Color,sf::Font);
    ~Background();
    void initObjects();
    sf::Vector2f Get_play_size();
    sf::Vector2f Get_play_pos();
    void updateScore(int);
    void rotateBox();
    void Explode();
    void moveMsg(float);
    void Draw(sf::RenderWindow&,bool);
    void Draw(sf::RenderWindow&,int);
    void Draw(sf::RenderWindow&,Piece*);
    void Draw(sf::RenderWindow&);
    
};

#endif /* Background_hpp */
