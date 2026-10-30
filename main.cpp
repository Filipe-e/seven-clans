#include "player.hpp"
#include <vector>
#include <time.h>
#include <fstream>

vector<string> loadname(string nome_arq){

}

int main(){
    srand(time(0));
    vector<Character*> clan1;
    vector<Character*> clan2;


    vector<Character*> clan3;
    vector<Character*> clan4;
    vector<vector<Character*>> kidom; // Crio um sistema de ponteiros para permitir que kidom possa receber classes filhas de Character
    kidom.push_back(clan1);
    kidom.push_back(clan2);

    while(kidom.size() > 1){
        size_t clanattk = rand() % kidom.size();
        size_t clandef;
        do{
            clandef = rand() % kidom.size();
        }while(clandef == clanattk);
        while (!(kidom.at(clanattk).empty()) && !(kidom.at(clandef).empty()))
        {
            size_t persnattkc = rand() % kidom.at(clanattk).size();
            size_t persndef = rand() % kidom.at(clandef).size();
            cout << kidom.at(clanattk).at(persnattkc)->getname() << " de forma feroz atacou " << kidom.at(clandef).at(persndef)->getname() << endl;
            cout << kidom.at(clandef).at(persndef)->getname() << " sofreu " << kidom.at(clanattk).at(persnattkc)->attack(*kidom.at(clandef).at(persndef)) << endl; // uso * para que eu passe o objeto diretamente, em vez do ponteiro
            if (kidom.at(clandef).at(persndef)->state()){
                cout << kidom.at(clandef).at(persndef)->getname() << " de forma feroz devolveu o ataque " << kidom.at(clanattk).at(persnattkc)->getname() << endl;
                cout << kidom.at(clanattk).at(persnattkc)->getname() << " sofreu " << kidom.at(clandef).at(persndef)->attack(*kidom.at(clanattk).at(persnattkc)) << endl;
                if(kidom.at(clanattk).at(persnattkc)->getlife() == 0){
                    cout << "nao tankou e foi de arrasta!\n";
                    kidom.at(clandef).erase(kidom.at(clandef).begin() + persndef);
                } 
            }
            else{
                cout << "O mantando!\n";
                kidom.at(clanattk).erase(kidom.at(clanattk).begin() + persnattkc);
            }
            
        }
        for(size_t i = 0; i < kidom.at(0).size() ; i++){
            cout << "E os vencedores sao: \n";
            cout << kidom.at(0).at(i)->getname() << endl;
        }
        
    
    
    
    
    
    
    }
}