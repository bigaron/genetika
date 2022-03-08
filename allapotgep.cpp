/**
 * \file allapotgep.cpp
 *
 * Ebben a fájlban kell megvalósítania az Allapotgep osztály
 * metódusait, valamint mindazon további osztályokat, melyek szükségesek
 * a feladat megvalósításához.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include <iostream>
#include <fstream>

#include "allapotgep.h"
#include "memtrace.h" 

//Eltárolja az egyes állapotokat
void Allapotgep::getStates(std::ifstream &file){
    State state;
    char name[21];
    char type;
    for(int i = 0; i < stateNum; i++){
        file >> type;
        file >> name;

        state.setType(type);
        state.setStateName(name);
        states[i] = state;
    }
}

void Allapotgep::konfigural(const char* fajlnev){
    std::ifstream file(fajlnev);

    if(!file.is_open()) {
        stateNum = -1;
        throw("GIS2YB");
    }

    //Allapotok beolvasasa
    file >> stateNum;
    if(states != nullptr) freeStates();
    states = new State[stateNum];
    
    int len = stateNum * stateNum;
    if(controller != nullptr) freeController();
    controller = new char*[len];
    for(int i = 0; i < len; i++) controller[i] = new char[5];
    

    getStates(file);
    int track = 0;
    char placeHolder[5];

    while(!file.eof()){
        file >> placeHolder;
        if(track < len) strcpy(controller[track], placeHolder);
        track++;
    }

    currentState = 0;
    file.close();
}

const char* Allapotgep::aktualisallapot(){
    return states[currentState].getName();
}

bool Allapotgep::elfogad(){
    return states[currentState].getType();
}

void Allapotgep::atmenet(Bazis b){
    int j = 0;
    for(int i = currentState * stateNum; i < (currentState + 1) * stateNum; i++){
        while(controller[i][j] != '\0'){
            //std::cout << controller[i][j] << " ";
            if(controller[i][j] != '0'){
                if(cast(controller[i][j]) == b) {
                    currentState = i % stateNum;
                    return;
                }           
            }
            j++;
        }
        j = 0;
    }
    //std::cout << std::endl;
}

bool Allapotgep::feldolgoz(const Bazis* b, int n){

    //for(int i =0; i < stateNum * stateNum; i++) std::cout<< controller[i] << " ";

    for(int i = 0; i < n; i++){
        atmenet(b[i]);
    }

    return elfogad();
}

void Allapotgep::alaphelyzet(){
    currentState = 0;
}


Allapotgep::~Allapotgep(){
    if(stateNum > -1){
        freeController();
        freeStates();
    }
}


void Allapotgep::freeStates(){
    delete[] states;
    states = nullptr;
}

void Allapotgep::freeController(){
    for(int i = 0; i < stateNum * stateNum; i++) delete[] controller[i];
    delete[] controller;
    controller = nullptr;
}