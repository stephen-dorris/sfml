//
//  minipaint.cpp
//  mini-paint
//
//  Created by Stephen Dorris on 1/18/20.
//  Copyright © 2020 Stephen Dorris. All rights reserved.
//

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

// Include standard library C++ libraries.
#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>

// Function to return a numeric key (1-8)  --> color mapping.
std::map<const sf::Keyboard::Key,const sf:: Color> key_mapping (){
    // Colors
    const sf::Color black = sf::Color::Black;
    const sf::Color white = sf::Color::White;
    const sf::Color red = sf::Color::Red;
    const sf::Color green = sf::Color::Green;
    const sf::Color blue = sf::Color::Blue;
    const sf::Color yellow = sf::Color::Yellow;
    const sf::Color magenta  = sf::Color::Magenta;
    const sf::Color cyan = sf::Color::Cyan;
    
    // Keys
    const sf::Keyboard::Key k1 = sf::Keyboard::Key::Num1;
    const sf::Keyboard::Key k2 = sf::Keyboard::Key::Num2;
    const sf::Keyboard::Key k3 = sf::Keyboard::Key::Num3;
    const sf::Keyboard::Key k4 = sf::Keyboard::Key::Num4;
    const sf::Keyboard::Key k5 = sf::Keyboard::Key::Num5;
    const sf::Keyboard::Key k6 = sf::Keyboard::Key::Num6;
    const sf::Keyboard::Key k7 = sf::Keyboard::Key::Num7;
    const sf::Keyboard::Key k8 = sf::Keyboard::Key::Num8;
    
    
    std::vector<const sf::Keyboard::Key> keys  = { k1,k2,k3,k4,k5,k6,k7,k8};
    std::vector<const sf::Color> colors = {black,white,red,green,blue,yellow,magenta,cyan};
    
    
    std::map<const sf::Keyboard::Key,const sf:: Color> mapping ;
    // no need to assert size equals, since above is hard coded.
    for (size_t i = 0;  i < keys.size();++i){
        mapping.insert({keys.at(i),colors.at(i)});
    };
    return mapping;
}

std::string color_mapping(const sf::Color c){
    
    if (c == sf::Color::Black) return  "black";
    
    else if (c == sf::Color::White)  return "white";
    else if (c== sf::Color::Red) return "red";
    else if (c== sf::Color::Green) return "green";
    else if (c == sf::Color::Blue) return "blue";
    else if (c == sf::Color::Yellow) return "yellow";
    else if (c == sf::Color::Magenta) return "magenta";
    else if (c == sf::Color::Cyan ) return "cyan";

    else return "invalid";
}

bool inBounds(int mouse_x, int mouse_y, sf::Vector2u windowSize){
    
    return (0 <= mouse_x <= windowSize.x) && (0 <= mouse_y <= windowSize.y);
}

int main(){
    // Get Key --> Color Map.
    const std::map<const sf::Keyboard::Key,const sf:: Color> numeric_key_map  = key_mapping();

    
    /*
     Canvas  / Sprite Set up.
     */
    
    // Create background canvas for mini-paint app.
    // Set the sync rate after creating a window
    
    sf::RenderWindow window(sf::VideoMode(600,400), "Mini-Paint",sf::Style::Titlebar);
    window.setVerticalSyncEnabled(true);
   
    // create an image to draw on in the window
    sf::Image image;
    image.create(640,400, sf::Color::White);
    
    // Create the texture that will be displayed over sprite
    sf::Texture texture;
    texture.loadFromImage(image);
    
    
    // create a sprite, and then draw over it a 'texture' which is
    // what is drawn.
    // Sprites can consist of multiple textures (or layers) that may be blended
    // together for example.
    sf::Sprite sprite;
    sprite.setTexture(texture);
    
    
    /*
     Iteration Vars to keep track of.
    */
    
    //boolean  indicator if mouse is currently  held  down.
    //if no "mouse released" event has been triggered, then mini-paint will draw pixels where the
    // mouse is located.
    // once mouse released  event triggered, indicator switched to  false.
    bool is_pressed = false;
    
    // Color currently activated by key press. (1-8) (starts as  White).
    sf::Color  current_color = sf::Color::White;
    
    
    // Main Program Loop
    while(window.isOpen()){
        // Capture events in our main window
        sf::Event event;
        
        //  Event Queue Handler Loop and Main app logic
        while(window.pollEvent(event)){
            
            // Key Event Logic for canvas clearing, exiting, and active  color changing.
            if (event.type == sf::Event::KeyReleased){
                switch (event.key.code){
                    case sf::Keyboard::Escape:
                         window.close();
                         std::cout << "GoodBye\n";
                         exit(EXIT_SUCCESS);
                     
                    case sf::Keyboard::Space:
                        std::cout <<  "Clearing Canvas to :" << color_mapping(current_color) << std::endl;
                        window.clear(sf::Color::White);
                        //window.display();
                        for (int i=0; i <window.getSize().x; ++i){
                            for (int j=0; j <window.getSize().y;++j){
                                image.setPixel(i,j,current_color);
                            }
                        }
                        texture.loadFromImage(image);

                        break;
                    default:
                        // Check if numeric Key Pressed
                
                        if (numeric_key_map.find(event.key.code) != numeric_key_map.end()){
                           std::cout <<  "Changing Active Color to :" << color_mapping(numeric_key_map.at(event.key.code)) << std::endl;
                           current_color = numeric_key_map.at(event.key.code);
                        }
                        else{
                            std::cout << "Invalid key pressed, please try again. " <<  std::endl;
                        }
                        break;
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                is_pressed = true;
                
            }
            
            else if (event.type == sf::Event::MouseButtonReleased){
                is_pressed = false;
            }
            }
        
        if (is_pressed) {
            int mouse_x  = sf::Mouse::getPosition(window).x;
            int mouse_y = sf::Mouse::getPosition(window).y;
            sf::Vector2u windowbounds =  window.getSize();
            if (inBounds(mouse_x,mouse_y, windowbounds)){
                image.setPixel(mouse_x,mouse_y, current_color);
                texture.loadFromImage(image);
            }
            
        }
            
            
        
        
        
        // Clear our window
        window.clear();
        // Draw our sprite, which has a beautiful texture on it (initially a blank canvas)
        window.draw(sprite);
        // Display on our window any sprites or any shapes we have drawn.
        window.display();
    
            }
 
    
}

        

     

