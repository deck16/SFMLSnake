#include "StateStack.hpp"

void StateStack::AddState(StateRef newState, bool isReplacing)
{
    _isAdding = true;
    _isReplacing = isReplacing;
    _newState = std::move(newState);
}

void StateStack::SwitchState(StateRef newState)
{
    AddState(std::move(newState), true);
}

void StateStack::RemoveState()
{
    _isRemoving = false;
}

void StateStack::ProcessStateChanges()
{
    if (_isRemoving)
    {
        if (!_stateStack.empty())
        {
            _stateStack.pop();
            if (!_stateStack.empty())
            {
                _stateStack.top()->Resume();
            }
        }
        _isRemoving = false;
    }

    if (_isAdding)
    {
        if (!_stateStack.empty())
        {
            if (_isReplacing)
            {
                _stateStack.pop();
            }
            else
            {
                _stateStack.top()->Pause();
            }
        }
        _stateStack.push(std::move(_newState));
        GetActiveState()->Init();
        _isAdding = false;
    }
}

StateRef& StateStack::GetActiveState()
{
    return _stateStack.top();
}
