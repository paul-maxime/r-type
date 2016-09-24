#include "Components/Transform/ITransform.hpp"
#include "ParentDependentComponent.hpp"

RTYPE_COMPONENT_IMPL(ParentDependentComponent)

void ParentDependentComponent::start()
{
	auto t = gameObject().getComponent<ITransform>();

	_hasParent = false;
	if (t && t->hasParent())
		_hasParent = true;
}

void ParentDependentComponent::update()
{
	auto t = gameObject().getComponent<ITransform>();

	if (t)
	{
		if (t->hasParent() && !_hasParent)
			_hasParent = true;
		if (!t->hasParent() && _hasParent)
			gameObject().destroy();
	}
}
