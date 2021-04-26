//
//  Menu.cpp
//  tntetris
//
//  Created by Marc-Antoine Lacroix on 14/04/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Menu.hpp"

Menu::Menu(sf::Font c_font, sf::Vector2f c_screen_size){
    
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
    
    this->m_font = c_font;
    m_vs_size = 30.0f;
    m_s_size = 50.0f;
    m_b_size = 65.0f;
    m_selection = 0.0f;
    
    t_pause = sf::Text("Pause\n\nSpacebar to restart", m_font, m_s_size);
    t_pause.setFillColor(sf::Color::Red);
    t_pause.setPosition(c_screen_size.x*0.01,c_screen_size.y*0.5);
    
    t_game_over = sf::Text("GAME OVER!\n\n\n PRESS 'R'", m_font, m_b_size);
    t_game_over.setFillColor(sf::Color::Red);
    t_game_over.setPosition(c_screen_size.x*0.2,c_screen_size.y*0.4);
    
    t_credits = sf::Text("Game development:\nMarc-Antoine Lacroix\n\nArt conception:\nJohnny Khalil", m_font, m_vs_size);
    t_credits.setFillColor(sf::Color::Red);
    t_credits.setPosition(c_screen_size.x*0.05,c_screen_size.y*0.8);
    
    m_others.push_back(t_game_over);
    m_others.push_back(t_credits);
    m_others.push_back(t_pause);
    
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
//        for(auto& msg: m_difficulty){
//            window.draw(msg);
//        }
        for(auto& msg: m_diff_sel){
            window.draw(msg);
        }
        for(auto& msg: m_diff_des){
            window.draw(msg);
        }
    }else if(c_index==2){
        window.draw(m_others.at(0));
        window.draw(m_others.at(1));
    }else{
        window.draw(m_others.at(2));
    }
    
}
