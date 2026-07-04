let estado = {
    usuarioPrincipal: "Yo",
    amigos: ["Ana", "Luis"],
    gastos: [
        { id: 1, desc: "Pizza", pagador: "Yo", importe: 45.00, participantes: ["Yo", "Ana", "Luis"] },
        { id: 2, desc: "Cervezas", pagador: "Ana", importe: 15.00, participantes: ["Yo", "Ana"] }
    ]
};

function render() {
    // 1. Renderizar Gastos con diseño de tarjetas
    const contenedor = document.getElementById('contenedor-gastos');
    contenedor.innerHTML = estado.gastos.map(g => `
        <div class="expense-item">
            <div class="expense-info">
                <strong>${g.desc}</strong>
                <span>Pagado por ${g.pagador}</span>
            </div>
            <div class="expense-value ${g.pagador === estado.usuarioPrincipal ? 'positive' : 'negative'}">
                ${(g.importe / g.participantes.length).toFixed(2)} €
                <div style="font-size: 0.7rem; color: gray;">tu parte</div>
            </div>
        </div>
    `).join('');

    // 2. Calcular Balances Realistas
    actualizarBalances();
}

function actualizarBalances() {
    let balances = { "Yo": 0 };
    estado.amigos.forEach(a => balances[a] = 0);

    estado.gastos.forEach(g => {
        const cuota = g.importe / g.participantes.length;
        if (balances[g.pagador] !== undefined) balances[g.pagador] += g.importe;
        g.participantes.forEach(p => {
            if (balances[p] !== undefined) balances[p] -= cuota;
        });
    });

    const miStatus = balances["Yo"];
    document.getElementById('total-recibir').innerText = miStatus > 0 ? `+${miStatus.toFixed(2)} €` : "0.00 €";
    document.getElementById('total-pagar').innerText = miStatus < 0 ? `${miStatus.toFixed(2)} €` : "0.00 €";
}

// Navegación de pestañas
document.querySelectorAll('.nav-btn').forEach(btn => {
    btn.onclick = () => {
        document.querySelectorAll('.nav-btn').forEach(b => b.classList.remove('active'));
        document.querySelectorAll('.view-section').forEach(v => v.classList.add('hidden'));
        btn.classList.add('active');
        document.getElementById(btn.dataset.target).classList.remove('hidden');
    };
});

document.addEventListener('DOMContentLoaded', () => {
    const navButtons = document.querySelectorAll('.nav-btn');
    const sections = document.querySelectorAll('.view-section');

    navButtons.forEach(btn => {
        btn.addEventListener('click', () => {
            // 1. Cambiar clase activa en botones
            navButtons.forEach(b => b.classList.remove('active'));
            btn.classList.add('active');

            // 2. Mostrar/Ocultar secciones
            const target = btn.getAttribute('data-target');
            sections.forEach(sec => {
                if (sec.id === target) {
                    sec.classList.remove('hidden');
                } else {
                    sec.classList.add('hidden');
                }
            });
        });
    });
});
render();
