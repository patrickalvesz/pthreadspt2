# Grupo04N12

Nome: Patrick Alves Gonçalves          RA: 10409363

Nome: Nicholas dos Santos Leal         RA: 10409210

Nome: Gustavo Ibara                    RA: 10389067

# Exercício

Entregue a solução realizada em sala para o problema do cálculo de pi. Para a solução implementada apresente os logs de execução contendo:

* Quantidade de threads;

* Valor de pi calculado pelo algoritmo.

a) Implemente uma solução utilizando Mutex e comparece com a anterior. O que mudou? Por quê?

b) No final, entregue no README do repositório uma explicação resumida sobre as diferenças entre os valores atingidos. Quais foram as causas das divergências? Por que elas aconteceram?

# Logica Pensada + Resposta

a) 

  Para implementar o Mutex, fizemos as seguintes mudanças:
  
  Adicionamos um Mutex: Inicializamos um objeto Mutex usando "pthread_mutex_init".
  
  "Protegemos" a atualização da variável sum: Cada thread calcula sua própria soma parcial (my_sum). Em seguida, bloqueamos o Mutex antes de adicionar my_sum à soma global sum, e desbloqueamos o Mutex depois. Isso garante que apenas uma thread possa atualizar sum de cada vez.
  
	Destruímos o Mutex no final: Depois que todas as threads terminaram, destruímos o Mutex com "pthread_mutex_destroy".

  Com isso, a variável sum é "protegida" de acessos simultâneos pelas threads.


b)

  Sem Mutex, várias threads podiam mexer na variável sum ao mesmo tempo. Isso podia causar confusão e fazer com que o cálculo de pi não saísse certo.
  
	Com Mutex, ele "protege" a variável sum. Só permite que uma thread mexa na sum de cada vez. Isso evita a confusão e faz com que o cálculo de pi seja mais exato.
 
	Dessa forma, conseguimos ter certeza de que o cálculo do valor de pi vai ser preciso, mesmo quando várias threads estão trabalhando juntas.
 
	Então, a principal causa das divergências nos valores atingidos é a presença ou ausência de condições de corrida.


# Print da Execução

![image](https://github.com/patrickalvesz/pthreadspt2/assets/127363163/a768a4bb-6d3e-4e1a-941f-14bf8b3e429c)


 
