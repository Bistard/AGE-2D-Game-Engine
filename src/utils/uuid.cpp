#include "uuid.h"

#include <random>

namespace AGE
{

/** @brief generate random number stuff */
static std::random_device s_randomDevice;
static std::mt19937_64 s_engine( s_randomDevice() );
static std::uniform_int_distribution<uint64_t> s_uniformDistribution;

UUID::UUID(): _UUID { s_uniformDistribution(s_engine) } 
{}

UUID::UUID(uint64_t uuid): _UUID {0}
{}

} // AGE

