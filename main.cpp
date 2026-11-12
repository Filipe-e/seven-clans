#include "player.hpp"
#include <vector>
#include <time.h>
#include <fstream> // pra leitura de dados
#include <chrono> // pra fazer o terminal esperar
#include <thread> // pra fazer o terminal esperar

void printWelcome() {
    cout << R"(
 __          __  _                            _          _   _            _    _     _                 
 \ \        / / | |                          | |        | | | |          | |  (_)   | |                
  \ \  /\  / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |_| |__   ___  | | ___  __| | ___  _ __ ___  
   \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \  | __| '_ \ / _ \ | |/ / |/ _` |/ _ \| '_ ` _ \ 
    \  /\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | |_| | | |  __/ |   <| | (_| | (_) | | | | | |
     \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/   \__|_| |_|\___| |_|\_\_|\__,_|\___/|_| |_| |_|
                                                                                                       
                                                                                                     
)" << '\n';
}
void printCastle() {
    cout << R"(
                                  o
                                 /_\
                                /_ _\
                               |_|_|_|
                               |  _  |
                      o        | | | |        o
                     /_\       | | | |       /_\
                    /_ _\      | | | |      /_ _\
                   |_|_|_|     | | | |     |_|_|_|
                   |  _  |     | | | |     |  _  |
                   | | | |_____| | | |_____| | | |
                   | | | |_____+_|_|_+_____| | | |
                   | |_| |     |   _   |   | |_| |
                   | | | |     |  | |  |   | | | |
                  /  | |  \    |  | |  |  /  | |  \
                 |___|_|___|___|__| |__|___|___|_|___|
)" << '\n';
}

void printFireInTheKidom() {
    cout << R"(
 (     (    (                                            )  (    (         )     *     
 )\ )  )\ ) )\ )                      )    )          ( /(  )\ ) )\ )   ( /(   (  `    
(()/( (()/((()/( (     (           ( /( ( /(    (     )\())(()/((()/(   )\())  )\))(   
 /(_)) /(_))/(_)))\    )\   (      )\()))\())  ))\  |((_)\  /(_))/(_)) ((_)\  ((_)()\  
(_))_|(_)) (_)) ((_)  ((_)  )\ )  (_))/((_)\  /((_) |_ ((_)(_)) (_))_    ((_) (_()((_) 
| |_  |_ _|| _ \| __|  (_) _(_/(  | |_ | |(_)(_))   | |/ / |_ _| |   \  / _ \ |  \/  | 
| __|  | | |   /| _|   | || ' \)) |  _|| ' \ / -_)    ' <   | |  | |) || (_) || |\/| | 
|_|   |___||_|_\|___|  |_||_||_|   \__||_||_|\___|   _|\_\ |___| |___/  \___/ |_|  |_| 
)" << '\n';
}




Clan loadclan(const string& arq_name) {
    Clan clan;
    ifstream file_read(arq_name);
    size_t parameter;
    file_read >> parameter;
    file_read.ignore();
    
    if (file_read.is_open()) {
        string name, oweapon, dweapon;
        getline(file_read, name);
        clan.name = name; // Substitui clan.name
        
        while (getline(file_read, name, ';')) {
            getline(file_read, oweapon, ';');
            getline(file_read, dweapon);
            
            // Exemplo de como fica a adição de um guerreiro:
            if (parameter % 5 == 0) {
                clan.warriors.push_back(new Warrior(name, ((rand() % 200) + 1), ((rand() % 100) + 1), ((rand() % 20) + 1), dweapon, ((rand() % 20) + 1), ((rand() % 60) + 1), oweapon, ((rand() % 20) + 1), ((rand() % 40) + 1), ((rand() % 50) + 1), ((rand() % 100) + 1)));
                continue;
            }
            // ... (mantenha os outros if/else com push_back em clan.warriors) ...
        }
    } else {
        cout << "File was not opened " << endl;
    }
    file_read.close();
    return clan;
}

int random_status(int max){
    return ((rand() % max) + 1);
}


int main(){
    srand(time(0));
    printWelcome();
    Clan clan1 = loadclan("clan1.txt");
    Clan clan2 = loadclan("clan2.txt");
    Clan clan3 = loadclan("clan3.txt");
    Clan clan4 = loadclan("clan4.txt");
    
    vector<Clan> kidom; // Crio um sistema de ponteiros para permitir que kidom possa receber classes filhas de Character
    kidom.push_back(clan1);
    kidom.push_back(clan2);
    kidom.push_back(clan3);
    kidom.push_back(clan4);
    vector<string> historia_de_inicio = {"Havia bem distante um reino, onde existiam em conjunto ", "Existia distante a oeste um reino, onde haviam em conjunto ", "Ouviu-se distante nas terras do norte um reino, onde existiam em conjunto ", "Houve em terras longinquas um reino, onde existiam em conjunto "};
    vector<string> historia_de_destruicao_de_cla = {"Esmagando seu ultimo membro vence o cla ", "Queimando tudo o que sobrou do cla ", "Sem misericordia, eleminando por completo o cla ", "De forma fria, eficiente e cruel, o cla "};
    vector<string> historia_de_destruicao_de_fim = {"No fim, nesse amontoado de cinzas e sangue o cla ", "No fim dessa guerra o cla ", "Sobre fogo e cheiro de sangue o cla ", "De forma a superar as espectativas o cla "};
    vector<string> dinamica_de_ataque = {" olha intensamente e ", " se prepara para seu ataque, com olhos que desejam a morte ", " com maos cansadas ", " de forma a superar as espectativas "};
    vector<string> dinamica_de_defesa = {" apos sofrido o ataque  ", " mesmo cansado ", " com olhos que desejam vingaca pelo dano ", " com tudo o que tinha "};
    vector<string> dinamica_de_morte = {" apos sofrido o ataque morre, olhando pra cima e se perguntando de que vale tanto sangue\n", " depois de um golpe letal, olha intensamente pro seu adversario como quem se pergunta como e possivel, cai e morre\n", " com olhos cheio de lagrimas se debruca ao chao ja sem vida\n", " se vai com tudo o que tinha\n"};
    size_t hist = rand() % historia_de_inicio.size();
    cout << historia_de_inicio.at(hist) << clan1.name << ", " << clan2.name  << ", " << clan3.name  << " e o " <<  clan4.name  << endl;
    cout << "Quando a paz foi rompida, e o odio tomou o lugar do que antes foi amizade\n";
    this_thread::sleep_for(chrono::seconds(5));
    
    while(kidom.size() > 1){
        size_t clanattk = rand() % kidom.size();
        size_t clandef;
        do{
            clandef = rand() % kidom.size();
        }while(clandef == clanattk);
        cout << kidom.at(clanattk).name << " declara guerra ao cla" << kidom.at(clandef).name << endl;
        this_thread::sleep_for(chrono::seconds(0));
        while (true)
        {
            size_t persnattkc = rand() % kidom.at(clanattk).warriors.size();
            size_t persndef = rand() % kidom.at(clandef).warriors.size();
            hist = rand() % dinamica_de_ataque.size();
            Clan& clanAtk = kidom[clanattk];
            Clan& clanDef = kidom[clandef];
            Character* attacker = clanAtk.warriors[persnattkc];
            Character* defensor = clanDef.warriors[persndef];
            
            //Atacante:

            cout << "\n_______________________________________________________\n";
            cout << "[ " << attacker->getname() << dinamica_de_ataque.at(hist);
            cout << " ataca ";
            if(attacker->getoweapon().status()){
                cout << "com " << attacker->getoweapon().getname();
                if(attacker->getoweapon().getresistence() < 10){
                    cout << " que esta quase quebrando,";
                }
            }
            cout << " o ";
            cout << defensor->getname() << endl;
            
            float damage_s = attacker->attack(*defensor);
            cout << defensor->getname() << " sofre entao " << damage_s << " de dano\n" << endl;

            this_thread::sleep_for(chrono::seconds(0));

            //Defesa
            if (defensor->state()){
                hist = rand() % dinamica_de_defesa.size();
                if(defensor->getdweapon().status()){
                    cout << "Que defende com " << defensor->getdweapon().getname();
                    if(defensor->getoweapon().getresistence() < 10){
                        cout << " que estava quase quebrando\n";
                    }
                }
                else{
                    cout << "Que defende com suas propias maos ja feridas pela batalha.\n";
                }
                
                if(damage_s == 0){
                    cout << "Assim, conseguindo se esquivar/defender de todo o ataque.\n";
                }
                
                cout << defensor->getname() << dinamica_de_defesa.at(hist) <<" devolve o ataque a " << attacker->getname();
                
                damage_s = defensor->attack(*attacker);

                cout << "\n" << attacker->getname() << " sofreu " << damage_s << " de dano\n" << endl;
                // cout << kidom.at(clanattk).at(persnattkc)->getlife() << endl;
                if(attacker->getlife() == 0){
                    hist = rand() % dinamica_de_morte.size();
                    cout << attacker->getname() << dinamica_de_morte.at(hist);
                    delete attacker;
                    kidom.at(clanattk).warriors.erase(kidom.at(clanattk).warriors.begin() + persnattkc);
                    this_thread::sleep_for(chrono::seconds(0));
                } 
                else{
                    if(attacker->getdweapon().status()){
                        cout << "Que defende com " << attacker->getdweapon().getname();
                        if(attacker->getoweapon().getresistence() < 10){
                            cout << " que estava quase quebrando\n";
                        }
                        else{
                            cout << endl;
                        }
                    }
                    else{
                        cout << "Que defende com suas propias maos ja feridas pela batalha.\n";
                    }
                
                    if(damage_s == 0){
                        cout << "\nAssim, conseguindo se esquivar/defender de todo o ataque.\n";
                    }
                }
            }
            else{
                cout << "O mantando!\n";
                hist = rand() % dinamica_de_morte.size();
                cout << defensor->getname() << dinamica_de_morte.at(hist);
                delete defensor;
                kidom.at(clandef).warriors.erase(kidom.at(clandef).warriors.begin() + persndef);
                this_thread::sleep_for(chrono::seconds(0));
            }
            
            cout << "_______________________________________________________";
            if(kidom.at(clandef).warriors.empty()){
                hist = rand() % historia_de_destruicao_de_cla.size();
                printFireInTheKidom();
                cout << "\n" << historia_de_destruicao_de_cla.at(hist) << kidom.at(clandef).name << endl;
                kidom.erase(kidom.begin() + clandef);
                this_thread::sleep_for(chrono::seconds(0));
                break;
            }
            if(kidom.at(clanattk).warriors.empty()){
                hist = rand() % historia_de_destruicao_de_cla.size();
                cout << "\n" << historia_de_destruicao_de_cla.at(hist) << kidom.at(clanattk).name << endl;
                kidom.erase(kidom.begin() + clanattk);
                this_thread::sleep_for(chrono::seconds(0));
                break;
            }
        }
        
    
    }
    
    hist = rand() % historia_de_destruicao_de_fim.size();
    cout << "\n" << historia_de_destruicao_de_fim.at(hist) << kidom.at(0).name << "tem agora todo o poder em suas posses\n";
    printCastle();
    cout << "E agora reinam sozinhos: \n" ;
    for(size_t i = 0; i < kidom.at(0).warriors.size() ; i++){
            cout << kidom.at(0).warriors.at(i)->getname() << endl;
            delete kidom.at(0).warriors.at(i);
        }
    kidom.clear();
}