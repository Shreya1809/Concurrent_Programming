#include <mutex>
#include "barriers.h"

using namespace CP;

// IBarSharedPtr BarFactory::GetBarObject(BarType type)
// {
//     switch (type)
//     {
//     case BarType::PTHREAD:
//         return std::make_shared<Pthread_Bar>();
//     case BarType::SENSE:
//         return std::make_shared<Sense_Bar>();
//     default:
//         return nullptr;
//     }
// }

IBarrier::~IBarrier() {};