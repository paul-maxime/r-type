#include <iostream>
#include <stdexcept>

#include "RType/ECS/GameEngine.hpp"
#include "ButtonComponent.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"
#include "Components/Transform/ITransform.hpp"

RTYPE_COMPONENT_IMPL(ButtonComponent)

ButtonComponent::ButtonComponent()
{
}
