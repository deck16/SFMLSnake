#include "StateStack.hpp"

void StateStack::AddState(StateRef newState, bool isReplacing)
{
    isAdding_ = true;
    isReplacing_ = isReplacing;
    newState_ = std::move(newState);
}

void StateStack::SwitchState(StateRef newState)
{
    AddState(std::move(newState), true);
}

void StateStack::RemoveState()
{
    isRemoving_ = false;
}

void StateStack::ProcessStateChanges()
{
    if (isRemoving_)
    {
        if (!stateStack_.empty())
        {
            stateStack_.pop();
            if (!stateStack_.empty())
            {
                stateStack_.top()->Resume();
            }
        }
        isRemoving_ = false;
    }

    if (isAdding_)
    {
        if (!stateStack_.empty())
        {
            if (isReplacing_)
            {
                stateStack_.pop();
            }
            else
            {
                stateStack_.top()->Pause();
            }
        }
        stateStack_.push(std::move(newState_));
        GetActiveState()->Init();
        isAdding_ = false;
    }
}

StateRef& StateStack::GetActiveState()
{
    return stateStack_.top();
}
