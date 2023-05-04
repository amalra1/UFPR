CFLAGS = -Wall -g  # gerar "warnings" detalhados e infos de depuração
 
objs = myht.o hash.o
 
# regra default (primeira regra)
all: myht
 
# regras de ligacao
myht: $(objs)
 
# regras de compilação
myht.o:   myht.c hash.h
hash.o: hash.c hash.h
 
# remove arquivos temporários
clean:
	-rm -f $(objs) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f myht
