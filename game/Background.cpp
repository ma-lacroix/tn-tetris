//
//  Background.cpp - handles the backgrounds
//  Super_tetris
//
//  Created by Marc-Antoine Lacroix on 23/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Background.hpp"
#include <iostream>

Background::Background(float SCREEN_WIDTH, float SCREEN_HEIGHT,sf::Color c_color, sf::Font c_font){
    
    std::cout << "Background constructor called" << std::endl;
    
    if(!m_intro_texture.loadFromFile(resourcePath() + "b_intro.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_flicker_texture.loadFromFile(resourcePath() + "b_flickers.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_press_space_texture.loadFromFile(resourcePath() + "b_press_space.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_menu_texture.loadFromFile(resourcePath() + "b_menu.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_background_texture.loadFromFile(resourcePath() + "b_background.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_main_texture.loadFromFile(resourcePath() + "b_playing_area.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_second_texture.loadFromFile(resourcePath() + "b_next.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_third_texture.loadFromFile(resourcePath() + "b_score.png")){
        return EXIT_FAILURE;
    }
    
    if(!m_rose_texture.loadFromFile(resourcePath() + "b_rose.png")){
        return EXIT_FAILURE;
    }
    
    this->m_s_size = {SCREEN_WIDTH,SCREEN_HEIGHT};
    this->m_color=c_color;
    this->m_font=c_font;
    
    m_intro_bg.setSize(m_s_size);
    m_intro_bg.setTexture(&m_intro_texture);
    
    m_flicker_bg.setSize({483.0f,284.0f});
    m_flicker_bg.setOrigin(241.0f,196.0f);
    m_flicker_bg.setTexture(&m_flicker_texture);
    
    m_menu_bg.setSize(m_s_size);
    m_menu_bg.setTexture(&m_menu_texture);
    
    m_press_space_bg.setSize({348.0f,90.0f});
    m_press_space_bg.setOrigin(174.0f,45.0f);
    m_press_space_bg.setTexture(&m_press_space_texture);
    
    m_background_bg.setSize(m_s_size);
    m_background_bg.setTexture(&m_background_texture);
    
    m_main_bg.setSize({m_s_size.x*0.6f,m_s_size.y*0.8f});
    m_main_bg.setTexture(&m_main_texture);
    
    m_second_bg.setSize({m_s_size.x*0.270f,m_s_size.x*0.275f});
    m_second_bg.setTexture(&m_second_texture);
    
    m_third_bg.setSize({m_s_size.x*0.270f,m_s_size.x*0.275f});
    m_third_bg.setTexture(&m_third_texture);
    
    m_rose1.setSize({50.0f,100.0f});
    m_rose1.setTexture(&m_rose_texture);
    m_rose1.setRotation(270.0f);
    
    m_rose2.setSize({50.0f,100.0f});
    m_rose2.setTexture(&m_rose_texture);
    m_rose2.setRotation(180.0f);
    
    m_rose3.setSize({50.0f,100.0f});
    m_rose3.setTexture(&m_rose_texture);
    m_rose3.setRotation(190.0f);
    
    m_rose4.setSize({50.0f,100.0f});
    m_rose4.setTexture(&m_rose_texture);
    m_rose4.setRotation(230.0f);
    
    initObjects();
}

void Background::initObjects(){
// separate from class constructor for game reset
    m_score.setString("0");
    m_score.setOrigin(0.5f, 0.5f);
    m_score.setFont(m_font);
    m_score.setCharacterSize(m_s_size.y*0.03);
    m_score.setFillColor(sf::Color::Black);
    
    m_intro_bg.setPosition(0.0f,0.0f);
    m_flicker_bg.setPosition(m_s_size.x*0.5, m_s_size.y*0.7);
    m_press_space_bg.setPosition(m_s_size.x*0.51, m_s_size.y*0.67);
    
    m_background_bg.setPosition(0.0f,0.0f);
    m_main_bg.setPosition(m_s_size.x*0.019, m_s_size.y*0.19);
    m_main_bg.setRotation(0.0f);
    m_second_bg.setPosition(m_s_size.x*0.7, m_s_size.y*0.35);
    m_second_bg.setRotation(0.0f);
    m_third_bg.setPosition(m_s_size.x*0.7, m_s_size.y*0.67);
    m_third_bg.setRotation(0.0f);
    m_score.setPosition(m_s_size.x*0.75, m_s_size.y*0.73);
    m_rose1.setPosition(m_s_size.x*0.75, m_s_size.y*0.05);
    m_rose2.setPosition(m_s_size.x*0.85, m_s_size.y*0.10);
    m_rose3.setPosition(m_s_size.x*0.80, m_s_size.y*0.05);
    m_rose4.setPosition(m_s_size.x*0.90, m_s_size.y*0.15);
}

sf::Vector2f Background::Get_play_size(){
    return m_main_bg.getSize();
}

sf::Vector2f Background::Get_play_pos(){
    return m_main_bg.getPosition();
}

void Background::updateScore(int lines){
    m_lines+=lines;
    m_score.setString(std::to_string(m_lines));
}

void Background::rotateBox(){
    int randv = rand()%23;
    if(randv%2==0){
        
        m_second_bg.rotate(0.008);
        m_third_bg.rotate(0.01);
        m_score.rotate(0.012);
        m_third_bg.move(-randv%3/50.0f,randv%4/50.0f);
        m_score.move(-randv%3/100.0f,randv%4/100.0f);
        
        m_rose1.move(-randv%3/50.0f,randv%4/50.0f);
        m_rose2.move(-randv%5/19.0f,randv%4/18.0f);
        m_rose2.rotate(0.02);
        m_rose3.move(-randv%3/350.0f,randv%6/175.0f);
        m_rose4.move(-randv%3/250.0f,randv%6/200.0f);
    
    }
    
    if(randv%2!=0){
        
        m_second_bg.rotate(-0.008);
        m_third_bg.rotate(-0.01);
        m_score.rotate(-0.012);
        m_third_bg.move(randv%3/50.0f,-randv%4/50.0f);
        m_score.move(randv%3/80.0f,-randv%4/80.0f);
        
        m_rose1.move(-randv%3/50.0f,randv%5/60.0f);
        m_rose1.rotate(0.03f);
        m_rose2.move(-randv%3/19.0f,randv%5/18.0f);
        m_rose3.move(-randv%7/500.0f,randv%4/180.0f);
        m_rose4.move(-randv%7/650.0f,randv%4/130.0f);
    
    }
       
}

void Background::Explode(){
// more intense version of rotate() - to be refactored
    
    int randv = rand()%23;
    if(randv%2==0){
        
        m_second_bg.rotate(0.01);
        m_third_bg.rotate(0.1);
        m_score.rotate(0.12);
        m_main_bg.move(-randv%5/30.0f,randv%5/30.0f);
        m_third_bg.move(-randv%3/30.0f,randv%4/30.0f);
        m_score.move(-randv%3/30.0f,randv%4/30.0f);
        m_rose1.move(-randv%3,randv%4);
        m_rose2.move(-randv%5,randv%4);
        m_rose2.rotate(0.02);
        m_rose3.move(-randv%3,randv%6);
        m_rose4.move(-randv%3,randv%6);
    }
    
    if(randv%2!=0){
        m_second_bg.rotate(-0.01);
        m_third_bg.rotate(-0.1);
        m_score.rotate(-0.12);
        m_main_bg.move(randv%5/30.0f,-randv%5/30.0f);
        m_third_bg.move(randv%3/30.0f,-randv%4/30.0f);
        m_score.move(randv%3/30.0f,-randv%4/30.0f);
        m_rose1.move(-randv%3,randv%5);
        m_rose1.rotate(0.3f);
        m_rose2.move(-randv%3,randv%5);
        m_rose3.move(-randv%7,randv%4);
        m_rose4.move(-randv%7,randv%4);
    
    }
       
}


void Background::moveMsg(float c_totalTime){
    m_press_space_bg.move(-sinf(c_totalTime*3.1416)/100.0f,cosf(c_totalTime*3.1416)/100.0f);
}

void Background::Draw(sf::RenderWindow& window, bool c_show){
    window.draw(m_intro_bg);
    window.draw(m_press_space_bg);
    if(c_show){
        window.draw(m_flicker_bg);
    }
}

void Background::Draw(sf::RenderWindow& window, int c_code){
    window.draw(m_menu_bg);
}

void Background::Draw(sf::RenderWindow& window, Piece* p){
    window.draw(m_background_bg);
    window.draw(m_main_bg);
    window.draw(m_second_bg);
    window.draw(m_third_bg);
    window.draw(m_score);
    window.draw(m_rose1);
    window.draw(m_rose2);
    window.draw(m_rose3);
    window.draw(m_rose4);
    p->DrawNext(window);
}

void Background::Draw(sf::RenderWindow& window){
    window.draw(m_background_bg);
    window.draw(m_main_bg);
    window.draw(m_second_bg);
    window.draw(m_third_bg);
    window.draw(m_score);
    window.draw(m_rose1);
    window.draw(m_rose2);
    window.draw(m_rose3);
    window.draw(m_rose4);
}

Background::~Background(){std::cout << "Background destructor called" << std::endl;}
