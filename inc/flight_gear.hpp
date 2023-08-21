#ifndef FLIGHTGEAR_HPP
#define FLIGHTGEAR_HPP

#include <string>

class FlightGear {
public:
    FlightGear();
    void take_off();
    void land();
    std::string get_flight_status() const;

private:
    std::string m_flight_status;
};

#endif // FLIGHTGEAR_HPP
