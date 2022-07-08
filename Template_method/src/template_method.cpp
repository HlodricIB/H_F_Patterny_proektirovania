#include "template_method.h"

void CaffeineBeverageWithHook::prepareRecipe()
{
    boilWater();
    brew();
    pourInCup();
    if (customerWantsCondiments())
    {
        addCondiments();
    }
    std::cout << std::endl;
}

bool getCondimentsInfo(const std::string& question)
{
    char answer;
    std::cout << question;
    while (std::cin >> answer)
    {
        if (isalpha(answer))
        {
            answer = static_cast<char>(std::tolower(static_cast<int>(answer)));
            if (answer == 'y')
            {
                return true;
            } else {
                return false;
            }
        }
        std::cin.clear();
    }
    return false;
}
