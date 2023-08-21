#include "flight_gear.hpp"

FlightGear::FlightGear() 
: m_flight_status("Grounded")
{
}

void FlightGear::take_off() 
{
    m_flight_status = "In Air";
}

void FlightGear::land() 
{
    m_flight_status = "Landed";
}

std::string FlightGear::get_flight_status() const 
{
    return m_flight_status;
}