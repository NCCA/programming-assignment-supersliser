#include "system/SetSprintingSystem.h"

void SetSprintingSystem::run(IsSprintingComponent* i_ioComponent, int i_index) {
    i_ioComponent->m_isSprinting[i_index] = i_value;
}
