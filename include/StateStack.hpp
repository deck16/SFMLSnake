#pragma once
#include "IState.hpp"
#include <memory>
#include <stack>

typedef std::unique_ptr<IState> StateRef;

class StateStack
{
public:
    void AddState(StateRef newState, bool isReplacing = false);
    void SwitchState(StateRef newState);
    void RemoveState();
    void ProcessStateChanges();
    StateRef& GetActiveState();
private:
    std::stack<StateRef> stateStack_;
    StateRef newState_;
    bool isAdding_ = false;
    bool isRemoving_ = false;
    bool isReplacing_= false;
};