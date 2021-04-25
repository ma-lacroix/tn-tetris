//
//  Messages.cpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 09/04/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Messages.hpp"

Message::Message(sf::Font c_font,int c_size,std::string c_message,sf::Vector2f c_position,float c_speed){

    this->m_font = c_font;
    this->m_font_size = c_size;
    this->m_message = c_message;
    this->m_position = c_position;
    this->m_speed = c_speed;
    
    m_text.setFont(m_font);
    m_text.setString(m_message);
    m_text.setCharacterSize(m_font_size);
    m_text.setPosition(m_position);
    m_text.setFillColor(sf::Color(0,0,0,200));
    
    n8.loadFromFile(resourcePath() + "n_good.wav");
    n_good.setBuffer(n8);
    n_good.setVolume(90);
    
    n9.loadFromFile(resourcePath() + "n_all_right.wav");
    n_all_right.setBuffer(n9);
    n_all_right.setVolume(90);
    
    n10.loadFromFile(resourcePath() + "n_yyy.wav");
    n_yyy.setBuffer(n10);
    n_yyy.setVolume(90);
    
    n11.loadFromFile(resourcePath() + "n_onbc.wav");
    n_onbc.setBuffer(n11);
    n_onbc.setVolume(90);
    
    m_sounds.push_back(n_good);
    m_sounds.push_back(n_all_right);
    m_sounds.push_back(n_yyy);
    m_sounds.push_back(n_onbc);
    
}

Message::~Message(){
    std::cout << "Message destructor called" << std::endl;
}

void Message::Move(float deltaTime){
    if(m_text.getPosition().x>-3000.0f){
        m_text.move({-deltaTime*m_speed*100.0f,0.0f});
    }
}

void Message::Reset(){
    m_text.setPosition(m_position);
}

void Message::Play_noise(int c_ind){
    if(m_sounds.at(c_ind).getStatus()!=sf::Sound::Status::Playing){
        m_sounds.at(c_ind).play();
    }
}

void Message::Draw(sf::RenderWindow& window){
    window.draw(m_text);
}

