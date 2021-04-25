//
//  Field.cpp
//  super_tetris
//
//  Created by Marc-Antoine Lacroix on 25/03/2021.
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include "Field.hpp"

Field::Field(){
    std::cout<< "Field constructor called" << std::endl;
    m_status = Status::RUN;
    m_velocity_init = -0.20f; // decrease to make block explosions bigger
    m_velocity = m_velocity_init;
    
    n4.loadFromFile(resourcePath() + "n_impact2.wav");
    n_stop.setBuffer(n4);
    n_stop.setVolume(80);
    
    n5.loadFromFile(resourcePath() + "n_explode2.wav");
    n_explode.setBuffer(n5);
}

Field::~Field(){
    std::cout<< "Field destructor called" << std::endl;
}

size_t Field::GetComplSize(){
    return m_complete_lines.size();
}

void Field::ResetInventory(){
// resets the dead pieces map
    m_inventory.clear();
    for(auto square: m_field){
        std::map<float,int>::iterator it = m_inventory.find(square.getPosition().y);
        if(it!=m_inventory.end()){
            it->second++;
        }else{
            m_inventory.insert(std::make_pair(square.getPosition().y,1));
        }
        
    }
}

void Field::DropAdjust(float c_block_y,int lines_counter){
// adjust dropped pieces pixel count to match game grid

    for(auto line: m_complete_lines){
        for(size_t i{0};i<m_field.size();++i){
            if(m_field_hold.at(i).getPosition().y<line && m_field.at(i).getPosition().y < 2000.0f){
                float current = m_field.at(i).getPosition().y;
                float goal = m_field_hold.at(i).getPosition().y+c_block_y*lines_counter;
                float nmove = goal-current;
                if(current!=goal){
                    m_field.at(i).move(0.0f, nmove);
                }
            }
        }
    }
}

void Field::DropLines(float c_block_y, float deltaTime, std::vector<Message*> c_messages){
    
    int counter {0};
    int lines_counter = m_complete_lines.size();
    c_messages.at(lines_counter)->Play_noise(lines_counter-1);
    for(auto line: m_complete_lines){
        for(size_t i {0};i<m_field.size();++i){
            int randv = sqrt(rand()%10+1);
            m_velocity += deltaTime/(35.0f*lines_counter);
            if(m_field_hold.at(i).getPosition().y==line &&
                m_field.at(i).getPosition().y < 2000.0f){
                    m_field.at(i).setOrigin(20.0f, 20.0f);
                    m_field.at(i).rotate(sinf(i)/randv);
                    m_field.at(i).move(-sinf(i)/randv,m_velocity);
                    c_messages.at(lines_counter)->Move(deltaTime/(lines_counter*4));
                    ++counter;
            }
        }
        for(size_t i{0};i<m_field.size();++i){
            if(m_field.at(i).getPosition().y<line &&
               (m_field.at(i).getPosition().y-m_field_hold.at(i).getPosition().y) <= c_block_y*lines_counter){
                m_field.at(i).move(0.0f,deltaTime*300.0f);
                ++counter;
            }
        }
    }
    if(counter==0){
        c_messages.at(lines_counter)->Reset();
        m_velocity = m_velocity_init;
        DropAdjust(c_block_y,lines_counter);
        EraseLines();
    }
}

void Field::EraseLines(){
    
    // O(g(x)) massively unoptimised search and erase algorithm!
    
    for(size_t i = m_field.size()-1;i>0;--i){
        if(m_field_hold.at(i).getPosition().y>=2000.0f){
            m_field.erase(m_field.begin()+i);
        }
    }
    
    for(size_t i {0}; i < 1;++i){
        if(m_field_hold.at(i).getPosition().y>=2000.0f){
            m_field.erase(m_field.begin()+i);
        }
    }

    ResetInventory();
    m_status = Status::RUN;
}

void Field::CheckLines(float c_block_y){
    
    for(std::map<float,int>::iterator it = m_inventory.begin();it!=m_inventory.end();++it){
        if(it->second == 8){
            m_complete_lines.push_back(static_cast<int>(it->first));
        }
    }
}

void Field::CleanUp(float c_block_y){
    
    ResetInventory();
    m_complete_lines.clear();
    CheckLines(c_block_y);
    n_stop.play();
    
    if(m_complete_lines.size()>0){
        m_velocity = m_velocity_init*m_complete_lines.size();
        m_field_hold = m_field;
        m_status = Status::UPDATE;
        n_explode.setVolume(40.0f + 50.0f*static_cast<float>(m_complete_lines.size()));
        n_explode.play();
    }
}

void Field::Add_field(sf::RectangleShape c_rect){
    m_field.push_back(c_rect);
}

int Field::Collision(sf::RectangleShape c_rect,sf::Vector2f c_move, sf::Vector2f c_block){
// 0 = no collision, 1 = lateral collision, 2 = vertical collision
    int result {0};
    
    float c_x_s = static_cast<int>(c_rect.getPosition().x+c_move.x*c_block.x);
    float c_x_e = static_cast<int>(c_rect.getSize().x+c_x_s);
    float c_y_s = static_cast<int>(c_rect.getPosition().y+c_move.y*c_block.y);
    float c_y_e = static_cast<int>(c_rect.getSize().y+c_y_s);
    
    for(auto square: m_field){
        // get field boundaries
        float f_x_s = static_cast<int>(square.getPosition().x);
        float f_x_e = static_cast<int>(square.getSize().x+f_x_s);
        float f_y_s = static_cast<int>(square.getPosition().y);
        float f_y_e = static_cast<int>(square.getSize().y+f_y_s);
        
        if(c_x_s == f_x_s && c_y_e == f_y_s){
            
            if(c_move.x!=0){
                result+=1;
                break;
            }
            if(c_move.y!=0){
                result+=2;
                break;
            }
        }
    }
    return result;
}

bool Field::CheckEndGame(){
    for(std::map<float,int>::iterator it = m_inventory.begin();it!=m_inventory.end();++it){
        if(it->first <= 400.0 && it->second >= 1){ // 375.0f is where pieces are spawned
            n_explode.setVolume(200.0f);
            n_explode.setPitch(0.8f);
            n_explode.play();
            return true;
        }
    }
    return false;
}

void Field::Explode(float deltaTime){
    int counter {0};
    for(size_t i {0};i<m_field.size();++i){
        int randv = sqrt(rand()%10+1);
        m_velocity += deltaTime/(350.0f);
        if(m_field.at(i).getPosition().y < 2000.0f){
            m_field.at(i).setOrigin(20.0f, 20.0f);
            m_field.at(i).rotate(sinf(i)/randv);
            m_field.at(i).move(-sinf(i)/randv,m_velocity);
            ++counter;
        }
    }
    if(counter==0){
        m_status = Status::GAME_OVER;
    }
}

void Field::Draw(sf::RenderWindow& window,std::vector<Message*> c_messages){
    for(auto square: m_field){
        window.draw(square);
    }
    if(m_status == Status::UPDATE){
        c_messages.at(m_complete_lines.size())->Draw(window);
    }
}
