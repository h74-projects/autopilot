#include "telemetry.hpp"
#include "middle_man.hpp"
#include "client_telnet.hpp"
#include "server_udp.hpp"
#include "variables_environment.hpp"

#include <iostream> // cout

int main(void)
{
    std::string warp = "/sim/time/warp";
    std::string magnetos =  "/controls/switches/magnetos";
    std::string throttle =  "/controls/engines/current-engine/throttle";
    std::string mixture =  "/controls/engines/current-engine/mixture";
    std::string masterbat =  "/controls/switches/master-bat";
    std::string masteralt =  "/controls/switches/master-alt";
    std::string masteravionics =  "/controls/switches/master-avionics";
    std::string brakeparking =  "/sim/model/c172p/brake-parking";
    std::string primer =  "/controls/engines/engine/primer";
    std::string starter =  "/controls/switches/starter";
    std::string autostart =  "/engines/active-engine/auto-start";
    std::string breaks =  "/controls/flight/speedbrake";
    std::string heading =  "/instrumentation/heading-indicator/offset-deg";
    std::string airspeed =  "/instrumentation/airspeed-indicator/indicated-speed-kt";
    std::string roll =  "/instrumentation/attitude-indicator/indicated-roll-deg";
    std::string pitch =  "/instrumentation/attitude-indicator/internal-pitch-deg";
    std::string rudder =  "/controls/flight/rudder";
    std::string aileron =  "/controls/flight/aileron";
    std::string elevator =  "/controls/flight/elevator";
    std::string alt =  "/instrumentation/altimeter/indicated-altitude-ft";
    std::string rpm =  "/engines/engine/rpm";

    std::shared_ptr<fgear::Variables> binded_map = std::make_shared<fgear::Variables>();
    binded_map.get()->load_file("generic_small.xml");

    fgear::Environment environment{binded_map, std::make_unique<fgear::MiddleMan>(std::make_unique<fgear::TelnetClient>(), 5401)};
    std::shared_ptr<fgear::Protocol> protocol{std::make_shared<fgear::Protocol>(binded_map)};
    fgear::Telemetry telemetry{protocol, std::make_unique<fgear::UdpServer>(49002), "127.0.0.1"};
    telemetry.run_telemetry();

    environment.set(magnetos, 3);
    environment.set(throttle, 0.2);
    environment.set(mixture, 0.949);
    environment.set(masterbat, 1);
    environment.set(masteralt, 1);
    environment.set(masteravionics, 1);
    environment.set(brakeparking, 0);
    environment.set(primer, 3);
    environment.set(starter, 1);
    environment.set(autostart, 1);

    std::cout << "engine is warming...\n";
    std::cout << "rpm is: " << environment.get(rpm) << '\n';

    environment.set(rpm, 800);
    
    ::usleep(250*1000);
    while (environment.get(rpm) < 750) {
        std::cout << "\nengine rpm is: " << environment.get(rpm) << '\n';
        ::usleep(250*1000);
    }

    float h0 = environment.get(heading); 
    environment.set(breaks, 0);
    ::sleep(10);
    environment.set(throttle, 1);

    while (environment.get(alt) < 3500) {
        environment.set(rudder, (h0 - environment.get(heading)) / 20);
        environment.set(aileron, -environment.get(roll) / 70);
        environment.set(elevator, environment.get(pitch) / 50);
        std::cout << "\naltitude is: " << environment.get(alt) << '\n';
        ::usleep(250*1000);
    }    
}
