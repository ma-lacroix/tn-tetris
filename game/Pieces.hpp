//
//  Pieces.hpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 23/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#ifndef Pieces_hpp
#define Pieces_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Field.hpp"
#include "ResourcePath.hpp"


class Piece {
private:
    std::vector<sf::Vector2f> m_positions;
    std::vector<sf::RectangleShape> m_squares;
    sf::Vector2f m_block_size;
    sf::Vector2f m_play_size;
    sf::Vector2f m_play_pos;
    sf::Color m_color;
    sf::Texture m_texture;
    sf::Vector2i m_texture_start;
    sf::IntRect m_texture_rect;
    sf::Sound n_rotate;
    sf::SoundBuffer n6;
    bool m_is_alive;
    
public:
    Piece(sf::Vector2f,sf::Vector2f,int);
    ~Piece();
    void Activate_Piece();
    std::vector<float> Get_piece_bounds();
    std::vector<sf::RectangleShape> Get_m_squares();
    bool Check_boundaries(float,float,sf::Vector2f,Field*);
    bool Check_bottom(float, sf::Vector2f,Field*);
    bool Check_status();
    void Move(sf::Vector2f,Field*);
    void Adjust_rotation(sf::Vector2f);
    void Rotate_Textures();
    void Rotate();
    void Rotation_Outbound();
    void Draw(sf::RenderWindow&);
    void DrawNext(sf::RenderWindow&);
};

#endif /* Pieces_hpp */
