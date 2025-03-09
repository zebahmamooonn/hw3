#include <vector>
#include <random>
#include <iostream>


#include "gate.h"
#include "wire.h"


Gate::Gate(int num_inputs, Wire* output) 
	: m_output(output), m_inputs(num_inputs), m_delay(0), m_current_state('X')
{
    
}


Gate::~Gate(){}


void Gate::wireInput(unsigned int id, Wire* in)
{
    if(id < m_inputs.size())
    {
        m_inputs[id] = in;
    }
}


And2Gate::And2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}


Event* And2Gate::update(uint64_t current_time)
{
    
  char state = '1';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '0')
		{
			state = '0';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
    if(state != m_current_state)
	{
    m_current_state = state;
    uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
    return e;
}


Or2Gate::Or2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}


Event* Or2Gate::update(uint64_t current_time)
{
    
  char state = '0';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '1')
		{
			state = '1';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
  if(state != m_current_state)
	{
    m_current_state = state;
		uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
  return e;
}


NotGate::NotGate(Wire* input, Wire* output) : Gate(1, output){
  wireInput(0, input); 
}


Event* NotGate::update(uint64_t current_time){
  char input_state = m_inputs[0]->getState();
  char new_state = 'X';


  if (input_state == '0') new_state = '1';
  else if(input_state == '1') new_state = '0';


  if(new_state != m_current_state){
    m_current_state = new_state;
    uint64_t event_time = current_time + m_delay;
    return new Event{event_time, m_output, new_state};
  }
  return nullptr; 
}


Xor2Gate::Xor2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o){
  wireInput(0,a);
  wireInput(1,b); 
}


Event* Xor2Gate::update(uint64_t current_time){
  char in1 = m_inputs[0]->getState();
  char in2 = m_inputs[1]->getState(); 
  char state = 'X';

  if(in1 != 'X' && in2 != 'X'){
    state = (in1 != in2) ? '1' : '0'; 
  }

  if(state != m_current_state){
    m_current_state = state;
    uint64_t event_time = current_time + m_delay;
    return new Event {event_time, m_output, state}; 
  }
  return nullptr; 
}