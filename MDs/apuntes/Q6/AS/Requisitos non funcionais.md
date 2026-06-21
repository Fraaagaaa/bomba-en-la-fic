# Requisitos non funcionais
Definen **propiedades e restricións do sistema** (fiabilidade, tempo de resposta, capacidade de almacenamento, etc.)
- Poden incluír restricións de entorno e/ou negocio (tecnoloxías, ciclo de vida...).
- Afectan a todo o sistema e non só a compoñentes concretos.

Son **tanto ou máis críticos que os requisitos funcionais**, xa que de non cumprirse, o software pode resultar inútil, poden chegar a xerar ou restrinxir requisitos funcionais.

Adoitan ser máis complexos de **concretar**, pero se son imprecisos son difíciles de validar, debemos asegurarnos de que os requisitos non funcionais son **verificables**

Deben validarse en conxunto para asegurar que son **consistentes e realistas**.
- Hai requisitos conflictivos entre si?
- Poden implementarse co tempo e os recursos dispoñibles?


| Requisito non funcional                                    | Medida obxectiva                                                                                                                                           |
| ---------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Velocidade, rendemento                                     | Transaccións procesadas por segundo<br>Tempo de resposta a un evento<br>Tempo de recarga da pantalla<br>Tempo de reinicio despois dun fallo                |
| Consumo de recursos                                        | Memoria, capacidade de cómputo, enerxía                                                                                                                    |
| Facilidade de uso                                          | Tempo de adestramento/resolución de tarefa(s), "memorabilidade", Número de páxinas de axuda                                                                |
| Fiabilidade/dispoñibilidade<br>Robustez/tolerancia a erros | Tempo medio de fallo<br>Ratio de ocorrencia de fallos<br>Porcentaxe de eventos que provocan un fallo<br>Probabilidade de corrupción de datos tras un fallo |
| Portabilidade                                              | Número de plataformas obxectivo<br>Porcentaxe de elementos dependentes da plataforma                                                                       |
| Escalabilidade                                             | Peticións procesadas por segundo sen variación significativa da velocidade/rendemento                                                                      |
