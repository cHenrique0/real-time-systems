# Sistemas de tempo real

#### <ins>Atividades da 2ª Avaliação</ins>

Para cada questão, grave um vídeo apresentando os programas executando e explique o circuito e código fonte de cada um (3 a 5 min).


**<ins>[Questão 1](./q1)</ins>** - *(2 pontos)*

A partir do temporizador (Temporizador_Bruto.ino) disponibilizado no SIGAA, elabore as seguintes funções, para a plataforma Arduino. A seguir, implemente em alguma aplicação. Pode ser em circuito físico ou simulador (por exemplo piscar um LED).

* delay_ms(parametro) - efetua uma pausa no programa de acordo com o parâmetro dado em milisegundos
* delay_s(parametro) - efetua uma pausa no programa de acordo com o parâmetro dado em segundos


**<ins>[Questão 2](./q2)</ins>** - *(5 pontos)*

Implementar um sistema executivo cíclico em Arduino, usando temporizador sem bloqueio (não usar função delay(), usar smart delay) contendo três tarefas de livre escolha, uma tarefa obrigatória, e uma tarefa a ser desempenhada através de uma interrupção, de acordo com o modelo abordado nas aulas. Cada tarefa deve ter um período específico diferente dos demais. As tarefas possíveis estão descritas a seguir.


**<ins>[Questão 3](./q3/)</ins>** - *(3 pontos)*

Implementar um sistema multitarefa em Arduino contendo três tarefas de livre escolha mais uma tarefa obrigatória que deve ser tocar uma música utilizando a função tone() da linguagem Arduino. Deve ser utilizando o MicroKernel Soft Real Time abordado nas aulas. Cada tarefa deve ter um período específico diferente dos demais.

Para cada um dos sistemas solicitados, as tarefas podem envolver:
- Acendimento de LED (pisca)
- Contador Crescente/Decrescente usando LCD ou display de 7 segmentos
- Leitura de dados de sensor (temperatura, luminosidade ou até simulado com potenciômetro)
- Leitura de teclas (botões)
- Aviso sonoro (buzzer) - esta é a tarefa obrigatória
- Outra tarefa periódica qualquer a ser definida pelo aluno (recebimento de caractere pela porta serial, por exemplo)