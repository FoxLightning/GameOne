#include "GameSystem/AppInstance.h"
#include <memory>

int main(int argc, char *argv[]) 
{
    using namespace GameSystem;
    std::shared_ptr<AppInstance> gameInstance = std::make_shared<AppInstance>();
    gameInstance->Start();
    return 0;
}