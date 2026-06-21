# Ley de Amdahl
Con la programación paralela pretendemos que `p` procesadores sean capaces de resolver un problema `p` veces más rápido que en secuencial.

Existen una serie de factores, ya mencionados, que dificultan la consecución de este objetivo.

La ley de Amdahl mide el límite en la ganancia de velocidad obtenible en la resolución de un problema con una fracción intrísecamente secuencial (Fs) y otra perfectamente paralelizable (Fp).

AÑADIR LAS FORMULAS

$T{secuencial} = F{s} + F{p}$
$T{secuencial} = F{s} + \frac{F{p}}{P}$

$T{secuencial} = \frac{T{secuencial}}{T{paralelo}(p)} = \frac{F{s} + F{p}}{F{s} + \frac{F{p}}{p}}$
