Un barbero que atiende clientes, al terminar de atender a un cliente, el barbero comprueba la sala de espera, y si hay algún cliente esperando, lo atiende, si no hay clientes en la sala de espera, se pone a dormir. Cuando un cliente entra mira si el barbero está libre (lo despierta) u ocupado. Si está ocupado se va a la sala de espera. Si la sala de espera está llena se marcha.

``` C
#define mutex_t M
#define cond_t NOcustomers
int free_barbers;
int customers;

void barbero()
{
	While(true)
	{
	    lock(M);
	    free_barbers++;
	    while(customers == 0)
	    {
	        wait(NOcustomers, M);
	    }
	    customers--;
	    singal(BARBER_BUSY);
	    unlock(M);
	    cut_hair();
	}
}

void cliente()
{
	While(true)
	{
	    lock(M);
	    if (customers < chairs)
	    {
	        customers++;
	        while(free_barbers == 0)
	        {
	            wait(BARBER_BUSY, M);
	        }
	        free_barbers--;
	        unlock(M);
	        cut_hair();
	    }
	    else
	    {
	        unlock(M);
	    }
	}
}
```

