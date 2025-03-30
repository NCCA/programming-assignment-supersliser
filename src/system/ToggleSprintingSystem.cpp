#include "system/ToggleSprintingSystem.h"

void ToggleSprintingSystem::run(IsSprintingComponent* i_ioComponent, int i_index) {
    i_ioComponent->m_isSprinting[i_index] = !i_ioComponent->m_isSprinting[i_index];
}
