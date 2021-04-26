//
//  Menu.cpp
//  tntetris
//
//  Created by Marc-Antoine Lacroix on 14/04/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Menu.hpp"

Menu::Menu(sf::Font c_font, sf::Vector2f c_screen_size){
    
    this->m_font = c_font;
    m_vs_size = 30.0f;
    m_s_size = 50.0f;
    m_b_size = 65.0f;
    m_selection = 0.0f;

    if(!m_easy_textu_1.loadFromFile("Resources/images/b_m_easy_peasy_deselected.png")){
         std::cout << "error loading file" << std::endl;
    }

    if(!m_easy_textu_2.loadFromFile("Resources/images/b_m_easy_peasy_selected.png")){
         std::cout << "error loading file" << std::endl;
    }
    
    if(!m_medium_textu_1.loadFromFile("Resources/images/b_m_dude_seriously_deselected.png")){
         std::cout << "error loading file" << std::endl;
    }

    if(!m_medium_textu_2.loadFromFile("Resources/images/b_m_dude_seriously_selected.png")){
         std::cout << "error loading file" << std::endl;
    }
    
    if(!m_hard_textu_1.loadFromFile("Resources/images/b_m_f_this_deselected.png")){
         std::cout << "error loading file" << std::endl;
    }

    if(!m_hard_textu_2.loadFromFile("Resources/images/b_m_f_this_selected.png")){
         std::cout << "error loading file" << std::endl;
    }
    
    if(!m_pause_textu_b.loadFromFile("Resources/images/b_pause_layer.png")){
         std::cout << "error loading file" << std::endl;
    }

    if(!m_pause_textu_msg.loadFromFile("Resources/images/b_pause_text.png")){
         std::cout << "error loading file" << std::endl;
    }

    if(!m_game_over_textu_b.loadFromFile("Resources/images/b_game_over_layer.png")){
         std::cout << "error loading file" << std::endl;
    }

    if(!m_game_over_textu_msg.loadFromFile("Resources/images/b_game_over_text.png")){
         std::cout << "error loading file" << std::endl;
    }
    
    m_pause_b.setTexture(&m_pause_textu_b);
    m_pause_b.setFillColor(sf::Color(255,255,255,240));
    m_pause_b.setSize(c_screen_size);
    m_pause_msg.setTexture(&m_pause_textu_msg);
    m_pause_msg.setSize(c_screen_size);

    m_game_over_b.setTexture(&m_game_over_textu_b);
    m_game_over_b.setFillColor(sf::Color(255,255,255,175));
    m_game_over_b.setSize(c_screen_size*1.5f);
    m_game_over_b.setOrigin(100.0f,100.0f);
    m_game_over_msg.setTexture(&m_game_over_textu_msg);
    m_game_over_msg.setSize(c_screen_size);
    
    m_easy_1.setTexture(&m_easy_textu_1);
    m_easy_2.setTexture(&m_easy_textu_2);
    m_medium_1.setTexture(&m_medium_textu_1);
    m_medium_2.setTexture(&m_medium_textu_2);
    m_hard_1.setTexture(&m_hard_textu_1);
    m_hard_2.setTexture(&m_hard_textu_2);
    
    m_diff_des.push_back(m_easy_1);
    m_diff_sel.push_back(m_easy_2);
    m_diff_des.push_back(m_medium_1);
    m_diff_sel.push_back(m_medium_2);
    m_diff_des.push_back(m_hard_1);
    m_diff_sel.push_back(m_hard_2);
    
    for(size_t i {0};i<m_diff_des.size();++i){
        m_diff_des.at(i).setSize(c_screen_size);
        m_diff_sel.at(i).setSize(c_screen_size);
        m_diff_des.at(i).setPosition(0.0f,-250.0f); // fix to increase screen position
        m_diff_sel.at(i).setPosition(0.0f,-250.0f);
    }
    
    Update_menu_selection();
    
    // sounds
    n1.loadFromFile("Resources/sounds/n_start.wav");
    n_start.setBuffer(n1);
    n_start.setVolume(80);
    
    n2.loadFromFile("Resources/sounds/n_switch.wav");
    n_switch.setBuffer(n2);
    n_switch.setVolume(80);
    
    n3.loadFromFile("Resources/sounds/n_enter.wav");
    n_enter.setBuffer(n3);
    n_enter.setVolume(80);
    
}

Menu::~Menu(){

    std::cout << "menu destructor called" << std::endl;

}


void Menu::Move_selector(float c_move){

        if(m_selection+c_move>=0.0f && m_selection+c_move<=2.0f){
        m_selection+=c_move;
        n_switch.play();
        }
    Update_menu_selection();
}

void Menu::Move_options(float c_totalTime){
    
//    m_difficulty.at(0).move(-sinf(c_totalTime*3.1416)/200.0f,cosf(c_totalTime*3.1416)/200.0f);
    for(size_t i {0};i<m_diff_sel.size();++i){
        if(i==m_selection){
            m_diff_sel.at(i).move(-sinf(c_totalTime*3.1416)/200.0f,0.0f);
        }
    }
}

void Menu::Move_gameOver(float c_totalTime){
// makes the game over screen look like a broken TV
    m_game_over_b.move(sinf(c_totalTime*9000.0f)/20.0f,cosf(c_totalTime*5000.0f)/20.0f);
}

void Menu::Update_menu_selection(){
    
    for(size_t i {0};i<m_diff_des.size();++i){
        if(i==m_selection){
            m_diff_sel.at(i).setFillColor(sf::Color(255,255,255,255));
            m_diff_des.at(i).setFillColor(sf::Color(255,255,255,0));
        }else{
            m_diff_des.at(i).setFillColor(sf::Color(255,255,255,255));
            m_diff_sel.at(i).setFillColor(sf::Color(255,255,255,0));
        }
    }
}

float Menu::Get_difficulty(){
    if(m_selection==0.0f){
        m_level = 1.0f;
    }else if(m_selection==1.0f){
        m_level = 0.5f;
    }else if(m_selection==2.0f){
        m_level = 0.1f;
    }
    
    n_enter.play();
    
    return m_level;

}

void Menu::Play_d_menu(){
    n_start.play();
}

void Menu::Draw(sf::RenderWindow& window, int c_index){
    
    if(c_index==1){
        for(auto& msg: m_diff_sel){
            window.draw(msg);
        }
        for(auto& msg: m_diff_des){
            window.draw(msg);
        }
    }else if(c_index==2){
        window.draw(m_game_over_b);
        window.draw(m_game_over_msg);
    }else{
        window.draw(m_pause_b);
        window.draw(m_pause_msg);
    }
    
}
