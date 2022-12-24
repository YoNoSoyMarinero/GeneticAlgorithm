#include "TicketsPool.h"


TicketsPool::TicketsPool(vector<int> tickets_vector)
{
    this->tickets_vector = tickets_vector;
}

//creates vector of tickets, best parent solution will have most tickets
void TicketsPool::createTicketsVector(int parent_size)
{
    int current_ticket = 0;
    for (int i = parent_size; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            this->tickets_vector.push_back(current_ticket);
        }
        ++current_ticket;
    }
    shuffle(this->tickets_vector.begin(), this->tickets_vector.end(), default_random_engine(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count())));
}