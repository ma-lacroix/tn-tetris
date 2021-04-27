//  SuperTetris
//
//  Created by Marc-Antoine Lacroix on 21/03/2021.
//  Art by Johnny Khalil
//  Music by Tri-Tachyon & Alexandr Zhelanov (obtained on Opengameart.org)
//  Copyright © 2021 Marc-Antoine Lacroix. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Background.hpp"
#include "Pieces.hpp"
#include "Messages.hpp"
#include "Menu.hpp"

// globals
enum class State {INTRO,DIFFICULTY,PLAYING,PAUSE,GAME_OVER,RESET};
const float SCREEN_WIDTH {800.0f};
const float SCREEN_HEIGHT {1500.0f};

void resizedView(const sf::RenderWindow& window, sf::View& view, const float view_height) {
    float aspectRatio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(view_height * aspectRatio,view_height);
}

std::vector<Piece*> gen(sf::Vector2f c_play_size, sf::Vector2f c_play_pos, int num_pieces){
    std::vector<Piece*> c_pieces;
    for(int i {0};i<num_pieces;++i){
        srand((int)time(0) * i * 5);
        int c_type = (rand() % 1)+1;
        Piece* p = new Piece(c_play_size,c_play_pos,c_type);
        c_pieces.push_back(p);
    }
    c_pieces.at(0)->Activate_Piece();
    return c_pieces;
}

std::vector<Message*> gen2(sf::Font c_font,int c_size,sf::Vector2f c_pos,float c_speed){
    
    std::vector<std::string> msgs = {"","GOOD!","ALL\n RIGHT!","YEAH\n YEAH\n YEAH!",
                                    "OW!\nNOW!\nBROWN!\nCOW!\n"};
    std::vector<Message*> c_messages;
    for(size_t i {0};i<msgs.size();++i){
        Message* m = new Message(c_font,c_size,msgs.at(i),c_pos,c_speed);
        c_messages.push_back(m);
    }
    return c_messages;   
}


