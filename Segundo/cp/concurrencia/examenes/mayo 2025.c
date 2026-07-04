#include <stdlib.h>
#include <pthread.h>

#define STOPS 10

int main()
{
    return 0;
}
struct bus_line {
    int current_stop; // Current stop
    int total_stops; // Total number of stops
    pthread_mutex_t m;
    int get_off[STOPS]; // Number of passengers that want to leave at that stop
    int load[STOPS]; // Number of passengers that want to enter at that stop
    pthread_cond_t stop[STOPS];
    pthread_cond_t loading;
};

void bus(struct bus_line *bus);
void passenger(struct bus_line *bus, int from, int to)
{
    pthread_mutex_lock(&bus->m);
    if(bus->current_stop != from)
    {
        bus->load[from]++;
        pthread_cond_wait(&bus->stop[from], &bus->m);
        bus->load[from]--;
        if(bus->load[from] == 0) pthread_cond_signal(&bus->loading);
    }
    bus->get_off[to]++;
    pthread_cond_wait(&bus->stop[to], &bus->m);
    bus->get_off[to]--;
    if(bus->get_off[to] == 0) pthread_cond_signal(&bus->loading);
    pthread_mutex_unlock(&bus->m);
}