int main(){
    
    // music
    sf::Music s_menu;
    if (!s_menu.openFromFile("Resources/music/s_menu.ogg")) {
        return EXIT_FAILURE;
    }
    s_menu.setVolume(30.0f);
    s_menu.setPlayingOffset(sf::seconds(6.5f));
    
    sf::Music s_playing;
    if (!s_playing.openFromFile("Resources/music/s_playing.ogg")) {
        return EXIT_FAILURE;
    }
    s_playing.setVolume(30.0f);
    s_playing.setLoop(true);
    
    sf::Sound n_pause;
    sf::SoundBuffer n13;
    if(!n13.loadFromFile("Resources/sounds/n_pause.wav")){
        return EXIT_FAILURE;
    }
    n_pause.setBuffer(n13);
    n_pause.setVolume(60.0f);
    
    // time related stuff
    sf::Clock clock;
    sf::Clock clock2;
    float totalTime {0.0f};
    float deltaTime {0.0f};
    float difficulty {1.5f};
    
    sf::Vector2f nextMove {0.0f,0.0f};
    int piece_counter {0};
    int c_index {0};
    
    // Create the main window
    sf::Vector2f screen_size {SCREEN_WIDTH,SCREEN_HEIGHT};
    sf::RenderWindow window(sf::VideoMode(screen_size.x,screen_size.y),"TN-TETRIS",sf::Style::Titlebar | sf::Style::Resize);
    sf::View view(screen_size/2.0f,screen_size);
    
    sf::Font font;
    if (!font.loadFromFile("Resources/font/Excludedi.ttf")) {
        return EXIT_FAILURE;
    }
    
    Field* field = new Field();
    Menu* menu = new Menu(font,screen_size);
    Background* background = new Background(SCREEN_WIDTH,SCREEN_HEIGHT,sf::Color::Red,font);
    std::vector<Piece*> pieces = gen(background->Get_play_size(),background->Get_play_pos(),200);
    std::vector<Message*> messages = gen2(font,300,{SCREEN_WIDTH,SCREEN_HEIGHT/3},10.0f);
    
    State state = State::INTRO;
    // State state = State::GAME_OVER;
    
    // Start the game loop
    while (window.isOpen())
    {
        
        totalTime = clock.getElapsedTime().asSeconds();
        deltaTime = clock2.restart().asSeconds();
        
        // music management
        if(state == State::INTRO || state == State::DIFFICULTY ){
            if(s_menu.getStatus()!=sf::Music::Playing){
                s_menu.play();
            }
        }
        
        if(state == State::PLAYING){
            if(s_menu.getStatus()==sf::Music::Playing){
                s_menu.stop();
            }
            if(s_playing.getStatus()!=sf::Music::Playing){
                s_playing.play();
            }
        }
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            // restart
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                state = State::RESET;
                for(Piece* p: pieces){
                    delete p;
                }
                pieces.clear();
                delete field;
                s_menu.stop();
                s_playing.stop();
                totalTime = 0.0f;
                deltaTime = 0.0f;
                difficulty = 1.5f;
                nextMove = {0.0f,0.0f};
                piece_counter = 0;
                c_index = 0;
                background->initObjects();
                field = new Field();
                pieces = gen(background->Get_play_size(),background->Get_play_pos(),200);
                state = State::DIFFICULTY;
            }
            
            if(event.type == sf::Event::Resized){
                resizedView(window,view,SCREEN_HEIGHT);
                printf("New window width: %i New window height: %i\n", event.size.width, event.size.height);
            }
            
            // Start game
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && state == State::INTRO){
                state = State::DIFFICULTY;
                menu->Play_d_menu();
            }
            
            if(state == State::DIFFICULTY && event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Up){
                    menu->Move_selector(-1.0f);
                }else if(event.key.code == sf::Keyboard::Down){
                    menu->Move_selector(1.0f);
                }else if(event.key.code == sf::Keyboard::Enter){
                    difficulty = menu->Get_difficulty();
                    state = State::PLAYING;
                }
            }
            
            // Move pieces
            if(state == State::PLAYING && event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Left){
                    nextMove = {-1.0f,0.0f};
                }
                if(event.key.code == sf::Keyboard::Right){
                    nextMove = {1.0f,0.0f};
                }
                if(event.key.code == sf::Keyboard::Down){
                    nextMove = {0.0f,1.0f};
                }
                if(event.key.code == sf::Keyboard::Space){
                    nextMove = {99.0f,0.0f};
                }
                if(event.key.code == sf::Keyboard::P){
                    state = State::PAUSE;
                    s_playing.pause();
                    n_pause.play();
                    
                }
            }
            if(state == State::PAUSE && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
                state = State::PLAYING;
                s_playing.play();
            }
        }
        
        if(piece_counter==5 && difficulty-0.15f>0.0f){
            difficulty-=0.05f; // increase difficulty every 5 pieces
            piece_counter = 0;
        }
        
        if(totalTime>=difficulty && state == State::PLAYING){
            nextMove = {0.0f,1.0f};
            totalTime = clock.restart().asSeconds();
        }
        
        if(field->m_status == Field::Status::RUN && (nextMove.x!=0.0f || nextMove.y!=0.0f)){
            if(nextMove.x!=99.0f){
                pieces.at(c_index)->Move(nextMove, field);
            }else{
                pieces.at(c_index)->Rotate();
            }
            nextMove = {0.0f,0.0f};
            totalTime = clock.restart().asSeconds();
        }
        
        if(field->m_status == Field::Status::UPDATE){
            
            // screen shake
            int randv = rand()%23;
            view.setCenter(screen_size.x/2.0f+randv,screen_size.y/2.0f+randv*1.1f);
            if(randv%2==0){
                view.rotate(-0.001f);
            }
            if(randv%2!=0){
                view.rotate(0.001f);
            }
            background->rotateBox();
            background->updateScore(field->GetComplSize());
            field->DropLines(background->Get_play_size().x/8, deltaTime,messages);
        }
        
        if(field->m_status==Field::Status::RUN){
            if(field->CheckEndGame()){
                field->m_status=Field::Status::EXPLODE;
            }
        }
        
        if(field->m_status==Field::Status::EXPLODE){
            int randv = rand()%23;
            view.setCenter(screen_size.x/2.0f+randv,screen_size.y/2.0f+randv*1.5f);
            background->Explode();
            field->Explode(deltaTime);
        }
        
        if(field->m_status==Field::Status::GAME_OVER){
            state=State::GAME_OVER;
        }
        
        // Clear screen
        window.clear(sf::Color(200,200,230));
        window.setView(view);
        
        
        if(state==State::INTRO){
            background->moveMsg(totalTime);
            if(totalTime >= 2.0f){
                totalTime = clock.restart().asSeconds();
            }
            if(totalTime>=1.0f){
                background->Draw(window, true);
            }
            if(totalTime<1.0f){
                background->Draw(window, false);
            }
            
        }else if(state==State::DIFFICULTY){
            background->Draw(window,0);
            menu->Move_options(totalTime);
            menu->Draw(window,1);
//            view.move(-sinf(totalTime*3.1416)/250.0f,cosf(totalTime*3.1416)/250.0f); //screen shake
        }else if(state==State::PLAYING){
            if(c_index+1 <= pieces.size()-1){
                background->Draw(window,pieces.at(c_index+1));
                field->Draw(window,messages);
                pieces.at(c_index)->Draw(window);
            }else{
                state = State::GAME_OVER;
            }
        }else if(state==State::PAUSE){
            background->Draw(window);
            menu->Draw(window, 3);
        }else{
            view.setCenter(screen_size.x/2.0f,screen_size.y/2.0f);
            menu->Move_gameOver(totalTime);
            background->Draw(window);
            menu->Draw(window,2);
        }
        // Update the window
        window.display();
        
        // Switch to next piece
        if(state==State::PLAYING && !pieces.at(c_index)->Check_status() &&
                    c_index < pieces.size()-1 && field->m_status == Field::Status::RUN){
            ++c_index;
            pieces.at(c_index)->Activate_Piece();
            ++piece_counter;
        }
    }
    return EXIT_SUCCESS;
}
